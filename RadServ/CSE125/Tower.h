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
	void setShootRange(float r){ shoot_range = r; }
	float getShootRange(){ return shoot_range; }
	void setShootSpeed(float s){ shoot_speed = s; }
	float getShootSpeed(){ return shoot_speed; }
	void setDamage(int d){ damage = d; }
	int getDamage(){ return damage; }
	void setLastShootID(int id){ last_shoot_id = id; }
	int getLastShootID(){ return last_shoot_id; }
	void setLastShootDir(vec3 dir){ last_shoot_dir = dir; }
	vec3 getLastShootDir(){ return last_shoot_dir; }
private:
	LARGE_INTEGER last_shoot,freq;
	float interval;
	float shoot_range;
	float shoot_speed;
	int damage;
	int last_shoot_id;
	vec3 last_shoot_dir;
};