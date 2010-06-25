#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <list>
#include "graph.h"
#include "parser.h"
#include "file_utils.h"
#include "timer.h"

#define print(a) cout << a << endl

using namespace std;

string usage = "uso:  ./maxclique entrada salida [optimizado]";

int main(int argc, char* argv[]) {
    
    if(argc < 3 || argc > 4){
        print("bad arguments");
        print(usage);
        return 1;
    }
    const char* entrada = argv[1];
    const char* salida = argv[2];
    bool mejorado = argc == 4; 
    //ofstream testingOutput((string(entrada)+string(".times")).c_str());
    string contenido = leerArchivo(entrada);
    list<Grafo*> instancias =  parsearInstancias(contenido);
    Timer timer;
    std::stringstream aux;
    string resultado = "";
    string resultados = "";
    list<int>* nodos_ids = NULL;
    int i = 1;
    cout << "\n";
    for(list<Grafo*>::iterator it = instancias.begin(); it != instancias.end(); it++) {
        cout << "Grafo #" << i << endl;
        nodos_ids = new list<int>();
        timer.nueva();
        timer.empezar();
        (*it)->maxClique(nodos_ids, mejorado);
        timer.terminar();
        //escribo la medicion con el formato n  time(en nanosegundos)
        /*if(testingOutput.good()){
            testingOutput << (*it)->length() << "\t" << timer.getUltimaMedicion() << endl;
        }*/
        aux << nodos_ids->size();
        resultado = aux.str() + "\n" + "N ";
        for(list<int>::iterator itS = nodos_ids->begin(); itS != nodos_ids->end(); itS++){
            aux.str("");
            aux << (*itS);
            if(itS != nodos_ids->begin())
                resultado += " ";
            resultado += aux.str();
        }
        aux.str("");
        resultado += "\n";
        print(resultado);
        resultados += resultado;
        i++;
        delete (*it);
    }
    //string t("tiempos");
    //escribirArchivo( (t + string(entrada)).c_str(), timer.tiempos());
    
    if(escribirArchivo(salida, resultados)){
        print("error escribiendo archivo");
        return 1;
    }
    return 0;
}
