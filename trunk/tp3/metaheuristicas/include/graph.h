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
        set<int>* maxClique();
    private:
        //datos
        Nodo* nodos;
        int size;
        bool *adj;
        //metodos privados
        Nodo& getNodo(int nodo_id);
        bool sonAdyacentes(int i, int j);
        int getGrado(int nodo_id);
        int getDensidad(int nodo_id);
        void setDensidad(int nodo_id,int densidad);
        bool esClique(int nodo_id,set<int> Cq);
        set<int>* getVecinos(int nodo_id);
        set<int>* HC();
};


#endif //__GRAPH__
