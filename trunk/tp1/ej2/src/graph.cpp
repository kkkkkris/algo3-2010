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
    //nodo inicial
    Nodo* inicio = &getNodo(1);;
    path.push(inicio);
    inicio->visitada = true;
    //print("Visito 1");
    restantes[0] = inicio->links.begin();
    while(path.size() > 0){
        //nodo actualmente visitado
        Nodo * actual = path.top();
        it_list amiga = restantes[path.size() - 1];
        
        //APILO
        // si no termine los proximos de actual
        while(!actual->links.empty() && !getNodo(*amiga).visitada) {
            //mientras queden y no haya visitado el proximo. 
            // y tenga amigas 
            //apilar nodo.
            actual = &getNodo(*amiga);
            amiga = actual->links.begin();
            actual->visitada = true;
            restantes[path.size()] = amiga;
            path.push(actual);
        }
        
        //DESAPILO
        while(actual->links.empty() || amiga == actual->links.end() || getNodo(*amiga).visitada) { 
            //mientras me haya bloqueado o sea un nodo ya visitado.
            //desapilo/avanzo  nodos
            if(actual->links.empty() || amiga == actual->links.end()){
                //si consumi este nodo lo desapilo
                actual->visitada = false;
                path.pop();
                if(!path.empty()){
                    actual = path.top();
                    restantes[path.size() - 1]++;
                    amiga = restantes[path.size() - 1];
                } else {
                    delete [] restantes;
                    return false;
                }
            } else {
                //fue visitada pero no es la ultima
                if(path.size() == (unsigned int)this->size && *amiga == inicio->id){
                    //si llene el camino y la amiga es la primera
                    delete [] restantes;
                    return true;
                }
                restantes[path.size() - 1]++;
                amiga = restantes[path.size() - 1];
            }
        }
        
    }
    delete [] restantes;
    return false;
}
