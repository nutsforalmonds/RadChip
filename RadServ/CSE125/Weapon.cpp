#include "Weapon.h"

Weapon::Weapon()
: Item()
{
	damage = -1;
}

Weapon::Weapon(int dam)
: Item()
{
	damage = dam;
}

bool Weapon::isWeapon(){ return true; }
bool Weapon::isRangeWeapon(){ return false; }