#include <iostream>
#include <algorithm>
#include "grafo.hpp"

using namespace std;

list<uint> interseccion(const list<uint>& s1, const list<uint>& s2);

Grafo::Grafo(uint n): cantidadVertices(n), cantidadAristas(0), 
                      vecinos(vector<list<uint> >(n, list<uint>() ) ),
                      densidad(n,0) {}


void Grafo::conectarVertices(uint v1, uint v2) 
{
    if(v1 < cantidadVertices && v2 < cantidadVertices) {
        vecinos[v1].push_back(v2);
        vecinos[v2].push_back(v1);
        cantidadAristas++;
    }
}
/*
vector<bool> crearNoVisitados(uint largo) {
	vector<bool> res(largo);
	for (uint i=0; i<largo; i++){
		res[i] = false;
	}
	return res;
}*/

/*
void Grafo::desconectarVertices(uint v1, uint v2) {
    if(v1 < cantidadVertices && v2 < cantidadVertices) {
        vecinos[v1].erase(v2);
        vecinos[v2].erase(v1);
        cantidadAristas--;
    }
}*/

set<uint> Grafo::maxClique(uint maxIteraciones, float valoracionDelta, float valoracionRepetidos) {
	uint k = 0; //cantidad de iteraciones transcurridas desde que no se actualiza la mejor solucion
	set<uint> sol; //solucion actual
	set<uint> mejorSol; //mejor solucion encontrada
	list<uint> candidatos; //conjunto de nodos candidatos a elegir
	vector<bool> nodosVisitados(vecinos.size(), false); //vector que indica si un nodo ya fue usado alguna vez
    uint cantidadNodosVisitados = 0; //cantidad de nodos que fueron usados para alguna solucion
    vector<uint> vecesUsado(vecinos.size(), 0); //vector que indica para cada nodo cuantas veces fue usado en una solucion (antes de diversificar)
    
    //list<uint> listaTabuInsert;
	//list<uint> listaTabuDelete;
	
    //Calculamos las densidades de los nodos
    calcularDensidades();
    
	//eligo una solucion inicial
	mejorSol.insert(obtenerSolucionInicial(nodosVisitados));

	do {
		//Si la cantidad de iteraciones sin encontrar una mejor solucion supera el umbral, diversificamos
        if(k > maxIteraciones) {
			//Obtener una nueva solucion a partir de los nodos no usados
            uint nodoInicial = obtenerSolucionInicial(nodosVisitados);
            sol.clear();
            sol.insert(nodoInicial);
			k = 0;
            cantidadNodosVisitados++;
            vecesUsado.assign(vecinos.size(), 0);
            vecesUsado[nodoInicial] = 1;
            //listaTabuInsert.clear();
            //listaTabuDelete.clear();
		}
		
        //Calcular candidatos en funcion de la solucion temporal
		//calcularCandidatos(sol, candidatos, listaTabuDelete);
		calcularCandidatos(sol, candidatos);
        
		if (candidatos.size()>0) {
			uint c = elegirCandidatoExpansion(candidatos, vecesUsado, valoracionDelta, valoracionRepetidos);
			sol.insert(c);
			/*
            listaTabuInsert.push_back(c);
            if(listaTabuInsert.size() > maxLogitudTabu) {
				listaTabuInsert.pop_front();
			}
            */ 
			nodosVisitados[c]=true;
            cantidadNodosVisitados++;
		}
		else
		{
			if (sol.size()>1) {
				uint c = elegirCandidatoContraccion(sol, vecesUsado, valoracionDelta, valoracionRepetidos);
				sol.erase(sol.find(c));
				/*
                listaTabuDelete.push_back(c);
				if(listaTabuDelete.size() > maxLogitudTabu) { 
					listaTabuDelete.pop_front();
				}
                */ 
			}
		}
		
        //Actualizamos la cantidad de veces que cada nodo fue usado
        for (set<uint>::iterator it = sol.begin(); it!=sol.end(); it++) {
            vecesUsado[*it]++;
        }
        
        //Si la solucion encontrada es mejor (es decir, es un clique mas grande) actualizamos mejorSol
		if (sol.size() > mejorSol.size()) {
			mejorSol = sol;
			k = 0;
		}
        else {
            k++;
        }
  
	}while(cantidadNodosVisitados < vecinos.size());
	
    return mejorSol;
}

/**
 * En base al conjunto de nodos solucion recalcula el conjunto de
 * nodos candidatos para expandir a s. Utiliza listaTabu para
 * generar los nuevos candidatos. 
 * @param solucion : clique actual
 * @param candidatos: resultado
 */ 
void Grafo::calcularCandidatos(const set<uint>& solucion, list<uint>& candidatos) {
	candidatos = vecinos[*(solucion.begin())];
	for (set<uint>::iterator itS = solucion.begin(); itS != solucion.end(); itS++){
		candidatos = interseccion(candidatos, vecinos[*itS]);
	}
}

/**
 * Obtiene una nueva solucion inicial a partir de la lista de nodos no visitados por TS.
 * @param lista de nodos aun no visitados por TS.
 */ 
uint Grafo::obtenerSolucionInicial(vector<bool>& nodosVisitados) {
	//Buscamos el nodo de mayor densidad
    uint nodoElegido;
    bool seleccionInicial = false;
    
    for (uint v =0; v<vecinos.size(); v++) {
        if (!nodosVisitados[v]) {
            if (!seleccionInicial) {
                nodoElegido = v;
                seleccionInicial = true;
            }
            else {
                //Si el nodo no visitado tiene mas densidad que el que ya elegi, lo reemplazo
                if (densidad[v]>densidad[nodoElegido]) {
                    nodoElegido = v;
                }
            }
        }
    }
    
    nodosVisitados[nodoElegido] = true;
    	
	return nodoElegido;
}

/**
 * Interseccion de listas
 * 
 * @param s1: conjunto de nodos 1
 * @param s2: conjunto de nodos 2
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
 * Dado una lista de nodos s elige el proximo nodo para expandir el clique actual.
 * 
 * Criterio: maximizar f(v) = delta(v) - vecesUsado(v)
 * 
 * @param s: conjunto de nodos donde cada uno es vecino a todos los del clique.
 * @param vecesUsado: vector que indica, para cada nodo, cuantas veces fue usado en un clique o solucion temporal
 * @param valoracionDelta: valoracion que se le da a la componente delta o densidad en la funcion a maximizar
 * @param valoracionRepetidos: valoracion que se le da a la componente repetidos en la funcion a maximizar
 **/
uint Grafo::elegirCandidatoExpansion(const list<uint>& s, const vector<uint>& vecesUsado, float valoracionDelta, float valoracionRepetidos) {
	uint nodoElegido = *(s.begin());
    float fElegido   = valoracionDelta*densidad[nodoElegido] - valoracionRepetidos*vecesUsado[nodoElegido];
	for (list<uint>::const_iterator it = s.begin(); it!=s.end() ; it++) {
        float fv = valoracionDelta*densidad[*it] - valoracionRepetidos*vecesUsado[*it];
        if ( fv > fElegido) {
            nodoElegido = *it;
            fElegido = valoracionDelta*densidad[nodoElegido] - valoracionRepetidos*vecesUsado[nodoElegido];
        }
    }
    
    return nodoElegido;
}

/** 
 * Dado el clique s elige el proximo nodo para contraer el clique actual.
 * 
 * Criterio: maximizar f(v) = densidad(v) + vecesUsado(v)
 * 
 * @param s: solucion actual (clique)
 * @param vecesUsado: vector que indica para cada nodo, cuantas veces fue usado en una solucion intermedia
 * @param valoracionDelta: valoracion que se le da a la componente delta o densidad en la funcion a maximizar
 * @param valoracionRepetidos: valoracion que se le da a la componente repetidos en la funcion a maximizar
 **/
uint Grafo::elegirCandidatoContraccion(const set<uint>& s, const vector<uint>& vecesUsado, float valoracionDelta, float valoracionRepetidos) {
	uint nodoElegido = *(s.begin());
    float fElegido   = valoracionDelta*densidad[nodoElegido] + valoracionRepetidos*vecesUsado[nodoElegido];
    for (set<uint>::const_iterator it = s.begin(); it!=s.end(); it++) {        
        float fv = valoracionDelta*densidad[*it] + valoracionRepetidos*vecesUsado[*it];
        if (fv > fElegido) {
            nodoElegido = *it;
            fElegido = valoracionDelta*densidad[nodoElegido] + valoracionRepetidos*vecesUsado[nodoElegido];
        }
    }

	return nodoElegido;
}

/**
 * Calcula la densidad para todo nodo
 */ 
void Grafo::calcularDensidades() {
    for (uint v = 0; v<vecinos.size(); v++) {
        float d = 0.0;
        if (vecinos[v].size() > 0) {
            for(list<uint>::iterator it = vecinos[v].begin(); it!=vecinos[v].end(); it++) {
                d += vecinos[*it].size();
            }
            
            d /= vecinos[v].size();
        }
        densidad[v] = d;
    }
}
