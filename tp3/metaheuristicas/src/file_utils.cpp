#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <set>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
/**
 * lee un archivo de texto y devuelve su contenido en un string
 * */
string leerArchivo(const char* filename){
    string res = "";
    string line;
    ifstream data(filename);
    if (data.is_open()) {
        while (! data.eof() ) {
            getline(data, line);
            res += line + '\n';
        }
        data.close();
    }
    return res;
}

/**
 * escribe content en el archivo, true si fallo
 */
bool escribirArchivo(const char* filename, string content) {
    ofstream salida(filename);
    if (salida.is_open()) {
        salida << content;
        salida.close();
    } else {
        return true;
    }
    return false;
}

/**Formatea el set "cliquemax" para escribir en Archivo**/
string toString(set<int>& cliquemax){
    stringstream ss;
    ss<<cliquemax.size()<<"\nN";
    for(set<int>::iterator it= cliquemax.begin();it != cliquemax.end();it++){
            ss<<" "<<(*it);
    }
    ss<<"\n";
       return ss.str();
}
