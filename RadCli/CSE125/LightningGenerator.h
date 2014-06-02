#pragma once
#include "VAO.h"
#include "glslprogram.h"
#include "Structures.h"
#include "Object.h"
#include <array>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
using namespace std;

class LightningGenerator{
public:
	LightningGenerator(void){
		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&lastTime);
		srand(time(NULL));
	}
	bool generate(vector<vec2>& pos, int num){
		QueryPerformanceCounter(&currentTime);
		if (((double)currentTime.QuadPart - (double)lastTime.QuadPart) / (double)freq.QuadPart > dt){
			pos.clear();
			for (int i = 0; i < num; i++){
				pos.push_back(vec2(rand() % size - size / 2, rand() % size - size / 2));
			}
			lastTime = currentTime;
			return true;
		}
		return false;
	}
	void setSize(int s){ size = s; }
	void setDt(float d){ dt = d; }
private:
	int size;
	float dt;//time between two lightnings
	LARGE_INTEGER lastTime,currentTime,freq;
};