
#include "parser.h"
#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace std;

list<Grafo*> parsearInstancias(string entrada){
    list<Grafo*> grafos;
    list<int> nodos[] = NULL;
    int llaves[] = NULL;
    bool puertas[] = NULL;
    stringstream in(entrada);
    int i = 0, aristas = 0, puertas_t = 0, n = 0, p = 0, m = 0;
    while(!in.eof() && aristas != -1){
        string line;
        getline(in, line);
        if(aristas > 0){
            if (puertas_t > 0){
                stringstream par(line);
                int indice;
                par >> indice;
                par >> llaves[indice];
                puertas[(llaves[indice])] = true;
                puertas_t--;
            }
            else{
                stringstream nodo(line);
                int n1, n2;
                nodo >> n1;
                nodo >> n2;
                nodos[n1].push_back(n2);
                nodos[n2].push_back(n1);
                aristas--;
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
            aristas = n;
            puertas_t = p;
            if(aristas != -1) {
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

