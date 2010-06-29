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
ostream& operator<<(ostream&, const set<int>&);
string usage = "uso:  ./maxclique modo=[HC/HL] entrada  ";

int main(int argc, char* argv[]) {

    if(argc < 3){
        print("bad arguments");
        print(usage);
        return 1;
    }
    const char* modo = argv[1];
    const char* entrada = argv[2];
    size_t pos =string(entrada).find_last_of(".");
    string encabezado=string(entrada).substr(0,pos)+string(modo);
    string salida = encabezado +string(".out");
    ofstream testingOutput((encabezado+string(".times")).c_str());
    string contenido = leerArchivo(entrada);
    list<Grafo*> instancias =  parsearInstancias(contenido);
    Timer timer;
    string resultados = "";
    int i = 1;
    set<int> cliquemax;
    string HC("HC");
    string HL("HL");
    if (modo ==HC){
        for(list<Grafo*>::iterator it = instancias.begin(); it != instancias.end(); it++) {
                timer.nueva();
                timer.empezar();
                cliquemax = (*it)->HC();
                /** debug **********/
                string valido = (*it)->validar(cliquemax)? "si":"no";
                cout << "es valido?: " << valido << endl;
                cout<< "Clique max : " << cliquemax << endl;
                /**********************/
                timer.terminar();
                //escribo la medicion con el formato n  time(en nanosegundos)
                if(testingOutput.good()){
                    testingOutput << (*it)->length() << "\t" << timer.getUltimaMedicion() << endl;
                }

                resultados += toString(cliquemax);
                i++;
                delete (*it);
        }
    } else if (modo ==HL) {
            for(list<Grafo*>::iterator it = instancias.begin(); it != instancias.end(); it++) {
                timer.nueva();
                timer.empezar();
                cliquemax = (*it)->HL();
                /** debug **********/
                /*string valido = (*it)->validar(cliquemax)? "si":"no";
                cout << "es valido?: " << valido << endl;
                cout<< "Clique max : " << cliquemax << endl;*/
                /**********************/
                timer.terminar();
                //escribo la medicion con el formato n  time(en nanosegundos)
                if(testingOutput.good()){
                    testingOutput << (*it)->length() << "\t" << timer.getUltimaMedicion() << endl;
                }

                resultados += toString(cliquemax);
                i++;
                delete (*it);
        }
    } else {
        cout << "WROOONG" << endl;
    }
    string t("tiempos");
    escribirArchivo( (t + encabezado).c_str(), timer.tiempos());

    if(escribirArchivo(salida.c_str(), resultados)){
        print("error escribiendo archivo");
        return 1;
    }
    return 0;
}
