#pragma once
#include "VAO.h"
#include "glslprogram.h"
#include "Item.h"
#include "RangeWeapon.h"
#include "Boots.h"
#include "Structures.h"
#include <array>
#include <iostream>
using namespace std;

#define BASE_JUMPS 20
#define NUM_POWERUPS 5

static int iohjworihorhi = 0;

class Object
{
public:
	Object(void){
		velocity = vec3(0.0);
		modelM = mat4(1.0);
		Rotation = mat4(1.0);
		onGround = true;
		health = 7;
		maxHealth = 7;
		numJumps = 5;
		respawnCounter = 0;
		kills = 0;
		playerID = -1;
		weapon = new RangeWeapon();
		boots = new Boots(2, 10, 2);
		powerUp = (bool *)malloc(NUM_POWERUPS * sizeof(bool));
		memset(powerUp, 0, NUM_POWERUPS * sizeof(bool));
		powerUpDuration = (int *)malloc(NUM_POWERUPS * sizeof(int));
		memset(powerUpDuration, 0, NUM_POWERUPS * sizeof(int));
	}
	Object(string n, string t){
		name = n;
		type = t;
		velocity = vec3(0.0);
		modelM = mat4(1.0);
		onGround = true;
		health = 7;
		maxHealth = 7;
		numJumps = 5;
		respawnCounter = 0;
		kills = 0;
		playerID = -1;
		weapon = new RangeWeapon();
		boots = new Boots(2, 10, 2);
		powerUp = (bool *)malloc(NUM_POWERUPS * sizeof(bool));
		memset(powerUp, 0, NUM_POWERUPS * sizeof(bool));
		powerUpDuration = (int *)malloc(NUM_POWERUPS * sizeof(int));
		memset(powerUpDuration, 0, NUM_POWERUPS * sizeof(int));
	}
	~Object()
	{
	}
	virtual void draw(){/* This is a placeholder*/ }

	void setType(string t){type = t;}
	string getType(){return type;}
	void setName(string n){name = n;}
	string getName(){return name;}

	void postTrans(mat4 trans){ modelM = modelM*trans; }
	void postRotate(mat4 rot){ modelM = modelM*rot; }
	void preTrans(mat4 trans){ modelM = trans*modelM; }
	void preRotate(mat4 rot){ modelM = rot*modelM; }
	mat4 getModelM(){ return modelM; }
	void setModelM(mat4 m){ modelM = m; }

	mat4 getAliveModelM(){ return aliveModelM; }
	void setAliveModelM(mat4 m){ aliveModelM = m; }

	//set ad move in object space
	void setHMove(int m){ hmove = m; velocity[0] = m*speed; }
	int getHMove(){ return hmove; }
	void cancelHMove(int m){
		if (hmove == m){
			hmove = 0;
			velocity[0] = 0.0;
		}
	}
	//set ws move in object space
	void setVMove(int m){ vmove = m; velocity[2] = -m*speed; }
	int getVMove(){ return vmove; }
	void cancelVMove(int m){
		if (vmove == m){
			vmove = 0;
			velocity[2] = 0.0;
		}
	}

	//set the walking speed of object
	void setSpeed(float s){ speed = s; }
	float getSpeed(){ return speed; }

	//pending rotation from mouse passive movement
	void setPendingRot(float f){ pendingRot = f; }
	void pushRot(float f){ pendingRot += f; }
	float getPendingRote(){ return pendingRot; }

	//check if the object is on ground
	bool getTouchGround(){
		return onGround;
	}

	void jump(int i){
		velocity[1] += i;
	}

	void jump(){
		//cout << numJumps << endl;
		if (numJumps > 0)
		{
			velocity[1] = 10;
			numJumps--;
		}
	}

	int getNumJumps(){ return numJumps; }

	int getTotalJumps(){ return BASE_JUMPS + boots->getJumps(); } //

	void incNumJumps()
	{
		numJumps++;
	}

	void resetVelocity()
	{
		velocity[0] = 0;
		velocity[1] = 0;
		velocity[2] = 0;
	}

	//set bounding box of the object
	void setAABB(const AABB& box){bBox = box;}
	AABB getAABB(){
		AABB box;
		box.min = bBox.min + vec3(modelM*vec4(0, 0, 0, 1));
		box.max = bBox.max + vec3(modelM*vec4(0, 0, 0, 1));
		return box;
	}

	//set velocity in object space
	void setVelocity(vec3& v){ velocity = v; }
	vec3 getVelocity(){ return velocity; }
	void addVelocity(vec3& v){ velocity += v; }
	void clearYVelocity(){ velocity[1] = 0; }
	float getYVelocity(){ return velocity[1]; }

	//decide if the object is on ground
	void touchGround(bool g){ onGround = g; }

	int getHealth(){ return health; }

	int getMaxHealth() { return maxHealth; }

	void setMaxHealth(int i) { maxHealth += i; }

	void setHealth(int i){ health += i; }

	void putHealth(int i){ health = i; }

	int getRespawn() { return respawnCounter; }

	void setRespawn(int i){ respawnCounter = i; }

	int getKills(){ return kills; }

	void setKills(int i){ kills += i; }


	void setRotation(mat4 m){ Rotation = m; }
	mat4 getRotation(){ return Rotation; }

	RangeWeapon * getWeapon() { return weapon; }
	void setWeapon(RangeWeapon * i) { weapon = i; }

	Boots * getBoots() { return boots; }
	void setBoots(Boots * b) { boots = b; }

	int getPlayerID() { return playerID; }
	void setPlayerID(int i) { playerID = i; }
	int getTeamID(){ return teamID; }
	void setTeamID(int i){ teamID = i; }

	bool * getPowerUp() { return powerUp; }
	void setPowerUp(int i, bool val) { powerUp[i] = val; }

	int * getPowerUpDuration() { return powerUpDuration; }
	void setPowerUpDuration(int i, int val) { powerUpDuration[i] = val; }

protected:
	mat4 modelM;
	mat4 Rotation;
	string type;
	string name;
	AABB bBox;
	vec3 velocity;//velocity in object space
	int hmove;//-1:left, 0:stay, 1:right
	int vmove;//-1:back, 0:stay, 1:up
	float speed;//unit/second
	float pendingRot;
	float jumpVelocity;
	bool onGround;
	int health;
	int maxHealth;
	int numJumps;
	int respawnCounter;
	int kills;
	int playerID;
	int teamID;
	RangeWeapon * weapon;
	Boots * boots;
	mat4 aliveModelM;
	bool * powerUp;
	int * powerUpDuration;
};