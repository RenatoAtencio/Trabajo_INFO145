// metodos_var_entorno.cpp

#include <iostream>
#include <string>
#include "../include/funciones.h"

using namespace std;

int get_env_int(const char* var_name) { // Pasar a otro archivo
    const char* value = getenv(var_name);
    if (value != nullptr){
        return stoi(value);
    }
    cerr << "Variable de entorno: " << var_name << ", No definido" << endl;
    exit(-1);
}

double get_env_double(const char* var_name) { // Pasar a otro archivo
    const char* value = getenv(var_name);
    if (value != nullptr){
        return stod(value);
    }
    cerr << "Variable de entorno: " << var_name << ", No definido" << endl;
    exit(-1);
}
