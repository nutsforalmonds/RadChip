#include "RangeWeapon.h"

RangeWeapon::RangeWeapon()
: Weapon()
{
	distance = 30;
	speed = 50;
	damage = -1;
}

RangeWeapon::RangeWeapon(int dist, float spd, int dam)
: Weapon()
{
	distance = dist;
	speed = spd;
	damage = dam;
}

int RangeWeapon::getDistance()
{
	return distance;
}

void RangeWeapon::setDistance(int dist)
{
	distance = dist;
}

float RangeWeapon::getSpeed()
{
	return speed;
}

void RangeWeapon::setSpeed(float spd)
{
	speed = spd;
}

int RangeWeapon::getDamage()
{
	return damage;
}

//all damage values on weapons should be negative
void RangeWeapon::setDamage(int dam)
{
	damage = dam;
}

bool isRangeWeapon()
{
	return true;
}