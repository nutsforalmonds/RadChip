#include "PlayerChar.h"

PlayerChar::PlayerChar()
: Object()
{
	health = 7;
	weapon = new RangeWeapon();
}

void PlayerChar::takeItem(Item * item)
{
	if (item->isWeapon())
	{
		//delete weapon;
		weapon = (Weapon *)item;
		health += item->getHealth();
	}
	else if (item->isBoots())
	{
		boots = (Boots*)item;
		numJumps += ((Boots*)item)->getJumps();
	}
}

int PlayerChar::getHealth(){ return health; }
void PlayerChar::setHealth(int i){ health = i; }


Weapon * PlayerChar::getWeapon() { return weapon; }
void PlayerChar::setWeapon(Weapon * w) { weapon = w; }