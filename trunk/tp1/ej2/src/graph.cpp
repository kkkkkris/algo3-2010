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
        Nodo(const nodo_id id, list<int> links):links(links), id(id) {};
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
};

Grafo::Grafo(map<int, list<int> > nodos_p){
    this->size = nodos_p.size();
    this->nodos = new Nodo[nodos_p.size()];
    map<int, list<int> >::iterator it = nodos_p.begin();
    while(it != nodos_p.end()){
        assert(it->first > 0);
        this->nodos[it->first - 1] = Nodo(it->first, it->second);
        print(this->nodos[it->first - 1].toString());
        it++;
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
    assert(size > 1);
    //camino que hice a cada momento.
    stack<Nodo*> path;
    //ultimo nodo que visite en cada instancia del camino
    it_list* restantes = new it_list[this->size];
    //nodos que visite (1 a 1 con path)
    bool * visitadas = new bool[this->size];
    //proximo nodo.
    it_list amiga;
    //nodo inicial
    Nodo* inicio;
    
    inicio = &getNodo(1);
    path.push(inicio);
    for(int i = 0; i < this->size; i++)
        visitadas[i] = false;
    visitadas[0] = true;
    print("Visito 1");
    restantes[0] = inicio->links.begin();
    while(path.size() > 0){
        Nodo * actual = path.top();
        amiga = restantes[path.size() - 1];
        
        //APILO
        // si no termine los proximos de actual
        while(!actual->links.empty() && !visitadas[*amiga - 1]) {
            //mientras queden no haya visitado el proximo. Y 
            //apilar nodo.
            actual = &getNodo(*amiga);
            amiga = actual->links.begin();
            print("Visito " << actual->id);
            visitadas[actual->id - 1] = true;
            restantes[path.size()] = amiga;
            path.push(actual);
        }
        
        //DESAPILO
        while(actual->links.empty() || amiga == actual->links.end() || visitadas[*amiga - 1]) {
            //mientras me haya bloqueado o sea un nodo ya visitado.
            //desapilo/avanzo  nodos
            if(actual->links.empty() || amiga == actual->links.end()){
                //si consumi este nodo lo desapilo
                print("Desvisito " << actual->id);
                visitadas[actual->id - 1] = false;
                path.pop();
                if(!path.empty()){
                    actual = path.top();
                    restantes[path.size() - 1]++;
                    amiga = restantes[path.size() - 1];
                } else {
                    delete [] restantes;
                    delete [] visitadas;
                    return false;
                }
            } else if(visitadas[*amiga - 1]){
                //fue visitada pero no es la ultima
                if(path.size() == (unsigned int)this->size && *amiga == inicio->id){
                    //si llene el camino y la amiga es la primera
                    delete [] restantes;
                    delete [] visitadas;
                    return true;
                }
                restantes[path.size() - 1]++;
                amiga = restantes[path.size() - 1];
            }
        }
        
    }
    delete [] restantes;
    delete [] visitadas;
    return false;
}
