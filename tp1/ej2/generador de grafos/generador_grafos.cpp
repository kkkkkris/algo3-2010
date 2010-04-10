//Graph generator 1.0

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <set>

using namespace std;

int main(int argc, char* argv[]){
    if(argc < 4){
        cout << "usage: " << argv[0] << " salida min max" << endl;
        return 1;
    }
    
    //seteamos la semillita
    srand(time(NULL));
    //cantidad minima de vertices
    int min = atoi(argv[2]);
    //cantidad maxima de vertices
    int max = atoi(argv[3]);    
    //archivo de salida
    ofstream salida(argv[1]);
    
    //Generamos grafos desde 10 hasta 50 vertices
    for(int n = min; n <= max ; n++){
        cout << "Generando grafo de " << n << " vertices" << flush;
        //generamos 10 grafos con n vertices
        for(int i = 0; i < 10; i++){
            cout << "." << flush;
            //coloco la cantidad de vertices del grafo
            salida << "   " << n << endl;
            //Colocamos los n vertices
            for(int k = 1; k <= n; k++){
                //Elegimos al azar la cantidad de vertices adyacentes
                int adyacentes = rand() % n;
                salida << adyacentes << "    ";
                set<int> verticesUsados;
                while(adyacentes > 0){
                    int nodoAdyacente = (rand()%n) +1;
                    //evitamos las aristas que salen y vuelven al mismo vertice, ya que no queremos alumnas con problemas psicologicos
                    //ademas verificamos que no hayamos usado el vertices para no hacer un multigrafo (que entre dos vertices haya mas de 1 arista)
                    if( (nodoAdyacente != k) && (verticesUsados.find(nodoAdyacente) == verticesUsados.end()) ){
                        salida << nodoAdyacente << " ";
                        verticesUsados.insert(nodoAdyacente);
                        adyacentes--;
                    }
                }
                salida << endl;
            }
        }
        cout << endl;
    }
    salida << -1 << endl;

    salida.close();
    
    return 0;
}
