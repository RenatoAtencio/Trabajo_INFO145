#include <string>
#include <vector>

#ifndef FUNCIONES_H
#define FUNCIONES_H

using namespace std;

// binary_search.cpp
int binary_Search(int arr[], int size, int key);
void validarM(int success_binary_search, int numero_buscado);
double tiempo_binary_search(int largo_arreglo, int* Arr, int numero_buscado);
pair<int, int> binary_Search_Intervalos(int arr[], int largo_arr, int num);

// metodos_arr.cpp
void crear_ArrLineal(int largo_arreglo, int *Arr, int epsilon);
void crear_ArrNormal(int largo_arreglo, int *Arr, double mean, double stddev);
void gap_Coding(int *Arr, int *gapArr, int largo_arreglo);
void sample_Array(int *Arr, int *sample_Arr, int m, int b);
void print_Arr(int largo_arreglo, int *Arr);
int search_in_gap(int *Arr_gap, int num_buscado, int num_inicio, int index_inicio, int index_fin ,int largo_arreglo);

// metodos_archivos.cpp
void crear_archivo_txt(const string& path);
void escribir_resultados(const vector<double>& resultados, const string& path, int largo_arreglo, int numero_buscado, const string& tipo_arr);
void escribir_resultados_csv(const vector<double>& resultados_lineal,const vector<double>& resultados_normal, const string& path, int largo_arreglo);
string crear_file_name();

// metodos_var_entorno.cpp
int get_env_int(const char* var_name);
double get_env_double(const char* var_name);

#endif // FUNCIONES_H
