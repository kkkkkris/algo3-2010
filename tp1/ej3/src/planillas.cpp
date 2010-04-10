#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <list>
#include "parser.h"
#include "file_utils.h"
#define print(a) cout << a << endl

/***
 Planilla tiene las Entradas en Planilla[0-((tam/2)-1)] y las Salidas en Planilla[(tam/2)-i] con tam =Planilla.size()
***/

using namespace std;

string usage= "uso: ./planillas entrada salida ";
int maxCant(Planilla* planilla);
string toString(int i);

int main(int argc,char* argv[]) {
 if(argc < 3){
        print("bad arguments");
        print(usage);
        return 1;
    }
    const char* entrada = argv[1];
    const char* salida = argv[2];
    string contenido = leerArchivo(entrada);
    ///////////////////////ciclo principal/////////////////////////////
    list<Planilla*> planillas = parsearInstancias(contenido);
    string resultados="";
    string buf;
    int max;
    for(list<Planilla*>::iterator it =planillas.begin();it != planillas.end();it++){
        max=maxCant(*it);
        buf=toString(max);
        resultados += buf ;
    delete (*it);
    }
    ///////////////////////////////////////////////////////////////////
    print(resultados);
    if(escribirArchivo(salida, resultados)){
        print("error escribiendo archivo");
        return 1;
    }
    return 0;
}

int maxCant(Planilla* planilla){
      string res="";
      int tam= (int) planilla->size();
       //tam siempre deberia ser par y >=2
      if(tam%2!=0 || tam<2){
          print("El tamaño de la planilla no es par o es <2 ! es");
          cout<<tam<<endl;
          return 1;
      }
      //e y s indexan las subPlanillas de Entradas y Salidas respectivamente dentro de la Planilla
      int e=0,end_e=tam/2,s=tam/2;
      int aux=0,max=0;
      //mientras haya entradas puede haber max nuevo ,luego son solo salidas,ya no nos importa contar.
      while(e<end_e){
                //cuenta los q entran antes de q salga alguno
                while(e<end_e && ((*planilla)[e] <= (*planilla)[s])){
                    aux++;
                    e++;
                }
                 //setea el max si corresponde
                if(aux>max){max=aux;}
                //cuenta los que salen antes de que entre uno nuevo
                while(e<end_e && (*planilla)[s]<(*planilla)[e]){
                    aux--;
                    s++;
                    if(s>=tam){
                        print("Se paso el contador de Salidas");
                        return 1;
                    }
                }
     }
      return max;
}
string toString(int i) {
            stringstream ss;
            ss << i <<"\n";
            return ss.str();
}