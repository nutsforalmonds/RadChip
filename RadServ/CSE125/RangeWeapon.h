#ifndef _RANGEWEAPON_H_
#define _RANGEWEAPON_H_
#include "Weapon.h"

class RangeWeapon : public Weapon
{
public:
	RangeWeapon();
	~RangeWeapon();
	RangeWeapon(int dist, float spd, int dam);
	int getDistance();
	void setDistance(int dist);
	float getSpeed();
	void setSpeed(float spd);
	int getDamage();//should be negative
	void setDamage(int dam);
	bool isRangeWeapon();

protected:
	int distance;
	float speed;
};

#endif _RANGEWEAPON_H_