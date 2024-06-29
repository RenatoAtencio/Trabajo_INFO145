// binary_search.cpp
#include <iostream>
#include <chrono>
#include <iomanip>
#include "../include/funciones.h"

using namespace std;

// Binary Search 
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

// Binary Search pero devuelve los intervalos done pueda estar el numero
pair<int, int> binary_Search_Intervalos(int arr[], int largo_arr, int num){
    int low = 0;
    int high = largo_arr - 1;
    
    if (num < arr[low]) {
        return {-1, 0};     // El número es menor que el primer elemento
    }
    if (num > arr[high]) {
        return {high, -1};  // El número es mayor que el último elemento
    }
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (arr[mid] == num) {
            return {mid, mid};  // Número encontrado en una posición exacta
        } else if (arr[mid] < num) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return {high, low};
}