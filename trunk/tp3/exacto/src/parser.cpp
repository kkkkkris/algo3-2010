
#include "parser.h"
#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace std;

list<int> parsearNodo(string nodo);

list<Grafo*> parsearInstancias(string entrada){
    list<Grafo*> grafos;
    map<int, list<int> > nodos;
    stringstream in(entrada);
    int pos = 0,nodos_t = 0, g = 1;
    while(!in.eof() && nodos_t != -1){
        string line;
        getline(in,line);
        if(pos < nodos_t){
            nodos[pos + 1] = parsearNodo(line);
            pos++;
            
        } else {
            if(!nodos.empty()) {
                cout << "\nGrafo #" << g << endl;
                g++;
                grafos.push_back(new Grafo(nodos));
                grafos.back()->mostrar();
            }
            nodos_t = atoi(line.c_str());
            if(nodos_t != -1) {
                pos = 0;
                nodos.clear();
            }
        }   
    }
    cout << "\n";
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
