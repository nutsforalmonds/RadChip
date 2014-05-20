#ifndef _BOOTS_H_
#define _BOOTS_H_
#include "Item.h"

class Boots : public Item
{
public:
	Boots();
	Boots(int ms, int ss, int j);
	void setMoveSpeed(int spd);
	int getMoveSpeed();
	void setSprintSpeed(int spd);
	int getSprintSpeed();
	int getJumps();
	void setJumps(int i);
	bool isBoots();

protected:
	int moveSpeed;
	int sprintSpeed;
	int jumpMod;
};

#endif