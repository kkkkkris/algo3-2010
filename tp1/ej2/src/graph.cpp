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

Grafo::Grafo(map<int, list<int> > nodos_p){
    cicloDeHamilton = NO_SE_SABE;
    
    this->size = nodos_p.size();
    this->nodos = new Nodo[nodos_p.size()];
    
    //Empezamos suponiendo que se cumple la hipotesis
    bool hipotesisDirac = true;
    
    map<int, list<int> >::iterator it = nodos_p.begin();
    while(it != nodos_p.end()){
        assert(it->first > 0);
        this->nodos[it->first - 1] = Nodo(it->first, it->second);
        print(this->nodos[it->first - 1].toString());
        
        //Detectamos nodos con grado menor que 2
        int gradoDeNodo = (int)this->nodos[it->first - 1].links.size();
        if(gradoDeNodo < 2){
            cicloDeHamilton = NO_EXISTE;
        }
        
        if(gradoDeNodo < (size/2 + size%2)){
            hipotesisDirac = false;
        }
        it++;
    }
    
    //Veamos si se cumplen las condiciones del teorema de Dirac
    if(size >= 3 && hipotesisDirac){
        cicloDeHamilton = EXISTE;
    }
}

Grafo::~Grafo() {
    delete [] nodos;
}

Nodo &Grafo::getNodo(nodo_id id){
    assert(id <= this->size && id > 0);
    return this->nodos[id - 1];
}
        
bool Grafo::esHamilton() {
    assert(size > 2);

    //Si ya se que hay o no un ciclo, devuelvo la respuesta sin intentar encontrar el ciclo
    
    if(cicloDeHamilton == EXISTE){
        return true;
    }
    else if(cicloDeHamilton == NO_EXISTE){
        return false;
    }
    
    /** OPTIMIZACION - Probar si se cumplen las hipotesis del teorema de Ore (1960) **/
        
    /************************************************/


    //camino que hice a cada momento.
    stack<Nodo*> path;
    //ultimo nodo que visite en cada instancia del camino
    it_list* restantes = new it_list[this->size];
    //nodos que visite (1 a 1 con path)
    //bool * visitadas = new bool[this->size];
    //proximo nodo.
    it_list amiga;
    //nodo inicial
    Nodo* inicio = &getNodo(1);;
    path.push(inicio);
    /*for(int i = 0; i < this->size; i++)
        visitadas[i] = false;*/
    inicio->visitada = true;
    //print("Visito 1");
    restantes[0] = inicio->links.begin();
    while(path.size() > 0){
        Nodo * actual = path.top();
        amiga = restantes[path.size() - 1];
        
        //APILO
        // si no termine los proximos de actual
        while(!actual->links.empty() && !getNodo(*amiga).visitada) {//!visitadas[*amiga - 1]) {
            //mientras queden no haya visitado el proximo. Y 
            //apilar nodo.
            actual = &getNodo(*amiga);
            amiga = actual->links.begin();
            //print("Visito " << actual->id);
            actual->visitada = true;
            restantes[path.size()] = amiga;
            path.push(actual);
        }
        
        //DESAPILO
        while(actual->links.empty() || amiga == actual->links.end() || getNodo(*amiga).visitada) { //visitadas[*amiga - 1]) {
            //mientras me haya bloqueado o sea un nodo ya visitado.
            //desapilo/avanzo  nodos
            if(actual->links.empty() || amiga == actual->links.end()){
                //si consumi este nodo lo desapilo
                //print("Desvisito " << actual->id);
                actual->visitada = false;
                path.pop();
                if(!path.empty()){
                    actual = path.top();
                    restantes[path.size() - 1]++;
                    amiga = restantes[path.size() - 1];
                } else {
                    delete [] restantes;
                    //delete [] visitadas;
                    return false;
                }
            } else {
                //fue visitada pero no es la ultima
                if(path.size() == (unsigned int)this->size && *amiga == inicio->id){
                    //si llene el camino y la amiga es la primera
                    delete [] restantes;
                    //delete [] visitadas;
                    return true;
                }
                restantes[path.size() - 1]++;
                amiga = restantes[path.size() - 1];
            }
        }
        
    }
    delete [] restantes;
    //delete [] visitadas;
    return false;
}

/*
void Grafo::sortNodos(Nodo* v, int inicio, int fin){
    if(fin - inicio < 2){
        //swapeo los elementos de acuerdo a quien es mas grande
        if( v[inicio].links.size() > v[fin].links.size()){
            //swap
            Nodo aux    = v[inicio];
            v[inicio]   = v[fin];
            v[fin]      = aux;
        }
    }
    else{
        int mitad = (inicio + fin)/2;
        sortNodos(v, inicio, mitad);
        sortNodos(v, mitad+1, fin);
        
        //merge
        Nodo* sortedVector = new Nodo[fin-inicio+1];
        int i = inicio;
        int j = mitad+1;
        int k = 0;
        while(i<= mitad && j<=fin){
            if(v[i].links.size() < v[j].links.size()){
                sortedVector[k] = v[i];
                i++;
            }
            else{
                sortedVector[k] = v[j];
                j++;
            }
            k++;
        }
        
        while(i <= mitad){
            sortedVector[k] = v[i];
            i++;
            k++;
        }
     
        while(j <= fin){
            sortedVector[k] = v[j];
            j++;
            k++;
        }
 
        //restauramos v
        i = inicio;
        k = 0;
        while( i <= fin ){
            v[i] = sortedVector[k];
            i++;
            k++;
        }
        
        delete[] sortedVector;
    }
}*/
