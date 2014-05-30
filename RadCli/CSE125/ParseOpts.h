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

#define SHOOTBIT 1

#define PSPEEDINDEX 2
#define PSPEEDLEN 3

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

	bool getShoot(std::vector <std::pair<std::string, mat4>>* vec, int pid)
	{
		for (i = 0; i < 3; i++)
		{
			if (atoi(&((*vec)[i].first.c_str())[0]) == pid)
				break;
		}

		if ((*vec)[i].first.c_str()[SHOOTBIT] == 's')
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	int getPSpeed(std::vector <std::pair<std::string, mat4>>* vec, int pid)
	{
		speed = "";
		for (i = 0; i < 3; i++)
		{
			if (atoi(&((*vec)[i].first.c_str())[0]) == pid)
				break;
		}

		for (j = 0; j < PSPEEDLEN; j++)
		{
			speed += (*vec)[i].first.c_str()[PSPEEDINDEX + j];
		}


		return atoi(speed.c_str());
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

private:
	//std::vector <std::pair<std::string, mat4>>& vec_;
	bool shoot;
	int health;
	int i, j;
	std::string speed;
};