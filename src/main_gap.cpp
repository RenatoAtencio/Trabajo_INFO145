#include <iostream>
#include <chrono>
#include <iomanip>
#include <cmath>
#include <experimental/random>
#include <vector>
#include <string>

#include "../include/funciones.h"
#include "../include/Time_Interval.h"

using namespace std;

void secuencia_lineal(int largo_arreglo, int m, int b, int epsilon,int Arr_lineal[],int gap_Arr_lineal[] ,int sample_ArrLineal[] , vector<double>& resultados_lineal);
void secuencia_normal(int largo_arreglo, int m, int b, int epsilon, double mean, double stddev,int Arr_normal[], int gap_Arr_normal[],int sample_ArrNormal[], vector<double>& resultados_normal);

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

    const int iteraciones = get_env_int("ITERACIONES");
    const int epsilon = get_env_int("EPSILON");    
    const double mean = get_env_double("MEAN");  
    const double stddev = get_env_double("STDDEV");

    int m = int(sqrt(largo_arreglo)); // Largo del array sample
    int b = largo_arreglo / m;        // Largo de los intervalos en el sample (Tambiens se puede ver como el salto en el arreglo)

    // Vector de los resultados(tiempos) de la busqueda
    vector<double> resultados_lineal;
    vector<double> resultados_normal;

    // Crear .CSV
    string path = crear_file_name();
    crear_archivo_txt(path);

    // Arreglos estaticos que usaremos
    int Arr_lineal[largo_arreglo];
    int gap_Arr_lineal[largo_arreglo];
    int sample_ArrLineal[m];

    // Se podrian usar los mismos arreglos de arriba pero por orden los creamos 
    int Arr_normal[largo_arreglo];
    int gap_Arr_normal[largo_arreglo];
    int sample_ArrNormal[m];

    for (int i = 0; i < iteraciones; i++)
    {
        cout << "iteracion " << i+1 << endl; cout << endl;
        secuencia_lineal(largo_arreglo, m, b, epsilon, Arr_lineal, gap_Arr_lineal,sample_ArrLineal, resultados_lineal);
        cout << "--------------" << endl;
        secuencia_normal(largo_arreglo, m, b, epsilon, mean, stddev, Arr_normal, gap_Arr_normal,sample_ArrNormal, resultados_normal);
    }

    escribir_resultados_csv(resultados_lineal, resultados_normal, path, largo_arreglo);
    return 0;
}

void secuencia_lineal(int largo_arreglo, int m, int b, int epsilon,int Arr_lineal[], int gap_Arr_lineal[] ,int sample_ArrLineal[] ,vector<double>& resultados_lineal)
{

    crear_ArrLineal(largo_arreglo, Arr_lineal, epsilon);
    gap_Coding(Arr_lineal, gap_Arr_lineal, largo_arreglo);
    sample_Array(Arr_lineal, sample_ArrLineal, m, b);

    cout<<"arreglo lineal : "; print_Arr(largo_arreglo,Arr_lineal); cout<<endl;
    cout<<"arreglo gap    : "; print_Arr(largo_arreglo,gap_Arr_lineal); cout<<endl;
    cout<<"arreglo sample : "; print_Arr(m,sample_ArrLineal); cout<<endl;

    int numero_buscado = experimental::randint(int(Arr_lineal[0]), int(Arr_lineal[largo_arreglo-1]));

    Time_Interval* Tiempo = new Time_Interval();
    pair<int, int> intervalo = binary_Search_Intervalos(sample_ArrLineal, m, numero_buscado);
    search_in_gap(gap_Arr_lineal, numero_buscado, sample_ArrLineal[intervalo.first], intervalo.first * b, intervalo.second * b, largo_arreglo);
    double duration = Tiempo->tiempo_transcurrido();
    resultados_lineal.push_back(duration);

    delete Tiempo;
}

void secuencia_normal(int largo_arreglo, int m, int b, int epsilon, double mean, double stddev,int Arr_normal[],int gap_Arr_normal[],int sample_ArrNormal[], vector<double>& resultados_normal)
{
    crear_ArrNormal(largo_arreglo, Arr_normal, mean, stddev);
    gap_Coding(Arr_normal, gap_Arr_normal, largo_arreglo);
    sample_Array(Arr_normal, sample_ArrNormal, m, b);

    cout<<"arreglo Normal : "; print_Arr(largo_arreglo,Arr_normal); cout<<endl;
    cout<<"arreglo gap    : "; print_Arr(largo_arreglo,gap_Arr_normal); cout<<endl;
    cout<<"arreglo sample : "; print_Arr(m,sample_ArrNormal); cout<<endl;

    int numero_buscado = experimental::randint(int(Arr_normal[0]), int(Arr_normal[largo_arreglo-1]));

    Time_Interval* Tiempo = new Time_Interval();
    pair<int, int> intervalo = binary_Search_Intervalos(sample_ArrNormal, m, numero_buscado);
    search_in_gap(gap_Arr_normal, numero_buscado, sample_ArrNormal[intervalo.first], intervalo.first * b, intervalo.second * b, largo_arreglo);
    double duration = Tiempo->tiempo_transcurrido();
    resultados_normal.push_back(duration);

    delete Tiempo;
}
