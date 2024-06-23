// main.cpp
#include <iostream>
#include <chrono>
#include <iomanip>
#include "../include/funciones.h"

using namespace std;

// Funciones 
void validarM(int success_binary_search, int numero_buscado);
void tiempo_binary_search(int largo_arreglo, int *Arr, int numero_buscado, vector<double>& resultados); // Pasar los tiempos a un objeto
string crear_file_name();

// Main
int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Entrada debe ser ./binaryS largo_arreglo numero_buscado" << endl;
        exit(1);
    }
    srand(time(nullptr));  

    int largo_arreglo = atoi(argv[1]);
    int numero_buscado = atoi(argv[2]);

    int iteraciones = 100;  // Pasarlo como var de entorno

    // Vector de los resultados(tiempos) de la busqueda
    vector<double> resultados_lineal;   
    vector<double> resultados_normal;   

    string path = crear_file_name();
    crear_archivo_txt(path);

    for (int i = 0; i < iteraciones; i++) {
        int* Arr_lineal = new int[largo_arreglo];
        int* Arr_normal = new int[largo_arreglo];

        int epsilon = 10;       // Pasarlo como var de entorno
        crear_ArrLineal(largo_arreglo, Arr_lineal, epsilon);
        double mean = 25.0;     // Pasarlo como var de entorno
        double stddev = 5.0;    // Pasarlo como var de entorno
        crear_ArrNormal(largo_arreglo, Arr_normal, mean, stddev);

        // Busqueda arreglo lineal
        tiempo_binary_search(largo_arreglo, Arr_lineal, numero_buscado, resultados_lineal);

        // Busqueda arreglo normal
        tiempo_binary_search(largo_arreglo, Arr_normal, numero_buscado, resultados_normal);

        delete[] Arr_lineal;
        delete[] Arr_normal;
    }

    escribir_resultados_csv(resultados_lineal,resultados_normal, path, largo_arreglo, numero_buscado);
    return 0;
}

void validarM(int success_binary_search, int numero_buscado) {
    if (success_binary_search == -1) {
        cout << "El valor " << numero_buscado << " no se encuentra en el arreglo." << endl;
    } else {
        cout << "El valor " << numero_buscado << " se encuentra en la posición " << success_binary_search + 1 << " del arreglo." << endl;
    }
}

void tiempo_binary_search(int largo_arreglo, int* Arr, int numero_buscado, vector<double>& resultados) {

    auto start = chrono::high_resolution_clock::now();
    int success_binary_search = binary_Search(Arr, largo_arreglo, numero_buscado);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, nano> duration = end - start;

    resultados.push_back(duration.count());
}

// Crea el path+file_name para los archivos de salida
string crear_file_name(){
    const char* user_env = std::getenv("USER");
    if (!user_env) {
        user_env = "user";
    }

    string titulo = "Tests";

    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    stringstream ss;
    ss << put_time(std::localtime(&in_time_t), "%Y-%m-%d %Hh-%Mm-%Ss");

    string path = "out/" + titulo + " - " + string(user_env) + " - " + ss.str() + ".csv";
    return path;
};