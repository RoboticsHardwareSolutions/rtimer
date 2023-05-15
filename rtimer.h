#ifndef __RTIMER_H
#define __RTIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdbool.h"
#include "stdint.h"
#include "rtimer_def.h"

typedef struct timer_elements rtimer;

/**
 * created timer with one of choosen type
 * periodically or once shot
 * return false if hardware timer not started
 */
bool rtimer_create(rtimer* instance);

/**
 * setup period of work timer and setup callback function which call
 */
bool rtimer_setup(rtimer* instance, uint32_t interval_us, void (*cb)(void));

/**
 * return time after last call callback or after create if function rtimer_setup()
 * didn't call early
 */
uint32_t rtimer_get_elapsed_time(rtimer* instance);

/**
 * deactivated timer
 */
bool rtimer_delete(rtimer* instance);

bool hardware_timer_deinit(void);

#ifdef __cplusplus
}
#endif

#endif
