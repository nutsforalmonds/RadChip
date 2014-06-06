#include "Item.h"

Item::Item(void)
{
	health = 0;
}

int Item::getHealth()
{
	return health;
}

Item::~Item(){

}

void Item::setHealth(int val)
{
	health = val;
}

bool Item::isWeapon(){ return false; }
bool Item::isBoots(){ return false; }