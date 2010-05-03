#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include "parser.h"
#include "file_utils.h"

#define print(a) cout << a << endl

using namespace std;

string usage = "uso:  ./bfs entrada salida";


int main(int argc, char* argv[]) {
    
    if(argc < 3){
        print("bad arguments");
        print(usage);
        return 1;
    }
    const char* entrada = argv[1];
    const char* salida = argv[2];
    cout << "Leyendo el archivo de entrada ..." << endl;
    string contenido = leerArchivo(entrada);
    cout << "... archivo leido exitosamente." << endl;
    cout << "Parseando el archivo de entrada ..." << endl;
    list<Grafo*> instancias = parsearInstancias(contenido);
    cout << "... el parseo termino exitosamente." << endl;
    
    cout << "Comenzando a procesar las instancias ..." << endl;
    contenido = "";
    for(list<Grafo*>::iterator it = instancias.begin(); it != instancias.end(); it++){
        if((*it)->bfsMejorado()){
            contenido += "libre\n";
            cout << "    libre" << endl;
        }
        else{
            contenido += "no\n";
            cout << "    no" << endl;
        }
    }
    cout << "... todas las instancias se procesaron exitosamente." << endl;
    
    cout << "Escribiendo el archivo de salida ..." << endl;
    if(escribirArchivo(salida, contenido)){
        print("error escribiendo archivo");
        return 1;
    }
    cout << "El archivo se ha escrito exitosamente ..." << endl;
    return 0;
}
