#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;
/**
 * lee un archivo de texto y devuelve su contenido en un string 
 * */
string leerArchivo(const char* filename){
    string res = "";
    string line;
    ifstream data(filename);
    if (data.is_open()) {
        while (! data.eof() ) {
            getline(data, line);
            res += line + '\n';
        }
        data.close();
    }
    return res;
}

/**
 * escribe content en el archivo, true si fallo
 */
bool escribirArchivo(const char* filename, string content) {
    ofstream salida(filename);
    if (salida.is_open()) {
        salida << content;
        salida.close();
    } else {
        return true;
    }
    return false;
}
