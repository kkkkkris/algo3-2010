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
    int size();
    bool isDirac();
    bool isOre();
private:
    int tam;
    vector<vector<bool> > adyacencia;
    vector<int> grados;
};

int main(int argc, char* argv[]){
    if(argc < 5){
        cout << "usage: " << argv[0] << " salida min max proba=1..100" << endl;
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
    //archivo de salida
    ofstream salida(argv[1]);
    
    //Generamos grafos entre min y max vertices
    int sumGrados;
    for(int n = min; n <= max ; n++){
        cout << "Generando grafo de " << n << " vertices" << flush;
        //generamos 5 grafos con n vertices
        for(int k = 0; k < 5; k++){
            //coloco la cantidad de vertices del grafo
            salida << "   " << n << endl;
            //generamos el grafo
            Grafo g(n);
            sumGrados = 0;
            for(int i=0; i<n ;i++){
                for(int j=i+1; j<n; j++){
                    if((rand() % 100) < proba){
                        g.conectar(i,j);
                        sumGrados++;
                    }
                }
            }
            
            // si no tiene aristas le agrego una
            if(sumGrados == 0){
                int posicionAgregar = rand() % n;
                g.conectar(posicionAgregar, posicionAgregar==n-1?0:posicionAgregar+1);
            }
            // si es completo saco al menos una arista
            else if(sumGrados == (g.size())*(g.size()-1)){
                int cantABorrar = rand() % n;
                if(cantABorrar == 0){cantABorrar = n;}
                for(int b = 0; b < cantABorrar; b++){
                    g.reducirGrado(b, 1);
                }
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

int Grafo::size(){
    return tam;
}

void Grafo::reducirGrado(int i, int g){
    for(int j=0; j<tam && g>0; j++){
        if(adyacencia[i][j]){
            desconectar(i,j);
            g--;
        }
    }
}
