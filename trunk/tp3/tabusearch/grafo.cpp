#include <iostream>
#include <algorithm>
#include "grafo.hpp"

using namespace std;

/**
 * Interseccion de conjuntos.
 *  
 * Complejidad: O( a log(b) ) 
 *              con a = min{|c1|, |c2|}
 *                  b = max{|c1|, |c2|}
 * 
 * @param c1: conjunto de nodos 1
 * @param c2: conjunto de nodos 2
 */ 
set<uint> interseccion(const set<uint>& c1, const set<uint>& c2) {
	set<uint> res;
	
    //Iteramos sobre el conjunto mas grande
    const set<uint> *s1;  //puntero al conjunto mas chico
    const set<uint> *s2;  //puntero al conjunto mas grande
    
    if (c1.size() > c2.size()) {
        s1 = &c2;
        s2 = &c1;
    }
    else {
        s1 = &c1;
        s2 = &c2;
    }
    
    //O( |s1| log(|s2|) )
	for (set<uint>::const_iterator its1 = s1->begin(); its1 != s1->end(); its1++) {
		//Buscamos en la otra lista si existe
        if (s2->find(*its1) != s2->end()) { //O(log |s2|)
			res.insert(*its1); //O(log |s1|)
		}
	}
	return res; //O(|s1|)
}

Grafo::Grafo(uint n): cantidadVertices(n), cantidadAristas(0), 
                      vecinos(vector<set<uint> >(n, set<uint>() ) ),
                      densidad(n,0) {}

TabuInfo obtenerTabuInfo(uint nodo, const list<TabuInfo>& lista) {
    for (list<TabuInfo>::const_iterator it = lista.begin(); it!=lista.end(); it++) {
        if ((*it).nodo == nodo) {
            return (*it);
        }
    }
    
    TabuInfo t;
    t.nodo = nodo;
    t.usosHistorico = 0;
    t.usosConsecutivos = 0;
    t.tiempo = 0;
    
    return t;
}

void actualizarTabu(list<TabuInfo>& tabu, uint largoTabu, uint nodo, uint usosHistorico, uint usosConsecutivos ) {
    list<TabuInfo>::iterator itMax = tabu.begin();
    bool elNodoEstaba=false;
    
    for (list<TabuInfo>::iterator it = tabu.begin(); it!=tabu.end(); it++) {
        if (it->nodo == nodo) {
            elNodoEstaba=true;
            it->usosConsecutivos=usosConsecutivos;
            it->usosHistorico=usosHistorico;
            it->tiempo=0;//Acaba de ser actualizado
        }
        else {
            it->tiempo++;//Aumentamos el tiempo de vejez del nodo en la lista tabu
        }
        
        if (it->tiempo > itMax->tiempo) {
            itMax = it;
        }
    }
    
    //Si el nodo no estaba, lo agregamos
    if (!elNodoEstaba) {
        TabuInfo t;
        t.nodo=nodo;
        t.usosConsecutivos=usosConsecutivos;
        t.usosHistorico=usosHistorico;
        t.tiempo=0;
        tabu.push_back(t);
    }
    
    //Si excedimos el tamaño permitido, borramos el que tiene tiempo mas grande
    if (tabu.size() > largoTabu) {
        tabu.erase(itMax);
    }
}

void Grafo::conectarVertices(uint v1, uint v2) {
    if(v1 < cantidadVertices && v2 < cantidadVertices) {
        vecinos[v1].insert(v2);
        vecinos[v2].insert(v1);
        cantidadAristas++;
    }
}

set<uint> Grafo::maxClique(uint maxIteraciones, char modoDelta, uint largoTabu) {
	uint k = 0; //cantidad de iteraciones transcurridas desde que no se actualiza la mejor solucion
	set<uint> sol; //solucion actual
	set<uint> mejorSol; //mejor solucion encontrada luego de diversificar
    set<uint> mejorSolGlobal; //mejor solucion encontrada durante todo el proceso
	set<uint> candidatos; //conjunto de nodos candidatos a elegir
	
    vector<bool> nodosVisitados(vecinos.size(), false); //vector que indica si un nodo ya fue usado alguna vez
    uint cantidadNodosVisitados = 0; //cantidad de nodos que fueron usados para alguna solucion
    
    //Para la complejidad, lt es largoTabu
    list<TabuInfo> listaTabu; //lista tabu de registro de la cantidad de veces que se uso cada nodo 
    
    //Calculamos las densidades de los nodos
    calcularDensidades(modoDelta); //O(n)
    
	do {
		//Si la cantidad de iteraciones sin encontrar una mejor solucion supera el umbral, diversificamos
        if(k > maxIteraciones) {
			//Obtener una nueva solucion a partir de los nodos no usados
            uint nodoInicial = obtenerSolucionInicial(nodosVisitados); //O(n)
            //Reinicializamos la solucion actual
            sol.clear(); //O(n)
            sol.insert(nodoInicial); //O(1) porque el conjunto esta vacio, es el primer elemento
			//Reiniciamos la cantidad de iteraciones que pasaron desde la obtencion de una mejor solucion
            k = 0;
            //Aumentamos la cantidad de nodos visitados
            cantidadNodosVisitados++;
            //Reiniciamos la lista tabu
            listaTabu.clear(); //O(lt)
            actualizarTabu(listaTabu, largoTabu, nodoInicial, 1, 1);
		}
		
        //Calcular candidatos en funcion de la solucion temporal
		calcularCandidatos(sol, candidatos); //O(m log(n))
        
		if (candidatos.size()>0) {
			uint c = elegirCandidatoExpansion(candidatos, listaTabu, largoTabu); //O(n*lt)
			sol.insert(c); //O(log n)
			nodosVisitados[c]=true; //O(1)
            cantidadNodosVisitados++;
		}
		else
		{
			if (sol.size()>1) {
				uint c = elegirCandidatoContraccion(sol, listaTabu, largoTabu ); //O(n*lt)
				sol.erase(c); //O(log n)
			}
            else {
                /* Si no tenemos candidatos para expandirnos, y la clique es de 
                 * tamanio 1, entonces estamos con una solucion que se un solo 
                 * nodo, por lo que no nos queda mucho por hacer, simplemente 
                 * diversificamos diciendole al algoritmo que ya no hay nada 
                 * mas que explorar para la solucion actual 
                 */ 
                 k = maxIteraciones;
            }
		}
		
        //Si la solucion encontrada es mejor (es decir, es un clique mas grande) actualizamos mejorSol
		if (sol.size() > mejorSol.size()) {
			mejorSol = sol; //O(n)
			k = 0;
		}
        else {
            k++;
        }
        
        //Actualizo la mejor solucion global
        if (mejorSol.size()>mejorSolGlobal.size()) {
            mejorSolGlobal = mejorSol;
        }
  
	}while(cantidadNodosVisitados < vecinos.size());
	
    return mejorSol;
}

void Grafo::calcularCandidatos(const set<uint>& solucion, set<uint>& candidatos) {
	//Al principio los candidatos son todos
    candidatos.clear(); //O(n)
    
    //O(n log(n))
    for(uint i = 0; i<vecinos.size(); i++) {
        candidatos.insert(i); //O(log n)
    }
	
    //O(d(v_1) log(n) + ... + d(v_n) log(n)) = O(m log(n))
    for (set<uint>::iterator itS = solucion.begin(); itS != solucion.end(); itS++){
		//O(|d(v)| (log n) ) donde v es un vertice del conjunto de vertices "solucion"
        candidatos = interseccion(candidatos, vecinos[*itS]);
	}
}

uint Grafo::obtenerSolucionInicial(vector<bool>& nodosVisitados) {
	//Buscamos el nodo de mayor densidad
    uint nodoElegido;
    bool seleccionInicial = false;
    
    //O(n)
    for (uint v =0; v<vecinos.size(); v++) {
        if (!nodosVisitados[v]) { //O(1)
            if (!seleccionInicial) {
                nodoElegido = v;
                seleccionInicial = true;
            }
            else {
                //Si el nodo no visitado tiene mas densidad que el que ya elegi, lo reemplazo
                if (densidad[v]>densidad[nodoElegido]) { //O(1)
                    nodoElegido = v;
                }
            }
        }
    }
    
    nodosVisitados[nodoElegido] = true; //O(1)
    	
	return nodoElegido;
}

uint Grafo::elegirCandidatoExpansion(const set<uint>& candidatos, list<TabuInfo>& listaTabu, uint largoTabu) {
	uint nodoElegido = *(candidatos.begin()); //O(1)
    TabuInfo te      = obtenerTabuInfo(nodoElegido, listaTabu); //O(lt)
    float fElegido   = densidad[nodoElegido] - te.usosHistorico; //O(1)
	
    //O(n*lt)
    for (set<uint>::const_iterator it = candidatos.begin(); it!=candidatos.end() ; it++) {
        TabuInfo t = obtenerTabuInfo(*it, listaTabu); //O(lt)
        float fv = densidad[*it] - t.usosHistorico; //0(1)
        if ( fv > fElegido) { //0(1)
            te = t; //0(1)
            fElegido = fv;//O(1)
        }
    }
    
    actualizarTabu(listaTabu, largoTabu, te.nodo, te.usosHistorico+1, te.usosConsecutivos+1);
    
    return te.nodo; //0(1)
}

uint Grafo::elegirCandidatoContraccion(const set<uint>& candidatos, list<TabuInfo>& listaTabu, uint largoTabu) {
	uint nodoElegido = *(candidatos.begin()); //O(1)
    TabuInfo te      = obtenerTabuInfo(nodoElegido, listaTabu); //O(lt)
    float fElegido   = densidad[nodoElegido] + te.usosConsecutivos; //O(1)
    
    //O(n*lt)
    for (set<uint>::const_iterator it = candidatos.begin(); it!=candidatos.end(); it++) {
        TabuInfo t = obtenerTabuInfo(*it, listaTabu); //O(lt)
        float fv = densidad[*it] + t.usosConsecutivos; //O(1)
        if (fv > fElegido) { //O(1)
            te = t; //O(1)
            fElegido = fv; //O(1)
        }
    }

    actualizarTabu(listaTabu, largoTabu, te.nodo, te.usosHistorico, 0);

	return te.nodo; //O(1)
}

void Grafo::calcularDensidades(char modoDelta) {
    for (uint v = 0; v<vecinos.size(); v++) {
        float d = 0.0;
        if (vecinos[v].size() > 0) {
            for(set<uint>::iterator it = vecinos[v].begin(); it!=vecinos[v].end(); it++) {
                d += vecinos[*it].size();
            }
            
            if (modoDelta=='p'){
                d = (d+vecinos[v].size())/(vecinos[v].size()+1);
            }
        }
        densidad[v] = d;
    }
}
