#include <iostream>
#include <fstream>
#include <grafo.hpp>
#include <list>
#include <types.hpp>

using namespace std;

void leerEntrada(const char *nombreArchivo, list<Grafo>& listaCiudades);
void escribirSalida(const char *nombreArchivo, list<bool>& listaResultados);

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
    
    for(list<Grafo>::iterator it = listaCiudades.begin(); it!=listaCiudades.end(); it++) {
        if(it->esOrientable()) {
            resultados.push_back(true);
            cout << "fuertemente conexo" << endl;
        }
        else {
            resultados.push_back(false);
            cout << "no" << endl;
        }
    }
    
    //escribirSalida(salida, resultados);
    
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
                    g.conectarVertices(i, v);
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
            //escribir...
        }
    }
}
