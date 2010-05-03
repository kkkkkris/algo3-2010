#ifndef __GRAPH__
#define __GRAPH__
#include <string>
#include <list>
#include <map>
using namespace std;

class Nodo;
class Grafo {
    public:
        Grafo(int n, int m, int p, list<int>* nodos[], int llaves[], bool puertas[]);
        bool bfsMejorado();
        ~Grafo();
    private:
        Nodo** nodos;
        // cantidad de nodos
        int n;
        // cantidad de aristas
        int m;
        // cantidad de puertas y llaves
        int p;
};


#endif //__GRAPH__
