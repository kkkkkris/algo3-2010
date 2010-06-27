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
struct candidato;

typedef  set<nodo_id>::iterator it_set;
typedef priority_queue<Nodo,vector<Nodo>,comparison> pqDelta ;

class Grafo {
    public:
        Grafo(map<int, list<int> >);
        ~Grafo();
        int length();
        set<int> HC();
        set<int> HL();
        set<int> HT();
    private:
        //datos
        Nodo* nodos;
        int size;
        bool *adj;
        //metodos privados
            //generales
            Nodo& getNodo(int nodo_id);
            int getGrado(int nodo_id);
            bool sonAdyacentes(int i, int j);
            //especificos
            float setDensidad(int nodo_id);
            nodo_id generarDensidad();
            set<nodo_id> vecindad(const set<nodo_id> & cq);
            bool esClique(int nodo_id, set<int>& Cq);
            void merge(int nodo_id,pqDelta& S,set<int>& Cq);
            set<nodo_id> expandClique(set<nodo_id>& ,pqDelta );
            candidato findCandidato(const set<nodo_id> &);

};


#endif //__GRAPH__
