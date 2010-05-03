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

enum Estado {INDEFINIDO, ABIERTA, CERRADA};

using namespace std;
class Nodo{
    public:
        Nodo(){};
        Nodo(const int id, list<int>* links, int llave, bool puerta):links(links), id(id), llave(llave), puerta(puerta) {};
        string toString() {
            stringstream ss;
            ss << "nodo #" << id << " [";
            for(it_list it = links->begin(); it != links->end(); it++) {
                if(it != links->begin())
                    ss << ", ";
                    ss << *it;
            }
            ss << "]";
            return ss.str();
        }
        list<int>* links;
        int id;
        // si es distinta de -1 dice el id de la puerta que abre
        int llave;
        bool puerta;
};

Grafo::Grafo(int n, int m, int p, list<int>* nodos[], int llaves[], bool puertas[]){
    this->n = n;
    this->m = m;
    this->p = p;
    this->nodos = new Nodo*[n];
    
    for(int i = 0; i < n; i++){
        this->nodos[i] = new Nodo(i+1, nodos[i], llaves[i], puertas[i]);
    }

}

bool Grafo::bfsMejorado(){
    cout << "        n = " << this->n << ", m = " << this->m << ", p = " << this->p << endl;
    for(int i = 0; i < n; i++){
        cout << "        " << (this->nodos[i])->toString() << endl;
    }
    
    bool marcados[this->n];
    Estado puertas[this->n];
    int i;
    Nodo* nodo;
    for(i = 0; i < n; i++){
        marcados[i] = false;
        puertas[i] = INDEFINIDO;
    }
    queue<int> cola;

    marcados[0] = true;  
    cola.push(0);
    while (!cola.empty()){
        nodo = (this->nodos)[cola.front()];
        cola.pop();
        cout << "        Habitacion " << nodo->id << endl;
        // si hay una puerta cerrada
        if((nodo->puerta) && (puertas[(nodo->id)-1] != ABIERTA)){
            puertas[(nodo->id)-1] = CERRADA;
            cout << "        Puerta " << nodo->id << " cerrada" << endl;
        }
        // no hay puerta o ya está abierta
        else{
            // si hay llave
            if((nodo->llave) != -1){
                if(puertas[(nodo->llave)-1] == CERRADA){
                    cola.push((nodo->llave)-1);
                }
                puertas[(nodo->llave)-1] = ABIERTA;
                cout << "        Puerta " << nodo->llave << " abierta" << endl;
            }
            
            Nodo* aux = NULL;
            for(it_list it = (nodo->links)->begin(); it != (nodo->links)->end(); it++){
                aux = (this->nodos)[(*it)-1];
                // si llego a la salida devuelvo true
                if(aux->id == this->n){return true;}
                if(!marcados[(aux->id)-1]){
                    marcados[(aux->id)-1] = true;
                    cola.push((aux->id)-1);
                }
            }
        }
    }

    // en este caso no pasé por la salida
    return false;
}

Grafo::~Grafo() {
    for(int i = 0; i < n; i++){
        delete this->nodos[i];
    }
    delete [] (this->nodos);
}
