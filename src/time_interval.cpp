#include "../include/Time_Interval.h"

using namespace std::chrono;

// Constructor
Time_Interval::Time_Interval() : time_start(high_resolution_clock::now()) {}

// Metodos Clase
long long Time_Interval::tiempo_transcurrido() const {
    auto now = high_resolution_clock::now();
    return duration_cast<nanoseconds>(now - time_start).count();
}
