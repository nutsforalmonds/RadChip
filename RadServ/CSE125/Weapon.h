#ifndef _WEAPON_H_
#define _WEAPON_H_
#include "Item.h"

class Weapon : public Item
{
public:
	Weapon();
	Weapon(int dam);
	bool isWeapon();
	bool isRangeWeapon();

protected:
	int damage;//should be negative
};

#endif