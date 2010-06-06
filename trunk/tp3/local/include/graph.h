#ifndef __GRAPH__
#define __GRAPH__
#include <string>
#include <list>
#include <map>
using namespace std;

class Nodo;
class Grafo {
    public:
        Grafo(map<int, list<int> >);
        ~Grafo();
        int length();
        Grafo* maxClique();
    private:
        Nodo& getNodo(int nodo_id);
        Nodo* nodos;
        int size;
        bool sonAdyacentes(int i, int j);
};


#endif //__GRAPH__
