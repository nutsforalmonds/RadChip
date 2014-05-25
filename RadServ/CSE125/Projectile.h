#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_
#include "Cube.h"
#include <vector>

class Projectile : public Cube
{
protected:
	float startX;
	float startY;
	int distance;
	std::vector<int> playersHit;
	int playerID;

public:
	Projectile(int numPlayers);
	void setStartX(float x);
	void setStartY(float y);
	float getStartX();
	float getStartY();
	int checkHit(int i);
	void setHit(int i);
	void setDistance(int i);
	int getDistance();
	void setPlayerID(int id){ playerID = id; }
	int getPlayerID(){ return playerID; }
};

#endif
