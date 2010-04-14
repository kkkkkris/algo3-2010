#include <iostream>
#include <sstream>
#include <string.h>
#include <cstdlib>
#include <list>
#include "modulo.h"
#include "file_utils.h"
#include "parser.h"
#include "timer.h"

using namespace std;


string usage = "uso: ./ej1 entrada salida [tiempos]";

int main(int argc, char* argv[]) {

    bool calcularTiempo = false;
    if (argc < 3 || argc > 4) {      
        cerr << "bad arguments" << endl;
        cerr << usage << endl;
        return 1;
    }
    if (argc == 4) {calcularTiempo = true;}

    Timer timer;
    long long int b = 0;
    long long int n = 0;
    long long int mod = 0;
    cout << "Leyendo archivo de entrada ..." << endl;
    string contenido = leerArchivo(argv[1]);
    cout << "Parseando instancias ..." << endl;
    list<long long int> instancias = parsearInstancias(contenido);
    stringstream resultados;

    cout << "Realizando calculos ..." << endl;
    for(list<long long int>::iterator it = instancias.begin(); it != instancias.end() && (*it) != -1; it++) {
        b = (*it);
        it++;
        n = (*it);
        if ((b < 0) || (n < 1)) {
            cerr << "    ERROR: b no puede ser negativo y/o n no puede ser menor a 1." << endl;
            return 1;
        }
        cout << "    " << b << "^" << n << " (mod " << n << ") = ";
        if (calcularTiempo) {
    		timer.nueva();
		    timer.empezar();
        }
        mod = modulo(b, n, n);
        if (calcularTiempo) {
            timer.terminar();
        }
        cout << mod << endl;
        resultados << mod << "\n";
    }
    cout << "... calculos terminados" << endl;

    cout << "Escribiendo los resultados en el archivo de salida ..." << endl;    
    if(escribirArchivo(argv[2], resultados.str())){
        cout << "ERROR: hubo un problema al escribir el archivo de salida." << endl;
        return 1;
    }

    if (calcularTiempo) {
        cout << "Escribiendo los tiempos de ejecucion en el archivo correspondiente ..." << endl;
        if(escribirArchivo(argv[3], timer.tiempos())){
            cout << "ERROR: hubo un problema al escribir los tiempos de ejecución." << endl;
            return 1;
        }
    }

    return 0;
}

