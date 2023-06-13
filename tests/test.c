#include "../rtimer.h"
#include "runit/src/runit.h"

#if defined(RTIMER_FOR_UNIX)
#    include "pthread.h"
#    include "stdlib.h"
#    include "unistd.h"
#endif

#if defined(RTIMER_FOR_WINDOWS)
#    include "stdlib.h"
#    include <string>
#    include <iostream>
#endif

#if defined(RTIMER_FOR_APPLE)
#    include "stdlib.h"
#    include "stdio.h"

#endif

#define TIMER_INTERVAL 1000

rtimer timer;

void cb(void)
{
    struct timespec tms;
    if (clock_gettime(CLOCK_REALTIME, &tms))
    {
        printf("get time\n");
    }

    long long micros = tms.tv_sec * 1000000;

    micros += tms.tv_nsec / 1000;

    if (tms.tv_nsec % 1000 >= 500)
    {
        ++micros;
    }

    printf("%lld\r\n", micros);

    if (!rtimer_setup(&timer, TIMER_INTERVAL, cb))
    {
        printf("\r\n");
    }
}

/**********************************************************************************************************************/
void test_rtimer_void(void)
{
    printf("Diff between value must be about 1000\n");
    runit_true(rtimer_create(&timer));
    runit_true(rtimer_setup(&timer, TIMER_INTERVAL, cb));
    usleep(TIMER_INTERVAL * 10);
    runit_true(rtimer_delete(&timer));
}

int main(void)
{
    test_rtimer_void();
    runit_report();
    return runit_at_least_one_fail;  // Non-zero in case of error to provide a proper exit-code
}

/**********************************************************************************************************************/
