#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

/**
 * Lee la sigueinte línea de un archivo de texto.
 * Asigna a b y a n los valores que corresponden.
 * Devuelve false si no se puede realizar la lectura o si la línea contiene un -1. 
 * */
bool leerArchivo(const char* filename, long long int& b, long long int& n){
    bool res = false;
    string line, str_b, str_n;
    ifstream data(filename);
    if (data.is_open()) {
        getline(data, line);
        stringstream ss(line);
        ss >> b;
        ss >> n;
        //stringstream(line) >> str_b >> str_n;
        //b = atoll(str_b.c_str());
        //n = atoll(str_n.c_str());
        //sscanf(line.c_str(), "%lld", &b);
        //sscanf(line.c_str(), "%lld", &n);
        if ((b != -1) && (n != -1)) {
            res = true;
        }
        data.close();
    }
    return res;
}

/**
 * Escribe en el archivo el valor pasado como parámetro.
 * Devuelve false si falla.
 */
bool escribirArchivo(const char* filename, string res) {
    ofstream salida(filename);
    bool ret = false;
    if (salida.is_open()) {
        salida << res;
        salida.close();
        ret = true;
    }
    return false;
}
