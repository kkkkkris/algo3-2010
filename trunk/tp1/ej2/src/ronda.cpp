#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <list>
#include "graph.h"
#include "parser.h"
#include "file_utils.h"

#define print(a) cout << a << endl

using namespace std;

string usage = "uso:  ./ronda entrada salida";


int main(int argc, char* argv[]) {
    
    if(argc < 3){
        print("bad arguments");
        print(usage);
        return 1;
    }
    const char* entrada = argv[1];
    const char* salida = argv[2];
    string contenido = readFile(entrada);
    
    
    
    
    if(writeFile(salida, contenido)){
        print("error escribiendo archivo");
        return 1;
    }
    return 0;
}
