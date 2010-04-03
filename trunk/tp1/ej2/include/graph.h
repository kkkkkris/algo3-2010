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
        bool esHamilton();
        ~Grafo();
    private:
        Nodo & getNodo(int nodo_id);
        Nodo * nodos;
        int size;
    
};


#endif //__GRAPH__
