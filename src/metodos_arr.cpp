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
    for(int i = 0; i < largo_arreglo; i++){
        gapArr[i] = Arr[i] - Arr[i-1];
    }

}

void print_Arr(int largo_arreglo, int *Arr){
    for (int i = 0; i < largo_arreglo; i++){
        cout << Arr[i] << " ";
    }
    cout << endl;
}
