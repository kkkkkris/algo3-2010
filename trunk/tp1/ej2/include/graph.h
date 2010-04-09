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
        Nodo& getNodo(int nodo_id);
        Nodo* nodos;
        int size;
        //cicloAsegurado indica si es necesario encontrar el ciclo para responder a la pregunta de su existencia, o ya fue probada por algun teorema
        enum proofState {EXISTE,NO_EXISTE, NO_SE_SABE} cicloDeHamilton;
        
        //Ordena el array de nodos de acuerdo a su cantidad de links con mergesort
        //void sortNodos(Nodo* v, int inicio, int fin);
        list<int> getNodosNoAdyacentes(int nodoId);
};


#endif //__GRAPH__
