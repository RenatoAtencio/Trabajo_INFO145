#include <queue>
#include <algorithm>
#include <bitset>
#include <iostream>

#include "../include/funciones.h"

using namespace std;

// Devuelve el largo del codigo de huffman mas largo
int codigo_mas_largo(const unordered_map<int, string>& huffmanCodes) {
    int max = 0;
    for (const auto& pair : huffmanCodes) {
        if (pair.second.length() > max) {
            max = pair.second.length();
        }
    }
    return max;
}

// Funcion para crear el arbol de huffman
Nodo_Huffman* crear_arbol_huffman(vector<Nodo_Huffman*>& nodos) {
    // Crear el minHeap
    priority_queue<Nodo_Huffman*, vector<Nodo_Huffman*>, comparar_nodos> minHeap;

    // Recorre el vector y añade los nodos a minHeap
    for (Nodo_Huffman* nodo : nodos) {
        minHeap.push(nodo);
    }
    
    // Iterar hasta que haya mas de un nodo en la cola
    while (minHeap.size() > 1) {
        // Sacar los 2 minimos
        Nodo_Huffman* hijo_izq = minHeap.top();
        minHeap.pop();
        Nodo_Huffman* hijo_der = minHeap.top();
        minHeap.pop();
        
        // Crear nuevo nodo
        Nodo_Huffman* newNode = new Nodo_Huffman(-1, hijo_izq->frecuencia + hijo_der->frecuencia);
        newNode->hijo_izq = hijo_izq;
        newNode->hijo_der = hijo_der;

        // Agregar nodo nuevo al heap
        minHeap.push(newNode);
    }
    
    // retornar la raiz
    return minHeap.top();
}

// Funcion para generar codigos de Huffman
void crear_codigos_huffman(Nodo_Huffman* root, unordered_map<int, string>& huffmanCodes, const string& code) {
    if (!root) return;
    
    // Si es un nodo hoja, asignar el codigo
    if (root->simbolo != -1) {
        huffmanCodes[root->simbolo] = code;
    }
    
    crear_codigos_huffman(root->hijo_izq, huffmanCodes, code + "0");
    crear_codigos_huffman(root->hijo_der, huffmanCodes, code + "1");
}

// Funcion para generar los codigos canonicos de Huffman
map<int, string> generar_canonico_huffman(const map<int, string>& huffmanCodes) {
    vector<pair<int, string>> sortedCodes(huffmanCodes.begin(), huffmanCodes.end());
    
    // Ordenar los códigos por longitud y luego por valor de símbolo
    sort(sortedCodes.begin(), sortedCodes.end(), [](const auto& a, const auto& b) {
        if (a.second.length() != b.second.length()) {
            return a.second.length() < b.second.length();
        }
        return a.first < b.first;
    });
    
    map<int, string> canonicalCodes;
    string code = "";
    
    for (size_t i = 0; i < sortedCodes.size(); ++i) {
        if (i == 0) {
            code = string(sortedCodes[i].second.length(), '0');
        } else {
            code = bitset<32>(bitset<32>(code).to_ulong() + 1).to_string();
            code = code.substr(32 - sortedCodes[i].second.length());
        }
        canonicalCodes[sortedCodes[i].first] = code;
    }
    
    return canonicalCodes;
}

unordered_map<int, string> padding_codigos(const unordered_map<int, string>& huffmanCodes, int fixedLength) {
    unordered_map<int, string> canonicalCodes;
    
    for (const auto& pair : huffmanCodes) {
        string paddedCode = pair.second;
        while (paddedCode.length() < fixedLength) {
            paddedCode += "0"; // Agregar ceros a la derecha
        }
        canonicalCodes[pair.first] = paddedCode;
    }

    return canonicalCodes;
}

map<int,int> frecuencias_gap_arr(int gap_arr[],int gap_lenght){
    map<int,int> frecuencias;

    for (int i=0 ; i < gap_lenght; i++ ){
        if (frecuencias.count(gap_arr[i]) > 0){
            frecuencias[gap_arr[i]] += 1; 
        }else{
            frecuencias.emplace(gap_arr[i],1);
        }
    }

    return frecuencias;
}