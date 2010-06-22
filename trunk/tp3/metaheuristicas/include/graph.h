#ifndef __GRAPH__
#define __GRAPH__
#include "nodo.h"
#include <string>
#include <list>
#include <map>
#include <set>
#include <queue>

using namespace std;
struct comparison;

typedef  set<nodo_id>::iterator it_set;
typedef priority_queue<Nodo,vector<Nodo>,comparison> pqDelta ;

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
        int getGrado(int nodo_id);
        bool sonAdyacentes(int i, int j);
        float setDensidad(int nodo_id);
        nodo_id generarDensidad();
        bool esClique(int nodo_id, set<int>& Cq);
        void merge(int nodo_id,pqDelta& S,set<int>& Cq);
        void set_to_String(set<int>& S);
       /*  class GreatNodo {
            public:
                GreatNodo(Grafo* p) : parent(p) {}
                bool operator() (const int& lhs, const int&rhs) const;
            private:
                Grafo* parent;
        };*/
        set<nodo_id>* expandClique(set<nodo_id>* ,pqDelta );

};


#endif //__GRAPH__
