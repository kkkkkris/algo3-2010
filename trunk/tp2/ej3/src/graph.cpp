#include <list>
#include <map>
#include <queue>
#include <string>
#include <iostream>
#include <sstream>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include "graph.h"
#define print(a) cout << a << endl

typedef list<int>::iterator it_list;

using namespace std;
class Nodo{
    public:
        Nodo(){};
        Nodo(const int id, list<int> links, int llave, bool puerta):links(links), id(id), puerta(puerta), llave(llave) {};
        string toString() {
            stringstream ss;
            ss << "nodo #" << id << " [";
            for(it_list it = links.begin(); it != links.end(); it++) {
                if(it != links.begin())
                    ss << ", ";
                    ss << *it;
            }
            ss << "]";
            return ss.str();
        }
        list<int> links;
        int id;
        // si es distinta de -1 dice el id de la puerta que abre
        int llave;
        bool puerta;
};

Grafo::Grafo(int n, int m, int p, list<int>[] nodos, int[] llaves, bool[] puertas){
    this->n = n;
    this->m = m;
    this->p = p;
    this->nodos = new Nodo*[n];
    
    for(int i = 0; i < n; i++){
        this->nodos[i] = new Nodo(i+1, nodos[i], llaves[i], puertas[i]);
        print(this->nodos[i].toString());
    }

}

bool bfsMejorado(){
    bool marcados[this->n];
    int i;
    Nodo* nodo;
    for(i = 0; i < n; i++){
        marcados[i] = false;
    }
    queue<int> cola;

    marcados[0] = true;  
    cola.push(0);
    while (!cola.empty()){
        nodo = nodos[cola.pop()];
        for(it_list it = (nodo->links).begin(); it != (nodo->links).end(); it++){
           if (!marcados[(nodo->id)-1]){
                marcados[(nodo->id)-1]) = true;
                cola.push((nodo->id)-1);
           }
        }
    }

    return false;
}

Grafo::~Grafo() {
    delete [] nodos;
}

Nodo* Grafo::getNodo(nodo_id id){
    assert(id <= this->n && id > 0);
    return this->nodos[id-1];
}

/*
int Grafo::puertaAbierta(int llave){
    assert(id <= this->n && id > 0);
    return this->llaves[llave];
}
*/

