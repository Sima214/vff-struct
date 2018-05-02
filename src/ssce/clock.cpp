#include "clock.hpp"

#include <cfloat>
#include <stdint.h>

/*
 * Clock implementation for linux systems.
 */
#ifdef __linux__

#include <time.h>
#include <unistd.h>

static const int MILLI2MICRO = 1000;
static const int MICRO2NANO = 1000;
static const int MSEC2NANO = 1000000;
static const int SEC2NANO = 1000000000;

namespace ssce {
  void Clock::start() {
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC_RAW, &tp);
    this->intcnt[0] = tp.tv_nsec;
    this->intcnt[1] = tp.tv_sec;
  }
  void Clock::stop() {
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC_RAW, &tp);
    int64_t nano_delta = (tp.tv_nsec - this->intcnt[0]) + SEC2NANO*(tp.tv_sec - this->intcnt[1]);
    double delta = ((double)nano_delta)/MSEC2NANO;
    this->count_query++;
    this->delta_sum += delta;
    this->avg = this->delta_sum / this->count_query;
    this->delta = delta;
    if(delta > this->max){
        this->max = delta;
    }
    if(delta < this->min){
        this->min = delta;
    }
  }
}

#endif
/*
 * Clock implementation for windows systems.
 */
#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

namespace ssce {

  static int64_t FREQUENCY = 0;
  void Clock::start() {
    if(FREQUENCY == 0){
      LARGE_INTEGER x;
      QueryPerformanceFrequency(&x);
      FREQUENCY = x.QuadPart/1000;
    }
    LARGE_INTEGER x;
    QueryPerformanceCounter(&x);
    this->last_query = x.QuadPart;
  }
  void Clock::stop() {
    LARGE_INTEGER x;
    QueryPerformanceCounter(&x);
    int64_t nano_delta = x.QuadPart;
    nano_delta = nano_delta - this->last_query;
    double delta = ((double)nano_delta) / FREQUENCY;
    this->count_query++;
    this->delta_sum += delta;
    this->avg = this->delta_sum / this->count_query;
    this->delta = delta;
    if(delta > this->max){
      this->max = delta;
    }
    if(delta < this->min){
      this->min = delta;
    }
  }
}
#endif