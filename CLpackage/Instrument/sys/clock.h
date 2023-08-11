#ifndef INSTRUMENT_CLOCK_H
#define INSTRUMENT_CLOCK_H

#include <chrono>

#ifdef linux
#include <unistd.h>

static inline void current(unsigned long long millisecond) {
    usleep((millisecond << 10u) - (millisecond << 4u) - (millisecond << 3u));
}
#endif

#ifdef WIN32
#include <windows.h>

static inline void current(unsigned long long millisecond) {
    Sleep(millisecond);
}
#endif

static inline unsigned int now() {
    auto chrono_stamp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()).time_since_epoch().count();
    return (unsigned int)chrono_stamp & 0xFFFFFFFFul;
}

#endif //INSTRUMENT_CLOCK_H
