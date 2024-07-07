#include "../include/Time_Interval.h"
#include <iostream>

using namespace std;
using namespace std::chrono;

/*
    Especificacion del objeto Time_Interval
*/

// Constructor
Time_Interval::Time_Interval() : time_start(high_resolution_clock::now()) {}

// Metodos
// Devuelve el tiempo transcurrido en ns, desde la creacion del objeto en el programa.
long long Time_Interval::tiempo_transcurrido() const {
    auto now = high_resolution_clock::now();
    return duration_cast<nanoseconds>(now - time_start).count();
}
