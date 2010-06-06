//Graph generator 1.0

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <vector>

using namespace std;

class Grafo{
public:
    inline Grafo(int n): tam(n), grados(n,0), adyacencia(n, vector<bool>(n, false)){};
    void conectar(int i, int j);
    void desconectar(int i, int j);
    bool sonAdyacentes(int i, int j);
    void reducirGrado(int i, int g);
    int getGrado(int i);
    bool isDirac();
    bool isOre();
private:
    int tam;
    vector<vector<bool> > adyacencia;
    vector<int> grados;
};

int main(int argc, char* argv[]){
    if(argc < 6){
        cout << "usage: " << argv[0] << " salida min max proba=1..100 consider-optimizations=true|false" << endl;
        return 1;
    }
    
    //seteamos la semillita
    srand(time(NULL));
    //cantidad minima de vertices
    int min = atoi(argv[2]);
    //cantidad maxima de vertices
    int max = atoi(argv[3]);
    //La probabilidad de que un nodo tenga muchos vecinos es random
    int proba = atoi(argv[4]);
    //generar grafos que no cumplan los casos de optimizacion
    bool considerarOptimizaciones = true;
    if(strcmp("true", argv[5])){
        cout << "NO considerando optimizaciones" << endl;
        considerarOptimizaciones = false;
    }
    //archivo de salida
    ofstream salida(argv[1]);
    
    //Generamos grafos entre min y max vertices
    for(int n = min; n <= max ; n++){
        cout << "Generando grafo de " << n << " vertices" << flush;
        //generamos 10 grafos con n vertices
        for(int k = 0; k < 10; k++){
            //coloco la cantidad de vertices del grafo
            salida << "   " << n << endl;
            //generamos el grafo
            Grafo g(n);
            for(int i=0; i<n ;i++){
                for(int j=i+1; j<n; j++){
                    if((rand() % 100) < proba){
                        g.conectar(i,j);
                    }
                }
            }
            
            if(considerarOptimizaciones){          
                if(g.isDirac()){
                    bool dirac = true;
                    for(int i=0; i<n && dirac; i++){
                        if( g.getGrado(i) >= (n/2 + n%2) ){
                            g.reducirGrado(i, g.getGrado(i)-(n/2 + n%2)+1);
                            dirac = false;
                        }
                    }    
                }
                
                if(g.isOre()){
                    bool ore = true;
                    for(int i=0; i<n && ore; i++){
                        for(int j=i+1; j<n && ore; j++){
                            if(g.getGrado(i)+g.getGrado(j) >= n){
                                //reduzco el grado del que tiene mas grado
                                if(g.getGrado(i)>g.getGrado(j)){
                                    g.reducirGrado(i, g.getGrado(i)+g.getGrado(j)-n+1);
                                }
                                else{
                                    g.reducirGrado(j, g.getGrado(i)+g.getGrado(j)-n+1);
                                }
                                ore = false;
                            }
                        }
                    }
                }
                /*
                //detectamos vertices con grado < 2            
                for(int i=0; i<n; i++){
                    if(g.getGrado(i)<2){
                        
                    }
                }    
                */
            }
            
            //escribo los nodos
            for(int i=0; i<n; i++){
                salida << g.getGrado(i) << "    ";
                for(int j=0; j<n; j++){
                    if(g.sonAdyacentes(i,j)){
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

void Grafo::conectar(int i, int j){
    adyacencia[i][j]=true;
    adyacencia[j][i]=true;
    grados[i]++;
    grados[j]++;
}

void Grafo::desconectar(int i, int j){
    adyacencia[i][j]=false;
    adyacencia[j][i]=false;
    grados[i]--;
    grados[j]--;
}

bool Grafo::isDirac(){
    bool dirac = true;
    for(int i=0; i<tam; i++){
        if(grados[i] < (tam/2 + tam%2)){
            dirac = false;
        }
    }
    return dirac;
}

bool Grafo::isOre(){
    bool ore = true;
    for(int i=0; i<tam && ore; i++){
        for(int j=i+1; j<tam && ore; j++){
            if(grados[i]+grados[j] < tam){
                ore = false;
            }
        }
    }
    return ore;
}

int Grafo::getGrado(int i){
    return grados[i];
}

bool Grafo::sonAdyacentes(int i, int j){
    return adyacencia[i][j];
}

void Grafo::reducirGrado(int i, int g){
    for(int j=0; j<tam && g>0; j++){
        if(adyacencia[i][j]){
            desconectar(i,j);
            g--;
        }
    }
}
