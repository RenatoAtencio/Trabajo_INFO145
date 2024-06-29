// metodos_var_entorno.cpp
#include <iostream>
#include <string>
#include "../include/funciones.h"

using namespace std;

/*
    Funciones para cargar las variables de entorno
*/

void err_msg(const char* var_name){
    cerr << "Variable de entorno: " << var_name << ", No definida o cargada" << endl;
}

int get_env_int(const char* var_name) {             
    const char* value = getenv(var_name);
    if (value != nullptr){
        return stoi(value);
    }
    err_msg(var_name);
    exit(EXIT_FAILURE);
}

double get_env_double(const char* var_name) {       
    const char* value = getenv(var_name);
    if (value != nullptr){
        return stod(value);
    }
    err_msg(var_name);
    exit(EXIT_FAILURE);
}
