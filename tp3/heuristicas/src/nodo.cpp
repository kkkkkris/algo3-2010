
#include "nodo.h"
#include <sstream>
using namespace std;
typedef set<nodo_id>::iterator it_set;
Nodo::Nodo(){};

Nodo::Nodo(const nodo_id id, list<int> vecinos) {
    this->links = set<nodo_id>(vecinos.begin(), vecinos.end());
    this->id = id;
    this->encolado = false;
    this-> grado = links.size();
    this->densidad = -1;
}

string Nodo::toString() {
    stringstream ss;
    ss << "nodo #" << id << " [";
    for(it_set it = links.begin(); it != links.end(); it++) {
        if(it != links.begin())
            ss << ", ";
        ss << *it;
    }
    ss << "]";
    return ss.str();
}


