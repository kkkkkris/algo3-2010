#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <list>
#include "parser.h"
#include "file_utils.h"
#include "timer.h"
#define Table int**
#define print(a) cout << a << endl

using namespace std;

string usage = "uso:  ./unimodal entrada salida tiempos";
string toString(int i);
int calcularMin(Table t);
void llenar_up(Table tabla,int i);
void llenar_down(Table tabla,int i);
int unimodalMax(Table tabla);
void tabla_toS(Table t);
void list_toS(list<Table> tablas);
void destructor(Table t);

int main(int argc, char* argv[]) {

    if(argc < 4){
        print("bad arguments");
        print(usage);
        return 1;
    }

    const char* entrada = argv[1];
    const char* salida = argv[2];
    const char* tiempos = argv[3];
    string res_tiempos;
    string contenido = leerArchivo(entrada);
    string buf;
    int res ;
    list<Table>::iterator it; //en main primero todas las declaraciones antes de funciones!?

    list<Table> list =parsearInstancias(contenido);
    Timer timer(false);
///oooooooooooooooooooooCICLO PRINCIPALoooooooooooooooooooooooooo///
    contenido="";
    for(it=list.begin();it!=list.end();it++){
        timer.nueva((*it)[0][number]);
        timer.empezar();
        res=calcularMin(*it);
        timer.terminar();
        buf=toString(res);
        contenido+=buf;
        //tabla_toS(*it);
        //cout<<"Min cant de eliminaciones :"<<buf<<endl;
        destructor(*it);
    }
    res_tiempos="Tamaño de secuencia     Tiempo \n";
    res_tiempos+=timer.tiempos();
///oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo///
    print(res_tiempos);
    print("Resultados :");
    print(contenido);

    if(escribirArchivo(salida, contenido)){
        print("error escribiendo archivo");
        return 1;
    }
    if(escribirArchivo(tiempos,res_tiempos)){
        print("error escribiendo tiempos en archivo");
        return 1;
    }
    return 0;
}
string toString(int i) {
            stringstream ss;
            ss << i <<"\n";
            return ss.str();
}

int calcularMin(Table tabla){
   //llenar long y pred
    int size=tabla[0][number],i,maxunimodal;
    for(i=1;i<size+1;i++){
        llenar_up(tabla,i);
    }
    for(i=size;i>0;i--){
        llenar_down(tabla,i);
    }
    maxunimodal=unimodalMax(tabla);
    return size-maxunimodal;
}


void llenar_up(Table tabla,int i){
    int longi,j,num;
    num=tabla[i][number];
    longi=0;
    //dame el predecesor maximo
    for(j=i-1;j>0;j--){
        if(tabla[j][number]<num && tabla[j][long_up]>longi){
            longi=tabla[j][long_up];
       }
    }
    //////////////////////////
    if(longi==0){
       tabla[i][long_up]=1;
    }else{
       tabla[i][long_up]=longi+1;
    }
}

void llenar_down(Table tabla,int i){
    int longi,j,size,num;
    size=tabla[0][number];
    num=tabla[i][number];
    longi=0;
   //dame el predecesor maximo
    for(j=i+1;j<size+1;j++){
        if(tabla[j][number]<num && tabla[j][long_down]>longi){
              longi=tabla[j][long_down];
        }
    }
    //////////////////////////
    if(longi==0){
       tabla[i][long_down]=1;
    }else{
       tabla[i][long_down]=longi+1;
    }
}
int unimodalMax(Table tabla){
    int size,k,max,aux,maxup_actual,i_maxup_actual,i_aux;
    size=tabla[0][number];
    max=tabla[1][long_down];   //seteo 1º caso base
    maxup_actual=tabla[1][long_up];
    i_maxup_actual=1;

    for(k=1;k<size;k++){
        //si el actual es mayor al maxup_actual (de los tabla[1..k-1][long_up]
        if(tabla[k][long_up]>maxup_actual){
            maxup_actual=tabla[k][long_up];
            i_maxup_actual=k;
            aux=maxup_actual+tabla[k+1][long_down];
            i_aux=k;
        }else{//si el actual no es mayor, tomo el maxup_actual
            aux=tabla[i_maxup_actual][long_up]+tabla[k+1][long_down];
            i_aux=i_maxup_actual;
        }
        //si supero al max acum
        if(aux>max){
            //si extremos a mergear son != acumulo aux
            if(tabla[i_aux][number] != tabla[k+1][number]){
                max=aux;
            }else{//si son iguales, el max sera aux-1 ,que en el peor caso sera = al max anterior
                max=aux-1;
            }
        }
    }
    if(tabla[size][long_up]>max){  //2º caso base
        max =tabla[size][long_up];
    }
    return max;
}
void tabla_toS(Table t){
    int size=t[0][number],i=1;
    print("tabla -->");
    for(i=1;i<size+1;i++){
        cout<<t[i][long_down];
    }
    cout<<endl;
    for(i=1;i<size+1;i++){
        cout<<t[i][number];
    }
    cout<<endl;
    for(i=1;i<size+1;i++){
        cout<<t[i][long_up];
    }
    cout<<endl;
}
void list_toS(list<Table> tablas){
     int size;
     for(list<Table>::iterator it=tablas.begin();it != tablas.end();it++){
        size=(*it)[0][number];
        cout<<"tabla -->"<<endl;
        cout<<"size :"<<size<<endl;
        for(int i=1;i<size+1;i++){
            cout<<(*it)[i][number]<<"-";
        }
        cout<<endl<<"fin" <<endl;
     }
}
void destructor(Table t){
    int size=t[0][number]+1;
    for(int i=0;i<size;i++){
         delete[] t[i];
    }
    delete t;
}
