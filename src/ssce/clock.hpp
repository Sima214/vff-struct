#ifndef SSCE_CLOCK_HPP
#define SSCE_CLOCK_HPP

#include <cfloat>
#include <stdint.h>

#if defined(__linux__)
  #define INTERNAL_STORAGE 2
#elif defined(__APPLE__)
  #define INTERNAL_STORAGE 0
#elif defined(_WIN32)
  #define INTERNAL_STORAGE 1
#else
  #error "Unknown platform."
#endif

namespace ssce{
class Clock {
  public:
    //Last measurement.
    float delta;
    //Mean delta since last reset.
    float avg;
    //Smallest delta since last reset.
    float min;
    //Biggest delta since last reset.
    float max;
    /*
     * Constructor.
     */
    Clock(): min(FLT_MAX), max(FLT_MIN), count_query(0), delta_sum(0) {};
    /*
     * Start measuring.
     */
    void start();
    /*
     * Stops measurement and calculates
     * new delta and updates statistics.
     */
    void stop();
    /*
     * Resets clock counters and statistics.
     */
    void reset() {
    this->count_query = 0;
    this->delta_sum = 0;
    this->max = FLT_MIN;
    this->min = FLT_MAX;
  }
  private:
    int64_t intcnt[INTERNAL_STORAGE];
    int64_t count_query;
    double delta_sum;
};
}
#endif /*SSCE_CLOCK_HPP*/