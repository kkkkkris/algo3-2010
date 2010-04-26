#include <cassert>
#include <iostream>
#include <sstream>
#include <ctime>
#include "timer.h"

using namespace std;

time_tt tomar_tiempo(); 

Timer::Timer() {
	midiendo = false;
	time = 0;
	autogenerado = true;
	current_id = 0;
}

Timer::Timer(bool is_autogenerado) {
	midiendo = false;
	time = 0;
	autogenerado = is_autogenerado;
}

void Timer::nueva() {
	assert(autogenerado);
	assert(!midiendo);
	current_id++;
	time = 0;
}

void Timer::nueva(int id) {
	assert(!autogenerado);
	assert(!midiendo);
	current_id = id;
	time = 0;
}

void Timer::empezar() {
	assert(time == 0);
	time = tomar_tiempo();
	midiendo = true;
}

void Timer::terminar() {
	assert(midiendo);
	time_tt fin, total;
	fin = tomar_tiempo();
	assert(fin > time);
	total = fin - time;
	medicion esta_medicion;
	esta_medicion.id = current_id;
	esta_medicion.time = total;
	mediciones.push_back(esta_medicion);
	midiendo = false;
}

string Timer::tiempos() {
	string res;
	stringstream ss;
	for(list<medicion>::iterator it = mediciones.begin(); it != mediciones.end(); it++) {
		ss << it->id;
		ss << "\t\t\t\t";
		ss << it->time;
		ss << "\n";
	}
	res = ss.str();
	return res;
}

time_tt tomar_tiempo() {
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	time_tt nanos = ts.tv_nsec;
	time_tt secs = ts.tv_sec;
	nanos += secs*1000000000;
	return nanos;
}



	


