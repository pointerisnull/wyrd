#include "utils.h"

#if defined(_WIN32)
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
#endif
    #include <time.h>

uint64_t current_time_ms() {
#if defined(_WIN32)
    static uint64_t frequency = 0;
    if (frequency == 0) {
        LARGE_INTEGER li;
        QueryPerformanceFrequency(&li);
        frequency = li.QuadPart;
    }
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);

    // To avoid overflow 
    uint64_t seconds = li.QuadPart / frequency;
    uint64_t fraction = li.QuadPart % frequency;
    return (seconds * 1000) + (fraction * 1000 / frequency);
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000 + (uint64_t)ts.tv_nsec / 1000000;
#endif
}