//Graph generator 1.0

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

int main(int argc, char* argv[]){
    if(argc < 4){
        cout << "usage: " << argv[0] << " salida min max proba" << endl;
        return 1;
    }
    
    //seteamos la semillita
    srand(time(NULL));
    //cantidad minima de vertices
    int min = atoi(argv[2]);
    //cantidad maxima de vertices
    int max = atoi(argv[3]);
    //probabilidad de que el par de vertices v,u sean adyacentes
    int proba = 50;
    if(argc > 4){
        proba = atoi(argv[4]);
    }
    //archivo de salida
    ofstream salida(argv[1]);
    
    //Generamos grafos desde 10 hasta 50 vertices
    for(int n = min; n <= max ; n++){
        cout << "Generando grafo de " << n << " vertices" << flush;
        //generamos 10 grafos con n vertices
        for(int k = 0; k < 1; k++){
            //coloco la cantidad de vertices del grafo
            salida << "   " << n << endl;
            //generamos el grado
            bool grafo[n][n];
            vector<int> grados(n,0);
            for(int i=0; i<n ;i++){
                grafo[i][i] = false;
                for(int j=i+1; j<n; j++){
                    if((rand() % 100) < proba){
                        grafo[i][j]=true;
                        grafo[j][i]=true;
                        grados[i]++;
                        grados[j]++;
                    }
                    else{
                        grafo[i][j]=false;
                        grafo[j][i]=false;
                    }
                }
            }
            
            //escribo los nodos
            for(int i=0; i<n; i++){
                salida << grados[i] << "    ";
                for(int j=0; j<n; j++){
                    if(grafo[i][j]){
                        salida << j+1 << " ";
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
