#ifndef __GRAPH__
#define __GRAPH__
#include <string>
#include <list>
#include <map>
using namespace std;

class Nodo;
class Grafo {
    public:
        Grafo();
        Grafo(map<int, list<int> >);
        ~Grafo();
        int length();
        void maxClique(list<int>* nodos_ids);
    private:
        void copiarNodos(list<Nodo>* copiaNodos);
        void interseccion(list<Nodo>* l1, list<int>* l2);
        void cliqueMax(list<Nodo>* R, list<Nodo>* P, list<Nodo>* X, list<int>* nodos_ids);
        Nodo& getNodo(int nodo_id);
        Nodo* nodos;
        int size;
        bool sonAdyacentes(int i, int j);
};


#endif //__GRAPH__
