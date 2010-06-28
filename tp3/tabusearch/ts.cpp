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

void leerEntrada(const char *nombreArchivo, list<Grafo>& listaCiudades);
void escribirSalida(const char *nombreArchivo, list<uint>& listaResultados);
time_tt getNanosegundos();

int main(int argc, char* argv[]) {
    if(argc < 3){
        cout << "Parametros insuficientes" << endl;
        return 1;
    }
    
    const char* entrada 	= argv[1];
    const char* salida 		= argv[2];
    int maxIter				= atoi(argv[3]);
    //double alpha 			= atof(argv[3]);
    //double beta 			= atof(argv[4]);
    
    //Lista de grafos
    list<Grafo> listaGrafos;
    //Leemos los grafos
    leerEntrada(entrada, listaGrafos);
    
    list<uint> resultados;
    list<pair<long long, time_tt> > tiempos;
    
    for(list<Grafo>::iterator it = listaGrafos.begin(); it!=listaGrafos.end(); it++) {
        time_tt min_time;
        uint maxClique = 0;
        
        /*
        for(int k=0; k<5; k++){
            time_tt start = getNanosegundos();
            esOrientable = it->esOrientable();
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
        uint n = it->getCantidadVertices();
        uint m = it->getCantidadAristas();
        tiempos.push_back(pair<long long, time_tt>(n*(n+m), min_time));
        */    
        
        maxClique = ((*it).maxClique(maxIter)).size();
        resultados.push_back(maxClique);
        cout << maxClique << endl;
    }
    
    escribirSalida(salida, resultados);
    
    /*
    ofstream o("tiempos");
    if(o.good()){
        for(list<pair<long long, time_tt> >::iterator it = tiempos.begin(); it!=tiempos.end(); it++){
            o << it->first << "\t" << it->second << endl;
        }
        o.close();
    }
    */
    return 0;
}

void leerEntrada(const char *nombreArchivo, list<Grafo>& listaGrafos) {
    ifstream datos(nombreArchivo);
    while(datos.good()) {
        int n;
        //Leemos la cantidad de esquinas
        datos >> n;
        if(n>0) {
            //Nuevo grafo
            Grafo g(n);
            //Leemos los nodos
            for(int i=0; i<n; i++) {
                //Leemos la cantidad de vecinos
                uint vecinos;
                datos >> vecinos;
                for(uint j=0; j<vecinos; j++) {
                    uint v;
                    datos >> v ;
                    g.conectarVertices(i, v-1);
                }
            }
            listaGrafos.push_back(g);
        }
        else {
            break;
        }
    }
    
    datos.close();    
}

void escribirSalida(const char *nombreArchivo, list<uint>& resultados) {
    ofstream salida(nombreArchivo);
    if(salida.good()) {
        for(list<uint>::iterator it = resultados.begin(); it!=resultados.end(); it++) {
            salida << (*it) << endl;
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
