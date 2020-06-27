#include "rtimer.h"
#include "string.h"

static rtimer *first_timer = NULL;
bool hardware_started = false;

bool rtimer_create(rtimer *instance , rtimer_type type){
    if(instance == NULL )
        return false;

    rtimer** timer = &first_timer;
    while(*timer != NULL) {
        timer = (rtimer**) &((*timer)->next);
    }
    *timer = instance;

    if(!hardware_started){

    }
}

bool rtimer_setup(rtimer *instance, uint32_t interval_us ){

}

void rtimer_delete(rtimer *instance){

}


bool hardware_timer_init()


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    BSP_LED_Toggle(LED4);
}