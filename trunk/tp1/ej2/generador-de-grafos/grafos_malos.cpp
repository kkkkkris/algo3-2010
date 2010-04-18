//Graph generator 1.0

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <vector>
#include <cassert>
#include <sstream>

using namespace std;

class Grafo{
public:
    Grafo(int n): tam(n), grados(n,0), adyacencia(n, vector<bool>(n, false)){};
    void conectar(int i, int j);
    bool sonAdyacentes(int i, int j);
    int getGrado(int i);
    bool isDirac();
    bool isOre();
    string toString();
private:
    int tam;
    vector<vector<bool> > adyacencia;
    vector<int> grados;
};

int main(int argc, char* argv[]){
    if(argc < 4){
        cout << "usage: " << argv[0] << " salida min max" << endl;
        return 1;
    }
    
    //archivo de salida
    ofstream salida(argv[1]);
    //seteamos la semillita
    srand(time(NULL));
    //cantidad minima de vertices
    int min = atoi(argv[2]);
    assert(min > 4);
    //cantidad maxima de vertices
    int max = atoi(argv[3]);
    assert(min <= max);
    
    //Generamos grafos entre min y max vertices
    for(int n = min; n <= max ; n++){
        cout << "Generando grafo de " << n << " vertices" << endl;
        //generamos 10 grafos con n vertices
        //coloco la cantidad de vertices del grafo
        salida << "   " << n << endl;
        //generamos el grafo
        Grafo g(n);
        for(int i=0; i<n - 2 ;i++){
            for(int j=i+1; j < n -2; j++){
                g.conectar(i,j);
            }
        }
        g.conectar(0,n-2);
        g.conectar(1,n-2);
        g.conectar(0,n-1);
        g.conectar(1,n-1);
        if(g.isDirac()){
            cout << "Dirac no va" << endl;
        }
        
        if(g.isOre()){
            cout << "Ore no va" << endl;
        }
        
        //escribo los nodos
        salida << g.toString();
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


string Grafo::toString() {
    stringstream salida;
    for(int i=0; i< tam; i++){
        salida << this->getGrado(i) << "    ";
        for(int j=0; j<tam; j++){
            if(this->sonAdyacentes(i,j)){
                salida << j+1 << " ";
            }
        }
        salida << endl;
    }
    return salida.str();
}
