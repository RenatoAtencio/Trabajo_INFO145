#include <iostream>
#include <chrono>
#include <iomanip>
#include <cmath>
#include <experimental/random>
#include <vector>
#include <string>

#include "../include/funciones.h"
#include "../include/Time_Interval.h"

using namespace std;

void secuencia_lineal(int largo_arreglo, int m, int b, int epsilon ,vector<double>& resultados_lineal,vector<double>& tiempo_arr_lineal);
void secuencia_normal(int largo_arreglo, int m, int b, int epsilon, double mean, double stddev,  vector<double>& resultados_normal,vector<double>& tiempo_arr_normal);

// Main
int main(int argc, char **argv){
    if (argc != 2){
        cout << "Entrada debe ser ./binaryS largo_arreglos" << endl;
        exit(1);
    }

    int largo_arreglo = atoi(argv[1]);
    if (largo_arreglo <= 0){
        cerr << "Largo de arreglo invalido (<= 0)" << endl;
        exit(EXIT_FAILURE);
    }

    // seed num random (Quizas pasar como parametro, como recomendo el profe Cristobal)
    srand(time(nullptr));  

    // Cargar var de entorno
    const int iteraciones = get_env_int("ITERACIONES");
    const int epsilon = get_env_int("EPSILON");    
    const double mean = get_env_double("MEAN");  
    const double stddev = get_env_double("STDDEV");

    int m = int(sqrt(largo_arreglo)); // Largo del array sample
    int b = largo_arreglo / m;        // Largo de los intervalos en el sample (Tambiens se puede interpretar como el salto en el arreglo)

    // Vector de los resultados(tiempos) de la busqueda
    vector<double> resultados_lineal;
    vector<double> resultados_normal;

    vector<double> tiempo_arr_lineal;   
    vector<double> tiempo_arr_normal;  

    cout << "Ejecutando" << endl;
    for (int i = 0; i < iteraciones; i++){
        // cout << "iteracion " << i+1 << endl; cout << endl;
        secuencia_lineal(largo_arreglo, m, b, epsilon, resultados_lineal,tiempo_arr_lineal);
        secuencia_normal(largo_arreglo, m, b, epsilon, mean, stddev, resultados_normal,tiempo_arr_normal);
    } 
    cout << "Ejecucion Terminada" << endl;
    
    // Path archivo .CSV de los resultados
    string path_tiempo_busqueda = crear_file_name("gap","busqueda");
    crear_archivo_txt(path_tiempo_busqueda);
    escribir_resultados_csv(resultados_lineal,resultados_normal, path_tiempo_busqueda, largo_arreglo);

    string path_tiempo_creacion = crear_file_name("gap","creacion");
    crear_archivo_txt(path_tiempo_creacion);
    escribir_resultados_csv(tiempo_arr_lineal,tiempo_arr_normal, path_tiempo_creacion, largo_arreglo);
    
    return 0;
};

void secuencia_lineal(int largo_arreglo, int m, int b, int epsilon ,vector<double>& resultados_lineal,vector<double>& tiempo_arr_lineal){
    // Crear los arreglos
    int *Arr_lineal = new int[largo_arreglo];
    int *gap_Arr_lineal = new int[largo_arreglo];
    int *sample_ArrLineal = new int[m];

    Time_Interval* Tiempo_creacion = new Time_Interval();
    crear_ArrLineal(largo_arreglo, Arr_lineal, epsilon);
    gap_Coding(Arr_lineal, gap_Arr_lineal, largo_arreglo);  // Rellena el arreglo gap
    sample_Array(Arr_lineal, sample_ArrLineal, m, b);       // Rellena el arreglo sample considerando los parametros indicados
    double duration = Tiempo_creacion->tiempo_transcurrido();
    tiempo_arr_lineal.push_back(duration);

    delete Tiempo_creacion;

    int numero_buscado = experimental::randint(int(Arr_lineal[0]), int(Arr_lineal[largo_arreglo-1]));

    // Busqueda del numero (Ahora se hace la busqueda binaria en el sample, luego se suma sequencialmente en el gap)
    Time_Interval* Tiempo = new Time_Interval();
    pair<int, int> intervalo = binary_Search_Intervalos(sample_ArrLineal, m, numero_buscado);
    search_in_gap(gap_Arr_lineal, numero_buscado, sample_ArrLineal[intervalo.first], intervalo.first * b, intervalo.second * b, largo_arreglo);
    duration = Tiempo->tiempo_transcurrido();
    resultados_lineal.push_back(duration);

    // Liberar espacio
    delete Tiempo;
    delete[] Arr_lineal;
    delete[] gap_Arr_lineal;
    delete[] sample_ArrLineal;
};

void secuencia_normal(int largo_arreglo, int m, int b, int epsilon, double mean, double stddev,  vector<double>& resultados_normal,vector<double>& tiempo_arr_normal){
    // Crear los arreglos
    int *Arr_normal = new int[largo_arreglo];
    int *gap_Arr_normal = new int[largo_arreglo];
    int *sample_ArrNormal = new int[m];

    Time_Interval* Tiempo_creacion = new Time_Interval();
    crear_ArrNormal(largo_arreglo, Arr_normal, mean, stddev);
    gap_Coding(Arr_normal, gap_Arr_normal, largo_arreglo);
    sample_Array(Arr_normal, sample_ArrNormal, m, b);
    double duration = Tiempo_creacion->tiempo_transcurrido();
    tiempo_arr_normal.push_back(duration);

    delete Tiempo_creacion;

    int numero_buscado = experimental::randint(int(Arr_normal[0]), int(Arr_normal[largo_arreglo-1]));

    // Busqueda del numero (Ahora se hace la busqueda binaria en el sample, luego se suma sequencialmente en el gap)
    Time_Interval* Tiempo = new Time_Interval();
    pair<int, int> intervalo = binary_Search_Intervalos(sample_ArrNormal, m, numero_buscado);
    search_in_gap(gap_Arr_normal, numero_buscado, sample_ArrNormal[intervalo.first], intervalo.first * b, intervalo.second * b, largo_arreglo);
    duration = Tiempo->tiempo_transcurrido();
    resultados_normal.push_back(duration);

    // Liberar espacio
    delete Tiempo;
    delete[] Arr_normal;
    delete[] gap_Arr_normal;
    delete[] sample_ArrNormal;
};
