#pragma once
#include "VAO.h"
#include "glslprogram.h"
#include "Structures.h"
#include "Object.h"
#include <array>
#include <vector>
using namespace std;

class Teleporter : public Object{
public:
	Teleporter(void){ endpoint = mat4(1.0); }
	void setEndpoint(mat4& v){ endpoint = v; }
	mat4 getEndpoint(){ return endpoint; }
private:
	mat4 endpoint;
};