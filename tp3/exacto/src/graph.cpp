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
        Nodo(const nodo_id id, list<int> links):links(links), id(id), visitada(false) {};
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
};

Grafo::Grafo(){
    this->size = 0;
    this->nodos = NULL;
}

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

void Grafo::maxClique(list<int>* nodos_ids) {
    list<Nodo>* R = new list<Nodo> ();
    list<Nodo>* P = new list<Nodo> ();
    list<Nodo>* X = new list<Nodo> ();
    this->copiarNodos(P);
    this->cliqueMax(R, P, X, nodos_ids);
}

void Grafo::copiarNodos(list<Nodo>* copiaNodos) {
    for(int i = 0; i < this->size; i++){
        copiaNodos->push_back(this->nodos[i]);
    }
}

/*
BronKerbosch1(R,P,X):
       if P and X are both empty:
           report R as a maximal clique
       for each vertex v in P:
           BronKerbosch1(R ⋃ {v}, P ⋂ N(v), X ⋂ N(v))
           P := P \ {v}
           X := X ⋃ {v}

BronKerbosch2(R,P,X):
       if P and X are both empty:
           report R as a maximal clique
       choose a pivot vertex u in P ⋃ X
       for each vertex v in P \ N(u):
           BronKerbosch2(R ⋃ {v}, P ⋂ N(v), X ⋂ N(v))
           P := P \ {v}
           X := X ⋃ {v}
*/

void Grafo::cliqueMax(list<Nodo>* R, list<Nodo>* P, list<Nodo>* X, list<int>* nodos_ids) {
    cout << "principio" << endl;
    if(P->empty() && X->empty()){
        cout << "if" << endl;
        if(R->size() > nodos_ids->size()){
            for(list<Nodo>::iterator it = R->begin(); it != R->end(); it++){
                nodos_ids->push_back(it->id);
            }
        }
    }
    else{
        cout << "else" << endl;
        for(list<Nodo>::iterator it = P->begin(); it != P->end(); it++){
            cout << "for" << endl;
            list<Nodo>* R2 = new list<Nodo> (*R);
            R2->push_back((*it)); // genera segmentation fault
            cout << "ok1" << endl;
            list<Nodo>* P2;
            if(P->empty() || (it->links).empty()){
                P2 = new list<Nodo> ();
            }
            else{
                P2 = new list<Nodo> (*P);
                this->interseccion(P2, &(it->links));
            }
            cout << "ok2" << endl;
            list<Nodo>* X2;
            if(X->empty() || (it->links).empty()){
                X2 = new list<Nodo> ();
            }
            else{
                X2 = new list<Nodo> (*X);
                this->interseccion(X2, &(it->links));
            }
            cout << "ok3" << endl;
            cliqueMax(R2, P2, X2, nodos_ids);
            
            delete R2;
            delete P2;
            delete X2;

            P->erase(it);
            X->push_back((*it));
            cout << "end for" << endl;
        }
    }
    cout << "final" << endl;
}

void Grafo::interseccion(list<Nodo>* l1, list<int>* l2) {
    bool pertenece;
    
    for(list<Nodo>::iterator it1 = l1->begin(); it1 != l1->end(); it1++){
        pertenece = false;
        for(list<int>::iterator it2 = l2->begin(); !pertenece && (it2 != l2->end()); it2++){
            pertenece = (it1->id) == (*it2);
        }
        if(!pertenece){
            l1->erase(it1);
        }
    }
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
