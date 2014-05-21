#ifndef _PLAYERCHAR_H_
#define _PLAYERCHAR_H_

#include "Mesh.h"
#include "MD5Model.h"
#include "Item.h"
#include "RangeWeapon.h"

class PlayerChar : public MD5Model
{
public:
	PlayerChar();
	void takeItem(Item * item);
	int getHealth();
	void setHealth(int i);
	Weapon * getWeapon();
	void setWeapon(Weapon * w);

protected:
	int health;
	Weapon * weapon;
	Boots * boots;

};

#endif