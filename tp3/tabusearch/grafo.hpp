#ifndef __GRAFO__H__
#define __GRAFO__H__

#include "types.hpp"
#include <vector>
#include <list>
#include <set>

using namespace std;

class Grafo {
    public:
        Grafo(uint n);
        void conectarVertices(uint v1, uint v2);
        void desconectarVertices(uint v1, uint v2);
       
        inline uint getCantidadVertices(){return cantidadVertices;}
        inline uint getCantidadAristas(){return cantidadAristas/2;}
        
        /**
         * Devuelve el maximo clique encontrado por la metaheuristica Tabu Search.
         * 
         * Cuando expande la clique actual, TS lo hace maximizando f1 para los posibles candidatos.
         * Cuando achica la clique actual, TS lo hace maximizando f2 para los posibles candidatos.
         * 
         * f1(v) = valoracionDelta * d(v) - valoracionRepetidos*vecesUsado(v)
         * f2(v) = valoracionDelta * d(v) + valoracionRepetidos*vecesUsadoConsecutivamente(v)
         * 
         * @param maxIteraciones: cantidad maxima de iteraciones sin obtener una mejora en la solucion actual antes de diversificar.
         * @param modoDelta: funcion delta (1 o 2)
         * @param largoTabu: el largo de la lista tabu (n como maximo)
         **/
        set<uint> maxClique(uint maxIteraciones, char modoDelta, uint largoTabu);
    private:
        //cantidad total de vertices
        uint cantidadVertices;
        //cantidad de aristas del grafo
        uint cantidadAristas;
        //Para la i-esima posicion, el vector contiene un set de los vecinos del i-esimo vertice.
        vector<set<uint> > vecinos; 
        //Para la i-esima posicion, da la densidad del i-esimo vertice
        vector<float> densidad;
        
        /**
         * Obtiene una nueva solucion inicial a partir de la lista 
         * de nodos no visitados por TS.
         * 
         * Complejidad: O(n)
         * 
         * @param vector que indica cual nodo ya fue visitado y cual no.
         */ 
        uint obtenerSolucionInicial(vector<bool>&);
        
        /**
         * En base al conjunto de nodos solucion recalcula el conjunto de
         * nodos candidatos para expandir a la clique actual.
         * Los candidatos son aquellos nodos que no pertenecen a la clique actual
         * pero que son vecinos de todos los nodos que si pertencen al a misma.
         * 
         * Complejidad: O(m log(n))
         * 
         * @param solucion : clique actual
         * @param candidatos: conjuto de candidatos
         */ 
        void calcularCandidatos(const set<uint>& solucion, set<uint>& candidatos);
        
        
        /** 
         * Dado conjunto de nodos (la clique actual) elige uno para quitar
         * y reducir la solucion actual.
         * 
         * Criterio: maximizar f(v) = densidad(v) + vecesUsado(v)
         * 
         * Complejidad: O(n*lt) con lt el largo de la lista tabu
         * 
         * @param candidatos: solucion actual (clique)
         * @param listaTabu
         * @param largoTabu: maximo largo de la lista tabu
         **/
        uint elegirCandidatoContraccion(const set<uint>& candidatos, list<TabuInfo>& listaTabu, uint largoTabu);
       
        /**
         * Dado un conjunto de nodos candidatos para expandir la clique actual
         * elige uno.
         * 
         * Criterio: maximizar f(v) = delta(v) - vecesUsado(v)
         * 
         * Complejidad: O(n*lt) con lt el largo de la lista tabu
         *
         * @param candidatos: conjunto de nodos candidatos para expandir la clique actual
         * @param listaTabu
         * @param largoTabu: maximo largo de la lista tabu
         **/
        uint elegirCandidatoExpansion(const set<uint>& candidatos, list<TabuInfo>& listaTabu, uint largoTabu);
        
        /**
         * Calcula la densidad para todo nodo
         * 
         * Complejidad: O(m) 
         * 
         * @param modoDelta: 's'=calcula el delta como la suma de los grados de los vecinos
         *                   'p'=calcula el delta como la suma de los grados de los vecinos mas el grado de si mismo sobre la cantidad de vecinos+1
         */ 
        void calcularDensidades(char modoDelta);
};

#endif //__GRAFO__H__
