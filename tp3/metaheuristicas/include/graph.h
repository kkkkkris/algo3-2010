#ifndef __GRAPH__
#define __GRAPH__
#include "nodo.h"
#include <string>
#include <list>
#include <map>
#include <set>
#include <queue>
using namespace std;

class Grafo {
    public:
        Grafo(map<int, list<int> >);
        ~Grafo();
        int length();
        set<int>* HC();
        set<int>* HL();
        set<int>* HT();
    private:
        //datos
        Nodo* nodos;
        int size;
        bool *adj;
        //metodos privados
        Nodo& getNodo(int nodo_id);
        bool sonAdyacentes(int i, int j);
        int getDensidad(int nodo_id);
        int setDensidad(int nodo_id);
        Nodo& generarDensidad();
        bool esClique(int nodo_id, set<int> Cq);
        class GreatNodo {
            public:
                GreatNodo(Grafo* p) : parent(p) {}
                bool operator() (const int& lhs, const int&rhs) const;
            private:
                Grafo* parent;
        };
        set<nodo_id>* expandClique(set<nodo_id>* ,priority_queue<int,vector<int>,GreatNodo>);
        
};


#endif //__GRAPH__
