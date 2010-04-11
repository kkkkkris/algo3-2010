#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <set>
#include <vector>
#include <string>
#include <ctime>
#define print(a) cout << a << endl
#define TOT_TIME 86400;

using namespace std;

string ito_hora(int secs);
int randomNumber(int hi);

int main (int argc,char* argv[]){
 
string usage ("uso: ./planillas modo file_out min max escala \n\n");
       usage +="modo = [r = random, w = worst,a= average]\n";
       usage +="min = cantidad de programadores para la planilla mas chica \n";
       usage +="max = cantidad de programadores para la planilla mas grande \n";
       usage +="escala = escala para la iteracion de las cantidades por planilla\n";

  if(argc<6){
    print("bad arguments");
    print(usage);
    return 1;
    } 
    char modo= *argv[1];
    ofstream salida(argv[2]);
    int min =atoi(argv[3]);           
    int max = atoi(argv[4]);
    int escala =atoi(argv[5]);
    
    switch(modo){  
     case 'r': { 
        srand ( time(NULL) );
        cout <<"Generando planillas random ...."<<endl;
        if(min<1 || max>2000){
        cerr<<"El minimo debe ser >=1 y el maximo <=2000 "<<endl;
        return 1;
        }
        int n,k,time1,time2,p=1;
        string str_hora;
        multiset<int> entradas;
        multiset<int> salidas;
        for(n=min;n<=max;n+=escala){
           
            cout<< "Generando planilla de "<< n <<"programadores ..."<<endl;
            salida <<"   "<<n<<endl;
            for(k=1;k<=n;k++){
                time1 = rand()%TOT_TIME;//randomNumber(tot_time);
                time2 = rand()%TOT_TIME;//randomNumber(tot_time);
                if (time1 < time2){ //pueden entrar y salir a la misma hora 
                    entradas.insert(time1); 
                    salidas.insert(time2);
                }else{
                    entradas.insert(time2);
                    salidas.insert(time1);
                } 
             }
             if(entradas.size() != salidas.size() ){
                 cerr<<"NO HAY IGUAL CANTIDAD DE ENTRADAS Y SALIDAS !!!!"<<endl;
                 cerr<<"entradas"<<entradas.size()<<"salidas"<<salidas.size()<<endl;
                 return 1;             
             }
             for( set<int>::const_iterator iter = entradas.begin();iter != entradas.end();iter++ ) {
              //convertir a string hora
               str_hora = ito_hora(*iter); 
               salida <<str_hora<<" "<<p<<endl;
               p++;
              }
              p=1;   
              for( set<int>::const_iterator iter = salidas.begin();iter != salidas.end();iter++ ) {
              //convertir a string hora
              str_hora = ito_hora(*iter); 
              salida<<str_hora<<" "<<p<<endl;
              p++;
              } 
              entradas.clear();
              salidas.clear();
              p=1; 
          }
      salida<<"   -1";
      return 0 ;
    }
    //Worst case , considero aquel en el que cada programador entra y sale al mismo instante y alternadamente
    case 'w': {
        cout<<"Generando planillas de peor caso ...";
        if(min<1 || max>2000){
        cerr<<"El minimo debe ser >=1 y el maximo <=2000 "<<endl;
        }
        int n,k,time1,p=1;
        string str_hora;
        multiset<int> entradas;
        multiset<int> salidas;
        for(n=min;n<=max;n+=escala){
    
            cout<< "Generando planilla de "<< n <<"programadores ..."<<endl;
            salida <<"   "<<n<<endl;
            for(k=1;k<=n;k++){
                time1 = k;
                entradas.insert(time1);
                salidas.insert(time1);
             }
             for( set<int>::const_iterator iter = entradas.begin();iter != entradas.end();++iter ) {
              //convertir a string hora
               str_hora = ito_hora(*iter); 
               salida <<str_hora<<" "<<p<<endl;
               p++;
              }
              p=1;   
              for( set<int>::const_iterator iter = salidas.begin();iter != salidas.end();++iter ) {
              //convertir a string hora
              str_hora = ito_hora(*iter); 
              salida<<str_hora<<" "<<p<<endl;
              p++;
              } 
              entradas.clear();
              salidas.clear();
              p=1; 
          }
      salida<<"   -1";
      return 0;
    }
    case 'a':{
        return 0;
    }
  }
}

string ito_hora(int secs){
    
     int hora=secs/3600;
     int min=(secs/60)%60;
     int sec=secs%60;
     char s[9];
     snprintf (s,9,"%.2d:%.2d:%.2d",hora,min,sec);
     return s;
    
}
int randomNumber(int hi)  //the correct random number generator for [0,hi-1]
    {
       // scale in range [0,1)
       const float scale = rand()/float(RAND_MAX);
 
       // return range [0..hi-1]
       return int(scale*hi); // implicit cast and truncation in return
   }
