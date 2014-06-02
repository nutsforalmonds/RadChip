#pragma once
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/vector_angle.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "constants.h"



//#define PSPEEDINDEX 2

using glm::mat4;

class ParseOpts
{
public:
	ParseOpts()
	{
	}
	~ParseOpts()
	{

	}

	bool getShoot(std::vector <std::pair<std::string, mat4>>* vec, int pid, int& shootID)
	{
		for (i = 0; i < 3; i++)
		{
			if (atoi(&((*vec)[i].first.c_str())[0]) == pid)
				break;
		}

		if ((*vec)[i].first.c_str()[SHOOTBIT] == 's')
		{
			std::string shoot_id = (*vec)[i].first.substr(SHOOT_ID_BEGIN,SHOOT_ID_END+1-SHOOT_ID_BEGIN);
			shootID = atoi(shoot_id.c_str());
			return true;
		}
		else
		{
			return false;                 
		}
	}

	//int getPSpeed(std::vector <std::pair<std::string, mat4>>* vec, int pid)
	//{
	//	speed = "";
	//	for (i = 0; i < 3; i++)
	//	{
	//		if (atoi(&((*vec)[i].first.c_str())[0]) == pid)
	//			break;
	//	}

	//	for (j = 0; j < PSPEEDLEN; j++)
	//	{
	//		speed += (*vec)[i].first.c_str()[PSPEEDINDEX + j];
	//	}


	//	return atoi(speed.c_str());
	//}

	bool getDamaged(std::vector <std::pair<std::string, mat4>>* vec, int pid)
	{
		for (i = 0; i < 3; i++)
		{
			if (atoi(&((*vec)[i].first.c_str())[0]) == pid)
				break;
		}

		if ((*vec)[i].first.c_str()[DAMAGEDBIT] == 'd')
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool getKilled(std::vector <std::pair<std::string, mat4>>* vec, int pid)
	{
		for (i = 0; i < 3; i++)
		{
			if (atoi(&((*vec)[i].first.c_str())[0]) == pid)
				break;
		}

		if ((*vec)[i].first.c_str()[KILLEDBIT] == 'k')
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	int getPHealth(std::vector <std::pair<std::string, mat4>>* vec, int pid)
	{
		health = "";
		/*for (i = 0; i < 3; i++)
		{
			if (atoi(&((*vec)[i].first.c_str())[0]) == pid)
				break;
		}*/

		for (j = PHEALTH_BEGIN; j < PHEALTH_END; j++)
		{
			health += (*vec)[i].first.c_str()[PHEALTH_BEGIN + j];
		}


		return atoi(health.c_str());
	}

	int getPKills(std::vector <std::pair<std::string, mat4>>* vec, int pid)
	{
		kills = "";
		/*for (i = 0; i < 3; i++)
		{
		if (atoi(&((*vec)[i].first.c_str())[0]) == pid)
		break;
		}*/

		for (j = PKILLS_BEGIN; j < PKILLS_END; j++)
		{
			kills += (*vec)[i].first.c_str()[PKILLS_BEGIN + j];
		}


		return atoi(kills.c_str());
	}

	// Parameters are the pointer to the recvVec vector and the desired player ID
	/*bool getShoot(std::vector <std::pair<std::string, mat4>>* vec, int pid)
	{
	// Determine which index of the recvVec is the player we want
	for (i = 0; i < 3; i++)
	{
	if (atoi(&((*vec)[i].first.c_str())[0]) == pid)
	break;
	}

	// Extract player's (i) info from the #defined SHOOTBIT flag in the string
	if ((*vec)[i].first.c_str()[SHOOTBIT] == 's')
	{
	return true;
	}
	// Must have placeholder false value to maintain constant string length for index
	else
	{
	return false;
	}
	}*/

	std::vector<int> getPPDL(std::vector <std::pair<std::string, mat4>>* vec)
	{
		std::vector<int> result;
		std::string s = (*vec)[PPDL_MAT].first;
		for (int um = 0; um < s.length(); um += 3){
			result.push_back(atoi(s.substr(um,3).c_str()));
		}
		return result;
	}

private:
	//std::vector <std::pair<std::string, mat4>>& vec_;
	bool shoot;
	std::string health, kills, speed;
	int i, j;
};