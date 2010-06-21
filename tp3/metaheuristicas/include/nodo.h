
#ifndef NODO_H
#define NODO_H
#include <list>
#include <string>


using namespace std;
typedef int nodo_id;
typedef list<int>::iterator it_list;

class Nodo
{
	public:
		Nodo();
    Nodo(const nodo_id id, list<int> links);
    string toString();
    list<int> links;
    nodo_id id;
    bool visitada;
    int grado;
    int densidad;
			
};

#endif /* NODO_H */ 
