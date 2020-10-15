#ifndef __RTIMER_H
#define __RTIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdbool.h"
#include "stdint.h"
#include "rtimer_def.h"

typedef struct timer_elements rtimer;

bool rtimer_create(rtimer *instance);

bool rtimer_setup(rtimer *instance, uint32_t interval_us, void *cb);

uint32_t rtimer_get_elapsed_time(rtimer *instance);

void rtimer_delete(rtimer *instance);

#ifdef __cplusplus
}
#endif

#endif
