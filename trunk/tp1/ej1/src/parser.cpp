
#include "parser.h"
#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace std;

void parsearInstancia(string linea, long long int* res);

list<long long int> parsearInstancias(string entrada){
    list<long long int> instancias;
    stringstream in(entrada);
    while(!in.eof()){
        string line;
        getline(in, line);
        long long int* res = new long long int[2];
        parsearInstancia(line, res);
        instancias.push_back(res[0]);
        instancias.push_back(res[1]);
        delete (res);
    }
    return instancias;
}

void parsearInstancia(string linea, long long int* res) {
    stringstream ss(linea);
    ss >> res[0];
    ss >> res[1];
}

