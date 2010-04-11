#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include "parser.h"

using namespace std;

int parsearHora(string hora);

list<Planilla*> parsearInstancias(string entrada){
    list<Planilla*> planillas;
    Planilla planilla;

    stringstream in(entrada);
    int horas_size=0,pos=0,p=1;

    while(!in.eof() && horas_size != -1){
        string line;
        getline(in,line);
        if(pos < horas_size){                   //parsea las horas ,las transforma en int [0-86399] y las pone en planilla
        planilla.push_back(parsearHora(line));
        pos++;
        }else{                                  //cierra y guarda anterior instancia si existe e inicia proxima instancia si no se termino
            if(!planilla.empty()){
//                cout<<"Planilla #"<<(horas_size/2)<<": [";
//                for(Planilla::iterator it =planilla.begin();it != planilla.end();it++){
//                    cout<<*it<<",";
//                }
//                cout<<"]"<<endl;
                p++;
                vector<int>* pl = new vector<int>(planilla);
                planillas.push_back(pl);
            }
            horas_size=2*(atoi(line.c_str()));  //dame tam de la prox planilla
            if(horas_size !=-1){                //si no es el final reseteo planilla
                pos=0;
                planilla.clear();
            }
        }
    }
    return planillas;
}

int parsearHora(string hora) {
    int res;
    if(hora.size()>8){
        res = atoi(hora.substr(0,2).c_str())*3600 ;   //c_str() convierte string a char[]
        res+= atoi(hora.substr(3,2).c_str())*60;
        res+= atoi(hora.substr(6,2).c_str())*1;
    }else{
        cout<<"fuera de rango substr"<<endl;
        return 1;
    }
    return res;
}
