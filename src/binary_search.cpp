// binary_search.cpp
#include "../include/funciones.h"

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
