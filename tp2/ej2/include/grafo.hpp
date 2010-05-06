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
    private:
        //typedef enum {POSIBLE_PUENTE, PUENTE, NO_PUENTE} tipo_arista_t;
        //cantidad total de vertices
        uint cantidadVertices;
        //cantidad de aristas del grafo
        uint cantidadAristas;
        //Para la i-esima posicion, el vector contiene un set de los vecinos del i-esimo vertice.
        vector<set<uint> > vecinos;
        //Cada m(i,j) indica si la arista (i,j) es puente o no
        //vector<vector<tipo_arista_t> > tipoAristas;
        //vector<vector<tipo_arista_t> > adyacencia;
        //Devuelve true si existen puentes en el grafo, o false en caso contrario
        bool hayPuentes();
};

#endif //__GRAFO__H__
