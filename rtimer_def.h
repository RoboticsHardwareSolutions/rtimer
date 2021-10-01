#ifndef __RTIMER_DEF_H
#define __RTIMER_DEF_H


#if defined (STM32G474xx)

struct timer_elements{
    uint32_t elapsed_time;
    uint32_t period;
    bool activated;
    void (*callback)(void);
    struct timer_elements *next;
} ;

#endif // STM32G474xx

#if defined (RTIMER_FOR_APPLE)

#include <dispatch/dispatch.h>
#include <sys/time.h>

struct timer_elements {
    dispatch_queue_t queue;
    dispatch_source_t timer;
    struct timeval last_sig;
    uint32_t period;
    void (*callback)(void);
    struct timer_elements *next;
};

#endif // RTIMER_FOR_APPLE



#if defined (RTIMER_FOR_UNIX)

#include <sys/time.h>
#include <time.h>
#include <signal.h>

struct timer_elements {
    timer_t timer;
    struct sigevent sigev;
    struct timeval last_sig;
    uint32_t period;
    void (*callback)(void);
    struct timer_elements *next;
};

#endif



#endif // __RTIMER_DEF_H
