#include <iostream>
#include <chrono>
#include <iomanip>
#include <cmath>
#include <experimental/random>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <algorithm>
#include <bitset>

#include "../include/funciones.h"
#include "../include/Time_Interval.h"

using namespace std;

void secuencia_lineal(int largo_arreglo, int m, int b, int epsilon,int Arr_lineal[],int gap_Arr_lineal[] ,int sample_ArrLineal[] , vector<double>& resultados_lineal);
void secuencia_normal(int largo_arreglo, int m, int b, int epsilon, double mean, double stddev,int Arr_normal[], int gap_Arr_normal[],int sample_ArrNormal[], vector<double>& resultados_normal);
map<int,int> frecuencias_gap_arr(int gap_arr[],int gap_lenght);

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
        secuencia_lineal(largo_arreglo, m, b, epsilon, Arr_lineal, gap_Arr_lineal,sample_ArrLineal, resultados_lineal);
        // secuencia_normal(largo_arreglo, m, b, epsilon, mean, stddev, Arr_normal, gap_Arr_normal,sample_ArrNormal, resultados_normal);
    }

    // escribir_resultados_csv(resultados_lineal, resultados_normal, path, largo_arreglo);
    return 0;
}

void secuencia_lineal(int largo_arreglo, int m, int b, int epsilon,int Arr_lineal[], int gap_Arr_lineal[] ,int sample_ArrLineal[] ,vector<double>& resultados_lineal)
{
    // Crear los arreglo que se usaran 
    crear_ArrLineal(largo_arreglo, Arr_lineal, epsilon);
    gap_Coding(Arr_lineal, gap_Arr_lineal, largo_arreglo);
    sample_Array(Arr_lineal, sample_ArrLineal, m, b);

    // Generamos un numero random entre los limites del arreglo
    // int numero_buscado = Arr_lineal[largo_arreglo-1];
    int numero_buscado = experimental::randint(int(Arr_lineal[0]), int(Arr_lineal[largo_arreglo-1]));
    cout << "Numero buscado: " << numero_buscado << endl;

    // Calculamos las frecuencias de los numeros para crear el arbol de huffman
    map<int,int> frecuencias = frecuencias_gap_arr(gap_Arr_lineal,largo_arreglo);
    
    // Crar vector de nodos para la creacion del arbol de huffman
    vector<Nodo_Huffman*> nodos;
    for (const auto& pair : frecuencias) {
        nodos.push_back(new Nodo_Huffman(pair.first, pair.second));
    }

    // Crear el arbol de huffman, devuelve el root
    Nodo_Huffman* root = crear_arbol_huffman(nodos);  

    // Generar codigos de Huffman, huffmanCodes es pasado como referencia. (Se llena al llamar a la funcion)
    unordered_map<int, string> huffmanCodes;
    crear_codigos_huffman(root, huffmanCodes);  


    int largo_max = codigo_mas_largo(huffmanCodes); // Obtenemos el codigo de Huffman mas largo (Lo usaremos para ver si usamos 4bits o 8bits)

    

    if (largo_max > 4){
        largo_max = 8;
        short int arr_gap_comprimido[largo_arreglo];
    }
    largo_max = 4;
    char arr_gap_comprimido[largo_arreglo];


    // Generar codigos canonicos de huffman con el padding para que sean del mismo largo
    map<int, string> canonicalCodes = padding_codigos_canonicos(huffmanCodes,largo_max);


    cout << "Codigos de huffman" << endl;
    // Imprimir los códigos canónicos
    for (const auto& pair : canonicalCodes) {
        cout << "Símbolo: " << pair.first << ", Código: " << pair.second << endl;
    }

    // Rellenar arreglo gap comprimido
    for (int i = 0; i<largo_arreglo;i++){
        bitset<32> codigo{canonicalCodes[gap_Arr_lineal[i]]};
        string binaryCode = codigo.to_string().substr(32 - largo_max);
        if (largo_max > 4){
            short int codigo_comprimido = static_cast<short int>(codigo.to_ulong());
        }
        char codigo_comprimido = static_cast<char>(codigo.to_ulong());
        arr_gap_comprimido[i] = codigo_comprimido;
    }
    

    Time_Interval* Tiempo = new Time_Interval();
    pair<int, int> intervalo = binary_Search_Intervalos(sample_ArrLineal, m, numero_buscado);

    search_in_gap_codificado(canonicalCodes,arr_gap_comprimido, numero_buscado, sample_ArrLineal[intervalo.first], intervalo.first * b, intervalo.second * b, largo_arreglo);
    
    
    cout << "Largo item comprimido " << sizeof(arr_gap_comprimido[0]) << endl;
    
    double duration = Tiempo->tiempo_transcurrido();
    resultados_lineal.push_back(duration);
    delete Tiempo;
}

void secuencia_normal(int largo_arreglo, int m, int b, int epsilon, double mean, double stddev,int Arr_normal[],int gap_Arr_normal[],int sample_ArrNormal[], vector<double>& resultados_normal)
{
    crear_ArrNormal(largo_arreglo, Arr_normal, mean, stddev);
    gap_Coding(Arr_normal, gap_Arr_normal, largo_arreglo);
    sample_Array(Arr_normal, sample_ArrNormal, m, b);

    int numero_buscado = experimental::randint(int(Arr_normal[0]), int(Arr_normal[largo_arreglo-1]));

    Time_Interval* Tiempo = new Time_Interval();
    pair<int, int> intervalo = binary_Search_Intervalos(sample_ArrNormal, m, numero_buscado);
    search_in_gap(gap_Arr_normal, numero_buscado, sample_ArrNormal[intervalo.first], intervalo.first * b, intervalo.second * b, largo_arreglo);
    double duration = Tiempo->tiempo_transcurrido();
    resultados_normal.push_back(duration);

    map<int,int> frecuencias = frecuencias_gap_arr(gap_Arr_normal,largo_arreglo);

    delete Tiempo;
}

// Imprimir Arreglos

    // cout<<"arreglo Normal : "; print_Arr(largo_arreglo,Arr_normal); cout<<endl;
    // cout<<"arreglo gap    : "; print_Arr(largo_arreglo,gap_Arr_normal); cout<<endl;
    // cout<<"arreglo sample : "; print_Arr(m,sample_ArrNormal); cout<<endl;

    // cout<<"arreglo lineal : "; print_Arr(largo_arreglo,Arr_lineal); cout<<endl;
    // cout<<"arreglo gap    : "; print_Arr(largo_arreglo,gap_Arr_lineal); cout<<endl;
    // cout<<"arreglo sample : "; print_Arr(m,sample_ArrLineal); cout<<endl;

    // for (const auto item : arr_gap_comprimido){
    //     cout << bitset<10>(item) << " ";
    // }
    // cout << endl;

    // cout << "Codigos de huffman" << endl;
    // // Imprimir los códigos canónicos
    // for (const auto& pair : huffmanCodes) {
    //     cout << "Símbolo: " << pair.first << ", Código: " << pair.second << endl;
    // }
    
    // cout << "Codigos de huffman canonicos" << endl;
    // // Imprimir los códigos canónicos
    // for (const auto& pair : canonicos) {
    //     cout << "Símbolo: " << pair.first << ", Código: " << pair.second << endl;
    // }

    // cout << "Codigos de huffman canonicos,mismo largo" << endl;
    // // Imprimir los códigos canónicos
    // for (const auto& pair : canonicalCodes) {
    //     cout << "Símbolo: " << pair.first << ", Código: " << pair.second << endl;
    // }
