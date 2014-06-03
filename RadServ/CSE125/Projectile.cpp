#include "Projectile.h"

Projectile::Projectile(int numPlayers)
: Cube()
{
	for (int i = 0; i < numPlayers; i++)
	{
		playersHit.push_back(0);
	}
}

void Projectile::setStartX(float x){ startX = x; }
void Projectile::setStartY(float y){ startY = y; }
void Projectile::setStartZ(float z){ startZ = z; }
float Projectile::getStartX(){
	return startX;
}
float Projectile::getStartY(){
	return startY;
}

float Projectile::getStartZ(){
	return startZ;
}

int Projectile::checkHit(int i)
{
	return playersHit[i];
}

void Projectile::setHit(int i)
{
	playersHit[i] = 1;
}

int Projectile::getDistance()
{
	return distance;
}

void Projectile::setDistance(int i)
{
	distance = i;
}