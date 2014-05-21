#include "Boots.h"

Boots::Boots()
: Item()
{
	moveSpeed = 1;
	sprintSpeed = 15;
	jumpMod = 0;
}

Boots::Boots(int ms, int ss, int j)
: Item()
{
	moveSpeed = ms;
	sprintSpeed = ss;
	jumpMod = j;
}

void Boots::setMoveSpeed(int spd){ moveSpeed = spd; }

int Boots::getMoveSpeed(){ return moveSpeed; }

void Boots::setSprintSpeed(int spd){ sprintSpeed = spd; }

int Boots::getSprintSpeed(){ return sprintSpeed; }

void Boots::setJumps(int i){ jumpMod = i; }

int Boots::getJumps(){ return jumpMod; }

bool Boots::isBoots(){ return true; }
