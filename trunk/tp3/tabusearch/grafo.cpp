#include <iostream>

#include "grafo.hpp"

using namespace std;

list<uint> interseccion(const list<uint>& s1, const list<uint>& s2);

Grafo::Grafo(uint n): cantidadVertices(n), cantidadAristas(0), 
                      vecinos(vector<list<uint> >(n, list<uint>() ) ) {}


void Grafo::conectarVertices(uint v1, uint v2) 
{
    if(v1 < cantidadVertices && v2 < cantidadVertices) {
        vecinos[v1].push_back(v2);
        vecinos[v2].push_back(v1);
        cantidadAristas++;
    }
}

 set<uint> createNovisitados(uint largo) {
	set<uint> res;
	for (uint i=0; i<largo; i++){
		res.insert(i);
	}
	return res;
}
/*
void Grafo::desconectarVertices(uint v1, uint v2) {
    if(v1 < cantidadVertices && v2 < cantidadVertices) {
        vecinos[v1].erase(v2);
        vecinos[v2].erase(v1);
        cantidadAristas--;
    }
}*/

set<uint> Grafo::maxClique(uint maxIteraciones, uint max_tabu_length) {
	uint k = 0;
	set<uint> s; //solucion
	set<uint> st; //solucion temporal
	list<uint> candidatos; //conjunto de nodos candidatos a elegir
	set<uint> noVisitados = createNovisitados(vecinos.size());
	list<uint> listaTabuInsert;
	list<uint> listaTabuDelete;
	
	//eligo una solucion inicial
	st = obtenerSolucionInicial(noVisitados);
	
	
	do {
		if(k > maxIteraciones) {
			s = obtenerSolucionInicial(noVisitados);	
			k = 0;
		}
		//Calcular candidatos en funcion de la solucion temporal
		calcularCandidatos(st, candidatos, listaTabuDelete);
		
		if (candidatos.size()>0) {
			uint c = elegirCandidatoExpansion(candidatos);
			st.insert(c);
			listaTabuInsert.push_back(c);
			if(listaTabuInsert.size() > max_tabu_length) {
				listaTabuInsert.pop_front();
			}
			noVisitados.erase(c);
		}
		else
		{
			if (st.size()>1) {
				uint c = elegirCandidatoContraccion(st, listaTabuDelete);
				st.erase(st.find(c));
				listaTabuDelete.push_back(c);
				if(listaTabuDelete.size() > max_tabu_length) { 
					listaTabuDelete.pop_front();
				}
			}
		}
		
		if (st.size() > s.size()) {
			s = st;
			k = 0;
		}
		
	}while(!noVisitados.empty());
	return s;
}

/**
 * En base al conjunto de nodos solucion recalcula el conjunto de
 * nodos candidatos para expandir a s. Utiliza listaTabu para
 * generar los nuevos candidatos. 
 * @param solucion : clique actual
 * @param candidatos: resultado
 * @param listaTabu: filtro
 */ 
void Grafo::calcularCandidatos(const set<uint>& solucion, list<uint>& candidatos, const list<uint>& listaTabu) {
	candidatos = vecinos[*(solucion.begin())];
	for (set<uint>::iterator itS = solucion.begin(); itS != solucion.end(); itS++){
		candidatos = interseccion(candidatos, vecinos[*itS]);
	}
	candidatos = interseccion(candidatos, listaTabu);
}

/**
 * Obtiene una nueva solucion inicial a partir de la lista de nodos no visitados por TS.
 * @param lista de nodos aun no visitados por TS.
 */ 
set<uint> Grafo::obtenerSolucionInicial(set<uint>& noVisitados) {
	//TODO: elegir el nodo o los nodos de forma inteligente
	set<uint> s0;
	s0.insert(*(noVisitados.begin()));
	noVisitados.erase(noVisitados.begin());
	return s0;
}

/**
 * Interseccion de listas
 */ 
list<uint> interseccion(const list<uint>& s1, const list<uint>& s2) {
	list<uint> res;
	set<uint> ss2(s2.begin(), s2.end());
	for (list<uint>::const_iterator its1 = s1.begin(); its1 != s1.end(); its1++) {
		if (ss2.find(*its1) != ss2.end()) {
			res.push_back(*its1);
		}
	}
	return res;
}

/**
 * Dado una lista de nodos s elige utilizando un criterio adecuado el proximo nodo para expandir el clique actual.
 * s es un conjunto de nodos donde cada uno es vecino a todos los del clique y ya estan filtrados por la lista tabu
 **/
uint Grafo::elegirCandidatoExpansion(const list<uint>& s)
{
	//TODO: Elegir el candidato usando algun criterio.
	return *(s.begin());
	
}

/** Dado el clique s elige utilizando un criterio adecuado el proximo nodo para contraer el clique actual. **/
uint Grafo::elegirCandidatoContraccion(const set<uint>& s, const list<uint>& listaTabuInsert)
{
	//TODO: Elegir el candidato usando algun criterio.
	return *(s.begin());
	
}
