// metodos_archivos.cpp
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <chrono>
#include <iomanip>

#include "../include/funciones.h"

using namespace std;

// Crea el path+file_name para los archivos de salida
string crear_file_name(string folder,string titulo){
    const char* user_env = getenv("USER");
    if (!user_env) {
        user_env = "user";
    }

    auto now = chrono::system_clock::now();
    auto in_time_t = chrono::system_clock::to_time_t(now);
    stringstream ss;
    ss << put_time(localtime(&in_time_t), "%Y-%m-%d %Hh-%Mm-%Ss");

    string path = "out/" + folder + "/" + titulo + " - " + string(user_env) + " - " + ss.str() + ".csv";
    return path;
};

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

void escribir_resultados_csv(const vector<double>& resultados_lineal,const vector<double>& resultados_normal, const string& path, int largo_arreglo) {
    ofstream myfile;
    myfile.open(path);
    if (myfile.is_open()) {
        myfile << "Resultados arreglos con: n=" << largo_arreglo << " y num_buscado=random(rango_intervalo) \n";
        myfile << "Iteracion,Tiempo_lineal (ns),Tiempo_normal (ns)\n";  // Cabecera del CSV
        for (size_t i = 0; i < resultados_lineal.size(); i++) {
            myfile << i+1 << "," << resultados_lineal[i] << "," << resultados_normal[i] << "\n";
        }
        myfile.close();
    } else {
        cerr << "No se encontró el archivo" << endl;
    }
}