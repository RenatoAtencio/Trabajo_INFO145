#include <iostream>
#include <chrono>
#include <iomanip>
#include <cmath>
#include <experimental/random>
#include <vector>
#include <string>
#include "../include/funciones.h"

using namespace std;

void secuencia_lineal(int largo_arreglo, int m, int b, int epsilon, double mean, double stddev, vector<double>& resultados_lineal);
void secuencia_normal(int largo_arreglo, int m, int b, int epsilon, double mean, double stddev, vector<double>& resultados_normal);
int get_env_int(const char* var_name);
double get_env_double(const char* var_name);

// Main
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cout << "Entrada debe ser ./binaryS largo_arreglos" << endl;
        exit(1);
    }
    srand(time(nullptr));

    int largo_arreglo = atoi(argv[1]);

    int iteraciones = get_env_int("ITERACIONES"); // Pasarlo como var de entorno

    int m = int(sqrt(largo_arreglo)); // Largo del array sample
    int b = largo_arreglo / m;        // salto entre los elementos del array original que habra en el sample

    // Vector de los resultados(tiempos) de la busqueda
    vector<double> resultados_lineal;
    vector<double> resultados_normal;

    // Crear .CSV
    string path = crear_file_name();
    crear_archivo_txt(path);

    const int epsilon = get_env_int("EPSILON");    
    const double mean = get_env_double("MEAN");  
    const double stddev = get_env_double("STDDEV");

    for (int i = 0; i < iteraciones; i++)
    {
        secuencia_lineal(largo_arreglo, m, b, epsilon, mean, stddev, resultados_lineal);
        secuencia_normal(largo_arreglo, m, b, epsilon, mean, stddev, resultados_normal);
    }

    escribir_resultados_csv(resultados_lineal, resultados_normal, path, largo_arreglo);
    return 0;
}

void secuencia_lineal(int largo_arreglo, int m, int b, int epsilon, double mean, double stddev, vector<double>& resultados_lineal)
{
    int *Arr_lineal = new int[largo_arreglo];
    int *gap_Arr_lineal = new int[largo_arreglo];
    int *sample_ArrLineal = new int[m];

    crear_ArrLineal(largo_arreglo, Arr_lineal, epsilon);
    gap_Coding(Arr_lineal, gap_Arr_lineal, largo_arreglo);
    sample_Array(Arr_lineal, sample_ArrLineal, m, b);

    int numero_buscado = experimental::randint(int(Arr_lineal[0]), int(Arr_lineal[largo_arreglo-1]));

    auto start = chrono::high_resolution_clock::now();

    pair<int, int> intervalo = binary_Search_Intervalos(sample_ArrLineal, m, numero_buscado);
    search_in_gap(gap_Arr_lineal, numero_buscado, sample_ArrLineal[intervalo.first], intervalo.first * b, intervalo.second * b, largo_arreglo);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, nano> duration = end - start;

    resultados_lineal.push_back(duration.count());
    delete[] Arr_lineal;
    delete[] gap_Arr_lineal;
    delete[] sample_ArrLineal;
}

void secuencia_normal(int largo_arreglo, int m, int b, int epsilon, double mean, double stddev, vector<double>& resultados_normal)
{
    int *Arr_normal = new int[largo_arreglo];
    int *gap_Arr_normal = new int[largo_arreglo];
    int *sample_ArrNormal = new int[m];

    crear_ArrNormal(largo_arreglo, Arr_normal, mean, stddev);
    gap_Coding(Arr_normal, gap_Arr_normal, largo_arreglo);
    sample_Array(Arr_normal, sample_ArrNormal, m, b);

    int numero_buscado = experimental::randint(int(Arr_normal[0]), int(Arr_normal[largo_arreglo-1]));

    auto start = chrono::high_resolution_clock::now();

    pair<int, int> intervalo = binary_Search_Intervalos(sample_ArrNormal, m, numero_buscado);
    search_in_gap(gap_Arr_normal, numero_buscado, sample_ArrNormal[intervalo.first], intervalo.first * b, intervalo.second * b, largo_arreglo);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, nano> duration = end - start;

    resultados_normal.push_back(duration.count());

    delete[] Arr_normal;
    delete[] gap_Arr_normal;
    delete[] sample_ArrNormal;
}
