#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "rtimer.h"

#if defined(RTIMER_FOR_UNIX)

#include "pthread.h"
#include "stdlib.h"
#include "unistd.h"


#endif

#if defined(RTIMER_FOR_WINDOWS)
#include "stdlib.h"
#include <string>
#include <iostream>
#endif

#define TIMER_INTERVAL 1000




rtimer timer;

void cb(void) {

    struct timespec tms;
    if (clock_gettime(CLOCK_REALTIME, &tms)) {
        perror("get time\r\n");
    }

    long long micros = tms.tv_sec * 1000000;

    micros += tms.tv_nsec / 1000;

    if (tms.tv_nsec % 1000 >= 500) {
        ++micros;
    }

    printf("%lld\r\n", micros);

    if (!rtimer_setup(&timer, TIMER_INTERVAL, cb)) {
        printf("\r\n");
    }

}


/**********************************************************************************************************************/

TEST_CASE("time measument") {

    SECTION("simple test") {
        // Diff between value must be 1000
        REQUIRE(rtimer_create(&timer) == true);
        REQUIRE(rtimer_setup(&timer, TIMER_INTERVAL, cb) == true);
        REQUIRE(usleep(TIMER_INTERVAL * 10)== 0);
        REQUIRE(rtimer_delete(&timer) == true);

    }
}

/**********************************************************************************************************************/









