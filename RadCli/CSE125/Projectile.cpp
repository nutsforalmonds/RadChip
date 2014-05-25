#include "Projectile.h"

Projectile::Projectile(int numPlayers)
: Mesh()
{
	for (int i = 0; i < numPlayers; i++)
	{
		playersHit.push_back(0);
	}
}

void Projectile::setStartX(float x){ startX = x; }
void Projectile::setStartY(float y){ startY = y; }
float Projectile::getStartX(){
	return startX;
}
float Projectile::getStartY(){
	return startY;
}

bool Projectile::checkHit(int i)
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