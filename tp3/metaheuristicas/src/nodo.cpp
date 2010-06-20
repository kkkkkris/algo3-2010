//      nodo.cpp
//      
//      Copyright 2010 Mariano Semelman <mariano@nancy>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.


#include "nodo.h"
#include <sstream>

typedef list<int>::iterator it_list;

Nodo::Nodo(){};

Nodo::Nodo(const nodo_id id, list<int> links):links(links), id(id), visitada(false),grado(links.size()),densidad(-1){};

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


