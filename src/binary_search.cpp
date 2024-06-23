// binary_search.cpp
#include <iostream>
#include <chrono>
#include <iomanip>
#include "../include/funciones.h"

using namespace std;

int binary_Search(int arr[], int largo_arr, int num) {
    int low = 0;
    int high = largo_arr - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == num) {
            return mid; // Elemento encontrado
        }
        if (arr[mid] < num) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1; // Elemento no encontrado
}

void validarM(int success_binary_search, int numero_buscado) {
    if (success_binary_search == -1) {
        cout << "El valor " << numero_buscado << " no se encuentra en el arreglo." << endl;
        return;
    }
    cout << "El valor " << numero_buscado << " se encuentra en la posición " << success_binary_search + 1 << " del arreglo." << endl;
}

double tiempo_binary_search(int largo_arreglo, int* Arr, int numero_buscado) {

    auto start = chrono::high_resolution_clock::now();
    int success_binary_search = binary_Search(Arr, largo_arreglo, numero_buscado);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, nano> duration = end - start;

    return(duration.count());
}
