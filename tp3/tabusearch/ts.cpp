#include <iostream>
#include <fstream>
#include <list>
#include <utility>
#include <ctime>
#include <cstdlib>

#include "types.hpp"
#include "grafo.hpp"

typedef unsigned long int time_tt;

using namespace std;

Grafo* leerGrafoDeEntrada(ifstream& archivo);
void escribirSalida(const char *nombreArchivo, list<set<uint> >& listaResultados);
time_tt getNanosegundos();

int main(int argc, char* argv[]) {
    if(argc < 4){
        cout << "Parametros insuficientes" << endl;
        return 1;
    }

    int maxIter				= atoi(argv[1]);
    const char* modoDelta   = argv[2];
    uint largoTabu          = atoi(argv[3]);
    
    //Leemos los grafos
    ifstream datos("Tp3.in");
    
    list<set<uint> > resultados;
    list<pair<long long, time_tt> > tiempos;
    
    while(datos.good()) {
        Grafo *g = leerGrafoDeEntrada(datos);
        time_tt min_time;
        set<uint> maxClique;
                
        if (g) {
            for(int k=0; k<5; k++){
                time_tt start = getNanosegundos();
                maxClique = g->maxClique(maxIter, modoDelta[0], largoTabu);
                time_tt finish = getNanosegundos();
                if(k==0){
                    min_time = finish-start;
                }
                else{
                    if(finish-start < min_time){
                        min_time = finish-start;
                    }
                }
            }
            uint n = g->getCantidadVertices();
            uint m = g->getCantidadAristas();
            
            //maxClique = g->maxClique(maxIter, modoDelta[0], largoTabu);
            resultados.push_back(maxClique);
            cout << maxClique.size() << " " << n << " " << m << " " << min_time << endl;
            
            delete g;
        }
    }
    
    escribirSalida("Tp3TS.out", resultados);
    
    return 0;
}

Grafo* leerGrafoDeEntrada(ifstream& datos) {
    int n=0;
    //Leemos la cantidad de esquinas
    datos >> n;
    if(n>0) {
        Grafo *g = new Grafo(n);
        //Leemos los nodos
        for(int i=0; i<n; i++) {
            //Leemos la cantidad de vecinos
            uint vecinos;
            datos >> vecinos;
            for(uint j=0; j<vecinos; j++) {
                uint v;
                datos >> v ;
                g->conectarVertices(i, v-1);
            }
        }
        return g;
    }
    else {
        return NULL;
    }
}

void escribirSalida(const char *nombreArchivo, list<set<uint> >& resultados) {
    ofstream salida(nombreArchivo);
    if(salida.good()) {
        for(list<set<uint> >::iterator it = resultados.begin(); it!=resultados.end(); it++) {
            salida << (*it).size() << endl;
            salida << "N";
            for (set<uint>::iterator its = it->begin(); its != it->end(); its++) {
                salida << " " << *its;
            }
            salida << endl;
        }
        salida.close();
    }
}

time_tt getNanosegundos(){
    struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	time_tt nanos = ts.tv_nsec;
	time_tt secs = ts.tv_sec;
	nanos += secs*1000000000;
	return nanos;
}
