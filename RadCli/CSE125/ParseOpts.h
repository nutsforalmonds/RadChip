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
#include "Structures.h"



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

	void getTowerShoot(std::vector <std::pair<std::string, mat4>>* vec,  vector<TowerShootInfoClient>& tsi){
		tsi.clear();
		for (int i = TOWER_MAT_BEGIN; i < TOWER_MAT_END+1; i++){
			if ((*vec)[i].first.c_str()[0] == 'T'){
				int towerID = atoi((*vec)[i].first.substr(TOWER_ID,1).c_str());
				int projectileID = atoi((*vec)[i].first.substr(TOWER_SHOOT_ID_BEGIN, TOWER_SHOOT_ID_END + 1 - TOWER_SHOOT_ID_BEGIN).c_str());
				vec3 direction;
				direction[0] = atoi((*vec)[i].first.substr(DIR_0_BEGIN, DIR_0_END + 1 - DIR_0_BEGIN).c_str()) / 100000.0-1;
				direction[1] = atoi((*vec)[i].first.substr(DIR_1_BEGIN, DIR_1_END + 1 - DIR_1_BEGIN).c_str()) / 100000.0-1;
				direction[2] = atoi((*vec)[i].first.substr(DIR_2_BEGIN, DIR_2_END + 1 - DIR_2_BEGIN).c_str()) / 100000.0-1;
				//cout << "dirrrrr: " << direction[0] << " " << direction[1] << " " << direction[2] << endl;
				tsi.push_back(TowerShootInfoClient(towerID,projectileID,direction));
			}
		}
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

		for (j = PHEALTH_BEGIN; j <= PHEALTH_END; j++)
		{
			health += (*vec)[pid].first.c_str()[j];
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

		for (j = PKILLS_BEGIN; j <= PKILLS_END; j++)
		{
			kills += (*vec)[pid].first.c_str()[j];
		}

		return atoi(kills.c_str());
	}

	int getPPowerUp(std::vector <std::pair<std::string, mat4>>* vec, int pid)
	{
			pUp = (*vec)[pid].first.c_str()[POWER_UP_STATUS];

		return atoi(pUp.c_str());
	}

	bool getTramp(std::vector <std::pair<std::string, mat4>>* vec, int pid)
	{
		if ((*vec)[pid].first.c_str()[TRAMP_STATUS] == 't')
		{
			return true;
		}
		else
		{
			return false;
		}
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
	std::string health, kills, speed, pUp;
	int i, j;
};