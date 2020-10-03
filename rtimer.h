#ifndef __RTIMER_H
#define __RTIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdbool.h"
#include "stdint.h"
#include "stm32g4xx_hal.h"

typedef enum {
    once,
    periodically,
} rtimer_type;

typedef struct {
    rtimer_type type;
    uint32_t elapsed_time;
    uint32_t period;
    bool activated;
    void (*callback)(void);
    struct rtimer_t *next;
} rtimer;


bool rtimer_create(rtimer *instance, rtimer_type type);

bool rtimer_setup(rtimer *instance, uint32_t period_ms, void *cb);

void rtimer_delete(rtimer *instance);

#ifdef __cplusplus
}
#endif

#endif
