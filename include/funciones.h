#include <string>
#include <vector>

#ifndef FUNCIONES_H
#define FUNCIONES_H

using namespace std;

// binary_search.cpp
int binary_Search(int arr[], int size, int key);

// metodos_arr.cpp
void crear_ArrLineal(int largo_arreglo, int *Arr, int epsilon);
void crear_ArrNormal(int largo_arreglo, int *Arr, double mean, double stddev);
void gap_Coding(int *Arr, int *gapArr, int largo_arreglo);
void print_Arr(int largo_arreglo, int *Arr);

// metodos_archivos.cpp
void crear_archivo_txt(const string& path);
void escribir_resultados(const vector<double>& resultados, const string& path, int largo_arreglo, int numero_buscado, const string& tipo_arr);
void escribir_resultados_csv(const vector<double>& resultados_lineal,const vector<double>& resultados_normal, const string& path, int largo_arreglo, int numero_buscado);

#endif // FUNCIONES_H
