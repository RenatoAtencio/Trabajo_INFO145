// main.cpp
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <random>

#include "../include/funciones.h"

using namespace std;

// Funciones 
void validarM(int success_binary_search, int numero_buscado);
void tiempo_binary_search(int largo_arreglo, int *Arr, int numero_buscado);          // Pasar los tiempos a un objeto

// Main
int main(int argc, char **argv){
    if (argc != 3){
        cout << "Entrada debe ser ./binaryS largo_arreglo numero_buscado" << endl;
        exit(1);
    }
    srand(time(nullptr)); 

    int largo_arreglo = atoi(argv[1]);
    int numero_buscado = atoi(argv[2]);

    int *Arr_lineal = new int[largo_arreglo];
    int *Arr_normal = new int[largo_arreglo];

    int epsilon = 10;
    crear_ArrLineal(largo_arreglo, Arr_lineal, epsilon);       
    double mean = 25.0;
    double stddev = 5.0;
    crear_ArrNormal(largo_arreglo, Arr_normal, mean, stddev);  

    cout << "Arreglo Lineal: ";
    // printArray(largo_arreglo, Arr_lineal);
    cout << "Arreglo Normal: ";
    // printArray(largo_arreglo, Arr_normal);

    cout << "Búsqueda en Arreglo Lineal:" << endl;
    tiempo_binary_search(largo_arreglo, Arr_lineal, numero_buscado);

    cout << "Búsqueda en Arreglo Normal:" << endl;
    tiempo_binary_search(largo_arreglo, Arr_normal, numero_buscado);

    delete[] Arr_lineal;
    delete[] Arr_normal;

    return 0;
}

void validarM(int success_binary_search, int numero_buscado){
    if (success_binary_search == -1){
        cout << "El valor " << numero_buscado << " no se encuentra en el arreglo." << endl;
    }
    else{
        cout << "El valor " << numero_buscado << " se encuentra en la posición " << success_binary_search + 1 << " del arreglo." << endl;
    }
}

void tiempo_binary_search(int largo_arreglo, int *Arr, int numero_buscado){
    auto start = chrono::high_resolution_clock::now();
    int success_binary_search = binary_Search(Arr, largo_arreglo, numero_buscado);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, nano> duration = end - start;

    validarM(success_binary_search, numero_buscado);
    cout << "Tiempo de búsqueda: " << duration.count() << " ns" << endl;
}
