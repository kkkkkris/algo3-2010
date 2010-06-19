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
typedef int nodo_id;

using namespace std;
class Nodo{
    public:
        Nodo(){};
        Nodo(const nodo_id id, list<int> links):links(links), id(id), visitada(false),grado(links.size()),densidad(0){};
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
        nodo_id id;
        bool visitada;
        int grado;
        int densidad;

};

Grafo::Grafo(map<int, list<int> > nodos_p){
    this->size = nodos_p.size();
    this->nodos = new Nodo[nodos_p.size()];

    map<int, list<int> >::iterator it = nodos_p.begin();
    while(it != nodos_p.end()){
        assert(it->first > 0);
        this->nodos[it->first - 1] = Nodo(it->first, it->second);
        //print(this->nodos[it->first - 1].toString());
        it++;
    }
}

Grafo::~Grafo() {
    delete [] nodos;
}

set<int>* Grafo::maxClique() {
    //TODO
    return NULL;
}

Nodo &Grafo::getNodo(nodo_id id){
    assert(id <= this->size && id > 0);
    return this->nodos[id - 1];
}

bool Grafo::sonAdyacentes(nodo_id i, nodo_id j) {
    Nodo* nodoi = &getNodo(i);
    Nodo* nodoj = &getNodo(j);
    //nodo cuya lista se recorre
    Nodo* nodoMaestro;
    //ID del nodo cuya lista no recorremos
    nodo_id nodoEsclavoId;

    //Si son adyacentes, i figura en la lista de links de j, y viceversa, por lo que
    //es lo mismo recorrer cualquiera de las dos listas. Entonces recorro la mas chica
    //para mejorar un poquito el tiempo de respuesta
    if(nodoi->links.size() > nodoj->links.size()){
        nodoMaestro     = nodoj;
        nodoEsclavoId   = i;
    }
    else{
        nodoMaestro     = nodoi;
        nodoEsclavoId   = j;
    }

    //asumimos que no son adyacentes
    bool adyacentes = false;
    //recorremos la lista para ver si efectivametne son o no son adyacentes
    for(list<int>::iterator it = nodoMaestro->links.begin(); it != nodoMaestro->links.end() && !adyacentes; it++){
        if(*it == nodoEsclavoId){
            adyacentes = true;
        }
    }

    return adyacentes;
}


int Grafo::length(){
    return size;
}


int Grafo::getGrado(nodo_id i){
    Nodo* nodoi = &getNodo(i);
    return nodoi->grado;
}

int Grafo::getDensidad(nodo_id i){
    Nodo* nodoi = &getNodo(i);
    int res;
    if(nodoi->densidad){ //si densidad no es 0
        res=nodoi->densidad;
    }else{
        int g=this->getGrado(i);
        res=g;
        for(list<int>::iterator it = nodoi->links.begin();it != nodoi->links.end();it++){
            res+=this->getGrado(*it);
        }
        res=res/(g+1);
    }
    return res;
}

void Grafo::setDensidad(nodo_id i,int densidad){
    Nodo* nodoi = &getNodo(i);
    nodoi->densidad = this->getDensidad(i);
}

bool Grafo::esClique(nodo_id i,set<nodo_id> Cq){
    for(set<nodo_id>::iterator it = Cq.begin();it != Cq.end();it++){
        if(!this->sonAdyacentes(i,*it))return false;
    }
    return true;
}

set<nodo_id>* Grafo::HC(){
//TODO
 return NULL;
}
