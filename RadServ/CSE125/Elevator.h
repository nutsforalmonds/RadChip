#pragma once
#include "VAO.h"
#include "glslprogram.h"
#include "Structures.h"
#include "Object.h"
#include <array>
#include <vector>
using namespace std;

class Elevator : public Object{
public:
	Elevator(void){ push = vec3(0, 0, 0); players = new vector<Object*>(); direction = 0; }
	void setPush(vec3& v){ push = v; }
	vec3 getPush(){ return push; }
	void addPlayer(Object* i){
		players->push_back(i);
	}
	vector<Object*> getPlayers(){
		return *players;
	}
	void removeAll(){
		players->clear();
	}
	void setDirection(int i){
		direction = i;
	}
	int getDirection(){
		return direction;
	}
private:
	vec3 push;
	int direction;
	vector<Object*>* players;
};