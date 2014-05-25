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
	void addObject(Object*);
	void removeObject(int);
	std::vector<Object*> getObjectByType(std::string);
	std::string getJSONStringFull();
	std::string getJSONStringModified();
	void parseJSONString(std::string);
	std::string getPosString(std::vector<std::pair<string, mat4>>*);
	std::vector<std::pair<string, mat4> >* parsePosString(std::string);
	void postTrans(int, mat4);
	void postRotate(int, mat4);
	void preTrans(int, mat4);
	void preRotate(int, mat4);
	void setModelM(int, mat4);
	void setHMove(int, int);
	void cancelHMove(int, int);
	void setVMove(int, int);
	void cancelVMove(int, int);
	void setSpeed(int, float);
	void setPendingRot(int, float);
	void pushRot(int, float);
	void jump(int);
	void setAABB(int, AABB);
	void setVelocity(int, vec3);
	void addVelocity(int, vec3);
	void clearYVelocity(int);
	void touchGround(int, bool);
	void setJumpVelocity(int, float);
	std::vector<std::string> getCommandsString();
	void setCam(int i, mat4* m);
	void setType(int i, std::string);
	void setName(int i, std::string);
	void setHealth(int i, int j);
	void setCam(int, mat4);
	mat4 getCam(int);
	void setShoot(int, bool);
	bool getShoot(int);

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

/*void gameState::setShoot(int in, bool b){
	objects->at(in)->setShoot(b);
	int exists = -1;
	for (int i = 0; i < commands->size(); ++i){
		if (commands->at(i).first == in){
			exists = i;
			break;
		}
	}
	if (exists == -1){
		commands->push_back(std::make_pair(in, "t"));
	}
	else {
		if (commands->at(exists).second.find("t") == std::string::npos)
			commands->at(exists).second.append("t");
	}
}
bool gameState::getShoot(int i){
	return objects->at(i)->getShoot();
}

void gameState::setCam(int in, mat4 m){

	objects->at(in)->setCam(m);
	int exists = -1;
	for (int i = 0; i < commands->size(); ++i){
		if (commands->at(i).first == in){
			exists = i;
			break;
		}
	}
	if (exists == -1){
		commands->push_back(std::make_pair(in, "c"));
	}
	else {
		if (commands->at(exists).second.find("c") == std::string::npos)
			commands->at(exists).second.append("c");
	}
}

mat4 gameState::getCam(int i){
	return objects->at(i)->getCam();
}*/

void gameState::setHealth(int in, int j){
	objects->at(in)->setHealth(j);
	int exists = -1;
	for (uint i = 0; i < commands->size(); ++i){
		if (commands->at(i).first == in){
			exists = i;
			break;
		}
	}
	if (exists == -1){
		commands->push_back(std::make_pair(in, "e"));
	}
	else {
		if (commands->at(exists).second.find("e") == std::string::npos)
			commands->at(exists).second.append("e");
	}
}

void gameState::setType(int i, std::string s){
	objects->at(i)->setType(s);
}

void gameState::setName(int i, std::string s){
	objects->at(i)->setName(s);
}
void gameState::postTrans(int in, mat4 m){
	objects->at(in)->postTrans(m);
	int exists = -1;
	for (uint i = 0; i < commands->size(); ++i){
		if (commands->at(i).first == in){
			exists = i;
			break;
		}
	}
	if (exists == -1)
		commands->push_back(std::make_pair(in, "p"));
	else {
		if (commands->at(exists).second.find("p") == std::string::npos)
			commands->at(exists).second.append("p");
	}
}

void gameState::postRotate(int in, mat4 m){
	objects->at(in)->postRotate(m);
	int exists = -1;
	for (uint i = 0; i < commands->size(); ++i){
		if (commands->at(i).first == in){
			exists = i;
			break;
		}
	}
	if (exists == -1)
		commands->push_back(std::make_pair(in, "p"));
	else {
		if (commands->at(exists).second.find("p") == std::string::npos)
			commands->at(exists).second.append("p");
	}
}

void gameState::preTrans(int in, mat4 m){
	objects->at(in)->preTrans(m);
	int exists = -1;
	for (uint i = 0; i < commands->size(); ++i){
		if (commands->at(i).first == in){
			exists = i;
			break;
		}
	}
	if (exists == -1)
		commands->push_back(std::make_pair(in, "p"));
	else {
		if (commands->at(exists).second.find("p") == std::string::npos)
			commands->at(exists).second.append("p");
	}
}

void gameState::preRotate(int in, mat4 m){
	objects->at(in)->preRotate(m);
	int exists = -1;
	for (uint i = 0; i < commands->size(); ++i){
		if (commands->at(i).first == in){
			exists = i;
			break;
		}
	}
	if (exists == -1)
		commands->push_back(std::make_pair(in, "p"));
	else {
		if (commands->at(exists).second.find("p") == std::string::npos)
			commands->at(exists).second.append("p");
	}
}

void gameState::setModelM(int in, mat4 m){
	objects->at(in)->setModelM(m);
	int exists = -1;
	for (uint i = 0; i < commands->size(); ++i){
		if (commands->at(i).first == in){
			exists = i;
			break;
		}
	}
	if (exists == -1)
		commands->push_back(std::make_pair(in, "p"));
	else {
		if (commands->at(exists).second.find("p") == std::string::npos)
			commands->at(exists).second.append("p");
	}
}

void gameState::setHMove(int in, int x){
	objects->at(in)->setHMove(x);
	int exists = -1;
	for (uint i = 0; i < commands->size(); ++i){
		if (commands->at(i).first == in){
			exists = i;
			break;
		}
	}
	if (exists == -1)
		commands->push_back(std::make_pair(in, "vh"));
	else {
		if (commands->at(exists).second.find("v") == std::string::npos)
			commands->at(exists).second.append("v");
		if (commands->at(exists).second.find("h") == std::string::npos)
			commands->at(exists).second.append("h");
	}
}

void gameState::cancelHMove(int in, int x){
	objects->at(in)->cancelHMove(x);
	int exists = -1;
	for (uint i = 0; i < commands->size(); ++i){
		if (commands->at(i).first == in){
			exists = i;
			break;
		}
	}
	if (exists == -1)
		commands->push_back(std::make_pair(in, "vh"));
	else {
		if (commands->at(exists).second.find("v") == std::string::npos)
			commands->at(exists).second.append("v");
		if (commands->at(exists).second.find("h") == std::string::npos)
			commands->at(exists).second.append("h");
	}
}

void gameState::setVMove(int in, int x){
	objects->at(in)->setVMove(x);
	int exists = -1;
	for (uint i = 0; i < commands->size(); ++i){
		if (commands->at(i).first == in){
			exists = i;
			break;
		}
	}
	if (exists == -1)
		commands->push_back(std::make_pair(in, "vm"));
	else {
		if (commands->at(exists).second.find("v") == std::string::npos)
			commands->at(exists).second.append("v");
		if (commands->at(exists).second.find("m") == std::string::npos)
			commands->at(exists).second.append("m");
	}
}

void gameState::cancelVMove(int in, int x){
	objects->at(in)->cancelVMove(x);
	int exists = -1;
	for (uint i = 0; i < commands->size(); ++i){
		if (commands->at(i).first == in){
			exists = i;
			break;
		}
	}
	if (exists == -1)
		commands->push_back(std::make_pair(in, "vm"));
	else {
		if (commands->at(exists).second.find("v") == std::string::npos)
			commands->at(exists).second.append("v");
		if (commands->at(exists).second.find("m") == std::string::npos)
			commands->at(exists).second.append("m");
	}
}

void gameState::setSpeed(int in, float x){
	objects->at(in)->setSpeed(x);
	int exists = -1;
	for (uint i = 0; i < commands->size(); ++i){
		if (commands->at(i).first == in){
			exists = i;
			break;
		}
	}
	if (exists == -1){
		commands->push_back(std::make_pair(in, "s"));
	}
	else {
		if (commands->at(exists).second.find("s") == std::string::npos)
			commands->at(exists).second.append("s");
	}
}

void gameState::setPendingRot(int in, float x){
	objects->at(in)->setPendingRot(x);
	int exists = -1;
	for (uint i = 0; i < commands->size(); ++i){
		if (commands->at(i).first == in){
			exists = i;
			break;
		}
	}
	if (exists == -1)
		commands->push_back(std::make_pair(in, "r"));
	else {
		if (commands->at(exists).second.find("r") == std::string::npos)
			commands->at(exists).second.append("r");
	}
}

void gameState::pushRot(int in, float x){
	objects->at(in)->pushRot(x);
	int exists = -1;
	for (uint i = 0; i < commands->size(); ++i){
		if (commands->at(i).first == in){
			exists = i;
			break;
		}
	}
	if (exists == -1)
		commands->push_back(std::make_pair(in, "r"));
	else {
		if (commands->at(exists).second.find("r") == std::string::npos)
			commands->at(exists).second.append("r");
	}
}

void gameState::jump(int in){
	objects->at(in)->jump();
	int exists = -1;
	for (uint i = 0; i < commands->size(); ++i){
		if (commands->at(i).first == in){
			exists = i;
			break;
		}
	}
	if (exists == -1)
		commands->push_back(std::make_pair(in, "v"));
	else {
		if (commands->at(exists).second.find("v") == std::string::npos)
			commands->at(exists).second.append("v");
	}
}

void gameState::setAABB(int in, AABB x){
	objects->at(in)->setAABB(x);
	int exists = -1;
	for (uint i = 0; i < commands->size(); ++i){
		if (commands->at(i).first == in){
			exists = i;
			break;
		}
	}
	if (exists == -1)
		commands->push_back(std::make_pair(in, "a"));
	else {
		if (commands->at(exists).second.find("a") == std::string::npos)
			commands->at(exists).second.append("a");
	}
}

void gameState::setVelocity(int in, vec3 x){
	objects->at(in)->setVelocity(x);
	int exists = -1;
	for (uint i = 0; i < commands->size(); ++i){
		if (commands->at(i).first == in){
			exists = i;
			break;
		}
	}
	if (exists == -1)
		commands->push_back(std::make_pair(in, "v"));
	else {
		if (commands->at(exists).second.find("v") == std::string::npos)
			commands->at(exists).second.append("v");
	}
}

void gameState::addVelocity(int in, vec3 x){
	objects->at(in)->addVelocity(x);
	int exists = -1;
	for (uint i = 0; i < commands->size(); ++i){
		if (commands->at(i).first == in){
			exists = i;
			break;
		}
	}
	if (exists == -1)
		commands->push_back(std::make_pair(in, "v"));
	else {
		if (commands->at(exists).second.find("v") == std::string::npos)
			commands->at(exists).second.append("v");
	}
}

void gameState::clearYVelocity(int in){
	objects->at(in)->clearYVelocity();
	int exists = -1;
	for (uint i = 0; i < commands->size(); ++i){
		if (commands->at(i).first == in){
			exists = i;
			break;
		}
	}
	if (exists == -1)
		commands->push_back(std::make_pair(in, "v"));
	else {
		if (commands->at(exists).second.find("v") == std::string::npos)
			commands->at(exists).second.append("v");
	}
}

void gameState::touchGround(int in, bool x){
	objects->at(in)->touchGround(x);
	int exists = -1;
	for (uint i = 0; i < commands->size(); ++i){
		if (commands->at(i).first == in){
			exists = i;
			break;
		}
	}
	if (exists == -1)
		commands->push_back(std::make_pair(in, "g"));
	else {
		if (commands->at(exists).second.find("g") == std::string::npos)
			commands->at(exists).second.append("g");
	}
}

//void gameState::setJumpVelocity(int in, float x){
//	objects->at(in)->setJumpVelocity(x);
//	int exists = -1;
//	for (int i = 0; i < commands->size(); ++i){
//		if (commands->at(i).first == in){
//			exists = i;
//			break;
//		}
//	}
//	if (exists == -1)
//		commands->push_back(std::make_pair(in, "j"));
//	else {
//		if (commands->at(exists).second.find("j") == std::string::npos)
//			commands->at(exists).second.append("j");
//	}
//}

//std::string gameState::getJSONStringFull(){
//	rapidjson::Document fromScratch;
//	fromScratch.SetObject();
//	rapidjson::Document::AllocatorType& allocator = fromScratch.GetAllocator();
//	std::string temp, temp2, temp3, temp4, temp5, temp6;
//	for (int i = 0; i < commands->size(); ++i){
//		rapidjson::Value object(rapidjson::kObjectType);
//		std::string mod = commands->at(i).second;
//		for (int j = 0; j < mod.size(); ++j){
//			rapidjson::Value array(rapidjson::kArrayType);
//			switch (mod[j]){
//			case 'p':
//				//std::cout << "p";
//				for (int k = 0; k < 4; ++k)
//				for (int l = 0; l < 4; ++l)
//					array.PushBack(objects->at(commands->at(i).first)->getModelM()[k][l], allocator);
//				object.AddMember("p", array, allocator);
//				break;
//			case 'v':
//				//	std::cout << "v";
//				array.PushBack(objects->at(commands->at(i).first)->getVelocity()[0], allocator).PushBack(objects->at(commands->at(i).first)->getVelocity()[1], allocator).PushBack(objects->at(commands->at(i).first)->getVelocity()[2], allocator);
//				object.AddMember("v", array, allocator);
//				break;
//			case 'b':
//				//std::cout << "b";
//				for (int k = 0; k < 3; ++k)
//					array.PushBack(objects->at(commands->at(i).first)->getAABB().min[k], allocator);
//				for (int k = 0; k < 3; ++k)
//					array.PushBack(objects->at(commands->at(i).first)->getAABB().max[k], allocator);
//				object.AddMember("b", array, allocator);
//				break;
//			case 's':
//				object.AddMember("s", objects->at(commands->at(i).first)->getSpeed(), allocator);
//				break;
//			case 'r':
//				//std::cout << "putting in for r : " << objects->at(commands->at(i).first)->getPendingRote() << std::endl;
//				object.AddMember("r", objects->at(commands->at(i).first)->getPendingRot(), allocator);
//				break;
//			case 'j':
//				object.AddMember("j", objects->at(commands->at(i).first)->getJumpVelocity(), allocator);
//				break;
//			case 'g':
//				object.AddMember("g", objects->at(commands->at(i).first)->getTouchGround(), allocator);
//				break;
//			case 'h':
//				object.AddMember("h", objects->at(commands->at(i).first)->getHMove(), allocator);
//				break;
//			case 'm':
//				object.AddMember("m", objects->at(commands->at(i).first)->getVMove(), allocator);
//				break;
//			case 'e':
//				object.AddMember("e", objects->at(commands->at(i).first)->getHealth(), allocator);
//				break;
//			case 't':
//				object.AddMember("t", objects->at(commands->at(i).first)->getShoot(), allocator);
//			case 'c':
//				for (int k = 0; k < 4; ++k)
//				for (int l = 0; l < 4; ++l)
//					array.PushBack(objects->at(commands->at(i).first)->getCam()[k][l], allocator);
//				object.AddMember("c", array, allocator);
//				break;
//			}
//		}
//		temp2 = "";
//		temp2 += std::to_string(commands->at(i).first);
//		fromScratch.AddMember(temp2.c_str(), object, allocator);
//	}
//	rapidjson::StringBuffer strbuf;
//	rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
//	fromScratch.Accept(writer);
//	return strbuf.GetString();
//}
//void gameState::parseJSONString(std::string str){
//	rapidjson::Document parsedFromString;
//	parsedFromString.SetObject();
//	parsedFromString.Parse<0>(str.c_str());
//
//	for (rapidjson::Value::ConstMemberIterator it = parsedFromString.MemberBegin(); it != parsedFromString.MemberEnd(); it++)
//	for (rapidjson::Value::ConstMemberIterator it2 = it->value.MemberBegin(); it2 != it->value.MemberEnd(); it2++){
//		if (it2->name.GetString() == "p"){
//			mat4 m;
//			for (rapidjson::Value::ConstMemberIterator it3 = it2->value.MemberBegin(); it3 != it2->value.MemberEnd();)
//			for (int i = 0; i < 4; ++i)
//			for (int j = 0; j < 4; ++j){
//				m[i][j] = (float)it3->value.GetDouble();
//				it3++;
//			}
//			objects->at(std::atoi(it->name.GetString()))->setModelM(m);
//		}
//		else if (it2->name.GetString() == "v"){
//			vec3 v;
//			for (rapidjson::Value::ConstMemberIterator it3 = it2->value.MemberBegin(); it3 != it2->value.MemberEnd();)
//			for (int i = 0; i < 3; ++i){
//				v[i] = (float)it3->value.GetDouble();
//				it3++;
//			}
//			objects->at(std::atoi(it->name.GetString()))->setVelocity(v);
//		}
//		else if (it2->name.GetString() == "b"){
//			AABB box;
//			vec3 v1, v2;
//			for (rapidjson::Value::ConstMemberIterator it3 = it2->value.MemberBegin(); it3 != it2->value.MemberEnd();){
//				for (int i = 0; i < 3; ++i){
//					v1[i] = (float)it3->value.GetDouble();
//					it3++;
//				}
//				for (int i = 0; i < 3; ++i){
//					v2[i] = (float)it3->value.GetDouble();
//					it3++;
//				}
//			}
//			box.min = v1;
//			box.max = v2;
//			objects->at(std::atoi(it->name.GetString()))->setAABB(box);
//		}
//		else if (it2->name.GetString() == "s"){
//			objects->at(std::atoi(it->name.GetString()))->setSpeed((float)it2->value.GetDouble());
//		}
//		else if (it2->name.GetString() == "r"){
//			objects->at(std::atoi(it->name.GetString()))->setPendingRot((float)it2->value.GetDouble());
//		}
//		else if (it2->name.GetString() == "j"){
//			objects->at(std::atoi(it->name.GetString()))->setJumpVelocity((float)it2->value.GetDouble());
//		}
//		else if (it2->name.GetString() == "g"){
//			objects->at(std::atoi(it->name.GetString()))->setJumpVelocity((float)it2->value.GetDouble());
//		}
//		else if (it2->name.GetString() == "h"){
//			objects->at(std::atoi(it->name.GetString()))->setHMove((float)it2->value.GetDouble());
//		}
//		else if (it2->name.GetString() == "m"){
//			objects->at(std::atoi(it->name.GetString()))->setVMove((float)it2->value.GetDouble());
//		}
//		else if (it2->name.GetString() == "e"){
//			objects->at(std::atoi(it->name.GetString()))->setHealth((float)it2->value.GetInt());
//		}
//		else if (it2->name.GetString() == "t"){
//			objects->at(std::atoi(it->name.GetString()))->setShoot((it2->value.GetBool()));
//		}
//		else if (it2->name.GetString() == "c"){
//			mat4 m;
//			for (rapidjson::Value::ConstMemberIterator it3 = it2->value.MemberBegin(); it3 != it2->value.MemberEnd();)
//			for (int i = 0; i < 4; ++i)
//			for (int j = 0; j < 4; ++j){
//				m[i][j] = (float)it3->value.GetDouble();
//				it3++;
//			}
//			objects->at(std::atoi(it->name.GetString()))->setCam(m);
//		}
//	}
//
//
//	std::vector<Object* > poop;
//
//}

std::string gameState::getPosString(std::vector<std::pair<string, mat4>>* v){
	rapidjson::Document fromScratch;
	fromScratch.SetObject();
	rapidjson::Document::AllocatorType& allocator = fromScratch.GetAllocator();
	rapidjson::Value array(rapidjson::kArrayType);
	std::string temp;
	for (uint h = 0; h < v->size(); ++h){
		rapidjson::Value array(rapidjson::kArrayType);
		for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j){
			temp = "";
			temp += std::to_string(v->at(h).second[i][j]);
			array.PushBack(v->at(h).second[i][j], allocator);
		}
		fromScratch.AddMember(v->at(h).first.c_str(), array, allocator);
	}

	rapidjson::StringBuffer strbuf;
	rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
	fromScratch.Accept(writer);
	return strbuf.GetString();

}

std::vector<std::pair<string, mat4> >* gameState::parsePosString(std::string str){
	rapidjson::Document parsedFromString;
	parsedFromString.SetObject();
	parsedFromString.Parse<0>(str.c_str());
	std::vector<std::pair<string, mat4> >* pos = new std::vector<std::pair<string, mat4> >;
	if (!parsedFromString["player1"].IsNull()){
		float nums[16] = { 0.0 };
		int k = 0;
		for (int i = 0; i < 4; ++i){
			for (int j = 0; j < 4; ++j){
				nums[i * 4 + j] = (float)parsedFromString["player1"][k].GetDouble();
				k++;
			}
		}

		glm::mat4 bbb = (glm::make_mat4(nums));
		pos->push_back(std::make_pair("player1", bbb));
	}
	if (!parsedFromString["player2"].IsNull()){
		float nums[16] = { 0.0 };
		int k = 0;
		for (int i = 0; i < 4; ++i){
			for (int j = 0; j < 4; ++j){
				nums[i * 4 + j] = (float)parsedFromString["player2"][k].GetDouble();
				k++;
			}
		}

		glm::mat4 bbb = (glm::make_mat4(nums));
		pos->push_back(std::make_pair("player2", bbb));
	}
	if (!parsedFromString["player3"].IsNull()){
		float nums[16] = { 0.0 };
		int k = 0;
		for (int i = 0; i < 4; ++i){
			for (int j = 0; j < 4; ++j){
				nums[i * 4 + j] = (float)parsedFromString["player3"][k].GetDouble();
				k++;
			}
		}

		glm::mat4 bbb = (glm::make_mat4(nums));
		pos->push_back(std::make_pair("player3", bbb));
	}
	if (!parsedFromString["player4"].IsNull()){
		float nums[16] = { 0.0 };
		int k = 0;
		for (int i = 0; i < 4; ++i){
			for (int j = 0; j < 4; ++j){
				nums[i * 4 + j] = (float)parsedFromString["player4"][k].GetDouble();
				k++;
			}
		}

		glm::mat4 bbb = (glm::make_mat4(nums));
		pos->push_back(std::make_pair("player4", bbb));
	}


	return pos;
}



//void gameState::addObject(Object* obj){
//
//	if (openIndices.size() == 0){
//		objects->push_back(obj);
//		obj->setGameStateIndex(objects->size() - 1);
//
//		commands->push_back(std::make_pair(objects->size() - 1, "pvbsrjghme"));
//	}
//	else {
//		objects->at(openIndices.back()) = obj;
//		obj->setGameStateIndex(openIndices.back());
//		openIndices.pop_back();
//		commands->push_back(std::make_pair(openIndices.back(), "pvbsrjghme"));
//	}
//
//}

void gameState::removeObject(int i){
	//cout << "remove object\n";
	delete objects->at(i);
	objects->at(i) = NULL;
	openIndices.push_back(i);
}

std::vector<Object*> gameState::getObjectByType(string type){
	std::vector<Object*> res;
	for (uint i = 0; i < objects->size(); ++i)
	if (objects->at(i)->getType() == type)
		res.push_back(objects->at(i));

	return res;
}

std::string gameState::matToString(mat4 m){
	std::string temp = "";
	for (int i = 0; i < 4; ++i)
	for (int j = 0; j < 4; ++j){
		temp += m[i][j];
		temp += " ";
	}
	return temp;
}
std::string gameState::vecToString(vec3 v){
	std::string temp = "";
	temp += v[0];
	temp += " ";
	temp += v[1];
	temp += " ";
	temp += v[2];
	temp += " ";
	return temp;
}
std::string gameState::floatToString(float f){
	return std::to_string(f);
}
std::string gameState::AABBToString(AABB a){
	std::string temp = "";
	for (int i = 0; i < 3; ++i){
		temp += a.min[i];
		temp += " ";
	}
	for (int i = 0; i < 3; ++i){
		temp += a.max[i];
		temp += " ";
	}
	return temp;
}
std::string gameState::intToString(int i){
	return std::to_string(i);
}
std::string gameState::boolToString(bool b){
	return std::to_string(b);
}
