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
#include <unistd.h> 

#include "../include/funciones.h"
#include "../include/Time_Interval.h"

using namespace std;

// Estructura de los vectores resultado
struct Vectores_de_resultados {
    vector<double> tiempo_frecuencias;
    vector<double> tiempo_huffman;
    vector<double> tiempo_busqueda_gap_codificado;
};

// Estructura de los datos para la creacion de los arreglos
struct Datos {
    const int epsilon;
    const double mean;
    const double stddev;
    int m;
    int b;

    // Constructor para inicializar los datos
    Datos(int largo_arreglo)
        : epsilon(get_env_int("EPSILON")),      // Carga var de entorno
          mean(get_env_double("MEAN")),
          stddev(get_env_double("STDDEV")),
          m(int(sqrt(largo_arreglo))),          // Define m 
          b(largo_arreglo / m) {}               // Define b
};

// Declaracion de funciones
void secuencia(char modo, int largo_arreglo, Vectores_de_resultados &resultados, Datos configuracion);

// Main
int main(int argc, char **argv){
    if (argc != 2){
        cout << "Entrada debe ser ./binaryS largo_arreglos" << endl;
        exit(1);
    }

    srand(time(nullptr));

    int largo_arreglo = atoi(argv[1]);

    Datos configuracion = Datos(largo_arreglo);   // Estructura con los datos para la creacion de los arreglos (Es mas ordenado que pasar todos lo datos por separado)

    // Cargar var de entorno
    const int iteraciones = get_env_int("ITERACIONES");

    // Vectores de resultados
    Vectores_de_resultados resultados_arreglo_lineal;
    Vectores_de_resultados resultados_arreglo_normal;

    cout << "PID del programa: " << getpid() << endl;

    cout << "Ejecutando" << endl;
    for (int i = 0; i < iteraciones; i++){
        secuencia('l', largo_arreglo, resultados_arreglo_lineal, configuracion);
        secuencia('n', largo_arreglo, resultados_arreglo_normal, configuracion);
    } 
    cout << "Ejecucion Terminada" << endl;

    // Path archivo .CSV de los resultados
    string path_tiempo_busqueda = crear_file_name("huffman","busqueda_gap_codificado");
    crear_archivo_txt(path_tiempo_busqueda);
    escribir_resultados_csv(resultados_arreglo_lineal.tiempo_busqueda_gap_codificado,resultados_arreglo_normal.tiempo_busqueda_gap_codificado, path_tiempo_busqueda, largo_arreglo);

    string path_frec = crear_file_name("huffman","calculo_frecuencias");
    crear_archivo_txt(path_frec);
    escribir_resultados_csv(resultados_arreglo_lineal.tiempo_frecuencias,resultados_arreglo_normal.tiempo_frecuencias, path_frec, largo_arreglo);

    string path_huffman = crear_file_name("huffman","creacion_huffman_codes");
    crear_archivo_txt(path_huffman);
    escribir_resultados_csv(resultados_arreglo_lineal.tiempo_huffman,resultados_arreglo_normal.tiempo_huffman, path_huffman, largo_arreglo);

    return 0;
};

// Secuencia principal, Como se aplican los mismo procesos a los arreglos lineal y normal solo estos serian lo que cambia en cada experimento
void secuencia(char modo, int largo_arreglo, Vectores_de_resultados &resultados, Datos configuracion){
    int m = configuracion.m;
    int b = configuracion.b;

    // Declarar los arreglo
    int *arreglo = new int[largo_arreglo];      // Arreglo original
    int *arreglo_gap = new int[largo_arreglo];  // Arreglo gap
    int *arreglo_sample = new int[m];           // Arreglo sample

    // Crear los arreglos dependiendo del modo (l: lineal, n: normal)
    switch (modo){
        case ('l'):
            crear_ArrLineal(largo_arreglo, arreglo, configuracion.epsilon);     // Crea el arreglo lineal
            break;  
        case ('n'):
            crear_ArrNormal(largo_arreglo, arreglo, configuracion.mean, configuracion.stddev);  // Crea el arreglo normal
            break;
        default:
            cerr << "Modo seleccionado invalido" << endl;
            exit(EXIT_FAILURE);
            break;
    }

    // Define un num_random a buscar entre el rango del arreglo
    int num_buscado = experimental::randint(int(arreglo[0]), int(arreglo[largo_arreglo-1]));    

    // Creacion de los arreglos Gap y Sample
    gap_Coding(arreglo, arreglo_gap, largo_arreglo);                    
    sample_Array(arreglo, arreglo_sample, m, b);

    delete[] arreglo;   // Borramos el arreglo original ya que no lo volveremos a usar

    // ###### Creacion Codigos ######
    // Calculamos la frecuencia de los numeros en el Gap
    Time_Interval* tiempo_frecuencias = new Time_Interval(); 
    unordered_map<int,int> frecuencias = frecuencias_gap_arr(arreglo_gap,largo_arreglo);
    double duracion_frec = tiempo_frecuencias->tiempo_transcurrido();
    resultados.tiempo_frecuencias.push_back(duracion_frec);

    // Crar vector de nodos para la creacion del arbol de huffman
    vector<Nodo_Huffman*> nodos;
    for (const auto& pair : frecuencias) {
        nodos.push_back(new Nodo_Huffman(pair.first, pair.second));
    }
    
    Time_Interval* tiempo_huffman = new Time_Interval();
    // Crear el arbol de huffman, devuelve el root
    Nodo_Huffman* root = crear_arbol_huffman(nodos);  
    
    // Generar codigos de Huffman, huffmanCodes es pasado como referencia. (Se llena al llamar a la funcion)
    unordered_map<int, string> huffmanCodes;
    crear_codigos_huffman(root, huffmanCodes);  
    
    // int largo_max = codigo_mas_largo(huffmanCodes); // Obtenemos el codigo de Huffman mas largo (Lo usaremos para ver si usamos 8bits o 16bits)

    int largo_max = 8;
    char *arreglo_gap_comprimido = new char[largo_arreglo]; 
    
    // Crea un mapa con los codigos + padding, el padding son 0 a la derecha hasta completar el largo necesario
    unordered_map<int, string> padded_huffman;
    padded_huffman = padding_codigos(huffmanCodes,largo_max);
    double duracion_huffman = tiempo_huffman->tiempo_transcurrido();
    resultados.tiempo_huffman.push_back(duracion_huffman);

    // Rellenar arreglo gap comprimido
    for (int i = 0; i<largo_arreglo;i++){
        bitset<32> codigo{padded_huffman[arreglo_gap[i]]};
        string binaryCode = codigo.to_string().substr(32 - largo_max);
        if (largo_max > 8){
            short int codigo_comprimido = static_cast<short int>(codigo.to_ulong());
        }
        char codigo_comprimido = static_cast<char>(codigo.to_ulong());
        arreglo_gap_comprimido[i] = codigo_comprimido;
    }

    delete[] arreglo_gap;   // Ahora se puede borrar el gap

    // ###### Busqueda en Sample ######
    // Busqueda binaria sobre el Sample
    pair<int, int> intervalo = binary_Search_Intervalos(arreglo_sample, m, num_buscado);

    // ###### Busqueda en Gap codificado ######
    Time_Interval* tiempo_busqueda_gap_cod = new Time_Interval();
    // Busqueda secuencial en el Gap
    search_in_gap_codificado(padded_huffman,arreglo_gap_comprimido, num_buscado, arreglo_sample[intervalo.first], intervalo.first * b, intervalo.second * b, largo_arreglo);
    double tiempo_busqueda = tiempo_busqueda_gap_cod->tiempo_transcurrido();
    resultados.tiempo_busqueda_gap_codificado.push_back(tiempo_busqueda);

    delete tiempo_busqueda_gap_cod;
    delete tiempo_frecuencias;
    delete tiempo_huffman;

    delete[] arreglo_gap_comprimido;
    delete[] arreglo_sample;
};