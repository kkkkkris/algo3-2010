#include <grafo.hpp>

Grafo::Grafo(uint n): cantidadVertices(n), adyacencia(vector<vector<bool> >( n, vector<bool>(n, false)  ) )
{
}

void Grafo::conectarVertices(uint v1, uint v2) 
{
    if(v1 < cantidadVertices && v2 < cantidadVertices)
    {
        adyacencia[v1][v2] = true;
        adyacencia[v2][v1] = true;
    }
}
void Grafo::desconectarVertices(uint v1, uint v2) {
    if(v1 < cantidadVertices && v2 < cantidadVertices)
    {
        adyacencia[v1][v2] = false;
        adyacencia[v2][v1] = false;
    }
}
bool Grafo::sonAdyacentes(uint v1, uint v2) {
    return adyacencia[v1][v2];    
}

bool Grafo::esOrientable() {
    
    return false;
}

