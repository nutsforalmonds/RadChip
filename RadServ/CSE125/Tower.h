#pragma once
#include <stdlib.h>
#include <time.h>
//#include <Window.h>
#include "VAO.h"
#include "glslprogram.h"
#include "Structures.h"
#include "Object.h"
#include <array>
#include <vector>
using namespace std;

class Tower : public Object{
public:
	Tower(){
		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&last_shoot);
		interval = 1;
	}
	void setLastShoot(LARGE_INTEGER t){ last_shoot = t; }
	LARGE_INTEGER getLastShoot(){ return last_shoot; }
	void setInterval(float d){ interval = d; }
	float getInterval(){ return interval; }
	bool checkShoot(LARGE_INTEGER t){
		if (((double)t.QuadPart - (double)last_shoot.QuadPart) / (double)freq.QuadPart > interval){
			return true;
		}
		return false;
	}

private:
	LARGE_INTEGER last_shoot,freq;
	float interval;
};