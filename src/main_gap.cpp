#include <iostream>
#include <chrono>
#include <iomanip>
#include <cmath>
#include <experimental/random>
#include <vector>
#include <string>
#include <unistd.h> 

#include "../include/funciones.h"
#include "../include/Time_Interval.h"

using namespace std;

// Estructura de los vectores resultado
struct Vectores_de_resultados {
    vector<double> tiempo_busqueda_binaria;
    vector<double> tiempo_suma_secuencial;
    vector<double> tiempo_creacion_arreglos;
};

// Estructura de los datos para la creacion de los arreglos
struct Datos {
    const int epsilon;
    const double mean;
    const double stddev;
    int m;
    int b;

    // Constructor para inicializar los datos
    Datos(int largo_arreglo)
        : epsilon(get_env_int("EPSILON")),      // Carga var de entorno
          mean(get_env_double("MEAN")),
          stddev(get_env_double("STDDEV")),
          m(int(sqrt(largo_arreglo))),          // Define m 
          b(largo_arreglo / m) {}               // Define b
};

// Declaracion de funciones
void secuencia(char modo, int largo_arreglo, Vectores_de_resultados &resultados, Datos configuracion);

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

    Datos configuracion = Datos(largo_arreglo);   // Estructura con los datos para la creacion de los arreglos (Es mas ordenado que pasar todos lo datos por separado)

    // Cargar var de entorno
    const int iteraciones = get_env_int("ITERACIONES");

    // Vectores de resultados
    Vectores_de_resultados resultados_arreglo_lineal;
    Vectores_de_resultados resultados_arreglo_normal;


    cout << "PID del programa: " << getpid() << endl;

    cout << "Ejecutando" << endl;
    for (int i = 0; i < iteraciones; i++){
        secuencia('l', largo_arreglo, resultados_arreglo_lineal, configuracion);
        secuencia('n', largo_arreglo, resultados_arreglo_normal, configuracion);
    } 
    cout << "Ejecucion Terminada" << endl;
    
    // Path archivo .CSV de los resultados
    string path_tiempo_busqueda = crear_file_name("gap","busqueda_binaria");
    crear_archivo_txt(path_tiempo_busqueda);
    escribir_resultados_csv(resultados_arreglo_lineal.tiempo_busqueda_binaria,resultados_arreglo_normal.tiempo_busqueda_binaria, path_tiempo_busqueda, largo_arreglo);

    string path_tiempo_busqueda_suma = crear_file_name("gap","busqueda_suma");
    crear_archivo_txt(path_tiempo_busqueda_suma);
    escribir_resultados_csv(resultados_arreglo_lineal.tiempo_suma_secuencial,resultados_arreglo_normal.tiempo_suma_secuencial, path_tiempo_busqueda_suma, largo_arreglo);
    
    string path_tiempo_creacion = crear_file_name("gap","creacion_arreglos_gap_sample");
    crear_archivo_txt(path_tiempo_creacion);
    escribir_resultados_csv(resultados_arreglo_lineal.tiempo_creacion_arreglos,resultados_arreglo_normal.tiempo_creacion_arreglos, path_tiempo_creacion, largo_arreglo);

    return 0;
};

// Secuencia principal, Como se aplican los mismo procesos a los arreglos lineal y normal solo estos serian lo que cambia en cada experimento
void secuencia(char modo, int largo_arreglo, Vectores_de_resultados &resultados, Datos configuracion){
    int m = configuracion.m;
    int b = configuracion.b;

    // Declarar los arreglo
    int *arreglo = new int[largo_arreglo];
    int *arreglo_gap = new int[largo_arreglo];
    int *arreglo_sample = new int[m];

    // Crear los arreglos dependiendo del modo (l: lineal, n: normal)
    switch (modo){
        case ('l'):
            crear_ArrLineal(largo_arreglo, arreglo, configuracion.epsilon);     // Crea el arreglo lineal
            break;  
        case ('n'):
            crear_ArrNormal(largo_arreglo, arreglo, configuracion.mean, configuracion.stddev);  // Crea el arreglo normal
            break;
        default:
            cerr << "Modo seleccionado invalido" << endl;
            exit(EXIT_FAILURE);
            break;
    }

    // Calculo del tiempo de creacion de los arreglos Gap y Sample
    Time_Interval* tiempo_creacion = new Time_Interval();
    gap_Coding(arreglo, arreglo_gap, largo_arreglo);                    
    sample_Array(arreglo, arreglo_sample, m, b);
    double duracion = tiempo_creacion->tiempo_transcurrido();    
    resultados.tiempo_creacion_arreglos.push_back(duracion);

    // Define un num_random a buscar entre el rango del arreglo
    int num_buscado = experimental::randint(int(arreglo[0]), int(arreglo[largo_arreglo-1]));    

    delete[] arreglo;   // El arreglo original solo lo usamos para generar el Gap y el Sample, asi que lo podemos borrar altiro
    

    // Calculo del tiempo de la busqueda binaria del intervalo en el sample
    Time_Interval* tiempo_busqueda_binaria = new Time_Interval();
    pair<int, int> intervalo = binary_Search_Intervalos(arreglo_sample, m, num_buscado);  
    double duration_busqueda_binaria = tiempo_busqueda_binaria->tiempo_transcurrido();
    // cout << "Busqueda binaria: " << duration_busqueda_binaria << endl;
    resultados.tiempo_busqueda_binaria.push_back(duration_busqueda_binaria);

    // Calculo del tiempo de la suma secuencial en Gap, para determinar si el numero esta en el arreglo original
    Time_Interval* tiempo_suma_secuencial = new Time_Interval();
    search_in_gap(arreglo_gap, num_buscado, arreglo_sample[intervalo.first], intervalo.first * b, intervalo.second * b, largo_arreglo); // Suma secuencial
    double duration_suma = tiempo_suma_secuencial->tiempo_transcurrido();
    resultados.tiempo_suma_secuencial.push_back(duration_suma);

    // Liberar espacio
    delete tiempo_creacion;
    delete tiempo_busqueda_binaria;
    delete tiempo_suma_secuencial;
    delete[] arreglo_gap;
    delete[] arreglo_sample;    
};