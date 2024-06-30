// main_normal.cpp
#include <iostream>
#include <experimental/random>
#include <string>
#include "../include/funciones.h"
#include "../include/Time_Interval.h"

using namespace std;

void secuencia_lineal(int largo_arreglo, int epsilon, vector<double>& resultados_lineal, vector<double>& tiempo_arr_lineal);
void secuencia_normal(int largo_arreglo, double mean, double stddev, vector<double>& resultados_normal, vector<double>& tiempo_arr_normal);

// Main
int main(int argc, char** argv) {

    if (argc != 2) {
        cout << "Entrada debe ser ./binaryS largo_arreglo" << endl;
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

    // Vector de los resultados(tiempos) de la busqueda del numero
    vector<double> resultados_lineal;   
    vector<double> resultados_normal;   

    vector<double> tiempo_arr_lineal;   
    vector<double> tiempo_arr_normal;   

    // Loop de la ejecucion principal
    cout << "Ejecutando" << endl;
    for (int i = 0; i < iteraciones; i++) {
        // cout << "Iteracion: " << i+1 << endl;
        secuencia_lineal(largo_arreglo, epsilon, resultados_lineal,tiempo_arr_lineal);
        secuencia_normal(largo_arreglo, mean, stddev, resultados_normal,tiempo_arr_normal);
    }
    cout << "Ejecucion Terminada" << endl;

    // Path archivo .CSV de los resultados
    string path_tiempo_busqueda = crear_file_name("normal","busqueda");
    crear_archivo_txt(path_tiempo_busqueda);
    escribir_resultados_csv(resultados_lineal,resultados_normal, path_tiempo_busqueda, largo_arreglo);

    string path_tiempo_creacion = crear_file_name("normal","creacion");
    crear_archivo_txt(path_tiempo_creacion);
    escribir_resultados_csv(tiempo_arr_lineal,tiempo_arr_normal, path_tiempo_creacion, largo_arreglo);

    return 0;
};


// Tiempo de la busqueda binaria con el arreglo lineal
void secuencia_lineal(int largo_arreglo, int epsilon, vector<double>& resultados_lineal, vector<double>& tiempo_arr_lineal){

    // Crear nuevo Arreglo
    Time_Interval* Tiempo_creacion = new Time_Interval();
    int *Arr_lineal = new int[largo_arreglo]; 
    double duration = Tiempo_creacion->tiempo_transcurrido();
    tiempo_arr_lineal.push_back(duration);

    delete Tiempo_creacion;

    // Rellenar con randoms
    crear_ArrLineal(largo_arreglo, Arr_lineal, epsilon);
    
    // Num buscado random entre los extremos del arreglo
    int numero_buscado = experimental::randint(int(Arr_lineal[0]), int(Arr_lineal[largo_arreglo-1]));

    // Busqueda
    Time_Interval* Tiempo = new Time_Interval();
    binary_Search(Arr_lineal, largo_arreglo, numero_buscado);
    duration = Tiempo->tiempo_transcurrido();
    resultados_lineal.push_back(duration);

    // Liberar espacio
    delete Tiempo;  
    delete[] Arr_lineal;
};


// Tiempo de la busqueda binaria con el arreglo normal
void secuencia_normal(int largo_arreglo, double mean, double stddev, vector<double>& resultados_normal, vector<double>& tiempo_arr_normal){

    // Crear nuevo Arreglo
    Time_Interval* Tiempo_creacion = new Time_Interval();
    int *Arr_normal = new int[largo_arreglo];
    double duration = Tiempo_creacion->tiempo_transcurrido();
    tiempo_arr_normal.push_back(duration);

    delete Tiempo_creacion;

    // Rellenar con randoms
    crear_ArrNormal(largo_arreglo, Arr_normal, mean, stddev);

    // Num buscado random entre los extremos del arreglo
    int numero_buscado = experimental::randint(int(Arr_normal[0]), int(Arr_normal[largo_arreglo-1]));

    // Busqueda binaria
    Time_Interval* Tiempo = new Time_Interval();
    binary_Search(Arr_normal, largo_arreglo, numero_buscado);
    duration = Tiempo->tiempo_transcurrido();
    resultados_normal.push_back(duration);

    // Liberar espacio
    delete Tiempo;
    delete[] Arr_normal;
};