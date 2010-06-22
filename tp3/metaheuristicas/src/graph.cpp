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

using namespace std;


/**
*Funcion que da la prioridad a la cola de prioridad de densidad de nodos
*/
struct comparison{
  bool operator()( Nodo &a, Nodo &b) {
    return a.densidad<b.densidad;
  }
};


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

/**
*Devuelve el grado del nodo
*/
int Grafo::getGrado(nodo_id i){
    Nodo* nodoi = &getNodo(i);
    return nodoi->grado;
}
/**
*Calcula y setea la densidad del nodo i
*/
float Grafo::setDensidad(nodo_id i){
    assert(i <= this->size && i > 0);
    float res;
    int g;
    Nodo* nodoi = &getNodo(i);
    g=this->getGrado(i);
    res=g;
    for(it_list it = nodoi->links.begin();it != nodoi->links.end();it++){
        res+=this->getGrado(*it);
    }
    res=res/(g+1);
    nodoi->densidad=res;
    return res;
}


/** dice si agregar el nodo_id i al clique cq sigue siendo clique*/
bool Grafo::esClique(nodo_id i,set<nodo_id>& Cq){
    for(it_set it = Cq.begin();it != Cq.end();it++){
        if(!this->sonAdyacentes(i,*it))return false;
    }
    return true;
}

/** Setea las densidad a todos y devuelve el Id del nodo con mas densidad*/
nodo_id Grafo::generarDensidad() {
    int nodomax=1;
    float d,maxd=0;
    for(int i = 1;i <= this->size; i++){
       d= this->setDensidad(i);
       assert(d>=0 && d<=this->size);
       if(d > maxd) {
           maxd = d;
           nodomax = i;
       }
      // cout<<"la densidad del nodo "<<i<<"es :"<<d<<endl;
    }
    return nodomax;
}

/**
*Agrega a la cola de prioridad S los vecinos de i que no estan en Cq ni fueron encolados en S.
*/
void Grafo::merge(nodo_id i,pqDelta& S,set<int>& Cq){
    Nodo* nodoi = &getNodo(i);
    Nodo* nodoj ;
    for(it_list it=nodoi->links.begin();it!=nodoi->links.end();it++){
       nodoj=&getNodo(*it);
       if(Cq.count(*it)==0 && !(nodoj->encolado)){
           nodoj->encolado=true;
           S.push(*nodoj);;
        //   cout<<"S + "<<(*it)<<endl;
       }
    }
}
/**
*Imprime un set por pantalla
*/
void Grafo::set_to_String(set<int>& S){
    for(it_set it=S.begin();it!=S.end();it++){
        cout<<*it<<",";
    }
        cout<<endl;
}


/**
*HEURISTICA CONSTRUCTIVA
*/
set<nodo_id>* Grafo::HC(){
    cout<<" \n GRAFO : "<<endl;
    //Inicializo las densidades del grafo
    nodo_id nodoMax = generarDensidad();

    //Genero el conjunto maximo Clique resultado
    set<nodo_id> Cq,*p_Cq;
    Cq.insert(nodoMax);
    p_Cq=&Cq;
    //Genero la cola de prioridad S de nodos candidatos ordenados por su densidad
    pqDelta S;
    merge(nodoMax,S,Cq);

    return this->expandClique(p_Cq, S);
}

/** dado un clique y un conjunto de candidatos, expande el grafo clique */
set<nodo_id>* Grafo::expandClique(set<nodo_id>* Cq,pqDelta S) {
    //ciclo ppal
    while(!S.empty()){
        nodo_id w = S.top().id;//hay alguna razon para declarar un nuevo nodo_id en cada iteracion?
        if(esClique(w,*Cq)){
      //      cout<<"S.top =nodo "<<w <<endl;
            Cq->insert(w);
            merge(w,S,*Cq);
        }
        S.pop();
    }
    cout<<"Clique max : ";
    set_to_String(*Cq);
    return Cq;
}

/*
bool Grafo::GreatNodo::operator()(const nodo_id& left, const nodo_id& right) const{
    return parent->getNodo(left).densidad > parent->getNodo(right).densidad;
}
*/
set<nodo_id>* Grafo::HL() {
    return NULL;
}
