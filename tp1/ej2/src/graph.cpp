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

bool chequeeListaEnN(const it_list *restantes , it_list ultimo, int n);

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

Nodo &Grafo::getNodo(nodo_id id){
    assert(id <= this->size && id > 0);
    return this->nodos[id - 1];
}
        
bool Grafo::esHamilton() {
    assert(size > 1);
    stack<Nodo*> path;
    it_list* restantes = new it_list[this->size];
    bool * visitadas = new bool[this->size];
    it_list amiga;
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
            //mientras no haya visitado el proximo. Y QUEDEN
            //avanzar nodo
            actual = &getNodo(*amiga);
            amiga = actual->links.begin();
            print("Visito " << actual->id);
            visitadas[actual->id - 1] = true;
            restantes[path.size()] = amiga;
            path.push(actual);
        }
        
        //DESAPILO
        while(actual->links.empty() || amiga == actual->links.end() || visitadas[*amiga - 1]) {
            if(actual->links.empty() || amiga == actual->links.end()){
                print("Desvisito " << actual->id);
                visitadas[actual->id - 1] = false;
                path.pop();
                if(!path.empty()){
                    actual = path.top();
                    restantes[path.size() - 1]++;
                    amiga = restantes[path.size() - 1];
                } else {
                    return false;
                }
            } else if(visitadas[*amiga - 1]){
                //fue visitada pero no es la ultima
                restantes[path.size() - 1]++;
                amiga = restantes[path.size() - 1];
                if(path.size() == (unsigned int)this->size && *amiga == inicio->id){
                    //si llene el camino y la amiga es la primera
                    return true;
                }
            }
        }
        
    }
    return false;
}
bool chequeeListaEnN(const it_list *restantes , it_list ultimo, int n){
    print("viendo si en el nivel " << n - 1 <<" es el \"proximo\" del ultimo.");
    it_list ultimo_que_chequee = restantes[n - 1];
    ultimo_que_chequee--;
    print("pep");
    return ultimo_que_chequee == ultimo;
}
