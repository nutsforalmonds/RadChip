#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_
#include "Cube.h"
#include <vector>

class Projectile : public Cube
{
protected:
	float startX;
	float startY;
	float startZ;
	int distance;
	std::vector<int> playersHit;
	int playerID;
	int shootID;

public:
	Projectile(int numPlayers);
	void setStartX(float x);
	void setStartY(float y);
	void setStartZ(float z);
	float getStartX();
	float getStartY();
	float getStartZ();
	int checkHit(int i);
	void setHit(int i);
	void setDistance(int i);
	int getDistance();
	void setPlayerID(int id){ playerID = id; }
	int getPlayerID(){ return playerID; }
	void setShootID(int id){ shootID = id; }
	int getShootID(){ return shootID; }
};

#endif
