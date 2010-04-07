#include <iostream>
#include <cstdlib>


using namespace std;

/* esto no funciona, probar con la función recursiva
// calcula b^n mod n
// requiere b>=0 y n>0
long long int modulo(long long int b, long long int n);
*/

long long int modulo(long long int b, long long int m, long long int n);

string usage = "uso: ./ej1 b n";

int main(int argc, char* argv[]){
    
    if(argc != 3){
        cerr << "bad arguments" << endl;
        cerr << usage << endl;
        return 1;
    }

    long long int b = atoll(argv[1]);
    long long int n = atoll(argv[2]);

    if ((b < 0) || (n < 1)){
        cerr << "ERROR: b no puede ser negativo y/o n no puede ser menor a 1.";
        return 1;
    }

//    long long int res = modulo(b, n);
    long long int res = modulo(b, n, n);

    cout << b << "^" << n << " mod " << n << " = " << res << endl;

    return 0;
}

long long int modulo(long long int b, long long int m, long long int n){

    if (m == 1){
        return (b % n);
    }

    long long int aux = modulo(b, m/2, n);
    aux = ((aux * aux) % n);
    if ((m % 2) == 1){
        aux = ((aux * b) % n);
    }

    return (aux % n);

}

/* esto no funciona, probar con la función recursiva

// calcula b^n mod n
long long int modulo(long long int b, long long int n){
    
    // estos casos los hago aparte porque son molestos y fáciles
    if ((n == 1) || (b == 0)){return 0;}
    
    if (b == 1){return 1;}

    // ahora puedo suponer que b>1 y n>1  

    long long int res = (b % n);
    long long int m = n;
    while (m > 1){
        res = ((res * res) % n);
        m = m/2;
    }

    long long int res2 = 1;
    m = n;
    while (m > 1){
        res2 = ((res2 * res2) % n);
        if (m % 2 == 1){
            res2 = ((res2 * b) % n);
        }       
        m = m/2;
    }

    res = ((res * res2) % n);

    return res;
}
*/

