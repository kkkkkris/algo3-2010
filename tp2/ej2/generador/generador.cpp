#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]){
    cout << "Generando..." << flush;
    
    int min = atoi(argv[1]);
    int max = atoi(argv[2]);
    
    ofstream output("peorcaso.in");
    
    if(output.good()) {
        for(int n = min; n < max; n++)
        {
            output << n << endl;
            for(int i=0; i<n; i++){
                //hago +n porque el operador % hace algo como (-1)%10 = -1
                output << 2 << '\t' << (i-1+n)%n + 1 << " " << (i+1+n)%n + 1 << endl;
            }
        }    
        output << -1 << endl;
        
        output.close();
    }
    
    cout << "listo!" << endl;
    
    return 0;
}
