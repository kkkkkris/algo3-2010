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
    friend bool operator>(const Nodo &a,const Nodo &b);
    public:
        Nodo(){};
        Nodo(const nodo_id id, list<int> links, int orden):links(links), id(id), orden(orden) {};
        string toString() {
            stringstream ss;
            ss << "nodo #" << id << " {";
            for(it_list it = links.begin(); it != links.end(); it++) {
                if(it != links.begin())
                    ss << ", ";
                ss << *it;
            }
            ss << "}";
            return ss.str();
        }
        list<int> links;
        nodo_id id;
        int orden;
};

bool operator<(const Nodo &a,const Nodo &b){
    return a.links.size() < b.links.size();
}

Grafo::Grafo(){
    this->size = 0;
    this->nodos = NULL;
    this->m = 0;
}

Grafo::Grafo(map<int, list<int> > nodos_p){
    this->size = nodos_p.size();
    this->nodos = new Nodo[nodos_p.size()];
    this->m = 0;
    
    list<Nodo>* aux = new list<Nodo>();
    
    map<int, list<int> >::iterator it = nodos_p.begin();
    while(it != nodos_p.end()){
        assert(it->first > 0);
        this->m += it->second.size();
        this->nodos[it->first - 1] = Nodo(it->first, it->second, 0);
        aux->push_back(this->nodos[it->first - 1]);
        //print(this->nodos[it->first - 1].toString());
        it++;
    }
    this->m = m/2;
    
    aux->sort();
    int i = 1;
    for(list<Nodo>::reverse_iterator itA = aux->rbegin(); itA != aux->rend(); itA++){
        (this->nodos[itA->id - 1]).orden = i;
        i++;
    }
    delete aux;
}

Grafo::~Grafo() {
    delete [] nodos;
}

void Grafo::mostrar() {
    cout << "size: " << this->size << endl;
    cout << "nodos:" << endl;
    for(int i = 0; i < this->size; i++){
        cout << "       " << i+1 << " {";
        for(list<int>::iterator itL = (this->nodos[i]).links.begin(); itL != (this->nodos[i]).links.end(); itL++){
            if (itL != (this->nodos[i]).links.begin())
                cout << ", ";
            cout << (*itL);
        }
        cout << "}    orden " << (this->nodos[i]).orden << endl;
    }
}

void Grafo::maxClique(list<int>* nodos_ids, bool mejorado) {
    if(this->size == 0){
        //cout << "vacio" << endl;
        return;
    }
    else if(this->m == 0){
        //cout << "sin aristas" << endl;
        nodos_ids->push_back(1);
    }
    else if(2*(this->m) == (this->size)*(this->size-1)){
        //cout << "completo" << endl;
        for(int i = 0; i < this->size; i++)
            nodos_ids->push_back(i+1);
    }
    else{
        list<int>* R = new list<int> ();
        list<int>* P = new list<int> ();
        list<int>* X = new list<int> ();
        //this->copiarNodos(P);
        for(int i = 0; i < this->size; i++){
            P->push_back(i+1);
        }
        if(mejorado)
            this->cliqueMax(R, P, X, nodos_ids);
        else
            this->cliqueMaxSinMejoras(R, P, X, nodos_ids);
    }
}

void Grafo::copiarNodos(list<int>* copiaNodos) {
    for(int i = 0; i < this->size; i++){
        copiaNodos->push_back((this->nodos[i]).id);
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
*/

void Grafo::cliqueMaxSinMejoras(list<int>* R, list<int>* P, list<int>* X, list<int>* nodos_ids) {
    if(P->empty() && X->empty()){
        if(R->size() > nodos_ids->size()){
            nodos_ids->clear();
            for(list<int>::iterator itR = R->begin(); itR != R->end(); itR++){
                nodos_ids->push_back((*itR));
            }
            //cout << "nodos_ids = "; imprimirSecu(R); cout << "\n";
        }
        /*else{
            cout << "No es max: R = "; imprimirSecu(R); cout << "\n";
        }*/
    }
    else{
        for(list<int>::iterator itP = P->begin(); itP != P->end();){
            /*cout << "R = "; imprimirSecu(R);
            cout << "   P = "; imprimirSecu(P);
            cout << "   X = "; imprimirSecu(X); cout << "\n";*/
            list<int>* R2 = new list<int> (*R);
            R2->push_back((*itP));

            list<int>* P2;
            if(P->empty() || (this->nodos[(*itP)-1].links).empty()){
                P2 = new list<int> ();
            }
            else{
                P2 = new list<int> (*P);
                this->interseccion(P2, &(this->nodos[(*itP)-1].links));
            }

            list<int>* X2;
            if(X->empty() || (this->nodos[(*itP)-1].links).empty()){
                X2 = new list<int> ();
            }
            else{
                X2 = new list<int> (*X);
                this->interseccion(X2, &(this->nodos[(*itP)-1].links));
            }
            
            /*cout << "   R2 = "; imprimirSecu(R2);
            cout << "   P2 = "; imprimirSecu(P2);
            cout << "   X2 = "; imprimirSecu(X2); cout << "\n";*/
            cliqueMaxSinMejoras(R2, P2, X2, nodos_ids);

            delete R2;
            delete P2;
            delete X2;

            X->push_back((*itP));
            itP = P->erase(itP);
        }
    }
}

/*
    BronKerbosch2(R,P,X):
       if P and X are both empty:
           report R as a maximal clique
       choose a pivot vertex u in P ⋃ X
       for each vertex v in P \ N(u):
           BronKerbosch2(R ⋃ {v}, P ⋂ N(v), X ⋂ N(v))
           P := P \ {v}
           X := X ⋃ {v}
*/

void Grafo::cliqueMax(list<int>* R, list<int>* P, list<int>* X, list<int>* nodos_ids) {
    if(P->empty() && X->empty()){
        if(R->size() > nodos_ids->size()){
            nodos_ids->clear();
            for(list<int>::iterator itR = R->begin(); itR != R->end(); itR++){
                nodos_ids->push_back((*itR));
            }
            //cout << "nodos_ids = "; imprimirSecu(R); cout << "\n";
        }
        /*else
            cout << "No es max: R = "; imprimirSecu(R); cout << "\n";*/
    }
    else{
        int pivote = this->elegirPivote(P, X);
        //cout << "pivote = " << pivote << endl;
        list<int>* aux = new list<int>((*P));
        sacarVecinos(aux, pivote);
        //cout << "P - N(pivote) = "; imprimirSecu(aux); cout << "\n";
        for(list<int>::iterator itAux = aux->begin(); itAux != aux->end();){
            /*cout << "R = "; imprimirSecu(R);
            cout << "   P = "; imprimirSecu(P);
            cout << "   X = "; imprimirSecu(X); cout << "\n";*/
            list<int>* R2 = new list<int> (*R);
            R2->push_back((*itAux));

            list<int>* P2;
            if(P->empty() || (this->nodos[(*itAux)-1].links).empty()){
                P2 = new list<int> ();
            }
            else{
                P2 = new list<int> (*P);
                this->interseccion(P2, &(this->nodos[(*itAux)-1].links));
            }

            list<int>* X2;
            if(X->empty() || (this->nodos[(*itAux)-1].links).empty()){
                X2 = new list<int> ();
            }
            else{
                X2 = new list<int> (*X);
                this->interseccion(X2, &(this->nodos[(*itAux)-1].links));
            }
            
            /*cout << "   R2 = "; imprimirSecu(R2);
            cout << "   P2 = "; imprimirSecu(P2);
            cout << "   X2 = "; imprimirSecu(X2); cout << "\n";*/
            cliqueMax(R2, P2, X2, nodos_ids);

            delete R2;
            delete P2;
            delete X2;

            X->push_back((*itAux));
            P->remove((*itAux));
            itAux = aux->erase(itAux);
        }
    }
}

void Grafo::sacarVecinos(list<int>* l, int v){
    bool pertenece;
    for(list<int>::iterator itV = this->nodos[v - 1].links.begin(); itV != this->nodos[v - 1].links.end(); itV++){
        pertenece = false;
        for(list<int>::iterator itList = l->begin(); !pertenece && (itList != l->end()); itList++){
            pertenece = (*itV) == (*itList);
            if(pertenece)
                itList = l->erase(itList);
        }
    }
}

void Grafo::imprimirSecu(list<int>* l) {
    cout << "{";
    for(list<int>::iterator itI = l->begin(); itI != l->end(); itI++){
        if (itI != l->begin())
            cout << ", ";
        cout << (*itI);
    }
    cout << "}";
}

int Grafo::elegirPivote(list<int>* l1, list<int>* l2){
    int pivote = 0;
    for(list<int>::iterator itPiv = l1->begin(); itPiv != l1->end(); itPiv++){
        if(pivote == 0 || this->nodos[(*itPiv) - 1].orden < this->nodos[pivote - 1].orden)
            pivote = *itPiv;
    }
    for(list<int>::iterator itPiv = l2->begin(); itPiv != l2->end(); itPiv++){
        if(pivote == 0 || this->nodos[(*itPiv) - 1].orden < this->nodos[pivote - 1].orden)
            pivote = *itPiv;
    }
    return pivote;
}

void Grafo::interseccion(list<int>* l1, list<int>* l2) {
    bool pertenece;
    for(list<int>::iterator it1 = l1->begin(); it1 != l1->end();){
        pertenece = false;
        for(list<int>::iterator it2 = l2->begin(); !pertenece && (it2 != l2->end()); it2++){
            pertenece = (*it1) == (*it2);
        }
        if(!pertenece){
            it1 = l1->erase(it1);
        }
        else{
            it1++;
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

int Grafo::aristas(){
    return m;
}   
