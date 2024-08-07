// metodos_arr.cpp
#include <random>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <bitset>

#include "../include/funciones.h"

using namespace std;

// Rellena el Arr de manera lineal
void crear_ArrLineal(int largo_arreglo, int *Arr, int epsilon){
    Arr[0] = rand() % 50;
    for (int i = 1; i < largo_arreglo; i++){
        Arr[i] = Arr[i - 1] + rand() % epsilon;
    }
}

// Rellena el Arr de manera normal
void crear_ArrNormal(int largo_arreglo, int *Arr, double mean, double stddev){
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<> d(mean, stddev);

    for (int i = 0; i < largo_arreglo; i++){
        Arr[i] = static_cast<int>(d(gen));
    }

    sort(Arr, Arr + largo_arreglo);
}

// Rellena el Arr_gap con la diferencia de numeros consecutivos
void gap_Coding(int *Arr, int *gapArr, int largo_arreglo){
    gapArr[0] = Arr[0];
    for(int i = 1; i < largo_arreglo; i++){
        gapArr[i] = Arr[i] - Arr[i-1];
    }
}

// Imprime un Arr de enteros
void print_Arr(int largo_arreglo, int *Arr){
    for (int i = 0; i < largo_arreglo; i++){
        cout << Arr[i] << " ";
    }
    cout << endl;
}

// Rellena el Arr_sample
void sample_Array(int *Arr, int *sample_Arr, int m, int b){
    sample_Arr[0] = Arr[0];
    int indice = 0;
    for(int i = 1; i < m; i++){
        sample_Arr[i] = Arr[indice+b];
        indice = indice + b;
    }
}

// Busca final para el numero, suma secuencialmente hasta encontrar el numero o hasta pasarse
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
        }else if (num_buscado < num_inicio){
            // cout << "Numero no encontrado" << endl;
            return -1;
        }
    }
    // cout << "Numero no encontrado" << endl;
    return -1;
}

// Misma que search_in_gap pero se le da un map para que pueda decodificar los codigos en el Arr_gap_codificado
int search_in_gap_codificado(unordered_map<int, string> canonicalCodes,char *arr_gap_comprimido, int num_buscado, int num_inicio, int index_inicio, int index_fin ,int largo_arreglo){
    unordered_map<string, int> reversed;

    for (unordered_map<int, string>::iterator i = canonicalCodes.begin(); i != canonicalCodes.end(); ++i)
        reversed[i->second] = i->first;
    
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

        string s{(bitset<8>(arr_gap_comprimido[i])).to_string()};
        
        // cout << "i: " << i << " " <<(bitset<8>(arr_gap_comprimido[i])).to_string() << " " <<reversed[s] << endl;

        num_inicio += reversed[s];
        if (num_buscado == num_inicio){
            // cout << "Numero encontrado" << endl;
            return i;
        }
    }
    // cout << "Numero no encontrado" << endl;
    return -1;
}  