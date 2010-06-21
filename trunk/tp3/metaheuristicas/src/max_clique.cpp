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

string usage = "uso:  ./maxclique entrada salida";

int main(int argc, char* argv[]) {

    if(argc < 3){
        print("bad arguments");
        print(usage);
        return 1;
    }
    const char* entrada = argv[1];
    const char* salida = argv[2];
    ofstream testingOutput((string(entrada)+string(".times")).c_str());
    string contenido = leerArchivo(entrada);
    list<Grafo*> instancias =  parsearInstancias(contenido);
    Timer timer;
    string resultados = "";
    int i = 1;
    set<int>* cliquemax;
    for(list<Grafo*>::iterator it = instancias.begin(); it != instancias.end(); it++) {
            timer.nueva();
            timer.empezar();
            cliquemax = (*it)->HC();
            timer.terminar();
            //escribo la medicion con el formato n  time(en nanosegundos)
            if(testingOutput.good()){
                testingOutput << (*it)->length() << "\t" << timer.getUltimaMedicion() << endl;
            }

            resultados += toString(cliquemax);
            i++;
            delete (*it);
    }
    string t("tiempos");
    //escribirArchivo( (t + string(entrada)).c_str(), timer.tiempos());

    if(escribirArchivo(salida, resultados)){
        print("error escribiendo archivo");
        return 1;
    }
    return 0;
}
