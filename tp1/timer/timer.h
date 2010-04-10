#ifndef __TIMER__H__
#define __TIMER__H__
#include <list>
#include <string>

using namespace std;

typedef unsigned long long int time_tt;

typedef struct {
	int id;
	time_tt time;
} medicion;

class Timer{

	private:
		bool midiendo;
		time_tt time;
		list<medicion> mediciones;
		bool autogenerado;
		int current_id;
	public:
		Timer();
		Timer(bool);
		void nueva();
		void nueva(int id);
		void empezar();
		void terminar();
		string tiempos();
};

#endif
