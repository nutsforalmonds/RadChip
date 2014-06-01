#pragma once
#include "VAO.h"
#include "glslprogram.h"
#include "Structures.h"
#include "Object.h"
#include <array>
#include <vector>
using namespace std;

class Trampoline : public Object{
public:
	Trampoline(void){ boost = vec3(0, 0, 0); }
	void setBoost(vec3& v){ boost = v; }
	vec3 getBoost(){ return boost; }
private:
	vec3 boost;
};