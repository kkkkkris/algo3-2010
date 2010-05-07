#ifndef __GRAFO__H__
#define __GRAFO__H__

#include <types.hpp>
#include <vector>
#include <set>

using namespace std;

class Grafo {
    public:
        Grafo(uint n);
        void conectarVertices(uint v1, uint v2);
        void desconectarVertices(uint v1, uint v2);
        bool esConexo();
        bool esOrientable();
        inline uint getCantidadVertices(){return cantidadVertices;}
        inline uint getCantidadAristas(){return cantidadAristas/2;}
    private:
        //cantidad total de vertices
        uint cantidadVertices;
        //cantidad de aristas del grafo
        uint cantidadAristas;
        //Para la i-esima posicion, el vector contiene un set de los vecinos del i-esimo vertice.
        vector<set<uint> > vecinos;
        //Devuelve true si existen puentes en el grafo, o false en caso contrario
        bool hayPuentes();
};

#endif //__GRAFO__H__
