#include <list>
#include <map>
#include <stack>
#include <string>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include "graph.h"
#define print(a) cout << a << endl

typedef  set<nodo_id>::iterator it_set;
using namespace std;


Grafo::Grafo(map<int, list<int> > nodos_p){
    this->size = nodos_p.size();
    this->nodos = new Nodo[nodos_p.size()];
    this->adj = new bool[this->size*this->size];
    for(int i = 0; i < this->size*this->size; i++) {
        this->adj[i] = false;
    }
    map<int, list<int> >::iterator it = nodos_p.begin();
    while(it != nodos_p.end()){
        assert(it->first > 0);
        this->nodos[it->first - 1] = Nodo(it->first, it->second);
        for(it_list lit = it->second.begin(); lit != it->second.end(); lit++) {
            //matriz simetrica.
            this->adj[((it->first - 1)*this->size) + *lit - 1] = true;
            this->adj[((*lit - 1)*this->size) + it->first - 1] = true;
        }
        //print(this->nodos[it->first - 1].toString());
        it++;
    }
}

Grafo::~Grafo() {
    delete [] nodos;
}

Nodo &Grafo::getNodo(nodo_id id){
    assert(id <= this->size && id > 0);
    return this->nodos[id-1];
}

bool Grafo::sonAdyacentes(nodo_id i, nodo_id j) {
    return this->adj[(i-1)*this->size + j - 1];
}


int Grafo::length(){
    return size;
}


/** calcula la densidad para un nodo. */
int Grafo::getDensidad(nodo_id i){
    Nodo* nodoi = &getNodo(i);
    int res = 0;
    if( nodoi->densidad != -1){ //si densidad no es 0
        res=nodoi->densidad;
    }else{
        int g = nodoi->grado;
        for(it_list it = nodoi->links.begin();it != nodoi->links.end();it++){
            res += this->getNodo(*it).grado;
        }
        res= res / g;
    }
    return res;
}
/** dado el id de un nodo le pone su densidad y devuelve la densidad 
 * que le puso. */
int Grafo::setDensidad(nodo_id i){
    Nodo* nodoi = &getNodo(i);
    int densidad = this->getDensidad(i);
    nodoi->densidad = densidad;
    return densidad;
}

/** dice si agregar el nodo_id i al clique cq sigue siendo clique*/
bool Grafo::esClique(nodo_id i,set<nodo_id> Cq){
    for(it_set it = Cq.begin();it != Cq.end();it++){
        if(!this->sonAdyacentes(i,*it))return false;
    }
    return true;
}

/** Setea las densidad a todos y devuelve el Id del nodo con mas densidad*/
Nodo& Grafo::generarDensidad() {
    int nodomax=1, maxd=0;
    for(int i = 1;i <= this->size; i++){
       int d = this->setDensidad(i);
       if(d > maxd) {
           maxd = d;
           nodomax = i;
       }
    }
    return getNodo(nodomax);
}



set<nodo_id>* Grafo::HC(){
    set<int>* Cq = new set<int>();
    //inicializo las densidades del grafo
    Nodo nodoMax = generarDensidad();
    
    //Genero la cola de prioridad de nodos ordenados por su densidad
    //ARREGLAR: NO SE PRIORIZA POR DENSIDAD.
    list<nodo_id> vecinos = nodoMax.links;
    priority_queue<int,vector<int>,greater<int> > S;
    for(it_list it = vecinos.begin(); it != vecinos.end(); it++){
        S.push(*it);
    }
    //ciclo ppal
    while(!S.empty()){
        nodo_id w = S.top();
        if(esClique(w,*Cq)){
            Cq->insert(w);
            vecinos = getNodo(w).links;
            for(it_list it=vecinos.begin(); it != vecinos.end(); it++){
                S.push(*it);
            }
        }
        S.pop();
    }
    //???? estas devolviendo una referencia a memoria local. USAR NEW.
    return Cq;
}
