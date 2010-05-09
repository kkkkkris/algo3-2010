#include <iostream>
#include <fstream>
#include <grafo.hpp>
#include <list>
#include <utility>
#include <types.hpp>
#include <ctime>

typedef unsigned long int time_tt;

using namespace std;

void leerEntrada(const char *nombreArchivo, list<Grafo>& listaCiudades);
void escribirSalida(const char *nombreArchivo, list<bool>& listaResultados);
time_tt getNanosegundos();

int main(int argc, char* argv[]) {
    
    if(argc < 3){
        cout << "Parametros insuficientes" << endl;
        return 1;
    }
    
    const char* entrada = argv[1];
    const char* salida = argv[2];
    
    //Lista de ciudades
    list<Grafo> listaCiudades;
    //Leemos las ciudades
    leerEntrada(entrada, listaCiudades);
    
    list<bool> resultados;
    list<pair<long long, time_tt> > tiempos;
    
    for(list<Grafo>::iterator it = listaCiudades.begin(); it!=listaCiudades.end(); it++) {
        /*
        time_tt min_time;
        bool esOrientable;
        
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
        if(it->esOrientable()) {
            resultados.push_back(true);
        }
        else {
            resultados.push_back(false);
        }       
    }
    
    escribirSalida(salida, resultados);
    
    /*
    ofstream o("tiempos");
    if(o.good()){
        for(list<pair<long long, time_tt> >::iterator it = tiempos.begin(); it!=tiempos.end(); it++){
            o << it->first << "\t" << it->second << endl;
        }
        o.close();
    }*/
    
    return 0;
}

void leerEntrada(const char *nombreArchivo, list<Grafo>& listaCiudades) {
    ifstream datos(nombreArchivo);
    while(datos.good()) {
        int n;
        //Leemos la cantidad de esquinas
        datos >> n;
        if(n>0) {
            //Nueva ciudad
            Grafo g(n);
            //Leemos las n esquinas
            for(int i=0; i<n; i++) {
                //Leemos la cantidad de esquinas vecinas
                uint vecinas;
                datos >> vecinas;
                for(uint j=0; j<vecinas; j++) {
                    uint v;
                    datos >> v ;
                    g.conectarVertices(i, v-1);
                }
            }
            listaCiudades.push_back(g);
        }
        else {
            break;
        }
    }
    
    datos.close();    
}

void escribirSalida(const char *nombreArchivo, list<bool>& resultados) {
    ofstream salida(nombreArchivo);
    if(salida.good()) {
        for(list<bool>::iterator it = resultados.begin(); it!=resultados.end(); it++) {
            if (*it){
                salida << "fuertemente conexo";
            }
            else{
                salida << "no";
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
