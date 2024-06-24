// metodos_arr.cpp
#include <random>
#include <algorithm>
#include <cstdlib>
#include <iostream>

#include "../include/funciones.h"

using namespace std;

void crear_ArrLineal(int largo_arreglo, int *Arr, int epsilon){
    Arr[0] = rand() % 50;
    for (int i = 1; i < largo_arreglo; i++)
    {
        Arr[i] = Arr[i - 1] + rand() % epsilon;
    }
}

void crear_ArrNormal(int largo_arreglo, int *Arr, double mean, double stddev){
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<> d(mean, stddev);

    for (int i = 0; i < largo_arreglo; i++)
    {
        Arr[i] = static_cast<int>(d(gen));
    }
    sort(Arr, Arr + largo_arreglo);
}

void gap_Coding(int *Arr, int *gapArr, int largo_arreglo){
    gapArr[0] = Arr[0];
    for(int i = 1; i < largo_arreglo; i++){
        gapArr[i] = Arr[i] - Arr[i-1];
    }

}

void print_Arr(int largo_arreglo, int *Arr){
    for (int i = 0; i < largo_arreglo; i++){
        cout << Arr[i] << " ";
    }
    cout << endl;
}

void sample_Array(int *Arr, int *sample_Arr, int m, int b){
    sample_Arr[0] = Arr[0];
    int indice = 0;
    for(int i = 1; i < m; i++){
        sample_Arr[i] = Arr[indice+b];
        indice = indice + b;
    }
}

int search_in_gap(int *Arr_gap, int num_buscado, int num_inicio, int index_inicio, int index_fin ,int largo_arreglo){
    if (index_inicio <= -1){
        index_inicio = 0;
    }
    if (index_fin <= -1){
        index_fin = largo_arreglo-1 ;
    }
    if (num_buscado == num_inicio){
        return index_inicio;
    }

    for ( int i = index_inicio + 1 ; i <= index_fin ; i++){
        num_inicio += Arr_gap[i];
        if (num_buscado == num_inicio){
            // cout << "Numero encontrado" << endl;
            return i;
        }
    }
    // cout << "Numero no encontrado" << endl;
    return -1;
}