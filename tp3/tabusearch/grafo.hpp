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
        set<uint> maxClique(uint maxIteraciones, float valoracionDelta, float valoracionRepetidos);
        inline uint getCantidadVertices(){return cantidadVertices;}
        inline uint getCantidadAristas(){return cantidadAristas/2;}
    private:
        //cantidad total de vertices
        uint cantidadVertices;
        //cantidad de aristas del grafo
        uint cantidadAristas;
        //Para la i-esima posicion, el vector contiene un set de los vecinos del i-esimo vertice.
        vector<list<uint> > vecinos; 
        //Para la i-esima posicion, da la densidad del i-esimo vertice
        vector<float> densidad;
        
        //Devuelve una solucion inicial a partir de un conjunto de nodos
        uint obtenerSolucionInicial(vector<bool>&);
        //Calcula el conjunto de ndos candidatos a elegir por TS para expandir el clique actual
        void calcularCandidatos(const set<uint>& solucion, list<uint>& candidatos);
        //Devuelve un candidato a usar del conjunto s para contraer.
        uint elegirCandidatoContraccion(const set<uint>& s, const vector<uint>& vecesUsado, float valoracionDelta, float valoracionRepetidos);
        //devuelve un candidato para expandir.
        uint elegirCandidatoExpansion(const list<uint>& s, const vector<uint>& vecesUsado, float valoracionDelta, float valoracionRepetidos);
        //calcula las densidades para todos los nodos
        void calcularDensidades();
};

#endif //__GRAFO__H__
