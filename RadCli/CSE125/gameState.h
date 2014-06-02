#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filestream.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/reader.h"
#include "rapidjson/writer.h"
#include "Object.h"
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "constants.h"

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
	std::vector<std::pair<string, mat4> >* pos;

};

gameState::gameState()
{
	objects = new std::vector<Object*>;
	commands = new std::vector<std::pair<int, string>>;
	pos = new std::vector<std::pair<string, mat4> >;
}

gameState::~gameState()
{
}

std::vector<std::pair<string, mat4> >* gameState::parsePosString(std::string str){
	rapidjson::Document str_;
	str_.SetArray();
	str_.Parse<0>(str.c_str());
	pos->clear();

	for (int x = 0; x < NUMOFVECS * 2; x = x + 2)
	{
		//if (!str_[(rapidjson::SizeType)(x + 1)].IsNull())
		//{
		float nums[16] = { 0.0 };
		int k = 0;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				const rapidjson::Value& val = str_[(rapidjson::SizeType)(x + 1)];
				nums[i * 4 + j] = (float)val[k].GetDouble();
				k++;
			}
		}
		glm::mat4 mat = (glm::make_mat4(nums));
		pos->push_back(std::make_pair(str_[(rapidjson::SizeType)x].GetString(), mat));
		//}
	}
	return pos;
}