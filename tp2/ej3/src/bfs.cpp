#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include "parser.h"
#include "file_utils.h"
#include "timer.h"

#define print(a) cout << a << endl

using namespace std;

string usage = "uso:  ./bfs entrada salida [tiempos]";


int main(int argc, char* argv[]) {
    
    bool calcularTiempo = false;
    if (argc < 3 || argc > 4) {      
        cerr << "bad arguments" << endl;
        cerr << usage << endl;
        return 1;
    }
    if (argc == 4) {calcularTiempo = true;}
    
    Timer timer;
    const char* entrada = argv[1];
    const char* salida = argv[2];
    bool libre;
    cout << "Leyendo el archivo de entrada ..." << endl;
    string contenido = leerArchivo(entrada);
    cout << "... archivo leido exitosamente." << endl;
    cout << "Parseando el archivo de entrada ..." << endl;
    list<Grafo*> instancias = parsearInstancias(contenido);
    cout << "... el parseo termino exitosamente." << endl;
    
    cout << "Comenzando a procesar las instancias ..." << endl;
    contenido = "";
    for(list<Grafo*>::iterator it = instancias.begin(); it != instancias.end(); it++){
        if (calcularTiempo) {
            timer.nueva();
            timer.empezar();
        }
        libre = (*it)->bfsMejorado();
        if (calcularTiempo) {
            timer.terminar();
        }
        
        if(libre){
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
    
    if (calcularTiempo) {
        cout << "Escribiendo los tiempos de ejecucion en el archivo correspondiente ..." << endl;
        if(escribirArchivo(argv[3], timer.tiempos())){
            cout << "ERROR: hubo un problema al escribir los tiempos de ejecución." << endl;
            return 1;
        }
        cout << "El archivo con los tiempos de ejecucion se ha escrito exitosamente ..." << endl;
    }
    
    return 0;
}
