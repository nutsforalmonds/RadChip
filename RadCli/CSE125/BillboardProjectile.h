#ifndef _BILLBOARD_PROJECTILE_H_
#define _BILLBOARD_PROJECTILE_H_
#include "Cube.h"
#include <vector>
#include "ParticleAnimated.h"

class BillboardProjectile : public ParticleAnimated
{
protected:
	float startX;
	float startY;
	int distance;
	std::vector<int> playersHit;
	int playerID;
	int shootID;

public:
	BillboardProjectile(const ParticleAnimated& other) :ParticleAnimated(other){}
	void setStartX(float x){ startX = x; }
	void setStartY(float y){ startY = y; }
	float getStartX(){ return startX; }
	float getStartY(){ return startY; }
	void setDistance(int i){ distance = i; }
	int getDistance(){ return distance; }
	void setPlayerID(int id){ playerID = id; }
	int getPlayerID(){ return playerID; }
	void setShootID(int id){ shootID = id; }
	int getShootID(){ return shootID; }
};

#endif
