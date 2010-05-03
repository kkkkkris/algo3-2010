#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <ctime>
#define print(a) cout << a << endl
#define TOT_TIME 40;

using namespace std;

int randomNumber(int hi);

int main (int argc,char* argv[]){
 
string usage ("uso: ./secuencias modo file_out min max  \n\n");
       usage +="modo = [r = random, w = worst,a= average]\n";
       usage +="min = tamaño de la secuencia minima \n";
       usage +="max = tamaño de la secuencia maxima \n";
       usage +="escala = escala para iterar tamaños entre min max \n";
  if(argc<6){
    print("bad arguments");
    print(usage);
    return 1;
    } 
    char modo= *argv[1];
    ofstream salida(argv[2]);
    int min =atoi(argv[3]);           
    int max = atoi(argv[4]);
    int escala = atoi(argv[5]);
    
    switch(modo){  
     case 'r': { 
        srand ( time(NULL) );
        cout <<"Generando planillas random ...."<<endl;
        if(min<1 || max>800){
        cerr<<"El minimo debe ser >=1 y el maximo <=800 "<<endl;
        return 1;
        }
        int n,k,s;
        for(n=min;n<=max;n+=escala){
            cout<< "Generando secuencia de "<< n <<"numeros ..."<<endl;
            salida <<n<<" ";
            for(k=1;k<=n;k++){
                s = rand()%TOT_TIME;//randomNumber(tot_time);
                salida<<s<<" ";                 
             }
            salida<<endl;
          }
      salida<<"-1";
      return 0 ;
    }
    //Worst case ,
    case 'w': {
//        cout<<"Generando planillas de peor caso ...";
//        if(min<1 || max>500){
//        cerr<<"El minimo debe ser >=1 y el maximo <=500 "<<endl;
//        }
//        int n,k,s;
//           for(n=min;n<=max;n++){
//            cout<< "Generando secuencia de "<< n <<"numeros ..."<<endl;
//            salida <<n<<" ";
//            for(k=1;k<=n;k++){
//                s = rand()%TOT_TIME;//randomNumber(tot_time);
//                salida<<s<<" ";                 
//             }
//            salida<<endl;
//          }
//      salida<<"-1";
    return 0;
    }
    case 'a':{
        return 0;
    }
  }
}


int randomNumber(int hi)  //the correct random number generator for [0,hi-1]
    {
       // scale in range [0,1)
       const float scale = rand()/float(RAND_MAX);
 
       // return range [0..hi-1]
       return int(scale*hi); // implicit cast and truncation in return
   }
