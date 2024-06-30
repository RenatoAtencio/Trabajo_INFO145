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

void secuencia_lineal(int largo_arreglo, int m, int b, int epsilon,vector<double>& resultados_lineal,vector<double>& resultados_prebusqueda_lienal);
void secuencia_normal(int largo_arreglo, int m, int b, int epsilon, double mean, double stddev, vector<double>& resultados_normal,vector<double>& resultados_prebusqueda_normal);
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

    vector<double> resultados_prebusqueda_lineal;   
    vector<double> resultados_prebusqueda_normal;  

    


    cout << "Ejecutando" << endl;
    for (int i = 0; i < iteraciones; i++)
    {
        // cout << "Iteracion: " << i+1 << endl;
        secuencia_lineal(largo_arreglo, m, b, epsilon, resultados_lineal,resultados_prebusqueda_lineal);
        secuencia_normal(largo_arreglo, m, b, epsilon, mean, stddev, resultados_normal,resultados_prebusqueda_normal);
    }
    cout << "Ejecucion Terminada" << endl;

    // Path archivo .CSV de los resultados
    string path_tiempo_busqueda = crear_file_name("huffman","busqueda");
    crear_archivo_txt(path_tiempo_busqueda);
    escribir_resultados_csv(resultados_lineal,resultados_normal, path_tiempo_busqueda, largo_arreglo);

    string path_tiempo_prebusqueda = crear_file_name("huffman","prebusqueda");
    crear_archivo_txt(path_tiempo_prebusqueda);
    escribir_resultados_csv(resultados_prebusqueda_lineal,resultados_prebusqueda_normal, path_tiempo_prebusqueda, largo_arreglo);

    return 0;
}

void secuencia_lineal(int largo_arreglo, int m, int b, int epsilon,vector<double>& resultados_lineal,vector<double>& resultados_prebusqueda_lineal)
{
    int *Arr_lineal = new int[largo_arreglo];
    int *Arr_gap_lineal = new int[largo_arreglo];
    int *Arr_sample_lineal = new int[m];


    // Llenar los arreglos 
    // Arr_lineal
    crear_ArrLineal(largo_arreglo, Arr_lineal, epsilon);
    // Arr_gap
    gap_Coding(Arr_lineal, Arr_gap_lineal, largo_arreglo);
    // Arr_sample
    sample_Array(Arr_lineal, Arr_sample_lineal, m, b);

    // Generamos un numero random entre los limites del arreglo
    // int numero_buscado = Arr_lineal[largo_arreglo-1];
    int numero_buscado = experimental::randint(int(Arr_lineal[0]), int(Arr_lineal[largo_arreglo-1]));
    

    Time_Interval* Tiempo_prebusqueda = new Time_Interval();

    // Calculamos las frecuencias de los numeros para crear el arbol de huffman
    map<int,int> frecuencias = frecuencias_gap_arr(Arr_gap_lineal,largo_arreglo);

    
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

    
    int largo_max = codigo_mas_largo(huffmanCodes); // Obtenemos el codigo de Huffman mas largo (Lo usaremos para ver si usamos 8bits o 16bits)

    if (largo_max > 8){
        largo_max = 16;
    }
    largo_max = 8;
    char *arr_gap_comprimido = new char[largo_arreglo]; 

    // Crea un mapa con los codigos + padding, el padding son 0 a la derecha hasta completar el largo necesario
    unordered_map<int, string> padded_huffman;
    padded_huffman = padding_codigos(huffmanCodes,largo_max);

    
    // Rellenar arreglo gap comprimido
    for (int i = 0; i<largo_arreglo;i++){
        bitset<32> codigo{padded_huffman[Arr_gap_lineal[i]]};
        string binaryCode = codigo.to_string().substr(32 - largo_max);
        if (largo_max > 8){
            short int codigo_comprimido = static_cast<short int>(codigo.to_ulong());
        }
        char codigo_comprimido = static_cast<char>(codigo.to_ulong());
        arr_gap_comprimido[i] = codigo_comprimido;
    }

    double duration = Tiempo_prebusqueda->tiempo_transcurrido();
    resultados_prebusqueda_lineal.push_back(duration);
    delete Tiempo_prebusqueda;

    // Prints de espacio principal usado
    // cout << "Size arr: " << sizeof(Arr_lineal[0]) * largo_arreglo << endl;
    // cout << "Size arr gap: " << sizeof(Arr_gap_lineal[0]) * largo_arreglo << endl;
    // cout << "Size arr sample: " << sizeof(Arr_sample_lineal[0]) * m << endl;
    // cout << "Size arr comprimido: " << sizeof(arr_gap_comprimido[0]) * largo_arreglo << endl;

    Time_Interval* Tiempo = new Time_Interval();

    // Busqueda binaria sobre el sample
    pair<int, int> intervalo = binary_Search_Intervalos(Arr_sample_lineal, m, numero_buscado);
    // Suma secuencial en el gap 
    search_in_gap_codificado(padded_huffman,arr_gap_comprimido, numero_buscado, Arr_sample_lineal[intervalo.first], intervalo.first * b, intervalo.second * b, largo_arreglo);
    
    duration = Tiempo->tiempo_transcurrido();
    resultados_lineal.push_back(duration);
    
    // Liberar memoria 
    delete Tiempo; 
    delete[] arr_gap_comprimido;
    delete[] Arr_lineal;
    delete[] Arr_gap_lineal;
    delete[] Arr_sample_lineal;
}

void secuencia_normal(int largo_arreglo, int m, int b, int epsilon, double mean, double stddev, vector<double>& resultados_normal,vector<double>& resultados_prebusqueda_normal)
{

    int *Arr_normal = new int[largo_arreglo];
    int *gap_Arr_normal = new int[largo_arreglo];
    int *sample_ArrNormal = new int[m];

    crear_ArrNormal(largo_arreglo, Arr_normal, mean, stddev);
    gap_Coding(Arr_normal, gap_Arr_normal, largo_arreglo);
    sample_Array(Arr_normal, sample_ArrNormal, m, b);

    int numero_buscado = experimental::randint(int(Arr_normal[0]), int(Arr_normal[largo_arreglo-1]));

    Time_Interval* Tiempo_prebusqueda = new Time_Interval();

    // Calculamos las frecuencias de los numeros para crear el arbol de huffman
    map<int,int> frecuencias = frecuencias_gap_arr(gap_Arr_normal,largo_arreglo);

    
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

    
    int largo_max = codigo_mas_largo(huffmanCodes); // Obtenemos el codigo de Huffman mas largo (Lo usaremos para ver si usamos 8bits o 16bits)

    if (largo_max > 8){
        largo_max = 16;
    }
    largo_max = 8;
    char *arr_gap_comprimido = new char[largo_arreglo]; 

    // Crea un mapa con los codigos + padding, el padding son 0 a la derecha hasta completar el largo necesario
    unordered_map<int, string> padded_huffman;
    padded_huffman = padding_codigos(huffmanCodes,largo_max);

    
    // Rellenar arreglo gap comprimido
    for (int i = 0; i<largo_arreglo;i++){
        bitset<32> codigo{padded_huffman[gap_Arr_normal[i]]};
        string binaryCode = codigo.to_string().substr(32 - largo_max);
        if (largo_max > 8){
            short int codigo_comprimido = static_cast<short int>(codigo.to_ulong());
        }
        char codigo_comprimido = static_cast<char>(codigo.to_ulong());
        arr_gap_comprimido[i] = codigo_comprimido;
    }

    double duration = Tiempo_prebusqueda->tiempo_transcurrido();
    resultados_prebusqueda_normal.push_back(duration);
    delete Tiempo_prebusqueda;

    // Prints de espacio principal usado
    // cout << "NORMAL Size arr: " << sizeof(Arr_normal[0]) * largo_arreglo << endl;
    // cout << "NORMAL Size arr gap: " << sizeof(gap_Arr_normal[0]) * largo_arreglo << endl;
    // cout << "NORMAL Size arr sample: " << sizeof(sample_ArrNormal[0]) * m << endl;
    // cout << "NORMAL Size arr comprimido: " << sizeof(arr_gap_comprimido[0]) * largo_arreglo << endl;

    Time_Interval* Tiempo = new Time_Interval();
    pair<int, int> intervalo = binary_Search_Intervalos(sample_ArrNormal, m, numero_buscado);
    search_in_gap_codificado(padded_huffman,arr_gap_comprimido, numero_buscado, sample_ArrNormal[intervalo.first], intervalo.first * b, intervalo.second * b, largo_arreglo);
    
    duration = Tiempo->tiempo_transcurrido();
    resultados_normal.push_back(duration);

    delete Tiempo;
    delete[] Arr_normal;
    delete[] gap_Arr_normal;
    delete[] sample_ArrNormal;
}