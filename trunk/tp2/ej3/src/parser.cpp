
#include "parser.h"
#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace std;

list<int> parsearNodo(string nodo);

list<Grafo*> parsearInstancias(string entrada){
    list<Grafo*> grafos;
    list<int> nodos[] = NULL;
    int llaves[] = NULL;
    bool puertas[] = NULL;
    stringstream in(entrada);
    int i = 0, nodos_t = 0, puertas_t = 0, n = 0, p = 0, m = 0;
    while(!in.eof() && nodos_t != -1){
        string line;
        getline(in, line);
        if(nodos_t > 0){
            if (puertas_t > 0){
                stringstream par(line);
                int indice;
                par >> indice;
                par >> llaves[indice];
                puertas[(llaves[indice])] = true;
                puertas_t--;
            }
            else{
                nodos[i] = parsearNodo(line);
                nodos_t--;
                i++;
            }
        }
        else {
            if(!nodos.empty()) {
                grafos.push_back(new Grafo(n, m, p, nodos, llaves, puertas));
            }
            stringstream ss(line);
            ss >> n;
            ss >> p;
            ss >> m;
            nodos_t = n;
            puertas_t = p;
            if(nodos_t != -1) {
                if (nodos != NULL){
                    delete nodos;
                    delete llaves;
                    delete puertas;
                }
                nodos = new list<int>[n];
                llaves = new int[n];
                puertas = new bool[n];
                for(i = 0; i < n; i++){
                    llaves[i] = -1;
                    puertas[i] = false;
                }
                i = 0;
            }
        }   
    }
    return grafos;
}

list<int> parsearNodo(string nodo) {
    list<int> res;
    stringstream ss(nodo);
    int size;
    ss >> size;
    while(size > 0) {
        int other_node;
        ss >> other_node;
        res.push_back(other_node);
        size--;
    }
    return res;
}
