// TIME_INTERVAL_H
#ifndef TIME_INTERVAL_H
#define TIME_INTERVAL_H

#include <chrono>

using namespace std::chrono;

class Time_Interval {
public:
    // Contructor
    Time_Interval();

    // Metodos
    long long tiempo_transcurrido() const;

private:
    high_resolution_clock::time_point time_start;
};

#endif