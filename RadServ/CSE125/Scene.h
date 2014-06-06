#pragma once
#include <vector>
#include <map>
#include <math.h> 
#include <iostream>
#include "Object.h"
#include "Octree.h"
#include "Projectile.h"
#include "Window.h"
#include "Camera.h"
#include "Ground.h"
#include "billboard_list.h"
#include "Trampoline.h"
#include "Tower.h"
#include "Elevator.h"
#include "Teleporter.h"
#include "constants.h"
using namespace std;


#define RESPAWN_COUNTER 1500

#define MAX_SPEED 100
#define MAX_DISTANCE 100
#define MAX_DAMAGE -50

#define POWERUP_DURATION 1000
#define NUM_POWERUPS 5

#define GRAVITY_SCALE 2.5
#define PLAYER_SPEED 10

#define NUM_TOWERS 6

struct TowerShootInfo{
	TowerShootInfo(int td, int pd, vec3 dir){
		towerID = td;
		projectileID = pd;
		direction = dir;
	}
	int towerID;
	int projectileID;
	vec3 direction;
};


class Scene
{
public:
	Scene(){
		for (int i = 0; i < NUM_TOWERS; i++){
			tower_shoot_check[i] = false;
			tower_damaged[i] = false;
			tower_kill[i] = false;
		}
		tower_shoot_counter = 0;
		camM.push_back(mat4(1.0));
		camM.push_back(mat4(1.0));
		camM.push_back(mat4(1.0));
		camM.push_back(mat4(1.0));
		initialize();
	}
	~Scene(){
		for (uint i = 0; i<stationary.size(); i++){
			delete stationary[i];
		}
		stationary.clear();
		//for (uint i = 0; i<elevator.size(); i++){
		//	delete elevator[i];
		//}
		//elevator.clear();
		for (uint i = 0; i<player.size(); i++){
			delete player[i];
		}
		player.clear();
		for (uint i = 0; i<respawn.size(); i++){
			delete respawn[i];
		}
		respawn.clear();
		for (uint i = 0; i<tower.size(); i++){
			delete tower[i];
		}
		tower.clear();
		for (uint i = 0; i<skillShot.size(); i++){
			delete skillShot[i];
		}
		skillShot.clear();
		for (uint i = 0; i<virtualTower.size(); i++){
			delete virtualTower[i];
		}
		virtualTower.clear();
		for (uint i = 0; i<projectile.size(); i++){
			delete projectile[i];
		}
		projectile.clear();
		for (uint i = 0; i<tower_projectile.size(); i++){
			delete tower_projectile[i];
		}
		tower_projectile.clear();
		for (uint i = 0; i<powerUps.size(); i++){
			delete powerUps[i];
		}
		powerUps.clear();
	}

	Object * getPlayerObj(int playerID)
	{
		for (uint i = 0; i < player.size(); i++)
		{
			if (player[i]->getPlayerID() == playerID)
				return player[i];
		}
		return NULL;
	}

	Object * getTowerObj(int playerID)
	{
		for (uint i = 0; i < tower.size(); i++)
		{
			if (tower[i]->getPlayerID() == playerID)
				return tower[i];
		}
		return NULL;
	}

	int getPlayerHealth(int playerID)
	{
		pPtr = getPlayerObj(playerID);
		return pPtr->getMaxHealth();
	}

	int getPlayerKills(int playerID)
	{
		pPtr = getPlayerObj(playerID);
		return pPtr->getKills();
	}

	int getPlayerPowerUp(int playerID)
	{
		pPtr = getPlayerObj(playerID);
		return pPtr->getPowerUp();
	}

	bool getPlayerOnTramp(int playerID)
	{
		return playerOnTramp[playerID];
	}

	void clearPlayerOnTramp()
	{
		playerOnTramp[0] = false;
		playerOnTramp[1] = false;
		playerOnTramp[2] = false;
		playerOnTramp[3] = false;
	}

	bool getPlayerOnTele(int playerID)
	{
		return playerOnTele[playerID];
	}

	void clearPlayerOnTele()
	{
		playerOnTele[0] = false;
		playerOnTele[1] = false;
		playerOnTele[2] = false;
		playerOnTele[3] = false;
	}

	int getPUpState()
	{
		int ret = 0;

		if (pUpCooldown[SPEEDUP] > 0)
			ret = ret | 1;
		if (pUpCooldown[DOUBLEDAMAGE] > 0)
			ret = ret | 1 << 1;
		if (pUpCooldown[HEALTHBOOST] > 0)
			ret = ret | 1 << 2;
		if (pUpCooldown[FASTERSHOOT] > 0)
			ret = ret | 1 << 3;
		if (pUpCooldown[FARTHERSHOOT] > 0)
			ret = ret | 1 << 4;

		//cout << pUpCooldown[FASTERSHOOT] << " " << pUpCooldown[FARTHERSHOOT] << endl;

		return ret;
	}

	void simulate(float t, float sub){
		resolvePlayerRotation();
		while (t > sub){
			t -= sub;
			resolvePlayerTransition(sub);
			resolveProjectileTransition(sub);
			//resolveTowerTransition(sub);
		//	//octree here
			towerProjectileAttack(sub);
			collisionDetection();
			collisionDetectionPlayer();
			collisionDetectionProjectile();
			collisionDetectionPowerUp();
			despawnProjectile();
			rechargeJump();
			respawnObjs();
			//respawnTower();
			removePowerUp();
			moveElevators();
		}
		resolvePlayerTransition(t);
		resolveProjectileTransition(t);
		//resolveTowerTransition(t);
		////octree here
		towerProjectileAttack(t);
		collisionDetection();
		collisionDetectionPlayer();
		collisionDetectionProjectile();
		collisionDetectionPowerUp();
		despawnProjectile();
		rechargeJump();
		respawnObjs();
		//respawnTower();
		removePowerUp();
		moveElevators();
	}

	void moveElevators(){
		if (counter2 == 1000){
			counter3 = -counter3;
			counter2 = 0;
		}
		for (uint i = 0; i < elevator.size(); ++i){
			if (elevator[i]->getDirection() != 1){
				if (elevator[i]->getDirection() == -1){
					elevator[i]->preTrans(glm::translate(vec3(0, 0, -counter3)));
					vector<Object*> elplayers = elevator[i]->getPlayers();
					for (uint j = 0; j < elplayers.size(); ++j)
						elplayers[j]->preTrans(glm::translate(vec3(0, 0, -counter3)));
				}
				else {
					elevator[i]->preTrans(glm::translate(vec3(0, 0, counter3)));
					vector<Object*> elplayers = elevator[i]->getPlayers();
					for (uint j = 0; j < elplayers.size(); ++j)
						elplayers[j]->preTrans(glm::translate(vec3(0, 0, counter3)));
				}
			}
			else {
				elevator[i]->preTrans(glm::translate(vec3(0, counter3, 0)));
				vector<Object*> elplayers = elevator[i]->getPlayers();
				for (uint j = 0; j < elplayers.size(); ++j)
					elplayers[j]->preTrans(glm::translate(vec3(0, counter3, 0)));
				/*
				ofstream ofile;
				ofile.open("debug.txt", ios::app);

				for (int i = 0; i < 4; ++i)
				for (int j = 0; j < 4; ++j)
				ofile << elevator[1]->getModelM()[i][j] << " ";

				ofile << endl;
				ofile.close();*/

			}
			elevator[i]->removeAll();
		}
		counter2++;
	}
	void collisionDetection(Octree* octree);
	void collisionDetection(){
		for (uint i = 0; i < player.size(); i++){
			bool touchGround1 = false;
			bool touchGround2 = false;
			//player-stationary detection
			for (uint j = 0; j < stationary.size(); j++){
				if ((stationary[j]->getType() == GROUND)){
					AABB pBox = player[i]->getAABB();
					vec3 mid = (pBox.max + pBox.min) / 2.0f;
					float disp = ((Ground*)stationary[j])->getDispY(mid[0], mid[2]);
					if (disp != -1){
						if (pBox.min[1] < disp){
							touchGround1 = true;
							player[i]->postTrans(glm::translate(vec3(0.0f,disp-pBox.min[1],0.0f)));
							player[i]->clearYVelocity();
						}
						if (pBox.min[1] - disp < 0.1)
							touchGround1 = true;
					}
				}
				else{
					AABB pBox = player[i]->getAABB();
					AABB sBox = stationary[j]->getAABB();
					bool collide = true;
					for (int v = 0; v < 3; v++){
						if (pBox.max[v] <= sBox.min[v] || sBox.max[v] <= pBox.min[v]){
							collide = false;
							break;
						}
					}
					if (collide){
						fixCollision(player[i], stationary[j], pBox, sBox, touchGround1, touchGround2);
					}
					
					stationary[j]->touchGround(touchGround2);
				}
			}
			player[i]->touchGround(touchGround1);
		}
		//collisionDetectionTower();
	}

	void collisionDetectionTower(){
		//tower-stationary detection
		for (uint i = 0; i < tower.size(); i++){
			bool touchGround1 = false;
			bool touchGround2 = false;
			for (uint j = 0; j < stationary.size(); j++){
				if ((stationary[j]->getType() == GROUND)){
					AABB pBox = tower[i]->getAABB();
					vec3 mid = (pBox.max + pBox.min) / 2.0f;
					float disp = ((Ground*)stationary[j])->getDispY(mid[0], mid[2]);
					if (disp != -1){
						if (pBox.min[1] < disp){
							touchGround1 = true;
							tower[i]->postTrans(glm::translate(vec3(0.0f, disp - pBox.min[1], 0.0f)));
							tower[i]->clearYVelocity();
						}
						if (pBox.min[1] - disp < 0.1)
							touchGround1 = true;
					}
				}
				else{
					AABB pBox = tower[i]->getAABB();
					AABB sBox = stationary[j]->getAABB();
					bool collide = true;
					for (int v = 0; v < 3; v++){
						if (pBox.max[v] <= sBox.min[v] || sBox.max[v] <= pBox.min[v]){
							collide = false;
							break;
						}
					}
					if (collide){
						fixCollision(tower[i], stationary[j], pBox, sBox, touchGround1, touchGround2);
					}
					stationary[j]->touchGround(touchGround2);
				}
			}

			tower[i]->touchGround(touchGround1);
		}
	}
	void collisionDetectionPlayer(){
		for (uint i = 0; i < player.size(); i++){
			bool touchGround1 = player[i]->getTouchGround();
			//player-tower detection
			for (uint j = 0; j < tower.size(); j++){
				bool touchGround2 = tower[j]->getTouchGround();
				AABB pBox = player[i]->getAABB();
				AABB sBox = tower[j]->getAABB();
				bool collide = true;
				for (int v = 0; v < 3; v++){
					if (pBox.max[v] <= sBox.min[v] || sBox.max[v] <= pBox.min[v]){
						collide = false;
						break;
					}
				}
				if (collide){
					fixCollision(player[i], tower[j], pBox, sBox, touchGround1, touchGround2);
				}
				tower[j]->touchGround(touchGround2);
			}
			//player-player detection
			for (uint j = i + 1; j < player.size(); j++){
				bool touchGround2 = player[j]->getTouchGround();
				AABB pBox = player[i]->getAABB();
				AABB sBox = player[j]->getAABB();
				bool collide = true;
				for (int v = 0; v < 3; v++){
					if (pBox.max[v] <= sBox.min[v] || sBox.max[v] <= pBox.min[v]){
						collide = false;
						break;
					}
				}
				if (collide){
					fixCollision(player[i], player[j], pBox, sBox, touchGround1, touchGround2);
				}
				player[j]->touchGround(touchGround2);
			}
			player[i]->touchGround(touchGround1);
		}
	}

	void collisionDetectionPowerUp()
	{
		bool inX, inY, inZ;
		AABB playerAABB;
		vec3 powerUpPos;
		for (uint i = 0; i < player.size(); i++)
		{
			playerAABB = player[i]->getAABB();
			//iterate through list of power up types
			for (uint j = 0; j < powerUps.size(); j++)
			{
				//iterate through all billboard positions for a given powerup, in case there are multiple copies of a type
				for (uint l = 0; l < (powerUps[j]->getPos())->size(); l++)
				{
					powerUpPos = (*powerUps[j]->getPos())[l];
					inX = (playerAABB.min[0] <= powerUpPos[0] + 2) && (powerUpPos[0] - 2 <= playerAABB.max[0]);
					inY = (playerAABB.min[1] <= powerUpPos[1] + 2) && (powerUpPos[1] - 2 <= playerAABB.max[1]);
					inZ = (playerAABB.min[2] <= powerUpPos[2] + 2) && (powerUpPos[2] - 2 <= playerAABB.max[2]);

					if (inX && inY && inZ)
					{
						// TODO needs to despawn powerup on server side
						// check all players, if anyone has the powerup, it can't be applied
						// to a new player
						//MS boost , uses index 0
						if (j == 0 && pUpCooldown[SPEEDUP] <= 0)
						{
							if (player[i]->getPowerUp() == NOPOWER)
							{
								player[i]->getBoots()->setMoveSpeed(4);
 								player[i]->setPowerUp(SPEEDUP);
								//std::cout << "speed boost if" << std::endl;
							}
							else
							{
								if (player[i]->getPowerUp() == SPEEDUP)
									break;
								else if (player[i]->getPowerUp() == DOUBLEDAMAGE)
									player[i]->getWeapon()->setDamage(-1);
								else if (player[i]->getPowerUp() == HEALTHBOOST)
									player[i]->setTempHealth(0);
								else if (player[i]->getPowerUp() == FASTERSHOOT)
									player[i]->getWeapon()->setSpeed(50);
								else if (player[i]->getPowerUp() == FARTHERSHOOT)
									player[i]->getWeapon()->setDistance(40);

								
								player[i]->getBoots()->setMoveSpeed(4);
								player[i]->setPowerUp(SPEEDUP);
								//std::cout << "speed boost else" << std::endl;
							}
							pUpCooldown[SPEEDUP] = POWERUP_DURATION;
							player[i]->setPowerUpDuration(POWERUP_DURATION);
						}
						//DMG boost , uses index 1
						else if (j == 1 && pUpCooldown[DOUBLEDAMAGE] <= 0)
						{
							if (player[i]->getPowerUp() == NOPOWER)
							{
								player[i]->getWeapon()->setDamage(-4);
								player[i]->setPowerUp(DOUBLEDAMAGE);
								//std::cout << "dmg if" << std::endl;
							}
							else
							{
								if (player[i]->getPowerUp() == SPEEDUP)
									player[i]->getBoots()->setMoveSpeed(2);
								else if (player[i]->getPowerUp() == DOUBLEDAMAGE)
									break;
								else if (player[i]->getPowerUp() == HEALTHBOOST)
									player[i]->setTempHealth(0);
								else if (player[i]->getPowerUp() == FASTERSHOOT)
									player[i]->getWeapon()->setSpeed(50);
								else if (player[i]->getPowerUp() == FARTHERSHOOT)
									player[i]->getWeapon()->setDistance(40);

								player[i]->getWeapon()->setDamage(-4);
								player[i]->setPowerUp(DOUBLEDAMAGE);
								//std::cout << "dmg else" << std::endl;
								//std::cout << player[i]->getPowerUp() << std::endl;
							}
							pUpCooldown[DOUBLEDAMAGE] = POWERUP_DURATION;
							player[i]->setPowerUpDuration(POWERUP_DURATION);
						}
						//Health boost , uses index 2
						else if (j == 2 && pUpCooldown[HEALTHBOOST] <= 0)
						{
							if (player[i]->getPowerUp() == NOPOWER)
							{
								player[i]->setTempHealth(4);
								player[i]->setPowerUp(HEALTHBOOST);
							}
							else
							{
								if (player[i]->getPowerUp() == SPEEDUP)
									player[i]->getBoots()->setMoveSpeed(2);
								else if (player[i]->getPowerUp() == DOUBLEDAMAGE)
									player[i]->getWeapon()->setDamage(-1);
								else if (player[i]->getPowerUp() == HEALTHBOOST)
									break;
								else if (player[i]->getPowerUp() == FASTERSHOOT)
									player[i]->getWeapon()->setSpeed(50);
								else if (player[i]->getPowerUp() == FARTHERSHOOT)
									player[i]->getWeapon()->setDistance(40);

								player[i]->setTempHealth(4);
								player[i]->setPowerUp(HEALTHBOOST);
							}
							pUpCooldown[HEALTHBOOST] = POWERUP_DURATION;
							player[i]->setPowerUpDuration(POWERUP_DURATION);
						}
						//Shot Spd boost , uses index 3
						else if (j == 3 && pUpCooldown[FASTERSHOOT] <= 0)
						{
							if (player[i]->getPowerUp() == NOPOWER)
							{
								player[i]->getWeapon()->setSpeed(70);
								player[i]->setPowerUp(FASTERSHOOT);
							}
							else
							{
								if (player[i]->getPowerUp() == SPEEDUP)
									player[i]->getBoots()->setMoveSpeed(2);
								else if (player[i]->getPowerUp() == DOUBLEDAMAGE)
									player[i]->getWeapon()->setDamage(-1);
								else if (player[i]->getPowerUp() == HEALTHBOOST)
									player[i]->setTempHealth(0);
								else if (player[i]->getPowerUp() == FASTERSHOOT)
									break;
								else if (player[i]->getPowerUp() == FARTHERSHOOT)
									player[i]->getWeapon()->setDistance(40);

								player[i]->getWeapon()->setSpeed(70);
								player[i]->setPowerUp(FASTERSHOOT);
							}
							pUpCooldown[FASTERSHOOT] = POWERUP_DURATION;
							player[i]->setPowerUpDuration(POWERUP_DURATION);
						}
						//Shot Range boost , uses index 4
						else if (j == 4 && pUpCooldown[FARTHERSHOOT] <= 0)
						{
							if (player[i]->getPowerUp() == NOPOWER)
							{
								player[i]->getWeapon()->setDistance(70);
								player[i]->setPowerUp(FARTHERSHOOT);
							}
							else
							{
								if (player[i]->getPowerUp() == SPEEDUP)
									player[i]->getBoots()->setMoveSpeed(2);
								else if (player[i]->getPowerUp() == DOUBLEDAMAGE)
									player[i]->getWeapon()->setDamage(-1);
								else if (player[i]->getPowerUp() == HEALTHBOOST)
									player[i]->setTempHealth(0);
								else if (player[i]->getPowerUp() == FASTERSHOOT)
									player[i]->getWeapon()->setSpeed(50);
								else if (player[i]->getPowerUp() == FARTHERSHOOT)
									break;
								
								player[i]->getWeapon()->setDistance(70);
								player[i]->setPowerUp(FARTHERSHOOT);
							}
							pUpCooldown[FARTHERSHOOT] = POWERUP_DURATION;
							player[i]->setPowerUpDuration(POWERUP_DURATION);
						}
					}
				}
			}
		}
	}

	//returns 3 if no winner yet, 0 for team 0 win, 1 for team 1 win
	int checkTowerAlive()
	{
		int team0 = 0;
		int team1 = 0;
		for (uint i = 0; i < tower.size(); i++)
		{
			if (tower[i]->getHealth() < 1)
			{
				if (tower[i]->getTeamID())
					team1++;
				else
					team0++;
			}
		}
		if (team1 == NUM_TOWERS / 2)
		{
			gameOver = true;
			return 1;
		}
		else if (team0 == NUM_TOWERS / 2)
		{
			gameOver = true;
			return 0;
		}
		else
			return 3;

	}

	void fixCollision(Object* obj1, Object* obj2, AABB& box1, AABB& box2, bool& onGround1, bool& onGround2){
		float Rewind[3];
		float minRewind = 999;
		int minID = 0;
		vec3 v1 = vec3(obj1->getModelM()*vec4(obj1->getVelocity(), 0.0));
		vec3 v2 = vec3(obj2->getModelM()*vec4(obj2->getVelocity(), 0.0));
		vec3 vDiff = v1 - v2;

		for (int v = 0; v<3; v++){
			if (vDiff[v] > 0){
				Rewind[v] = (box1.max[v] - box2.min[v]) / vDiff[v];
			}
			else if (vDiff[v] < 0){
				Rewind[v] = (box1.min[v] - box2.max[v]) / vDiff[v];
			}
			else{//avoid division by 0
				Rewind[v] = 999;
			}
			if (Rewind[v] < minRewind){
				minRewind = Rewind[v];
				minID = v;
			}
		}
		vec3 rwVelocity1 = vec3(0.0);
		rwVelocity1[minID] = -v1[minID];
		obj1->preTrans(glm::translate(rwVelocity1*minRewind));
		vec3 rwVelocity2 = vec3(0.0);
		rwVelocity2[minID] = -v2[minID];
		obj2->preTrans(glm::translate(rwVelocity2*minRewind));
		if (minID == 1){

			if (obj1->getAABB().min[1] >= obj2->getAABB().min[1]){
				obj1->clearYVelocity();
				obj2->clearYVelocity();
				onGround1 = true;
			}
			else{
				obj1->clearYVelocity();
				obj2->clearYVelocity();
				onGround2 = true;
			}
		}
		else{//stair effect
			AABB b1 = obj1->getAABB();
			AABB b2 = obj2->getAABB();
			if (b2.max[1] > b1.min[1] && b2.max[1] - b1.min[1] <= 0.11){
				obj1->preTrans(glm::translate(glm::vec3(0.0f, b2.max[1]-b1.min[1]+0.01f, 0.0f)));
			}
		}
		if ((obj2->getType() == TRAMPOLINE)&&onGround1){
			obj1->addVelocity(((Trampoline*)obj2)->getBoost());
			playerOnTramp[obj1->getPlayerID()] = true;
		}
		if ((obj2->getType() == TELEPORTER) && onGround1){
			obj1->setModelM(((Teleporter*)obj2)->getEndpoint());
			playerOnTele[obj1->getPlayerID()] = true;
		}
		if ((obj2->getType() == ELEVATOR) && onGround1){
			((Elevator*)obj2)->addPlayer(obj1);
			obj1->setOnElevator(true);
		}
	}
	void addPlayer(Object* p){ player.push_back(p); }
	void addTower(Tower* t){ tower.push_back(t); }
	void addStationary(Object* s){ stationary.push_back(s); }
	void addProjectile(Projectile* p){ projectile.push_back(p); }
	void setGravity(vec3& g){ gravity = g; }
	void resolvePlayerRotation(){
		for (uint i = 0; i < player.size(); i++){
			player[i]->postRotate(glm::rotate(mat4(1.0), player[i]->getPendingRote(), vec3(0, 1, 0)));
			player[i]->setPendingRot(0);
		}
	}
	void setCamM(int playerID, mat4 m){
		if (playerID >= 4){
			cout << playerID << endl;
			system("pause");
		}
		camM[playerID] = m;
	}


	void resolvePlayerTransition(float t){
		float extra_speed = t*GRAVITY_SCALE;
		for (uint i = 0; i < player.size(); i++){
			player[i]->addVelocity(gravity*extra_speed);
			player[i]->postTrans(glm::translate(player[i]->getVelocity()*t));
		}
	} 
	void resolveTowerTransition(float t){
		float extra_speed = t*GRAVITY_SCALE;
		for (uint i = 0; i < tower.size(); i++){
			if (tower[i]->getHealth() < 1)
				continue;
			tower[i]->addVelocity(gravity*extra_speed);
			tower[i]->postTrans(glm::translate(tower[i]->getVelocity()*t));
		}
	}
	void resolveProjectileTransition(float t){
		float extra_speed = t*GRAVITY_SCALE;
		for (uint i = 0; i < projectile.size(); i++){
			projectile[i]->addVelocity(gravity*t);
			projectile[i]->preTrans(glm::translate(projectile[i]->getVelocity()*t));
		}
		for (uint i = 0; i < tower_projectile.size(); i++){
			tower_projectile[i]->preTrans(glm::translate(tower_projectile[i]->getVelocity()*t));
		}
	}

	void setHMove(int playerID, int m){ player[playerID]->setHMove(m); }
	void cancelHMove(int playerID, int m){ player[playerID]->cancelHMove(m); }
	void setVMove(int playerID, int m){ player[playerID]->setVMove(m);  }
	void cancelVMove(int playerID, int m){ player[playerID]->cancelVMove(m); }

	void setPendingRot(int playerID, float f){ getPlayerObj(playerID)->setPendingRot(f); }
	void pushRot(int playerID, float f){ getPlayerObj(playerID)->pushRot(f); }
	void jump(int playerID){
		if (getPlayerObj(playerID)->getOnElevator()){
			getPlayerObj(playerID)->preTrans(glm::translate(vec3(0, counter3, 0)));
			getPlayerObj(playerID)->setOnElevator(false);
		}
		else
			getPlayerObj(playerID)->jump();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////// START OF PLAYER ACTIONS /////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool getGameOver()
	{
		return gameOver;
	}

	vector<Object *> * getStationary()
	{
		return &stationary;
	}

	vector<bool> getPlatformDamaged()
	{
		return platformDamaged;
	}

	void setPlatformDamaged(int i, bool b)
	{
		platformDamaged[i] = b;
	}

	vector<bool> getPlatformDead()
	{
		return platformDead;
	}

	void setPlatformDead(int i, bool b)
	{
		platformDead[i] = b;
	}

	void removePowerUp()
	{
		if (pUpCooldown[SPEEDUP] > 0)
			pUpCooldown[SPEEDUP] -= 1;
		if (pUpCooldown[DOUBLEDAMAGE] > 0)
			pUpCooldown[DOUBLEDAMAGE] -= 1;
		if (pUpCooldown[HEALTHBOOST] > 0)
			pUpCooldown[HEALTHBOOST] -= 1;
		if (pUpCooldown[FASTERSHOOT] > 0)
			pUpCooldown[FASTERSHOOT] -= 1;
		if (pUpCooldown[FARTHERSHOOT] > 0)
			pUpCooldown[FARTHERSHOOT] -= 1;

		for (uint i = 0; i < player.size(); i++)
		{
			if (player[i]->getPowerUp() != 0)
			{
				//std::cout << player[i]->getPowerUp() << std::endl;
				player[i]->setPowerUpDuration(player[i]->getPowerUpDuration() - 1);
				if (player[i]->getPowerUpDuration() <= 0)
				{
					if (player[i]->getPowerUp() == SPEEDUP)
						player[i]->getBoots()->setMoveSpeed(2);
					else if (player[i]->getPowerUp() == DOUBLEDAMAGE)
						player[i]->getWeapon()->setDamage(-1);
					else if (player[i]->getPowerUp() == HEALTHBOOST)
						player[i]->setTempHealth(0);
					else if (player[i]->getPowerUp() == FASTERSHOOT)
						player[i]->getWeapon()->setSpeed(50);
					else if (player[i]->getPowerUp() == FARTHERSHOOT)
						player[i]->getWeapon()->setDistance(40);

					player[i]->setPowerUp(NOPOWER);
				}
			}
		}
	}

	void respawnObjs()
	{
		Object * holder;
		//int id;
		for (uint i = 0; i < player.size(); i++)
		{
			if (player[i]->getHealth() < 1)
			{
				holder = player[i];
				holder->setModelM(holder->getModelM()*glm::translate(vec3(0, -20, 0)));
				
				if (holder->getRespawn() < 1)
				{
					//Window::addDrawList(holder);
					//Window::addPlayerList(holder);
					//Window::respawnPlayer(holder->getName());
					holder->putHealth(7);
					holder->setModelM(holder->getAliveModelM());
					//holder->setVelocity(vec3(0, 20, 0));
					setPlayerDead(holder->getPlayerID(), false);
					//cout << holder->getName() << " " << holder->getRespawn() << " " << holder->getHealth() << " " << player[i]->getHealth() << endl;

					//id = holder->getPlayerID();
					////insert the player at position at playerID
					////removes all players after playerID and appends them to the list.
					//for (int i = id; i < player.size() - 1; i++)
					//{
					//	holder = player[id];
					//	player.erase(player.begin() + id);
					//	player.push_back(holder);
					//}

					//cout << "" << endl;
				}
				else
					holder->setRespawn(holder->getRespawn() - 1);
			}
		}

		for (uint i = 0; i < stationary.size(); i++)
		{
			if (stationary[i]->getIsPlatformDamage())
			{
				if (stationary[i]->getHealth() < 1)
				{

					holder = stationary[i];
					holder->setRespawn(holder->getRespawn() - 1);

					if (holder->getRespawn() < 1)
					{
						holder->putHealth(7);
						holder->setModelM(holder->getAliveModelM());
						platformDead[i] = false;
					}
				}
			}
		}
	}
	void respawnTower()
	{
		Tower * holder;
		//int id;
		for (uint i = 0; i < tower.size(); i++)
		{
			if (tower[i]->getHealth() < 1)
			{
				holder = tower[i];
				holder->setModelM(holder->getModelM()*glm::translate(vec3(0, -20, 0)));

				if (holder->getRespawn() < 1)
				{
					holder->putHealth(20);
					holder->setModelM(holder->getAliveModelM()*glm::translate(vec3(0, 30, 0)));
					holder->setVelocity(vec3(0, 20, 0));
				}
				else
					holder->setRespawn(holder->getRespawn() - 1);
			}
		}
	}
	void collisionDetectionProjectile(){
		//player-projectile detection
		for (uint i = 0; i < projectile.size(); i++)
		{
			for (uint j = 0; j < player.size(); j++)
			{
				if (player[j]->getHealth()<1 || projectile[i]->getTeamID() == player[j]->getTeamID())
					continue;
				AABB pBox = projectile[i]->getAABB();
				AABB sBox = player[j]->getAABB();
				bool collide = true;
				for (int v = 0; v < 3; v++){
					if (pBox.max[v] <= sBox.min[v] || sBox.max[v] <= pBox.min[v]){
						collide = false;
						break;
					}
				}
				if (collide){
					vec3 pv = projectile[i]->getVelocity();
					//vec3 pv = vec3(player[projectile[i]->getPlayerID()]->getModelM()*vec4(projectile[i]->getVelocity(), 0.0));
					pv[1] = 0;
					pv = glm::normalize(pv);
					pv[1] = 1;
					player[j]->preTrans(glm::translate(pv));
					damagePlayer(player[j]->getPlayerID(), projectile[i]->getPlayerID());
					despon_player_projectile_list.push_back(projectile[i]->getShootID());
					delete projectile[i];
					projectile.erase(projectile.begin() + i);
					i--;
					break;
				}
			}
		}
		//tower-projectile detection
		for (uint i = 0; i < projectile.size(); i++)
		{
			for (uint j = 0; j < tower.size(); j++)
			{
				if (tower[j]->getHealth()<1 || projectile[i]->getTeamID() == tower[j]->getTeamID())
					continue;
				AABB pBox = projectile[i]->getAABB();
				AABB sBox = tower[j]->getAABB();
				bool collide = true;
				for (int v = 0; v < 3; v++){
					if (pBox.max[v] <= sBox.min[v] || sBox.max[v] <= pBox.min[v]){
						collide = false;
						break;
					}
				}
				if (collide){
					//vec3 pv = projectile[i]->getVelocity();
					//pv[1] = 0;
					//pv = glm::normalize(pv);
					//pv[1] = 1;
					//tower[j]->preTrans(glm::translate(pv));
					damageTower(tower[j]->getPlayerID(), projectile[i]->getPlayerID());
					despon_player_projectile_list.push_back(projectile[i]->getShootID());
					delete projectile[i];
					projectile.erase(projectile.begin() + i);
					i--;
					break;
				}
			}
		}
		//player-tower projectile detecion
		for (uint i = 0; i < tower_projectile.size(); i++){
			for (uint j = 0; j < player.size(); j++){
				if (tower_projectile[i]->getTeamID() == player[j]->getTeamID())
					continue;
				AABB pBox = tower_projectile[i]->getAABB();
				AABB sBox = player[j]->getAABB();
				bool collide = true;
				for (int v = 0; v < 3; v++){
					if (pBox.max[v] <= sBox.min[v] || sBox.max[v] <= pBox.min[v]){
						collide = false;
						break;
					}
				}
				if (collide){
					vec3 pv = tower_projectile[i]->getVelocity();
					pv[1] = 0;
					pv = glm::normalize(pv);
					pv[1] = 1;
					player[j]->preTrans(glm::translate(pv));
					damagePlayerT(player[j]->getPlayerID(), tower_projectile[i]->getPlayerID());
					despon_tower_projectile_list.push_back(tower_projectile[i]->getShootID());
					delete tower_projectile[i];
					tower_projectile.erase(tower_projectile.begin() + i);
					i--;
					break;
				}
			}
		}

		//stationary-projectile detection
		for (uint i = 0; i < projectile.size(); i++)
		{
			for (uint j = 0; j < stationary.size(); j++)
			{
				AABB pBox = projectile[i]->getAABB();
				AABB sBox = stationary[j]->getAABB();
				bool collide = true;
				for (int v = 0; v < 3; v++){
					if (pBox.max[v] <= sBox.min[v] || sBox.max[v] <= pBox.min[v]){
						collide = false;
						break;
					}
				}
				if (collide){
					if (stationary[j]->getIsPlatformDamage())
					{
						damageStationary(j, projectile[i]->getPlayerID());
					}
					despon_player_projectile_list.push_back(projectile[i]->getShootID());
					delete projectile[i];
					projectile.erase(projectile.begin() + i);
					i--;
					break;
				}
			}
		}

		//stationary-tower projectile detection
		for (uint i = 0; i < tower_projectile.size(); i++){
			for (uint j = 0; j < stationary.size(); j++){
				if (!stationary[j]->getIsPlatformDamage())
					continue;
				AABB pBox = tower_projectile[i]->getAABB();
				AABB sBox = stationary[j]->getAABB();
				bool collide = true;
				for (int v = 0; v < 3; v++){
					if (pBox.max[v] <= sBox.min[v] || sBox.max[v] <= pBox.min[v]){
						collide = false;
						break;
					}
				}
				if (collide){
					damageStationaryT(j, tower_projectile[i]->getPlayerID());
					despon_tower_projectile_list.push_back(tower_projectile[i]->getShootID());
					delete tower_projectile[i];
					tower_projectile.erase(tower_projectile.begin() + i);
					i--;
					break;
				}
			}
		}
	}
	void damagePlayer(int targetId, int playerId)
	{
		Object * playerHolder = getPlayerObj(playerId);
		Object * targetHolder = getPlayerObj(targetId);
		if (targetHolder->getTempHealth() <= 0)
			targetHolder->setHealth(((RangeWeapon *)playerHolder->getWeapon())->getDamage());
		else
		{
			targetHolder->setTempHealth(targetHolder->getTempHealth() + ((RangeWeapon *)playerHolder->getWeapon())->getDamage());

		}
		playerDamaged[targetId] = true;
		if (targetHolder->getHealth() < 1)
		{
			playerDead[targetId] = true;
			targetHolder->setRespawn(RESPAWN_COUNTER);
			//Window::removeDrawList((*targetHolder).getName());
			//Window::removePlayerList((*targetHolder).getName());
			//respawn.push_back(targetHolder);
			/*
			for (uint i = 0; i < player.size(); i++)
			{
				if (player[i]->getPlayerID() == targetId)
				{
					player[i]->setAliveModelM(player[i]->getModelM());
					////////////////////////////////player[i]->setModelM(player[i]->getModelM()*glm::translate(vec3(0, 1000, 0)));
				}
			}*/
			//cout << playerId << " " << dmg << endl;
			//RangeWeapon * newItem = new RangeWeapon(dist,
													//spd,
													//dmg);
			//playerHolder->setWeapon(newItem);
			playerHolder->setKills(1);
			//RangeWeapon * newItem = new RangeWeapon(((RangeWeapon *)player[0]->getItem())->getDistance() * 3
			//										, ((RangeWeapon *)player[0]->getItem())->getSpeed() * 3);
		}
	}
	void damagePlayerT(int targetId, int towerID)
	{
		Tower* tw = tower[towerID];
		Object * targetHolder = getPlayerObj(targetId);
		//targetHolder->setHealth(tw->getDamage());
		if (targetHolder->getTempHealth() <= 0)
			targetHolder->setHealth(tw->getDamage());
		else
			targetHolder->setTempHealth(targetHolder->getTempHealth() + tw->getDamage());
		playerDamaged[targetId] = true;
		if (targetHolder->getHealth() < 1)
		{
			playerDead[targetId] = true;
			targetHolder->setRespawn(RESPAWN_COUNTER);
			for (uint i = 0; i < player.size(); i++)
			{
				if (player[i]->getPlayerID() == targetId)
				{
					///////////////////////////////player[i]->setModelM(player[i]->getModelM()*glm::translate(vec3(0, 1000, 0)));
				}
			}
		}
	}
	void damageTower(int targetId, int playerId)
	{
		Object * playerHolder = getPlayerObj(playerId);
		Object * targetHolder = getTowerObj(targetId);

		//if base tower id
		if (targetId == 5)
		{
			//if side towers are dead
			if (tower[0]->getHealth() < 1 && tower[1]->getHealth() < 1)
			{
				targetHolder->setHealth(((RangeWeapon *)playerHolder->getWeapon())->getDamage());
				tower_damaged[targetId] = true;
			}
		}
		else if (targetId == 4)
		{
			if (tower[2]->getHealth() < 1 && tower[3]->getHealth() < 1)
			{
				targetHolder->setHealth(((RangeWeapon *)playerHolder->getWeapon())->getDamage());
				tower_damaged[targetId] = true;
			}
		}
		else
		{
			targetHolder->setHealth(((RangeWeapon *)playerHolder->getWeapon())->getDamage());
			tower_damaged[targetId] = true;
		}

		if (targetHolder->getHealth() < 1)
		{
			tower_kill[targetId] = true;

			targetHolder->setRespawn(RESPAWN_COUNTER);
			//Window::removeDrawList((*targetHolder).getName());
			//Window::removePlayerList((*targetHolder).getName());
			//respawn.push_back(targetHolder);
			for (uint i = 0; i < tower.size(); i++)
			{
				if (tower[i]->getPlayerID() == targetId)
				{
					tower[i]->setAliveModelM(tower[i]->getModelM());
					tower[i]->setModelM(tower[i]->getModelM()*glm::translate(vec3(1000, 1000, 1000)));
				}
			}
			//cout << playerId << " " << dmg << endl;
			//RangeWeapon * newItem = new RangeWeapon(dist,
			//	spd,
			//	dmg);
			//playerHolder->setWeapon(newItem);
			playerHolder->setKills(1);
			//RangeWeapon * newItem = new RangeWeapon(((RangeWeapon *)player[0]->getItem())->getDistance() * 3
			//										, ((RangeWeapon *)player[0]->getItem())->getSpeed() * 3);
		}
	}

	void damageStationary(int targetId, int playerId)
	{
		Object * playerHolder = getPlayerObj(playerId);
		Object * targetHolder = stationary[targetId];
		targetHolder->setHealth(((RangeWeapon *)playerHolder->getWeapon())->getDamage());
		platformDamaged[targetId] = true;
		if (targetHolder->getHealth() < 1)
		{
			platformDead[targetId] = true;
			targetHolder->setRespawn(RESPAWN_COUNTER);
			//Window::removeDrawList((*targetHolder).getName());
			//Window::removePlayerList((*targetHolder).getName());
			//respawn.push_back(targetHolder);
			stationary[targetId]->setAliveModelM(stationary[targetId]->getModelM());
			stationary[targetId]->setModelM(stationary[targetId]->getModelM()*glm::translate(vec3(1000, 1000, 1000)));
		}
	}

	void damageStationaryT(int targetId, int playerId)
	{
		Object * playerHolder = tower[playerId];
		Object * targetHolder = stationary[targetId];
		targetHolder->setHealth(((Tower*)playerHolder)->getDamage());
		platformDamaged[targetId] = true;
		if (targetHolder->getHealth() < 1)
		{
			platformDead[targetId] = true;
			targetHolder->setRespawn(RESPAWN_COUNTER);
			//Window::removeDrawList((*targetHolder).getName());
			//Window::removePlayerList((*targetHolder).getName());
			//respawn.push_back(targetHolder);
			stationary[targetId]->setAliveModelM(stationary[targetId]->getModelM());
			stationary[targetId]->setModelM(stationary[targetId]->getModelM()*glm::translate(vec3(1000, 1000, 1000)));
		}
	}
	

	void basicAttack(int playerID)
	{
	  for (uint j = 0; j < player.size(); j++)
	    {
	    if (j == playerID)
	      continue;
	    AABB pBox = player[playerID]->getAABB();
	    AABB sBox = player[j]->getAABB();
	    vector<int> holder;	
	    //[p][s]
	    if ((pBox.max[2] <= sBox.max[2] + 5) && (pBox.max[2] >= sBox.max[2] - 5)  && pBox.max[0] == sBox.min[0])
	      {
		player[j]->postTrans(glm::translate(vec3(1, 0.5, 0)));
		damagePlayer(j, playerID);
	      }
	    //[s][p]
	    else if ((pBox.max[2] <= sBox.max[2] + 5) && (pBox.max[2] >= sBox.max[2] - 5) && pBox.min[0] == sBox.max[0])
	      {
		player[j]->postTrans(glm::translate(vec3(-1, 0.5, 0)));
		damagePlayer(j, playerID);
	      }
	    //[p]
	    //[s]
	    else if ((pBox.max[0] <= sBox.max[0] + 5) && (pBox.max[0] >= sBox.max[0] - 5) && pBox.min[2] == sBox.max[2])
	      {
		player[j]->postTrans(glm::translate(vec3(0, 0.5, -1)));
		damagePlayer(j, playerID);
	      }
	    //[s]
	    //[p]
	    else if ((pBox.max[0] <= sBox.max[0] + 5) && (pBox.max[0] >= sBox.max[0] - 5) && pBox.max[2] == sBox.min[2])
	      {
		player[j]->postTrans(glm::translate(vec3(0, 0.5, 1)));
		damagePlayer(j, playerID);
	      }
	    }
	  
	}
	void projectileAttack(int playerID, mat4 * cam, int shootID)
	{
		mat4 test = *cam; //cam->getCamM();
		vec4 holder = test*vec4(0, 0, -1, 0); //orientation of camera in object space
		mat4 player1 = getPlayerObj(playerID)->getModelM();
		vec4 playerHolder = player1*vec4(0, 0, 0, 1);
		Cube * playerObject = ((Cube *)getPlayerObj(playerID));
		Object * playerHold = getPlayerObj(playerID);

		Projectile* cubeT = new Projectile(player.size() + respawn.size());
		cubeT->setKd(vec3(0.8, 0.0, 0.0));
		cubeT->setKa(vec3(0.3, 0.0, 0.0));
		cubeT->setKs(vec3(0.4, 0.0, 0.0));
		cubeT->setShininess(100);
		cubeT->setReflectFactor(vec2(0.2, 0.5));
		cubeT->setEta(0.5);
		cubeT->setCubeMapUnit(3);
		cubeT->setSpeed(5);
		//cubeT->postTrans(glm::translate(vec3(playerHolder[0] -2 + ((holder[0]) / 4), playerHolder[1], playerHolder[2] - (holder[2] / 4))));
		cubeT->setModelM(player1*glm::translate(vec3(0, 2, 0)));//get the new cube matrix by translating the player0 matrix forward in player0 object space. This way the new matrix will inherit player0 oriantation 
		cubeT->setAABB(AABB(vec3(-0.8, -0.8, -0.8), vec3(0.8, 0.8, 0.8)));
		AABB hold = cubeT->getAABB();
		cubeT->setStartX(hold.max[0]);
		cubeT->setStartY(hold.max[1]);
		cubeT->setStartZ(hold.max[2]);
		cubeT->setPlayerID(playerID);
		cubeT->setTeamID(player[playerID]->getTeamID());

		//Name and type
		cubeT->setType(CUBE);
		cubeT->setName("Test Cube" + std::to_string(projectile_counter));
		projectile_counter++;
		cubeT->setDistance(((RangeWeapon *)(playerHold)->getWeapon())->getDistance());
		//cout << cubeT->getPlayerID() << " " << cubeT->getDistance() << " " << cubeT->getSpeed() << " " << ((RangeWeapon *)playerHold->getWeapon())->getDamage() << " " << endl;
		//Add Cube to the draw list
		////////////////////////////////////////////////////////Window::addDrawList(cubeT);
		projectile.push_back(cubeT);
		cubeT->setSpeed(50);
		//cubeT->setHMove((holder[0] / 4));
		cubeT->setVelocity(vec3(player1*vec4(vec3(holder)*((RangeWeapon *)playerHold->getWeapon())->getSpeed(),0.0)));// set object space velocity to camera oriantation in object space. Since camera always have the same xz oriantation as the object, xz oriantation wouldnt change when camera rotate.
		cubeT->setShootID(shootID);
		//cubeT->setVMove(1);  //do this if you want the cube to not have vertical velocity. uncomment the above setVelocity.
		//cout << holder[0] << ' ' << holder[1] << ' ' << holder[2] << ' ' << playerHolder[0] << ' ' << playerHolder[2] << endl;
	}
	void towerProjectileAttack(float t){
		LARGE_INTEGER ct;
		QueryPerformanceCounter(&ct);
		for (uint i = 0; i < tower.size(); i++){
			if (tower[i]->getHealth()>0 && tower[i]->checkShoot(ct)){
				int pid;
				float min_dist=10000;
				for (uint k = 0; k < player.size(); k++){
					if (player[k]->getHealth()>0 && tower[i]->getTeamID() != player[k]->getTeamID()){
						float dist = glm::distance(vec3(tower[i]->getModelM()*vec4(0, 0, 0, 1)), vec3(player[k]->getModelM()*vec4(0, 0, 0, 1)));
						if (dist < tower[i]->getShootRange() && dist<min_dist){
							pid = k;
							min_dist = dist;
						}
					}
				}
				if (min_dist != 10000){
					Projectile* cubeT = new Projectile(player.size() + respawn.size());
					cubeT->setSpeed(5);
					mat4 pjt_model = tower[i]->getModelM()*glm::translate(vec3(0, 5, 0));
					cubeT->setModelM(pjt_model);//get the new cube matrix by translating the player0 matrix forward in player0 object space. This way the new matrix will inherit player0 oriantation 
					cubeT->setAABB(AABB(vec3(-0.5, -0.5, -0.5), vec3(0.5, 0.5, 0.5)));
					AABB hold = cubeT->getAABB();
					cubeT->setStartX(hold.max[0]);
					cubeT->setStartY(hold.max[1]);
					cubeT->setStartZ(hold.max[2]);
					cubeT->setTeamID(tower[i]->getTeamID());
					cubeT->setPlayerID(tower[i]->getPlayerID());

					//Name and type
					cubeT->setType(CUBE);
					cubeT->setName("Test Cube" + std::to_string(projectile_counter));
					cubeT->setDistance(tower[i]->getShootRange());
					tower_projectile.push_back(cubeT);
					cubeT->setSpeed(50);
					vec3 dir = glm::normalize(vec3(player[pid]->getModelM()*vec4(0, 0, 0, 1)) - vec3(pjt_model*vec4(0, 0, 0, 1)));
					cubeT->setVelocity(dir*tower[i]->getShootSpeed());// set object space velocity to camera oriantation in object space. Since camera always have the same xz oriantation as the object, xz oriantation wouldnt change when camera rotate.
					int shootID = tower_shoot_counter;
					tower_shoot_counter++;
					tower_shoot_counter %= 1000;
					cubeT->setShootID(shootID);
					tower[i]->setLastShoot(ct);
					tower[i]->setLastShootDir(dir);

					tower_shoot.push_back(TowerShootInfo(i, shootID, dir));
					tower_shoot_check[i] = true;
				}
			}
		}
	}
	void clearTowerShoot(){
		tower_shoot.clear();
	}
	void despawnProjectile()
	{
		//cout << tower_projectile.size() << endl;
		for (uint i = 0; i < projectile.size(); i++)
		{
			float startX = projectile[i]->getStartX();
			float startY = projectile[i]->getStartY();
			float startZ = projectile[i]->getStartZ();
			AABB curr = projectile[i]->getAABB();
			int distance = sqrt(pow(curr.max[0] - startX, 2) + pow(curr.max[1] - startY, 2) + pow(curr.max[2] - startZ, 2));//Pythagorean Theorem


			//cout << startX << " " << curr.max[0] << " " << curr.max[0] - startX << " " << distance << endl;
			//cout << startY << " " << curr.max[1] << " " << curr.max[1] - startY << " " << distance << endl;
			//cout << startZ << " " << curr.max[2] << " " << curr.max[2] - startZ << " " << distance << endl;
			if (distance >= (*projectile[i]).getDistance())
			{
				////////////////////////////////////////////////Window::removeDrawList((*projectile[i]).getName());
				delete projectile[i];
				projectile.erase(projectile.begin() + i);
			}
		}
		for (uint i = 0; i < tower_projectile.size(); i++)
		{
			float startX = tower_projectile[i]->getStartX();
			float startY = tower_projectile[i]->getStartY();
			float startZ = tower_projectile[i]->getStartZ();
			AABB curr = tower_projectile[i]->getAABB();
			int distance = sqrt(pow(curr.max[0] - startX, 2) + pow(curr.max[1] - startY, 2) + pow(curr.max[2] - startZ, 2));//Pythagorean Theorem


			//cout << startX << " " << curr.max[0] << " " << curr.max[0] - startX << " " << distance << endl;
			if (distance >= (*tower_projectile[i]).getDistance())
			{
				////////////////////////////////////////////////Window::removeDrawList((*projectile[i]).getName());
				delete tower_projectile[i];
				tower_projectile.erase(tower_projectile.begin() + i);
			}
		}
	}
	void recover(int playerId)
	{
		getPlayerObj(playerId)->jump(20);
	}
	void rechargeJump()
	{
		for (uint i = 0; i < player.size(); i++)
		{
			if (player[i]->getTouchGround() && player[i]->getNumJumps() < player[i]->getTotalJumps())
				player[i]->incNumJumps();
		}
	}
	void takeItem()
	{

	}
	void resetVelocity(int playerId)
	{
		player[playerId]->resetVelocity();
	}
	int numPlayers()
	{
		return player.size();
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////// END OF PLAYER ACTIONS ///////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool getPlayerDamaged(int i)
	{
		return playerDamaged[i];
	}
	void setPlayerDamaged(int i, bool b)
	{
		playerDamaged[i] = b;
	}
	bool getPlayerDead(int i)
	{
		return playerDead[i];
	}
	void setPlayerDead(int i, bool b)
	{
		playerDead[i] = b;
	}

	boost::array<mat4, 4> getPlayerMats(){
		boost::array<mat4, 4> c;
		assert(player.size() == 4);
		for (uint i = 0; i < 4; i++){
			c[i] = player[i]->getModelM();
		}
		return c;
	}
	boost::array<mat4, 5> getElevatorMats(){
		boost::array<mat4, 5> c;
		for (uint i = 0; i < elevator.size(); i++){
			c[i] = elevator[i]->getModelM();
		}
		return c;
	}
	boost::array<mat4, 4> getPlayerCams(){
		boost::array<mat4, 4> m;
		assert(player.size() == 4);
		for (uint i = 0; i < 4; i++){
			m[i] = camM[i];
		}
		return m;
	}
	Object * getPlayerElement(int i)
	{
		return player[i];
	}
	Object * getPlayer(int i)
	{
		return getPlayerObj(i);
	}
	boost::array<mat4, NUM_TOWERS> getTowerMats(){
		boost::array<mat4, NUM_TOWERS> m;
		assert(tower.size() == NUM_TOWERS);
		for (uint i = 0; i < NUM_TOWERS; i++){
			m[i] = tower[i]->getModelM();
		}
		return m;
	}
	vector<int> getPlayerProjectileDespawnList(){
		return despon_player_projectile_list;
	}
	void clearPlayerProjectileDespawnList(){
		despon_player_projectile_list.clear();
	}
	vector<int> getTowerProjectileDespawnList(){ return despon_tower_projectile_list; }
	void clearTowerProjectileDespawnList(){ despon_tower_projectile_list.clear(); }
	bool* getTowerShootCheck(){ return tower_shoot_check; }
	void clearTowerShootCheck(){
		for (int i = 0; i < NUM_TOWERS; i++){
			tower_shoot_check[i] = false;
		}
	}
	int getLastTowerShootID(int tid){ return tower[tid]->getLastShootID(); }
	vec3 getLastTowerShootDir(int tid){ return tower[tid]->getLastShootDir(); }
	bool* getTowerDamaged(){ return tower_damaged; }
	void clearTowerDamaged(){
		for (int i = 0; i < NUM_TOWERS; i++){
			tower_damaged[i] = false;
		}
	}
	bool* getTowerKill(){ return tower_kill; }
	void clearTowerKill(){
		for (int i = 0; i < NUM_TOWERS; i++){
			tower_kill[i] = false;
		}
	}
	int getTowerHealth(int towerID){ return tower[towerID]->getHealth(); }
	void initialize(){

		Cube* md50 = new Cube();
		md50->setSpeed(PLAYER_SPEED);
		md50->postTrans(glm::translate(vec3(0, 100, -92)));
		md50->postRotate(glm::rotate(mat4(1.0), 180.0f, vec3(0, 1, 0)));
		md50->setAABB(AABB(vec3(-0.25, 0.0, -0.25), vec3(0.25, 1.5, 0.25)));
		md50->setType(MODEL);
		md50->setName("Player Model0");
		md50->setPlayerID(0);
		md50->setTeamID(0);
		md50->setAliveModelM(md50->getModelM());
		addPlayer(md50);

		Cube* md51 = new Cube();
		md51->setSpeed(PLAYER_SPEED);
		md51->postTrans(glm::translate(vec3(0, 100, 92)));
		md51->postRotate(glm::rotate(mat4(1.0), 0.0f, vec3(0, 1, 0)));
		md51->setAABB(AABB(vec3(-0.25, 0.0, -0.25), vec3(0.25, 1.5, 0.25)));
		md51->setType(MODEL);
		md51->setName("Player Model1");
		md51->setPlayerID(1);
		md51->setTeamID(1);
		md51->setAliveModelM(md51->getModelM());
		addPlayer(md51);

		Cube* md52 = new Cube();
		md52->setSpeed(PLAYER_SPEED);
		md52->postTrans(glm::translate(vec3(0, 100, -94)));
		md52->setAABB(AABB(vec3(-0.25, 0.0, -0.25), vec3(0.25, 1.5, 0.25)));
		md52->postRotate(glm::rotate(mat4(1.0), 180.0f, vec3(0, 1, 0)));
		md52->setType(MODEL);
		md52->setName("Player Model2");
		md52->setPlayerID(2);
		md52->setTeamID(0);
		md52->setAliveModelM(md52->getModelM());
		addPlayer(md52);

		Cube* md53 = new Cube();
		md53->setSpeed(PLAYER_SPEED);
		md53->postTrans(glm::translate(vec3(0, 100, 94)));
		md53->postRotate(glm::rotate(mat4(1.0), 0.0f, vec3(0, 1, 0)));
		md53->setAABB(AABB(vec3(-0.25, 0.0, -0.25), vec3(0.25, 1.5, 0.25)));
		md53->setType(MODEL);
		md53->setName("Player Model3");
		md53->setPlayerID(3);
		md53->setTeamID(1);
		md53->setAliveModelM(md53->getModelM());
		addPlayer(md53);

		for (uint i = 0; i < player.size(); i++)
		{
			playerDamaged.push_back(false);
			playerDead.push_back(false);
		}

		//triplet tower
		Tower* tw0 = new Tower();
		tw0->postTrans(glm::translate(vec3(-68, 14.0, -80)));
		tw0->setAABB(AABB(vec3(-0.7, 0.75, -0.7), vec3(0.7, 3.75, 0.7)));
		tw0->setInterval(1.0);//shoot every 1 second if target exists
		tw0->setShootRange(40);
		tw0->setShootSpeed(60);
		tw0->putHealth(20);
		tw0->setDamage(-3);
		tw0->setType(MODEL);
		tw0->setName("Tower Model0");
		tw0->setTeamID(0);
		tw0->setPlayerID(0);
		addTower(tw0);

		//triplet tower
		Tower* tw1 = new Tower();
		tw1->postTrans(glm::translate(vec3(68, 14.0, -80)));
		tw1->setAABB(AABB(vec3(-0.7, 0.75, -0.7), vec3(0.7, 3.75, 0.7)));
		tw1->setInterval(1.0);//shoot every 1 second if target exists
		tw1->setShootRange(40);
		tw1->setShootSpeed(60);
		tw1->putHealth(20);
		tw1->setDamage(-3);
		tw1->setType(MODEL);
		tw1->setName("Tower Model0");
		tw1->setTeamID(0);
		tw1->setPlayerID(1);
		addTower(tw1);

		//pctopus tower
		Tower* tw2 = new Tower();
		tw2->postTrans(glm::translate(vec3(68, 14, 80)));
		tw2->setAABB(AABB(vec3(-0.7, 0.6, -0.7), vec3(0.7, 4.79, 0.7)));
		tw2->setInterval(1.0);//shoot every 1 second if target exists
		tw2->setShootRange(40);
		tw2->setShootSpeed(60);
		tw2->putHealth(20);
		tw2->setDamage(-3);
		tw2->setType(MODEL);
		tw2->setName("Tower Model1");
		tw2->setTeamID(1);
		tw2->setPlayerID(2);
		addTower(tw2);

		//pctopus tower
		Tower* tw3 = new Tower();
		tw3->postTrans(glm::translate(vec3(-68, 14, 80)));
		tw3->setAABB(AABB(vec3(-0.7, 0.6, -0.7), vec3(0.7, 4.79, 0.7)));
		tw3->setInterval(1.0);//shoot every 1 second if target exists
		tw3->setShootRange(40);
		tw3->setShootSpeed(60);
		tw3->putHealth(20);
		tw3->setDamage(-3);
		tw3->setType(MODEL);
		tw3->setName("Tower Model1");
		tw3->setTeamID(1);
		tw3->setPlayerID(3);
		addTower(tw3);

		// TODO make this the boss tower
		Tower* tower100 = new Tower();
		tower100->postTrans(glm::translate(vec3(ORIGINX0,
			ORIGINY0 + CENTER_TOWERPLAT_HEIGHT - 0,
			ORIGINZ0)));
		tower100->setAABB(AABB(vec3(-0.7, 0.6, -0.7), vec3(0.7, 4.79, 0.7)));
		tower100->setInterval(1.0);//shoot every 1 second if target exists
		tower100->setShootRange(40);
		tower100->setShootSpeed(60);
		tower100->setHealth(20);
		tower100->setDamage(-3);
		tower100->setType(MODEL);
		tower100->setName("octo base");
		tower100->setTeamID(1);
		tower100->setPlayerID(4);

		addTower(tower100);


		// TODO make this the boss tower
		Tower* tower200 = new Tower();
		tower200->postTrans(glm::translate(vec3(ORIGINX1,
			ORIGINY1 + CENTER_TOWERPLAT_HEIGHT - 2,
			ORIGINZ1)));
		tower200->setAABB(AABB(vec3(-0.7, 0.6, -0.7), vec3(0.7, 4.79, 0.7)));
		tower200->setInterval(1.0);//shoot every 1 second if target exists
		tower200->setShootRange(40);
		tower200->setShootSpeed(60);
		tower200->setHealth(20);
		tower200->setDamage(-3);
		tower200->setType(MODEL);
		tower200->setName("nut base");
		tower200->setTeamID(0);
		tower200->setPlayerID(5);

		addTower(tower200);

		Ground* ground = new Ground();
		ground->loadColorTex("img/moon_tex/moon_COLOR.png", "PNG");
		ground->loadDispTex("img/moon_tex/moon_DISP.png", "PNG");
		ground->loadNormalTex("img/moon_tex/moon_NRM.png", "PNG");
		ground->loadOccTex("img/moon_tex/moon_OCC.png", "PNG");
		ground->loadSpecTex("img/moon_tex/moon_SPEC.png", "PNG");
		ground->setDimensionS(200);
		ground->setDimensionT(200);
		ground->setRow(100);
		ground->setColumn(100);
		ground->setHeight(6);
		ground->generate();
		ground->setType(GROUND);
		ground->setName("Ground");
		addStationary(ground);

		//elevator 
		Elevator* platform_01 = new Elevator();
		//platform_01->setSpeed(5); 
		platform_01->postTrans(glm::translate(vec3(0, 5.0, 0)));
		platform_01->setAABB(AABB(vec3(-10.0, -0.5, -10.0), vec3(10.0, 0.5, 10.0)));
		platform_01->setType(ELEVATOR);
		platform_01->setDirection(1);
		platform_01->setName("Test Platform");
		addStationary(platform_01);
		elevator.push_back(platform_01);

		//island 
		Cube* platform_02 = new Cube(-20, 20, -0.5, 0.5, -20, 20);
		//platform_01->setSpeed(5); 
		platform_02->postTrans(glm::translate(vec3(30, 14, 0)));
		platform_02->setAABB(AABB(vec3(-20, -0.5, -20), vec3(20, 0.5, 20)));
		platform_02->setType(CUBE);
		platform_02->setName("Test Platform");
		addStationary(platform_02);

		//island 
		Cube* platform_03 = new Cube(-20, 20, -0.5, 0.5, -20, 20);
		//platform_01->setSpeed(5); 
		platform_03->postTrans(glm::translate(vec3(-30, 14, 0)));
		platform_03->setAABB(AABB(vec3(-20, -0.5, -20), vec3(20, 0.5, 20)));
		platform_03->setType(CUBE);
		platform_03->setName("Test Platform");
		addStationary(platform_03);

		//walkway 
		Cube* platform_04 = new Cube(-10.0, 10.0, -0.5, 0.5, -10, 42);
		//platform_01->setSpeed(5); 
		platform_04->postTrans(glm::translate(vec3(0.0, 14.0, 20.0)));
		platform_04->setAABB(AABB(vec3(-10.0, -0.5, -10), vec3(10.0, 0.5, 42)));
		platform_04->setType(CUBE);
		platform_04->setName("Test Platform");
		addStationary(platform_04);

		//barricade on walkway 
		/*Cube* platform_05 = new Cube(-5, 5, -5, 5, -.5, .5);
		//platform_01->setSpeed(5); 
		platform_05->postTrans(glm::translate(vec3(0.0, 18.0, 40.0)));
		platform_05->setAABB(AABB(vec3(-5.0, -5, -0.5), vec3(5.0, 5, .5)));
		platform_05->setType(CUBE);
		platform_05->setName("Test Platform");
		addStationary(platform_05);*/

		//walkway 
		Cube* platform_07 = new Cube(-10.0, 10.0, -0.5, 0.5, -42, 10);
		//platform_01->setSpeed(5); 
		platform_07->postTrans(glm::translate(vec3(0.0, 14.0,-20.0)));
		platform_07->setAABB(AABB(vec3(-10.0, -0.5, -42), vec3(10.0, 0.5, 10)));
		platform_07->setType(CUBE);
		platform_07->setName("Test Platform");
		addStationary(platform_07);

		//barricade on walkway 
		/*Cube* platform_08 = new Cube(-5, 5, -5, 5, -.5, .5);
		//platform_01->setSpeed(5); 
		platform_08->postTrans(glm::translate(vec3(0.0, 18.0, -40.0)));
		platform_08->setAABB(AABB(vec3(-5.0, -5, -0.5), vec3(5.0, 5, 0.5)));
		platform_08->setType(CUBE);
		platform_08->setName("Test Platform");
		addStationary(platform_08);*/

		//tower island
		Cube* platform_09 = new Cube(-10, 10, -0.5, 0.5, -10, 10);
		//platform_01->setSpeed(5); 
		platform_09->postTrans(glm::translate(vec3(60.0, 14.0, -80.0)));
		platform_09->setAABB(AABB(vec3(-10, -0.5, -10), vec3(10, 0.5, 10)));
		platform_09->setType(CUBE);
		platform_09->setName("Test Platform");
		addStationary(platform_09);

		//tower island
		Cube* platform_10 = new Cube(-10, 10, -0.5, 0.5, -10, 10);
		//platform_01->setSpeed(5); 
		platform_10->postTrans(glm::translate(vec3(-60.0, 14.0, -80.0)));
		platform_10->setAABB(AABB(vec3(-10, -0.5, -10), vec3(10, 0.5, 10)));
		platform_10->setType(CUBE);
		platform_10->setName("Test Platform");
		addStationary(platform_10);

		//tower island
		Cube* platform_10b = new Cube(-10, 10, -0.5, 0.5, -10, 10);
		//platform_01->setSpeed(5); 
		platform_10b->postTrans(glm::translate(vec3(-60.0, 14.0, 80.0)));
		platform_10b->setAABB(AABB(vec3(-10, -0.5, -10), vec3(10, 0.5, 10)));
		platform_10b->setType(CUBE);
		platform_10b->setName("Test Platform");
		addStationary(platform_10b);

		//tower island
		Cube* platform_06 = new Cube(-10, 10, -0.5, 0.5, -10, 10);
		//platform_01->setSpeed(5); 
		platform_06->postTrans(glm::translate(vec3(60.0, 14.0, 80.0)));
		platform_06->setAABB(AABB(vec3(-10, -0.5, -10), vec3(10, 0.5, 10)));
		platform_06->setType(CUBE);
		platform_06->setName("Test Platform");
		addStationary(platform_06);

		//2nd level
		Cube* platform_11 = new Cube(-10, 10, -0.5, 0.5, -5, 5);
		//platform_01->setSpeed(5); 
		platform_11->postTrans(glm::translate(vec3(0, 50.0, 15.0)));
		platform_11->setAABB(AABB(vec3(-10, -0.5, -5), vec3(10, 0.5, 5)));
		platform_11->setType(CUBE);
		platform_11->setName("Test Platform");
		addStationary(platform_11);

		//2nd level
		Cube* platform_12 = new Cube(-10.0, 10.0, -0.5, 0.5, -5, 5);
		//platform_01->setSpeed(5); 
		platform_12->postTrans(glm::translate(vec3(0, 50.0, -15.0)));
		platform_12->setAABB(AABB(vec3(-10, -0.5, -5), vec3(10, 0.5, 5)));
		platform_12->setType(CUBE);
		platform_12->setName("Test Platform");
		addStationary(platform_12);

		//2nd level
		Cube* platform_13 = new Cube(-5.0, 5.0, -0.5, 0.5, -20, 20);
		//platform_01->setSpeed(5); 
		platform_13->postTrans(glm::translate(vec3(15.0, 50.0, 0.0)));
		platform_13->setAABB(AABB(vec3(-5, -0.5, -20), vec3(5, 0.5, 20)));
		platform_13->setType(CUBE);
		platform_13->setName("Test Platform");
		addStationary(platform_13);

		//2nd level
		Cube* platform_14 = new Cube(-5.0, 5.0, -0.5, 0.5, -20, 20);
		//platform_01->setSpeed(5); 
		platform_14->postTrans(glm::translate(vec3(-15.0, 50.0, 0.0)));
		platform_14->setAABB(AABB(vec3(-5, -0.5, -20), vec3(5, 0.5, 20)));
		platform_14->setType(CUBE);
		platform_14->setName("Test Platform");
		addStationary(platform_14);


		//base trampolines
		Trampoline* tramp_01 = new Trampoline();
		//platform_01->setSpeed(5); 
		tramp_01->postTrans(glm::translate(vec3(20, 5.0, 45)));
		tramp_01->setAABB(AABB(vec3(-2.0, -0.5, -2.0), vec3(2.0, 0.5, 2.0)));
		tramp_01->setBoost(vec3(0, 60, 0));
		tramp_01->setType(TRAMPOLINE);
		tramp_01->setName("Test Trampoline");
		addStationary(tramp_01);

		//base tramp
		Trampoline* tramp_02 = new Trampoline();
		//platform_01->setSpeed(5); 
		tramp_02->postTrans(glm::translate(vec3(-20, 5.0, 45)));
		tramp_02->setAABB(AABB(vec3(-2.0, -0.5, -2.0), vec3(2.0, 0.5, 2.0)));
		tramp_02->setBoost(vec3(0, 60, 0));
		tramp_02->setType(TRAMPOLINE);
		tramp_02->setName("Test Trampoline");
		addStationary(tramp_02);

		//base tramp 
		Trampoline* tramp_03 = new Trampoline();
		//platform_01->setSpeed(5); 
		tramp_03->postTrans(glm::translate(vec3(20, 5.0, -45)));
		tramp_03->setAABB(AABB(vec3(-2.0, -0.5, -2.0), vec3(2.0, 0.5, 2.0)));
		tramp_03->setBoost(vec3(0, 60, 0));
		tramp_03->setType(TRAMPOLINE);
		tramp_03->setName("Test Trampoline");
		addStationary(tramp_03);

		//base tramp
		Trampoline* tramp_04 = new Trampoline();
		//platform_01->setSpeed(5); 
		tramp_04->postTrans(glm::translate(vec3(-20, 5.0, -45)));
		tramp_04->setAABB(AABB(vec3(-2.0, -0.5, -2.0), vec3(2.0, 0.5, 2.0)));
		tramp_04->setBoost(vec3(0, 60, 0));
		tramp_04->setType(TRAMPOLINE);
		tramp_04->setName("Test Trampoline");
		addStationary(tramp_04);

		/*//Trampoline 
		Trampoline* tramp_05 = new Trampoline();
		//platform_01->setSpeed(5); 
		tramp_05->postTrans(glm::translate(vec3(-15, 6.0, 0)));
		tramp_05->setAABB(AABB(vec3(-2.0, -0.5, -2.0), vec3(2.0, 0.5, 2.0)));
		tramp_05->setBoost(vec3(0, 30, 0));
		tramp_05->setType(TRAMPOLINE);
		tramp_05->setName("Test Trampoline");
		addStationary(tramp_05);

		//Trampoline 
		Trampoline* tramp_06 = new Trampoline();
		//platform_01->setSpeed(5); 
		tramp_06->postTrans(glm::translate(vec3(15, 7.0, 0)));
		tramp_06->setAABB(AABB(vec3(-2.0, -0.5, -2.0), vec3(2.0, 0.5, 2.0)));
		tramp_06->setBoost(vec3(0, 30, 0));
		tramp_06->setType(TRAMPOLINE);
		tramp_06->setName("Test Trampoline");
		addStationary(tramp_06);*/



		//teleporter 
		Teleporter* tele_01 = new Teleporter();
		//platform_01->setSpeed(5); 
		tele_01->postTrans(glm::translate(vec3(80, 14.0, 80)));
		tele_01->setAABB(AABB(vec3(-2.0, -0.5, -2.0), vec3(2.0, 0.5, 2.0)));
		tele_01->setEndpoint(glm::translate(vec3(-65, 15, 85)));
		tele_01->setType(TELEPORTER);
		tele_01->setName("Test Teleporter");
		addStationary(tele_01);

		//teleporter 
		Teleporter* tele_02 = new Teleporter();
		//platform_01->setSpeed(5); 
		tele_02->postTrans(glm::translate(vec3(-80, 14.0, 80)));
		tele_02->setAABB(AABB(vec3(-2.0, -0.5, -2.0), vec3(2.0, 0.5, 2.0)));
		tele_02->setEndpoint(glm::translate(vec3(65, 15, 85)));
		tele_02->setType(TELEPORTER);
		tele_02->setName("Test Teleporter");
		addStationary(tele_02);

		//teleporter 
		Teleporter* tele_03 = new Teleporter();
		//platform_01->setSpeed(5); 
		tele_03->postTrans(glm::translate(vec3(80, 14.0, -80)));
		tele_03->setAABB(AABB(vec3(-2.0, -0.5, -2.0), vec3(2.0, 0.5, 2.0)));
		tele_03->setEndpoint(glm::translate(vec3(-65, 15, -85)));
		tele_03->setType(TELEPORTER);
		tele_03->setName("Test Teleporter");
		addStationary(tele_03);

		//teleporter 
		Teleporter* tele_04 = new Teleporter();
		//platform_01->setSpeed(5); 
		tele_04->postTrans(glm::translate(vec3(-80, 14.0, -80)));
		tele_04->setAABB(AABB(vec3(-2.0, -0.5, -2.0), vec3(2.0, 0.5, 2.0)));
		tele_04->setEndpoint(glm::translate(vec3(65, 15, -85)));
		tele_04->setType(TELEPORTER);
		tele_04->setName("Test Teleporter");
		addStationary(tele_04);



		Elevator* ele_01 = new Elevator();
		//platform_01->setSpeed(5); 
		ele_01->postTrans(glm::translate(vec3(45, 14.0,25)));
		ele_01->setAABB(AABB(vec3(-5.0, -0.5, -5.0), vec3(5.0, 0.5, 5.0)));
		ele_01->setType(ELEVATOR);
		ele_01->setName("Test Elevator");
		ele_01->setDirection(0);
		addStationary(ele_01);
		elevator.push_back(ele_01);

		Elevator* ele_02 = new Elevator();
		//platform_01->setSpeed(5); 
		ele_02->postTrans(glm::translate(vec3(45, 14.0,-75)));
		ele_02->setAABB(AABB(vec3(-5.0, -0.5, -5.0), vec3(5.0, 0.5, 5.0)));
		ele_02->setType(ELEVATOR);
		ele_02->setName("Test Elevator");
		ele_02->setDirection(0);
		addStationary(ele_02);
		elevator.push_back(ele_02);

		Elevator* ele_03 = new Elevator();
		//platform_01->setSpeed(5); 
		ele_03->postTrans(glm::translate(vec3(-45, 14.0,75)));
		ele_03->setAABB(AABB(vec3(-5.0, -0.5, -5.0), vec3(5.0, 0.5, 5.0)));
		ele_03->setType(ELEVATOR);
		ele_03->setName("Test Elevator");
		ele_03->setDirection(-1);
		addStationary(ele_03);
		elevator.push_back(ele_03);

		Elevator* ele_04 = new Elevator();
		//platform_01->setSpeed(5); 
		ele_04->postTrans(glm::translate(vec3(-45, 14.0,-25)));
		ele_04->setAABB(AABB(vec3(-5.0, -0.5, -5.0), vec3(5.0, 0.5, 5.0)));
		ele_04->setType(ELEVATOR);
		ele_04->setName("Test Elevator");
		ele_04->setDirection(-1);
		addStationary(ele_04);
		elevator.push_back(ele_04);

		counter2 = 0;
		counter3 = 0.05f;
		//m_pMesh2 = new Mesh();
		//m_pMesh2->LoadMesh("Model/monky_04_27_smooth.dae");
		//m_pMesh2->setShader(sdrCtl.getShader("basic_model"));
		//m_pMesh2->setAdjustM(glm::translate(vec3(0.0, 4.1, 0.0))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0))*glm::scale(vec3(0.2, 0.2, 0.2)));
		//m_pMesh2->setAABB();

		/*MD5Model* md5 = new MD5Model();
		md5->setSpeed(5);
		md5->setAABB(AABB(vec3(-25.25, 0.0, -10.25), vec3(0.25, 1.5, 0.25)));
		md5->setType(MODEL);
		md5->setName("Player Model");
		//addPlayer(md5);*/

		//md6 = new MD5Model();
		//md6->LoadModel("Model/fleurOptonl.md5mesh");
		//md6->LoadAnim("Model/fleurOptonl.md5anim");
		//md6->setShader(sdrCtl.getShader("basic_texture"));
		//md6->setShininess(30);
		//md6->setAdjustM(glm::translate(vec3(0.0, 1.7, 0.0))*glm::rotate(mat4(1.0), 180.0f, vec3(0.0, 1, 0))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0))*glm::scale(vec3(0.05, 0.05, 0.05)));
		//md6->setModelM(glm::translate(vec3(1.0, 0.0, 0.0)));
		//md6->setType(MODEL);
		//md6->setName("Player Model");

		//Floor
		Teleporter* platform_200 = new Teleporter();
		//platform_01->setSpeed(5); 
		platform_200->postTrans(glm::translate(vec3(ORIGINX0,
			ORIGINY0 + 5,
			ORIGINZ0)));
		platform_200->setAABB(AABB(vec3(-PERIMETER_WALL_RADIUS, -0.5, -PERIMETER_WALL_RADIUS), vec3(PERIMETER_WALL_RADIUS, 0.5, PERIMETER_WALL_RADIUS)));
		platform_200->setType(TELEPORTER);
		platform_200->setEndpoint(glm::translate(vec3(0, 100, 12)));
		platform_200->setName("Test Platform");
		// don't draw for now so we can peek inside
		//addStationary(platform_200);
		addStationary(platform_200);

		//wall0
		Cube* platform_201 = new Cube(-0.5, 0.5, -15, 15, -PERIMETER_WALL_RADIUS, PERIMETER_WALL_RADIUS);
		//platform_01->setSpeed(5); 
		platform_201->postTrans(glm::translate(vec3(ORIGINX0 + PERIMETER_WALL_RADIUS,
			ORIGINY0 + PERIMETER_WALL_HEIGHT,
			ORIGINZ0)));
		platform_201->setAABB(AABB(vec3(-0.5, -15, -PERIMETER_WALL_RADIUS), vec3(0.5, 15, PERIMETER_WALL_RADIUS)));
		platform_201->setType(CUBE);
		platform_201->setName("Test Platform");
		addStationary(platform_201);

		//wall1
		Cube* platform_202 = new Cube(-0.5, 0.5, -15, 15, -PERIMETER_WALL_RADIUS, PERIMETER_WALL_RADIUS);
		//platform_01->setSpeed(5); 
		platform_202->postTrans(glm::translate(vec3(ORIGINX0 - PERIMETER_WALL_RADIUS,
			ORIGINY0 + PERIMETER_WALL_HEIGHT,
			ORIGINZ0)));
		platform_202->setAABB(AABB(vec3(-0.5, -15, -PERIMETER_WALL_RADIUS), vec3(0.5, 15, PERIMETER_WALL_RADIUS)));
		platform_202->setType(CUBE);
		platform_202->setName("Test Platform");
		addStationary(platform_202);

		//wall2
		Cube* platform_203 = new Cube(-PERIMETER_WALL_RADIUS, PERIMETER_WALL_RADIUS, -15, 15, -0.5, 0.5);
		//platform_01->setSpeed(5); 
		platform_203->postTrans(glm::translate(vec3(ORIGINX0,
			ORIGINY0 + PERIMETER_WALL_HEIGHT,
			ORIGINZ0 + PERIMETER_WALL_RADIUS)));
		platform_203->setAABB(AABB(vec3(-PERIMETER_WALL_RADIUS, -15, -0.5), vec3(PERIMETER_WALL_RADIUS, 15, 0.5)));
		platform_203->setType(CUBE);
		platform_203->setName("Test Platform");
		addStationary(platform_203);

		//wall3
		Cube* platform_204 = new Cube(-PERIMETER_WALL_RADIUS, PERIMETER_WALL_RADIUS, -15, 15, -0.5, 0.5);
		//platform_01->setSpeed(5); 
		platform_204->postTrans(glm::translate(vec3(ORIGINX0,
			ORIGINY0 + PERIMETER_WALL_HEIGHT,
			ORIGINZ0 - PERIMETER_WALL_RADIUS)));
		platform_204->setAABB(AABB(vec3(-PERIMETER_WALL_RADIUS, -15, -0.5), vec3(PERIMETER_WALL_RADIUS, 15, 0.5)));
		platform_204->setType(CUBE);
		platform_204->setName("Test Platform");
		addStationary(platform_204);

		// inside middle
		Cube* platform_205 = new Cube(-2, 2, -0.5, 0.5, -2, 2);
		//platform_01->setSpeed(5);
		platform_205->postTrans(glm::translate(vec3(ORIGINX0,
			ORIGINY0 + CENTER_TOWERPLAT_HEIGHT,
			ORIGINZ0)));
		platform_205->setAABB(AABB(vec3(-2, -0.5, -2), vec3(2, 0.5, 2))); 
		platform_205->setType(CUBE);
		platform_205->setName("Test Platform");
		addStationary(platform_205);


		//diag plat 0
		Cube* platform_206 = new Cube(-5, 5, -0.5, 0.5, -5, 5);
		//platform_01->setSpeed(5); 
		platform_206->postTrans(glm::translate(vec3(ORIGINX0 + CENTER_PLAT_SPACING,
			ORIGINY0 + CENTER_PLAT_HEIGHT,
			ORIGINZ0 + CENTER_PLAT_SPACING)));
		platform_206->setAABB(AABB(vec3(-5, -0.5, -5), vec3(5, 0.5, 5))); 
		platform_206->setType(CUBE);
		platform_206->setName("Test Platform");
		platform_206->setIsPlatformDamage(true);
		addStationary(platform_206);

		//diag plat 1
		Cube* platform_207 = new Cube(-5, 5, -0.5, 0.5, -5, 5);
		//platform_01->setSpeed(5); 
		platform_207->postTrans(glm::translate(vec3(ORIGINX0 - CENTER_PLAT_SPACING,
			ORIGINY0 + CENTER_PLAT_HEIGHT,
			ORIGINZ0 - CENTER_PLAT_SPACING)));
		platform_207->setAABB(AABB(vec3(-5, -0.5, -5), vec3(5, 0.5, 5))); 
		platform_207->setType(CUBE);
		platform_207->setIsPlatformDamage(true);
		platform_207->setName("Test Platform");
		addStationary(platform_207);

		//diag plat 2
		Cube* platform_208 = new Cube(-5, 5, -0.5, 0.5, -5, 5);
		//platform_01->setSpeed(5);
		platform_208->postTrans(glm::translate(vec3(ORIGINX0 + CENTER_PLAT_SPACING,
			ORIGINY0 + CENTER_PLAT_HEIGHT,
			ORIGINZ0 - CENTER_PLAT_SPACING)));
		platform_208->setAABB(AABB(vec3(-5, -0.5, -5), vec3(5, 0.5, 5))); 
		platform_208->setType(CUBE);
		platform_208->setName("Test Platform");
		platform_208->setIsPlatformDamage(true);
		addStationary(platform_208);

		//diag plat 3
		Cube* platform_209 = new Cube(-5, 5, -0.5, 0.5, -5, 5);
		//platform_01->setSpeed(5); 
		platform_209->postTrans(glm::translate(vec3(ORIGINX0 - CENTER_PLAT_SPACING,
			ORIGINY0 + CENTER_PLAT_HEIGHT,
			ORIGINZ0 + CENTER_PLAT_SPACING)));
		platform_209->setAABB(AABB(vec3(-5, -0.5, -5), vec3(5, 0.5, 5))); 
		platform_209->setType(CUBE);
		platform_209->setIsPlatformDamage(true);
		platform_209->setName("Test Platform");
		addStationary(platform_209);

		//stairs0 top
		Cube* platform_210 = new Cube(-20, 20, -1.5, 1.5, -5, 5);
		//platform_01->setSpeed(5); 
		platform_210->postTrans(glm::translate(vec3(ORIGINX0,
			ORIGINY0 + 17.5,
			ORIGINZ0 - 45)));
		platform_210->setAABB(AABB(vec3(-20, -1.5, -5), vec3(20, 1.5, 5)));
		platform_210->setType(CUBE);
		platform_210->setName("Test Platform");
		addStationary(platform_210);

		//stairs1
		Cube* platform_211 = new Cube(-20, 20, -1.5, 1.5, -5, 5);
		//platform_01->setSpeed(5); 
		platform_211->postTrans(glm::translate(vec3(ORIGINX0,
			ORIGINY0 + 14,
			ORIGINZ0 - 55)));
		platform_211->setAABB(AABB(vec3(-20, -1.5, -5), vec3(20, 1.5, 5)));
		platform_211->setType(CUBE);
		platform_211->setName("Test Platform");
		addStationary(platform_211);

		//stairs2
		Cube* platform_212 = new Cube(-20, 20, -1.5, 1.5, -5, 5);
		//platform_01->setSpeed(5); 
		platform_212->postTrans(glm::translate(vec3(ORIGINX0,
			ORIGINY0 + 10.5,
			ORIGINZ0 - 65)));
		platform_212->setAABB(AABB(vec3(-20, -1.5, -5), vec3(20, 1.5, 5)));
		platform_212->setType(CUBE);
		platform_212->setName("Test Platform");
		addStationary(platform_212);

		//stairs3
		Cube* platform_213 = new Cube(-20, 20, -1.5, 1.5, -5, 5);
		//platform_01->setSpeed(5); 
		platform_213->postTrans(glm::translate(vec3(ORIGINX0,
			ORIGINY0 + 7,
			ORIGINZ0 - 75)));
		platform_213->setAABB(AABB(vec3(-20, -1.5, -5), vec3(20, 1.5, 5)));
		platform_213->setType(CUBE);
		platform_213->setName("Test Platform");
		addStationary(platform_213);


		//rampart0
		Cube* platform_214 = new Cube(-PERIMETER_WALL_RADIUS, PERIMETER_WALL_RADIUS, -0.5, 0.5, -3, 3);
		//platform_01->setSpeed(5); 
		platform_214->postTrans(glm::translate(vec3(ORIGINX0,
			ORIGINY0 + 20,
			ORIGINZ0 - PERIMETER_WALL_RADIUS - 2)));
		platform_214->setAABB(AABB(vec3(-PERIMETER_WALL_RADIUS, -0.5, -3), vec3(PERIMETER_WALL_RADIUS, 0.5, 3)));
		platform_214->setType(CUBE);
		platform_214->setName("Test Platform");
		addStationary(platform_214);

		//rampart1
		Cube* platform_215 = new Cube(-PERIMETER_WALL_RADIUS, PERIMETER_WALL_RADIUS, -0.5, 0.5, -3, 3);
		//platform_01->setSpeed(5); 
		platform_215->postTrans(glm::translate(vec3(ORIGINX0,
			ORIGINY0 + 20,
			ORIGINZ0 + PERIMETER_WALL_RADIUS + 2)));
		platform_215->setAABB(AABB(vec3(-PERIMETER_WALL_RADIUS, -0.5, -3), vec3(PERIMETER_WALL_RADIUS, 0.5, 3)));
		platform_215->setType(CUBE);
		platform_215->setName("Test Platform");
		addStationary(platform_215);

		//rampart2
		Cube* platform_216 = new Cube(-3, 3, -0.5, 0.5, -PERIMETER_WALL_RADIUS, PERIMETER_WALL_RADIUS);
		//platform_01->setSpeed(5); 
		platform_216->postTrans(glm::translate(vec3(ORIGINX0 + PERIMETER_WALL_RADIUS + 2,
			ORIGINY0 + 20,
			ORIGINZ0)));
		platform_216->setAABB(AABB(vec3(-3, -0.5, -PERIMETER_WALL_RADIUS), vec3(3, 0.5, PERIMETER_WALL_RADIUS)));
		platform_216->setType(CUBE);
		platform_216->setName("Test Platform");
		addStationary(platform_216);

		//rampart3
		Cube* platform_217 = new Cube(-3, 3, -0.5, 0.5, -PERIMETER_WALL_RADIUS, PERIMETER_WALL_RADIUS);
		//platform_01->setSpeed(5); 
		platform_217->postTrans(glm::translate(vec3(ORIGINX0 - PERIMETER_WALL_RADIUS - 2,
			ORIGINY0 + 20,
			ORIGINZ0)));
		platform_217->setAABB(AABB(vec3(-3, -0.5, -PERIMETER_WALL_RADIUS), vec3(3, 0.5, PERIMETER_WALL_RADIUS)));
		platform_217->setType(CUBE);
		platform_217->setName("Test Platform");
		addStationary(platform_217);










		//Floor
		Teleporter* platform_300 = new Teleporter();
		//platform_01->setSpeed(5); 
		platform_300->postTrans(glm::translate(vec3(ORIGINX1,
			ORIGINY1 + 5,
			ORIGINZ1)));
		platform_300->setAABB(AABB(vec3(-PERIMETER_WALL_RADIUS, -0.5, -PERIMETER_WALL_RADIUS), vec3(PERIMETER_WALL_RADIUS, 0.5, PERIMETER_WALL_RADIUS)));
		platform_300->setType(TELEPORTER);
		platform_300->setEndpoint(glm::translate(vec3(0, 100, -12)));
		platform_300->setName("Test Platform");
		// don't draw for now so we can peek inside
		//addStationary(platform_300);
		addStationary(platform_300);

		//wall0
		Cube* platform_301 = new Cube(-0.5, 0.5, -15, 15, -PERIMETER_WALL_RADIUS, PERIMETER_WALL_RADIUS);
		//platform_01->setSpeed(5); 
		platform_301->postTrans(glm::translate(vec3(ORIGINX1 + PERIMETER_WALL_RADIUS,
			ORIGINY1 + PERIMETER_WALL_HEIGHT,
			ORIGINZ1)));
		platform_301->setAABB(AABB(vec3(-0.5, -15, -PERIMETER_WALL_RADIUS), vec3(0.5, 15, PERIMETER_WALL_RADIUS)));
		platform_301->setType(CUBE);
		platform_301->setName("Test Platform");
		addStationary(platform_301);

		//wall1
		Cube* platform_302 = new Cube(-0.5, 0.5, -15, 15, -PERIMETER_WALL_RADIUS, PERIMETER_WALL_RADIUS);
		//platform_01->setSpeed(5); 
		platform_302->postTrans(glm::translate(vec3(ORIGINX1 - PERIMETER_WALL_RADIUS,
			ORIGINY1 + PERIMETER_WALL_HEIGHT,
			ORIGINZ1)));
		platform_302->setAABB(AABB(vec3(-0.5, -15, -PERIMETER_WALL_RADIUS), vec3(0.5, 15, PERIMETER_WALL_RADIUS)));
		platform_302->setType(CUBE);
		platform_302->setName("Test Platform");
		addStationary(platform_302);

		//wall2
		Cube* platform_303 = new Cube(-PERIMETER_WALL_RADIUS, PERIMETER_WALL_RADIUS, -15, 15, -0.5, 0.5);
		//platform_01->setSpeed(5); 
		platform_303->postTrans(glm::translate(vec3(ORIGINX1,
			ORIGINY1 + PERIMETER_WALL_HEIGHT,
			ORIGINZ1 + PERIMETER_WALL_RADIUS)));
		platform_303->setAABB(AABB(vec3(-PERIMETER_WALL_RADIUS, -15, -0.5), vec3(PERIMETER_WALL_RADIUS, 15, 0.5)));
		platform_303->setType(CUBE);
		platform_303->setName("Test Platform");
		addStationary(platform_303);

		//wall3
		Cube* platform_304 = new Cube(-PERIMETER_WALL_RADIUS, PERIMETER_WALL_RADIUS, -15, 15, -0.5, 0.5);
		//platform_01->setSpeed(5); 
		platform_304->postTrans(glm::translate(vec3(ORIGINX1,
			ORIGINY1 + PERIMETER_WALL_HEIGHT,
			ORIGINZ1 - PERIMETER_WALL_RADIUS)));
		platform_304->setAABB(AABB(vec3(-PERIMETER_WALL_RADIUS, -15, -0.5), vec3(PERIMETER_WALL_RADIUS, 15, 0.5)));
		platform_304->setType(CUBE);
		platform_304->setName("Test Platform");
		addStationary(platform_304);

		// inside middle
		Cube* platform_305 = new Cube(-2, 2, -0.5, 0.5, -2, 2);
		//platform_01->setSpeed(5);
		platform_305->postTrans(glm::translate(vec3(ORIGINX1,
			ORIGINY1 + CENTER_TOWERPLAT_HEIGHT,
			ORIGINZ1)));
		platform_305->setAABB(AABB(vec3(-2, -0.5, -2), vec3(2, 0.5, 2)));
		platform_305->setType(CUBE);
		platform_305->setName("Test Platform");
		addStationary(platform_305);

		//diag plat 0
		Cube* platform_306 = new Cube(-5, 5, -0.5, 0.5, -5, 5);
		//platform_01->setSpeed(5); 
		platform_306->postTrans(glm::translate(vec3(ORIGINX1 + CENTER_PLAT_SPACING,
			ORIGINY1 + CENTER_PLAT_HEIGHT,
			ORIGINZ1 + CENTER_PLAT_SPACING)));
		platform_306->setAABB(AABB(vec3(-5, -0.5, -5), vec3(5, 0.5, 5)));
		platform_306->setType(CUBE);
		platform_306->setIsPlatformDamage(true);
		platform_306->setName("Test Platform");
		addStationary(platform_306);

		//diag plat 1
		Cube* platform_307 = new Cube(-5, 5, -0.5, 0.5, -5, 5);
		//platform_01->setSpeed(5); 
		platform_307->postTrans(glm::translate(vec3(ORIGINX1 - CENTER_PLAT_SPACING,
			ORIGINY1 + CENTER_PLAT_HEIGHT,
			ORIGINZ1 - CENTER_PLAT_SPACING)));
		platform_307->setAABB(AABB(vec3(-5, -0.5, -5), vec3(5, 0.5, 5)));
		platform_307->setType(CUBE);
		platform_307->setIsPlatformDamage(true);
		platform_307->setName("Test Platform");
		addStationary(platform_307);

		//diag plat 2
		Cube* platform_308 = new Cube(-5, 5, -0.5, 0.5, -5, 5);
		//platform_01->setSpeed(5);
		platform_308->postTrans(glm::translate(vec3(ORIGINX1 + CENTER_PLAT_SPACING,
			ORIGINY1 + CENTER_PLAT_HEIGHT,
			ORIGINZ1 - CENTER_PLAT_SPACING)));
		platform_308->setAABB(AABB(vec3(-5, -0.5, -5), vec3(5, 0.5, 5)));
		platform_308->setType(CUBE);
		platform_308->setIsPlatformDamage(true);
		platform_308->setName("Test Platform");
		addStationary(platform_308);

		//diag plat 3
		Cube* platform_309 = new Cube(-5, 5, -0.5, 0.5, -5, 5);
		//platform_01->setSpeed(5); 
		platform_309->postTrans(glm::translate(vec3(ORIGINX1 - CENTER_PLAT_SPACING,
			ORIGINY1 + CENTER_PLAT_HEIGHT,
			ORIGINZ1 + CENTER_PLAT_SPACING)));
		platform_309->setAABB(AABB(vec3(-5, -0.5, -5), vec3(5, 0.5, 5)));
		platform_309->setType(CUBE);
		platform_309->setIsPlatformDamage(true);
		platform_309->setName("Test Platform");
		addStationary(platform_309);

		//stairs0 top
		Cube* platform_310 = new Cube(-20, 20, -1.5, 1.5, -5, 5);
		//platform_01->setSpeed(5); 
		platform_310->postTrans(glm::translate(vec3(ORIGINX1,
			ORIGINY1 + 17.5,
			ORIGINZ1 + 45)));
		platform_310->setAABB(AABB(vec3(-20, -1.5, -5), vec3(20, 1.5, 5)));
		platform_310->setType(CUBE);
		platform_310->setName("Test Platform");
		addStationary(platform_310);

		//stairs1
		Cube* platform_311 = new Cube(-20, 20, -1.5, 1.5, -5, 5);
		//platform_01->setSpeed(5); 
		platform_311->postTrans(glm::translate(vec3(ORIGINX1,
			ORIGINY1 + 14,
			ORIGINZ1 + 55)));
		platform_311->setAABB(AABB(vec3(-20, -1.5, -5), vec3(20, 1.5, 5)));
		platform_311->setType(CUBE);
		platform_311->setName("Test Platform");
		addStationary(platform_311);

		//stairs2
		Cube* platform_312 = new Cube(-20, 20, -1.5, 1.5, -5, 5);
		//platform_01->setSpeed(5); 
		platform_312->postTrans(glm::translate(vec3(ORIGINX1,
			ORIGINY1 + 10.5,
			ORIGINZ1 + 65)));
		platform_312->setAABB(AABB(vec3(-20, -1.5, -5), vec3(20, 1.5, 5)));
		platform_312->setType(CUBE);
		platform_312->setName("Test Platform");
		addStationary(platform_312);

		//stairs3
		Cube* platform_313 = new Cube(-20, 20, -1.5, 1.5, -5, 5);
		//platform_01->setSpeed(5); 
		platform_313->postTrans(glm::translate(vec3(ORIGINX1,
			ORIGINY1 + 7,
			ORIGINZ1 + 75)));
		platform_313->setAABB(AABB(vec3(-20, -1.5, -5), vec3(20, 1.5, 5)));
		platform_313->setType(CUBE);
		platform_313->setName("Test Platform");
		addStationary(platform_313);


		//rampart0
		Cube* platform_314 = new Cube(-PERIMETER_WALL_RADIUS, PERIMETER_WALL_RADIUS, -0.5, 0.5, -3, 3);
		//platform_01->setSpeed(5); 
		platform_314->postTrans(glm::translate(vec3(ORIGINX1,
			ORIGINY1 + 20,
			ORIGINZ1 - PERIMETER_WALL_RADIUS - 2)));
		platform_314->setAABB(AABB(vec3(-PERIMETER_WALL_RADIUS, -0.5, -3), vec3(PERIMETER_WALL_RADIUS, 0.5, 3)));
		platform_314->setType(CUBE);
		platform_314->setName("Test Platform");
		addStationary(platform_314);

		//rampart1
		Cube* platform_315 = new Cube(-PERIMETER_WALL_RADIUS, PERIMETER_WALL_RADIUS, -0.5, 0.5, -3, 3);
		//platform_01->setSpeed(5); 
		platform_315->postTrans(glm::translate(vec3(ORIGINX1,
			ORIGINY1 + 20,
			ORIGINZ1 + PERIMETER_WALL_RADIUS + 2)));
		platform_315->setAABB(AABB(vec3(-PERIMETER_WALL_RADIUS, -0.5, -3), vec3(PERIMETER_WALL_RADIUS, 0.5, 3)));
		platform_315->setType(CUBE);
		platform_315->setName("Test Platform");
		addStationary(platform_315);

		//rampart2
		Cube* platform_316 = new Cube(-3, 3, -0.5, 0.5, -PERIMETER_WALL_RADIUS, PERIMETER_WALL_RADIUS);
		//platform_01->setSpeed(5); 
		platform_316->postTrans(glm::translate(vec3(ORIGINX1 + PERIMETER_WALL_RADIUS + 2,
			ORIGINY1 + 20,
			ORIGINZ1)));
		platform_316->setAABB(AABB(vec3(-3, -0.5, -PERIMETER_WALL_RADIUS), vec3(3, 0.5, PERIMETER_WALL_RADIUS)));
		platform_316->setType(CUBE);
		platform_316->setName("Test Platform");
		addStationary(platform_316);

		//rampart3
		Cube* platform_317 = new Cube(-3, 3, -0.5, 0.5, -PERIMETER_WALL_RADIUS, PERIMETER_WALL_RADIUS);
		//platform_01->setSpeed(5); 
		platform_317->postTrans(glm::translate(vec3(ORIGINX1 - PERIMETER_WALL_RADIUS - 2,
			ORIGINY1 + 20,
			ORIGINZ1)));
		platform_317->setAABB(AABB(vec3(-3, -0.5, -PERIMETER_WALL_RADIUS), vec3(3, 0.5, PERIMETER_WALL_RADIUS)));
		platform_317->setType(CUBE);
		platform_317->setName("Test Platform");
		addStationary(platform_317);









		for (uint i = 0; i < stationary.size(); i++)
		{
			platformDamaged.push_back(false);
			platformDead.push_back(false);
		}
		//cout << stationary.size() << " " << platformDamaged.size() << " " << platformDead.size() << endl;
		//int test = 0;
		//for (int i = 0; i < stationary.size(); i++)
		//{
		//	if (stationary[i]->getIsPlatformDamage())
		//		test++;
		//}
		//cout << test << endl;



		///////////////////////////////////////////////////////////////////////////Initialize PowerUps//////////////////////////////////////////////////////////////////////
		BillboardList * speedUp = new BillboardList();
		speedUp->AddBoard(vec3(-20.0f, 9.0f, 0.0f));//spd
		powerUps.push_back(speedUp);

		BillboardList * pwrUp = new BillboardList();
		pwrUp->AddBoard(vec3(20.0f, 9.0f, 0.0f));//dmg up
		powerUps.push_back(pwrUp);

		BillboardList * healthUp = new BillboardList();
		healthUp->AddBoard(vec3(0.0f, 19.0f, -20.0f));//health up
		powerUps.push_back(healthUp);

		BillboardList * shotSpdUp = new BillboardList();
		shotSpdUp->AddBoard(vec3(0.0f, 19.0f, 20.0f));//Shot Speed up
		powerUps.push_back(shotSpdUp);

		BillboardList * shotRngUp = new BillboardList();
		shotRngUp->AddBoard(vec3(0.0f, 10.0f, 0.0f));//Shot Rng up
		powerUps.push_back(shotRngUp);


		counter = 0;
		projectile_counter = 0;
		gameOver = false;
	}


protected:
	int counter2;
	float counter3;
	vector<Object*> stationary;
	vector<Elevator*> elevator;
	vector<Object*> player;
	vector<Object*> respawn;
	vector<Tower*> tower;
	vector<Object*> skillShot;
	vector<Object*> virtualTower;
	vector<Projectile*> projectile;
	vector<Projectile*> tower_projectile;
	vector<BillboardList *> powerUps;
	vector<Item *> items;
	vector<mat4> camM;
	vec3 gravity;
	vector<vector<int>> prevAttacked;//first element is playerID, second is axis
	vector<bool> playerDamaged;
	vector<bool> playerDead;
	bool playerOnTramp[4];
	bool playerOnTele[4];
	int pUpCooldown[6];
	int counter;
	int projectile_counter;
	vector<int> despon_player_projectile_list;
	vector<bool> platformDamaged;
	vector<bool> platformDead;
	vector<int> despon_tower_projectile_list;
	vector<TowerShootInfo> tower_shoot;
	int tower_shoot_counter;
	bool tower_shoot_check[NUM_TOWERS];
	bool tower_damaged[NUM_TOWERS];//only last valid simulation
	bool tower_kill[NUM_TOWERS];//only last valid simulation
	bool gameOver;
	Object * pPtr;
};

