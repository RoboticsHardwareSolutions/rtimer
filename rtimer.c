#include "rtimer.h"
#include "string.h"
#include "stdio.h"
#include "led.h" // TODO delete


TIM_HandleTypeDef htim7;

static rtimer *first_timer = NULL;
bool hardware_started = false;

static bool hardware_timer_init(void);

void hardware_timer_cb(TIM_HandleTypeDef *htim);

void timer_msp_init_cb(TIM_HandleTypeDef *htim);

void timer_msp_deinit_cb(TIM_HandleTypeDef *htim);

/**
 * created timer with one of choosen type
 * periodically or once shot
 * return false if hardware timer not started
 */
bool rtimer_create(rtimer *instance, rtimer_type type) {

    if (instance == NULL)
        return false;

    rtimer **timer = &first_timer;
    while (*timer != NULL) {
        timer = (rtimer **) &((*timer)->next);
    }
    *timer = instance;
    instance->next = NULL;

    instance->type = type;
    instance->activated = false;


    if (!hardware_started) {

        if (!hardware_timer_init())
            return false;
        else
            hardware_started = true;
    }
    return true;
}

/**
 * setup period of work timer and setuped callback function which call
 */

bool rtimer_setup(rtimer *instance, uint32_t period_ms, void *cb) {
    if (instance == NULL || period_ms == 0 || cb == NULL)
        return false;

    instance->elapsed_time = 0;
    instance->callback = cb;
    instance->period = period_ms;
    instance->activated = true;

    return true;

}

/**
 * deactivated timer
 */
void rtimer_delete(rtimer *instance) {
    if (instance == NULL)
        return;

    instance->activated = false;
}


bool hardware_timer_init(void) {

    TIM_MasterConfigTypeDef config = {0};

    uint32_t timclock = HAL_RCC_GetPCLK1Freq();;
    uint32_t prescaler = timclock / 1000000 - 1;

    htim7.Instance = TIM7;
    htim7.Init.Prescaler = prescaler;
    htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim7.Init.Period = 1000 - 1;
    htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    config.MasterOutputTrigger = TIM_TRGO_RESET;
    config.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    config.MasterOutputTrigger2 = TIM_TRGO_RESET;


    if (HAL_TIM_RegisterCallback(&htim7, HAL_TIM_BASE_MSPINIT_CB_ID, timer_msp_init_cb) != HAL_OK)
        return false;

    if (HAL_TIM_RegisterCallback(&htim7, HAL_TIM_BASE_MSPDEINIT_CB_ID, timer_msp_deinit_cb) != HAL_OK)
        return false;

    if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
        return false;

    if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &config) != HAL_OK)
        return false;

    if (HAL_TIM_RegisterCallback(&htim7, HAL_TIM_PERIOD_ELAPSED_CB_ID, hardware_timer_cb) != HAL_OK)
        return false;

    if (HAL_TIM_Base_Start_IT(&htim7) != HAL_OK)
        return false;


    return true;
}

void hardware_timer_cb(TIM_HandleTypeDef *htim) {

    rtimer **timer = &first_timer;
    rtimer *current_timer = NULL;

    while (*timer != NULL) {

        current_timer = *timer;
        timer = (rtimer **) &((*timer)->next);

        if (current_timer->activated)
            current_timer->elapsed_time++;
        else
            continue;

        if (current_timer->period == current_timer->elapsed_time) {

                current_timer->callback();

            if (current_timer->type != periodically)
                current_timer->activated = false;

            current_timer->elapsed_time = 0;
        }
    }
}


void timer_msp_init_cb(TIM_HandleTypeDef *htim) {

    if (htim->Instance == TIM7) {
        __HAL_RCC_TIM7_CLK_ENABLE();
        HAL_NVIC_SetPriority(TIM7_DAC_IRQn, 5, 0);
        HAL_NVIC_EnableIRQ(TIM7_DAC_IRQn);
    }
    if (htim->Instance == TIM6) {
        __HAL_RCC_TIM6_CLK_ENABLE();
        HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 5, 0);
        HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
    }

}

void timer_msp_deinit_cb(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM7) {
        __HAL_RCC_TIM7_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(TIM7_DAC_IRQn);
    }
    if (htim->Instance == TIM6) {
        __HAL_RCC_TIM6_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(TIM6_DAC_IRQn);
    }
}

void TIM7_DAC_IRQHandler(void) {
    HAL_TIM_IRQHandler(&htim7);
}