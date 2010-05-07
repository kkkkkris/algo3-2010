#include <grafo.hpp>
#include <queue>
#include <list>
#include <iostream>

using namespace std;

Grafo::Grafo(uint n): cantidadVertices(n), cantidadAristas(0), 
                      vecinos(vector<set<uint> >(n, set<uint>() ) )
{
}

void Grafo::conectarVertices(uint v1, uint v2) 
{
    if(v1 < cantidadVertices && v2 < cantidadVertices)
    {
        vecinos[v1].insert(v2);
        vecinos[v2].insert(v1);
        cantidadAristas++;
    }
}

void Grafo::desconectarVertices(uint v1, uint v2) {
    if(v1 < cantidadVertices && v2 < cantidadVertices)
    {
        vecinos[v1].erase(v2);
        vecinos[v2].erase(v1);
        cantidadAristas--;
    }
}

bool Grafo::esConexo() {
    uint verticesVisitados = 0;
    //Cola usada para recorrer los nodos (BFS)
    queue<uint> nodosPorRecorrer;
    //Vector para saber si ya visite un nodo, y no encolarlo de nuevo.
    vector<bool> nodoVisitado(cantidadVertices, false);
    
    nodosPorRecorrer.push(0);
    nodoVisitado[0] = true;
    verticesVisitados++;
    
    while(!nodosPorRecorrer.empty() && verticesVisitados < cantidadVertices) {
        //Obtenemos el nodo actual
        uint nodoActual = nodosPorRecorrer.front();
        //Recorremos los vecinos del nodo actual
        for(set<uint>::iterator it = vecinos[nodoActual].begin(); it != vecinos[nodoActual].end(); it++) {
            //En caso de no haber sido visitado, lo encolo
            if(!nodoVisitado[*it]) {
                //Debemos encolar al vecino para visitarlo despues
                nodoVisitado[*it]=true;
                nodosPorRecorrer.push(*it);
                verticesVisitados++;
            }
        }
        nodosPorRecorrer.pop();
    }
    
    return (verticesVisitados==cantidadVertices);
}


bool Grafo::esOrientable() {
    //Veamos si existe algun vertice con grado 1
    for(uint i=0; i<cantidadVertices; i++){
        if(vecinos[i].size()<2){
            return false;
        }
    }
    
    return !hayPuentes();
}

bool Grafo::hayPuentes() {
    //Comenzamos suponiendo que todas las aristas son puentes. Luego por cada una que decidimos que no es puente, restamos esta cantidad
    uint existeUnPuente = false;
    //Cola usada para recorrer los nodos (BFS)
    queue<uint> nodosPorRecorrer;
    //Guardamos en una lista los nodos que debemos volver a visitar (en orden inverso al visitado en primer lugar)
    //El par indica nodo, nodoPadre para no tener que buscar quien es el padre cuando deshacemos la relacion y vemos si es conexo
    list<pair<uint, uint> > nodosPendientes;
    //Guardamos el nivel de cada nodo
    vector<int> nivelNodos(cantidadVertices, -1);
    
    //Encolamos el primero de los nodos
    nodosPorRecorrer.push(0);
    //Seteamos el nivel del nodo inicial en 0
    nivelNodos[0] = 0;
    
    while(!nodosPorRecorrer.empty()) {
        //Obtenemos el nodo actual
        uint nodoActual = nodosPorRecorrer.front();
        //Obtenemos el nivel actual
        int nivelActual = nivelNodos[nodoActual];
        //cout << nivelActual << endl;
        //Listas de vecinos de nivel nivelActual-1, nivelActual, y nivelActual+1 respectivamente 
        //uint nodosMarcados
        //Si el nodo tiene un unico vecino anterior, lo guardamos aca
        uint vecinoNivelAnterior;
        //list<uint> vecinosNivelActual;
        //list<uint> vecinosNivelPosterior;
        uint cantidadVecinosAnteriores = 0;
        uint cantidadVecinosMismoNivel = 0;
        
        //Recorremos los vecinos del nodo actual
        for(set<uint>::iterator it = vecinos[nodoActual].begin(); it != vecinos[nodoActual].end(); it++) {
            int nivelVecino = nivelNodos[*it];
            //En caso de no haber sido visitado antes, el nivel del vecino es el actual + 1
            if(nivelVecino == -1) {
                nivelVecino = nivelActual+1;
                nivelNodos[*it] = nivelVecino;
                //Debemos encolar al vecino para visitarlo despues
                nodosPorRecorrer.push(*it);
                //El nodo tiene vecinos de nivel mayor
                //vecinosNivelPosterior.push_back(*it);
            }
            else if(nivelVecino == nivelActual) {
                cantidadVecinosMismoNivel++;
                //vecinosNivelActual.push_back(*it);
            }
            else if(nivelVecino < nivelActual){
                cantidadVecinosAnteriores++;
                vecinoNivelAnterior = *it;
            }
        }        
        if (cantidadVecinosMismoNivel == 0 && cantidadVecinosAnteriores == 1) {
            nodosPendientes.push_back(pair<uint, uint>(nodoActual, vecinoNivelAnterior));
        }
        
        nodosPorRecorrer.pop();
    }
    
    //Recorro los nodos pendientes para decidir finalmente si su arista de nivel nivelActual-1 es o no puente
    for(list<pair<uint, uint> >::iterator it = nodosPendientes.begin(); (it != nodosPendientes.end()) && (!existeUnPuente); it++ ) {
        desconectarVertices(it->first, it->second);
        existeUnPuente = !esConexo();
        conectarVertices(it->first, it->second);
    }
    
    return existeUnPuente;
}
