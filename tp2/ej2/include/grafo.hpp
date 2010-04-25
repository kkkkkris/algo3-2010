#ifndef __GRAFO__H__
#define __GRAFO__H__

#include <types.hpp>
#include <string>
#include <vector>

using namespace std;

class Grafo {
    public:
        Grafo(uint n);
        void conectarVertices(uint v1, uint v2);
        void desconectarVertices(uint v1, uint v2);
        bool sonAdyacentes(uint v1, uint v2);
        bool esOrientable();
    private:
        uint cantidadVertices;
        vector<vector<bool> > adyacencia;
};

#endif //__GRAFO__H__
