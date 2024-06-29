// TIME_INTERVAL_H
#ifndef TIME_INTERVAL_H
#define TIME_INTERVAL_H

#include <chrono>

/*  
    Definicion de la clase Time_interval
    Los procesos especificos estan definidos en src/time_interval.cpp  
*/

using namespace std::chrono;

// Clase para los intervalos de tiempo
class Time_Interval {
    public:
        // Constructor
        Time_Interval();

        // Metodos
        long long tiempo_transcurrido() const;

    private:
        high_resolution_clock::time_point time_start;
};

#endif