#include "../rtimer.h"
#include "runit.h"

#if defined(RTIMER_FOR_UNIX)
#include "pthread.h"
#include "stdlib.h"
#include "unistd.h"
#endif

#if defined(RTIMER_FOR_WINDOWS)
#include "stdlib.h"
#include <iostream>
#include <string>
#endif

#if defined(RTIMER_FOR_APPLE)
#include "stdio.h"
#include "stdlib.h"

#endif

#if defined(RTIMER_FOR_UNIX) || defined(RTIMER_FOR_WINDOWS) ||                 \
    defined(RTIMER_FOR_APPLE)

#define TIMER_INTERVAL 1000

rtimer timer;

void cb(void) {
  struct timespec tms;
  if (clock_gettime(CLOCK_REALTIME, &tms)) {
    printf("get time\n");
  }

  long long micros = tms.tv_sec * 1000000;

  micros += tms.tv_nsec / 1000;

  if (tms.tv_nsec % 1000 >= 500) {
    ++micros;
  }

  printf("%lld\n", micros);

  if (!rtimer_setup(&timer, TIMER_INTERVAL, cb)) {
    printf("\n");
  }
}

/**********************************************************************************************************************/
void test_rtimer_void(void) {
  printf("Diff between value must be about 1000\n");
  runit_true(rtimer_create(&timer));
  runit_true(rtimer_setup(&timer, TIMER_INTERVAL, cb));
  usleep(TIMER_INTERVAL * 10);
  runit_true(rtimer_delete(&timer));
}
#endif

int main(void) {

#if defined(RTIMER_FOR_UNIX) || defined(RTIMER_FOR_WINDOWS) ||                 \
    defined(RTIMER_FOR_APPLE)
  test_rtimer_void();
#endif
  runit_report();
  return runit_at_least_one_fail;
}

/**********************************************************************************************************************/
