
#ifndef NODO_H
#define NODO_H
#include <list>
#include <set>
#include <string>


using namespace std;
typedef int nodo_id;
typedef list<int>::iterator it_list;

class Nodo
{
	public:
		Nodo();
    Nodo(const nodo_id id, list<nodo_id> links);
    string toString();
    set<nodo_id> links;
    nodo_id id;
    bool encolado;
    int grado;
    float densidad;

};

#endif /* NODO_H */
