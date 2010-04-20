#include <list>
#include <map>
#include <stack>
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
    this->nodos = new Nodo[n];
    
    for(int i = 0; i < n; i++){
        this->nodos[i] = new Nodo(i+1, nodos[i], llaves[i], puertas[i]);
    }
    
    map<int, list<int> >::iterator it = nodos.begin();
    while(it != nodos.end()){
        assert(it->first > 0);
        this->nodos[it->first - 1] = Nodo(it->first, it->second);
        print(this->nodos[it->first - 1].toString());
        it++;
    }  
}

bool bfsMejorado(){
    return false;
}

Grafo::~Grafo() {
    delete [] nodos;
}

Nodo &Grafo::getNodo(nodo_id id){
    assert(id <= this->size && id > 0);
    return this->nodos[id - 1];
}
           
