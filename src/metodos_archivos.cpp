// metodos_archivos.cpp
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

#include "../include/funciones.h"

using namespace std;

void crear_archivo_txt(const string& path) {
    ofstream myfile;
    myfile.open(path);
    myfile.close();
}

void escribir_resultados(const vector<double>& resultados, const string& path, int largo_arreglo, int numero_buscado, const string& tipo_arr) {
    ofstream myfile;
    myfile.open(path, ios::app);
    if (myfile.is_open()) {
        myfile << "Resultados arreglo " << tipo_arr << " con: n=" << largo_arreglo << " num=" << numero_buscado << endl;
        for (size_t i = 0; i < resultados.size(); i++) {
            myfile << "Iteracion " << i+1 << ": " << resultados[i] << " ns" <<endl;
        }
    } else {
        cout << "No se encontró el archivo" << endl;
    }
    myfile.close();
}

void escribir_resultados_csv(const vector<double>& resultados_lineal,const vector<double>& resultados_normal, const string& path, int largo_arreglo, int numero_buscado) {
    ofstream myfile;
    myfile.open(path);
    if (myfile.is_open()) {
        myfile << "Resultados arreglos con: n=" << largo_arreglo << " y num=" << numero_buscado << "\n";
        myfile << "Iteracion,Tiempo_lineal (ns),Tiempo_normal (ns)\n";  // Cabecera del CSV
        for (size_t i = 0; i < resultados_lineal.size(); i++) {
            myfile << i+1 << "," << resultados_lineal[i] << "," << resultados_normal[i] << "\n";
        }
        myfile.close();
    } else {
        cerr << "No se encontró el archivo" << endl;
    }
}