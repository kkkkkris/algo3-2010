#include <iostream>
#include "timer.h"

using namespace std;

int main() {

	Timer timer;
	for(int x = 0; x < 100; x++) {
		timer.nueva();
		timer.empezar();
		int t = 0;
		for(int y = 0; y < 100*x*x; y++) {
			t += y;	
		}
		timer.terminar();
	}

	cout << timer.tiempos()<< endl;

	return 0;
}
