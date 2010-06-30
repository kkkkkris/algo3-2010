#ifndef __TYPES__H__
#define __TYPES__H__

typedef unsigned int uint;
struct TabuInfo{
    uint nodo;
    uint usosHistorico;
    uint usosConsecutivos;
    uint tiempo; //iteraciones que pasaron desde la ultima vez que se actualizo algun valor 
};
#endif //__TYPES__H__
