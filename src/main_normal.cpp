// main_normal.cpp
#include <iostream>
#include <chrono>
#include <iomanip>
#include <experimental/random>
#include <string>
#include "../include/funciones.h"
#include "../include/Time_Interval.h"

using namespace std;

void secuencia_lineal(int largo_arreglo, int epsilon, vector<double>& resultados_lineal,int Arr_lineal[]);
void secuencia_normal(int largo_arreglo, double mean, double stddev, vector<double>& resultados_normal, int Arr_normal[]);

// Main
int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Entrada debe ser ./binaryS largo_arreglo" << endl;
        exit(1);
    }

    // Asegurar que el largo sea mayor a 0

    srand(time(nullptr));  

    int largo_arreglo = atoi(argv[1]);

    const int iteraciones = get_env_int("ITERACIONES");
    const int epsilon = get_env_int("EPSILON");    
    const double mean = get_env_double("MEAN");  
    const double stddev = get_env_double("STDDEV");

    // Vector de los resultados(tiempos) de la busqueda
    vector<double> resultados_lineal;   
    vector<double> resultados_normal;   

    // Path archivo .CSV
    string path = crear_file_name();
    crear_archivo_txt(path);

    // Arreglos a usar, estaticos. Guardan mas espacio por elemento y tenermos siempre el largo necesario
    // 4 Bytes = 32 bits por elemento en el arreglo. (Serian 8 bytes si se usa Arreglos dinamicos (Con punteros))
    int Arr_lineal[largo_arreglo];
    int Arr_normal[largo_arreglo];
    // cout << sizeof(Arr_lineal) << endl; 

    // Loop de la ejecucion principal
    for (int i = 0; i < iteraciones; i++) {
        secuencia_lineal(largo_arreglo, epsilon, resultados_lineal, Arr_lineal);
        secuencia_normal(largo_arreglo, mean, stddev, resultados_normal, Arr_normal);
    }

    // Pasar resultados al excel
    escribir_resultados_csv(resultados_lineal,resultados_normal, path, largo_arreglo);
    return 0;
}


// Tiempo de la busqueda binaria con el arreglo lineal
void secuencia_lineal(int largo_arreglo, int epsilon, vector<double>& resultados_lineal,int Arr_lineal[]){
    // Rellenar con randoms. No crea un arreglo nuevo, solo reemplaza con nuevos randoms
    crear_ArrLineal(largo_arreglo, Arr_lineal, epsilon);
    

    // Num buscado random entre los extremos del arreglo
    int numero_buscado = experimental::randint(int(Arr_lineal[0]), int(Arr_lineal[largo_arreglo-1]));
    // Busqueda binaria, Time_Interval es un objeto definido en time_interval.cpp
    Time_Interval* Tiempo = new Time_Interval();
    binary_Search(Arr_lineal, largo_arreglo, numero_buscado);
    double duration = Tiempo->tiempo_transcurrido();
    resultados_lineal.push_back(duration);
    delete Tiempo;  // Borra el objeto para despejar espacio
}


// Tiempo de la busqueda binaria con el arreglo normal
void secuencia_normal(int largo_arreglo, double mean, double stddev, vector<double>& resultados_normal, int Arr_normal[]){
    // Rellenar con randoms
    crear_ArrNormal(largo_arreglo, Arr_normal, mean, stddev);

    // Num buscado random entre los extremos del arreglo
    int numero_buscado = experimental::randint(int(Arr_normal[0]), int(Arr_normal[largo_arreglo-1]));

    // Busqueda binaria
    Time_Interval* Tiempo = new Time_Interval();
    binary_Search(Arr_normal, largo_arreglo, numero_buscado);
    double duration = Tiempo->tiempo_transcurrido();
    resultados_normal.push_back(duration);
    delete Tiempo;
}