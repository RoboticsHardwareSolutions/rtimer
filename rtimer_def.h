#ifndef __RTIMER_DEF_H
#define __RTIMER_DEF_H

#if defined(STM32G474xx)

#elif defined(STM32F103xB) || defined(STM32F103xE)

#    include "stm32f1xx_hal.h"
#    define HTIM htim4
#    define TIM TIM4
#    define TIM_IRQn TIM4_IRQn
#    define __HAL_RCC_TIM_CLK_DISABLE() __HAL_RCC_TIM4_CLK_DISABLE()
#    define __HAL_RCC_TIM_CLK_ENABLE() __HAL_RCC_TIM4_CLK_ENABLE()
#    define TIM_IRQHandler TIM4_IRQHandler

#elif defined(STM32F072xB) || defined(STM32F091xC)

#    include "stm32f0xx_hal.h"
#    define HTIM htim2
#    define TIM TIM2
#    define TIM_IRQn TIM2_IRQn
#    define __HAL_RCC_TIM_CLK_DISABLE() __HAL_RCC_TIM2_CLK_DISABLE()
#    define __HAL_RCC_TIM_CLK_ENABLE() __HAL_RCC_TIM2_CLK_ENABLE()
#    define TIM_IRQHandler TIM2_IRQHandler

#elif defined(STM32F407xx) || defined(STM32F429xx)
#    include "stm32f4xx_hal.h"
#    define HTIM htim2
#    define TIM TIM2
#    define TIM_IRQn TIM2_IRQn
#    define __HAL_RCC_TIM_CLK_DISABLE() __HAL_RCC_TIM2_CLK_DISABLE()
#    define __HAL_RCC_TIM_CLK_ENABLE() __HAL_RCC_TIM2_CLK_ENABLE()
#    define TIM_IRQHandler TIM2_IRQHandler

#endif

#if defined(STM32G474xx) || defined(STM32F103xB) || defined(STM32F072xB) || defined(STM32F091xC) || \
    defined(STM32F407xx) || defined(STM32F429xx) || defined(STM32F103xE)

struct timer_elements
{
    uint32_t elapsed_time;
    uint32_t period;
    bool     activated;
    void (*callback)(void);
    struct timer_elements* next;
};

#endif  // STM32G474xx

#if defined(RTIMER_FOR_APPLE)

#    include <dispatch/dispatch.h>
#    include <sys/time.h>

struct timer_elements
{
    dispatch_queue_t  queue;
    dispatch_source_t timer;
    struct timeval    last_sig;
    uint32_t          period;
    void (*callback)(void);
    struct timer_elements* next;
};

#endif  // RTIMER_FOR_APPLE

#if defined(RTIMER_FOR_UNIX)

#    include <sys/time.h>
#    include <time.h>
#    include <signal.h>

struct timer_elements
{
    bool            run;
    timer_t         timer;
    struct sigevent sigev;
    struct timeval  last_sig;
    uint32_t        period;
    void (*callback)(void);
    struct timer_elements* next;
};

#endif

#endif  // __RTIMER_DEF_H
