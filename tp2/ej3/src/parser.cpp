
#include "parser.h"
#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace std;

list<Grafo*> parsearInstancias(string entrada){
    list<Grafo*> grafos;
    list<int>** nodos = NULL;
    int* llaves = NULL;
    bool* puertas = NULL;
    stringstream in(entrada);
    string line;
    int aristas, puertas_t, n, p, m;
    aristas = 0;
    while(!in.eof() && aristas != -1){
        getline(in, line);
        if(aristas > 0){
            /* todavia me falta cargar este grafo */
            if (puertas_t > 0){
                /* me quedan puertas por ver*/
                stringstream par(line);
                int indice;
                par >> indice;
                par >> llaves[indice-1];
                //cout << "        La llave en " << indice << " abre la puerta " << llaves[indice-1] << endl;
                puertas[(llaves[indice-1])-1] = true;
                puertas_t--;
            }
            else{
                /* solo me queda ver el pasillo */
                stringstream nodo(line);
                int n1, n2;
                nodo >> n1;
                nodo >> n2;
                //cout << "        Hay un pasillo entre " << n1 << " y " << n2 << endl;
                nodos[n1-1]->push_back(n2);
                nodos[n2-1]->push_back(n1);
                aristas--;
            }
        }
        else {
            if(nodos != NULL) {
                /* se termino un grafo */
                //cout << "    * Instancia con " << n << " nodos, " << m << " aristas y " << p << " puertas." << endl;
                grafos.push_back(new Grafo(n, m, p, nodos, llaves, puertas));
                if (nodos != NULL){
                    delete nodos;
                    delete llaves;
                    delete puertas;
                }
                /*
                int k;
                cout << "llaves = [";
                for(k = 0; k < n; k++){
                    cout << llaves[k];
                    if(k != (n-1)){cout << ", ";}
                }
                cout << "]" << endl;
                cout << "puertas = [";
                for(k = 0; k < n; k++){
                    cout << puertas[k];
                    if(k != (n-1)){cout << ", ";}
                }
                cout << "]" << endl;
                */
            }
            /* nuevo grafo */
            stringstream ss(line);
            ss >> n;
            ss >> p;
            ss >> m;
            aristas = m;
            puertas_t = p;
            if(aristas != -1) {
                /* no termino el archivo */
                nodos = new list<int>*[n];
                llaves = new int[n];
                puertas = new bool[n];
                for(int i = 0; i < n; i++){
                    nodos[i] = new list<int>();
                    llaves[i] = -1;
                    puertas[i] = false;
                }
            }
        }   
    }
    return grafos;
}

