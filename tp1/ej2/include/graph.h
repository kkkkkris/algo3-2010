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
        
        //devuelve true si el par i,j corresponde a nodos adyacentes
        bool sonAdyacentes(int i, int j);
};


#endif //__GRAPH__
