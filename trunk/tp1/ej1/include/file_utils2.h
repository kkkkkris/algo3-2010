#ifndef __FILE_UTILS__
#define __FILE_UTILS__
using namespace std;

/**
 * Lee la sigueinte línea de un archivo de texto.
 * Asigna a b y a n los valores que corresponden.
 * Devuelve false si no se puede realizar la lectura o si la línea contiene un -1. 
 * */
bool leerArchivo(const char* filename, long long int& b, long long int& n);

/**
 * Escribe en el archivo el valor pasado como parámetro.
 * Devuelve false si falla.
 */
bool escribirArchivo(const char* filename, string res);

#endif
