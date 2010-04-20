#ifndef __GRAPH__
#define __GRAPH__
#include <string>
#include <list>
#include <map>
using namespace std;

class Nodo;
class Grafo {
    public:
        Grafo(int n, int m, int p, list<int>[] nodos, int[] llaves, bool[] puertas);
        bool bfsMejorado();
        ~Grafo();
    private:
        Nodo& getNodo(int nodo_id);
        Nodo* nodos;
        // el índice es el nodo donde está la puerta y devuelve dónde está la llave
        int* llaves;
        // devuelve en qué nodo está la llave que abre puerta
        int getLlave(int puerta)
        // cantidad de nodos
        int n;
        // cantidad de aristas
        int m;
        // cantidad de puertas y llaves
        int p;
};


#endif //__GRAPH__
