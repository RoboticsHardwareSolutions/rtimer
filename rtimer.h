#ifndef __RTIMER_H
#define __RTIMER_H

#include "stdbool.h"
#include "stdint.h"

typedef enum {
    once,
    periodically,
} rtimer_type;

typedef struct {
    rtimer_type type;
    uint32_t elapsed_time;
    bool activated;
    void *callback;
    struct rtimer_t *next;
} rtimer;



#endif
