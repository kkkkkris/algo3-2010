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
        void mostrar();
        void maxClique(list<int>* nodos_ids, bool mejorado);
    private:
        void sacarVecinos(list<int>* l, int v);
        void imprimirSecu(list<int>* l);
        void copiarNodos(list<int>* copiaNodos);
        int elegirPivote(list<int>* l1, list<int>* l2);
        void interseccion(list<int>* l1, list<int>* l2);
        void cliqueMaxSinMejoras(list<int>* R, list<int>* P, list<int>* X, list<int>* nodos_ids);
        void cliqueMax(list<int>* R, list<int>* P, list<int>* X, list<int>* nodos_ids);
        Nodo& getNodo(int nodo_id);
        Nodo* nodos;
        int size;
        bool sonAdyacentes(int i, int j);
};


#endif //__GRAPH__
