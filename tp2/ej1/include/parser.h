#ifndef __PARSER__
#define __PARSER__

#include <list>
#include <string>

#define Table int**
#define number 0
#define long_up 1
#define pred_up 2
#define long_down 3
#define pred_down 4
using namespace std;

list<Table> parsearInstancias(string entrada);

#endif //__PARSER__
