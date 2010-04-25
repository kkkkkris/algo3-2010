
#include "parser.h"
#include <string.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#define print(a) cout<<a<<endl;


using namespace std;

Table parsearSecu(string secu,int& secu_size);
void list_toS(list<Table> tablas);
void destructor(Table t);

list<Table> parsearInstancias(string entrada){
    int secu_size=0;
    char* str;
    char* pch;
    string line;
    stringstream in(entrada);
    Table tabla;
    list<Table> tablas;
    while(!in.eof() && secu_size != -1){
	    getline(in,line);
        str=strdup(line.c_str());//strdup duplica el const char* ,y devuelve char*,sino con el const char* no podemos operar
        pch=strtok(str," ");     //obtengo el token (separador por espacios)
        secu_size=atoi(pch);
	    if(secu_size!=-1){       //si no llegue al final parseo tabla y agrego a la lista
            tabla=parsearSecu(line,secu_size);
            tablas.push_back(tabla);
	    }
    }
    return tablas;
}

Table parsearSecu(string secu,int& secu_size) {
    int aux,i;
    char* str;
    char* pch;
    //tomo el size de la secuencia
    str=strdup(secu.c_str());
    pch=strtok(str," ");
    secu_size=atoi(pch);
    //creo tabla
    Table tabla =new int*[secu_size+1];
    for(i=0;i<secu_size+1;i++){
        tabla[i]=new int[5];
     }
     //convencion:en el primer elemento del array guardo el size
     tabla[0][number]=secu_size;
	 i=1;
	 //agrego secuencia a la tabla
	 while(pch != NULL && i<secu_size+1){
		 pch = strtok(NULL," ");
		 aux=atoi(pch);
		 tabla[i][number]=aux;
		 i++;
	 }
    return tabla;
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
    int size=t[0][number];
    for(int i=0;i<size;i++){
         delete[] t[i];
    }
    delete[] t;
}
