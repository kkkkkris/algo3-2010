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
#
using namespace std;


/**
*Funcion que da la prioridad a la cola de prioridad de densidad de nodos
*/
struct comparison{
  bool operator()( Nodo &a, Nodo &b) {
    return a.densidad<b.densidad;
  }
};
struct candidato {
  nodo_id nuevo;
  nodo_id viejo;
  float puntaje; 
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
    for(it_set it = nodoi->links.begin();it != nodoi->links.end();it++){
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
    for(it_set it=nodoi->links.begin();it!=nodoi->links.end();it++){
       nodoj=&getNodo(*it);
       if(Cq.count(*it)==0 && !(nodoj->encolado)){
           nodoj->encolado=true;
           S.push(*nodoj);;
        //   cout<<"S + "<<(*it)<<endl;
       }
    }
}
/**
* Imprime un set por pantalla
*/
ostream& operator<<(ostream& out, const set<int>& S) {
    for(it_set it=S.begin();it!=S.end();it++){
        out<<*it<<",";
    }
	return out;
}

/**
*HEURISTICA CONSTRUCTIVA
*/
set<nodo_id> Grafo::HC(){
    set<nodo_id>Cq;
    pqDelta S;
    nodo_id nodoMax;
    //Inicializo las densidades del grafo
    nodoMax = generarDensidad();
    //Genero el conjunto maximo Clique resultado
    Cq.insert(nodoMax);
    //Genero la cola de prioridad S de nodos candidatos ordenados por su densidad
    merge(nodoMax,S,Cq);
    return this->expandClique(Cq,S);
}

/** Dado un clique y un conjunto de candidatos, expande el grafo clique */
set<nodo_id> Grafo::expandClique(set<nodo_id>& Cq,pqDelta S) {
    while(!S.empty()){
        nodo_id w = S.top().id;
        if(esClique(w,Cq)){
      // cout<<"S.top =nodo "<<w <<endl;
            Cq.insert(w);
            merge(w,S,Cq);
        }
        S.pop();
    }
    return Cq;
}

/** HEURISTICA LOCAL ****************************************/

set<nodo_id> Grafo::HL() {
    set<nodo_id> cq = this->HC();
    bool movi = true;
    while(!movi){
        //MUEVO (YA ESTOY EXPANDIDO)
        candidato c = this->findCandidato(cq);
        if(c.puntaje > 0) {
            cq.erase(c.viejo);
            cq.insert(c.nuevo);
        } else {
            movi = false;
        }
        
        //SI ME MOVI ME EXPANDO.
        if(movi) {
            pqDelta S;
            this->merge(*cq.begin(),S,cq);
            this->expandClique(cq, S);
        }
    }
    return cq;
}

/** dado un clique el nodo con mayor puntaje que es vecino de todos 
 * menos uno */
candidato Grafo::findCandidato(const set<nodo_id>& cq) {
    candidato res;
    res.puntaje = 0;
    set<nodo_id> posibles = this->vecindad(cq);
    for(it_set v = posibles.begin(); v != posibles.end(); v++) {
        nodo_id op = this->findOpuesto(*v, cq);
        
        // c es el opuesto a v
        if(getNodo(*v).densidad - getNodo(op).densidad > res.puntaje) {
            // poner a v es mejor que dejar a c. y mejor que cambiar
            // a los anteriores. (res.puntaje >= 0)
            res.nuevo = *v;
            res.viejo = op;
            res.puntaje = getNodo(*v).densidad - getNodo(op).densidad;
        }
    }
    return res;
}

nodo_id Grafo::findOpuesto(nodo_id v, const set<nodo_id>& cq) {
    it_set c = cq.begin();
    set<nodo_id> l = getNodo(*c).links;
    //mientras este nodo lo contenga.
    while(this->sonAdyacentes(*c, v)) {
        c++;
        set<nodo_id> l = getNodo(*c).links;
    }
    return *c;
}
/** obtiene todos los nodos que son vecinos de todos menos uno. */
set<nodo_id> Grafo::vecindad(const set<nodo_id> & cq) {
    multiset<nodo_id> vecindad;
    set<nodo_id> posibles;
    //de todos los posibles nodos vecinos.
    for(it_set c = cq.begin(); c != cq.end(); c++){
        Nodo n = this->getNodo(*c);
        for(it_set v = n.links.begin(); v != n.links.end(); v++) {
            vecindad.insert(*v);
        }
    }
    //me quedo con aquellos que son vecinos de todos menos 1.
    for(multiset<nodo_id>::iterator v = vecindad.begin(); v != vecindad.end(); v++) {
        if(vecindad.count(*v) == cq.size() - 1) {
            posibles.insert(*v);
        }
    }
    return posibles;
}

bool Grafo::validar(const set<nodo_id> &cq) {
    set<nodo_id> temp;
    for(it_set c = cq.begin(); c!= cq.end(); c++) {
        if(!this->esClique(*c, temp)) {
            return false;
        }
        temp.insert(*c);
    }
    return true;
}
