
#include "nodo.h"
#include <sstream>


Nodo::Nodo(){};

Nodo::Nodo(const nodo_id id, list<int> links):links(links), id(id), encolado(false),grado(links.size()),densidad(-1){};

string Nodo::toString() {
    stringstream ss;
    ss << "nodo #" << id << " [";
    for(it_list it = links.begin(); it != links.end(); it++) {
        if(it != links.begin())
            ss << ", ";
        ss << *it;
    }
    ss << "]";
    return ss.str();
}


