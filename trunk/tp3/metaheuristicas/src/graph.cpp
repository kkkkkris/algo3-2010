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

set<int>* Grafo::maxClique() {
   // set<int>* cqMax= this->HC();
    return NULL;
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


int Grafo::getGrado(nodo_id i){
    Nodo* nodoi = &getNodo(i);
    return nodoi->grado;
}

int Grafo::getDensidad(nodo_id i){
    Nodo* nodoi = &getNodo(i);
    int res;
    if(nodoi->densidad!=-1){ //si densidad no es 0
        res=nodoi->densidad;
    }else{
        int g=this->getGrado(i);
        res=g;
        for(it_list it = nodoi->links.begin();it != nodoi->links.end();it++){
            res+=this->getGrado(*it);
        }
        res=res/(g+1);
    }
    return res;
}

void Grafo::setDensidad(nodo_id i,int densidad){
    Nodo* nodoi = &getNodo(i);
    nodoi->densidad = densidad;
}

bool Grafo::esClique(nodo_id i,set<nodo_id> Cq){
    for(it_set it = Cq.begin();it != Cq.end();it++){
        if(!this->sonAdyacentes(i,*it))return false;
    }
    return true;
}

set<int>* Grafo::getVecinos(nodo_id i){
    set<int> *s = new set<int>();
    Nodo* nodoi = &getNodo(i);
    for(it_list it=nodoi->links.begin();it!=nodoi->links.end();it++){
        s->insert(*it);
    }
    return s;
}

set<nodo_id>* Grafo::HC(){
    set<int> Cq,*p_Cq,*vecinos;
    //inicializo las densidades del grafo
    int d,nodomax=1,maxd=0,w;
    for(int i=1;i<=this->size;i++){
       d= this->getDensidad(i);
       assert(d>-1 && d<this->size);
       this->setDensidad(i,d);
       if(d>maxd){maxd=d;nodomax=i;}
    }
    priority_queue<int,vector<int>,greater<int> > S;
    vecinos=getVecinos(nodomax);
    for(set<int>::iterator it=vecinos->begin();it!=vecinos->end();it++){
        S.push(*it);
    }
    //ciclo ppal
    while(!S.empty()){
        w=S.top();
        if(esClique(w,Cq)){
            Cq.insert(w);
            vecinos=getVecinos(w);
            for(it_set it=vecinos->begin();it!=vecinos->end();it++){
                S.push(*it);
            }
        }
        S.pop();
    }
    p_Cq=&Cq;
    return p_Cq;
}
