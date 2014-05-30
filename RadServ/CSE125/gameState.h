#include "rapidjson\document.h"
#include "rapidjson\stringbuffer.h"
#include "rapidjson\filestream.h"
#include "rapidjson\prettywriter.h"
#include "rapidjson\rapidjson.h"
#include "rapidjson\reader.h"
#include "rapidjson\writer.h"
#include "Object.h"
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

class gameState
{

public:
	gameState();
	~gameState();
	std::string getPosString(std::vector<std::pair<string, mat4>>*);
	std::vector<std::pair<string, mat4> >* parsePosString(std::string);

	//helpers
	std::string matToString(mat4);
	std::string vecToString(vec3);
	std::string floatToString(float);
	std::string AABBToString(AABB);
	std::string intToString(int);
	std::string boolToString(bool);
private:
	std::vector<Object*>* objects;
	std::vector<std::pair<int, std::string> >* commands;
	std::vector<std::pair<int, mat4*>>* cams;
	std::vector<int> openIndices;

};

gameState::gameState()
{
	objects = new std::vector<Object*>;
	commands = new std::vector<std::pair<int, string>>;
}

gameState::~gameState()
{
}

std::string gameState::getPosString(std::vector<std::pair<string, mat4>>* v){

	// Begin json
	std::string str = "[";
	for (uint h = 0; h < v->size(); ++h){
		// Player ID
		str += "\"";
		str += v->at(h).first.c_str();
		// Begin mat4 array
		str += "\",[";
		for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j){
			str += std::to_string(v->at(h).second[i][j]);
			if (i == 3 && j == 3);
			else str += ",";
		}
		if (h < (v->size() - 1))
			str += "],";
		else
			str += "]";

	}
	str += "]";

	return str;
}