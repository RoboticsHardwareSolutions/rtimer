#ifndef __RTIMER_DEF_H
#define __RTIMER_DEF_H



#if defined (RTIMER_FOR_APPLE)

#include <dispatch/dispatch.h>
#include <sys/time.h>

struct timer_elements {
    dispatch_queue_t queue;
    dispatch_source_t timer;
    struct timeval last_sig;
    int type;
    uint32_t period;
    void (*callback)(void);
    struct timer_elements *next;
};

#endif


#endif