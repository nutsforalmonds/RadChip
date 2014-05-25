#pragma once
#include <vector>
#include <map>
#include <math.h> 
#include <iostream>
#include "Object.h"
#include "Octree.h"
#include "Projectile.h"
#include "Window.h"
#include "MD5Model.h"
using namespace std;

extern ShaderController sdrCtl;

class Scene
{
public:
	Scene(){
		initialize();
	}
	~Scene(){
		for (uint i = 0; i<stationary.size(); i++){
			delete stationary[i];
		}
		stationary.clear();
		for (uint i = 0; i<player.size(); i++){
			delete player[i];
		}
		player.clear();
	}
	void simulate(float t, float sub){
		resolvePlayerRotation();
		while (t > sub){
			t -= sub;
			resolvePlayerTransition(sub);
		//	//octree here
			collisionDetection();
			collisionDetectionPlayer();
			collisionDetectionProjectile();
			despawnProjectile();
		}
		resolvePlayerTransition(t);
		////octree here
		collisionDetection();
		collisionDetectionPlayer();
		collisionDetectionProjectile();
		despawnProjectile();
	}
	void collisionDetection(Octree* octree);
	void collisionDetection(){
		//player-stationary detection
		for (uint i = 0; i < player.size(); i++){
			bool touchGround1 = false;
			bool touchGround2 = false;
			for (uint j = 0; j < stationary.size(); j++){
				if (strcmp(stationary[j]->getType().c_str(), "Ground") == 0){
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
	}

	void collisionDetectionPlayer(){
		//player-stationary detection
		for (uint i = 0; i < player.size(); i++){
			bool touchGround1 = player[i]->getTouchGround();
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

	void collisionDetectionProjectile(){
		//player-stationary detection
		for (uint i = 0; i < projectile.size(); i++){
			bool touchGround1 = projectile[i]->getTouchGround();
			for (uint j = 1; j < player.size(); j++){
				AABB pBox = projectile[i]->getAABB();
				AABB sBox = player[j]->getAABB();
				bool touchGround2 = player[j]->getTouchGround();
				bool collide = false;
				//[p][s]
				if ((pBox.max[2] <= sBox.max[2] ) && (pBox.max[2] >= sBox.max[2] - 1) && (pBox.max[0] <= sBox.max[0] ) && (pBox.max[0] >= sBox.max[0] - 1) && !(*projectile[i]).checkHit(j))
				{
					player[j]->postTrans(glm::translate(vec3(1, 0.5, 0)));
					player[j]->setHealth(-1);
					(*projectile[i]).setHit(j);
					if (player[j]->getHealth() < 1)
					{
						Window::removeDrawList((*player[j]).getName());
						player.erase(player.begin() + j);
					}
				}
				//[s][p]
				else if ((pBox.max[2] <= sBox.max[2]) && (pBox.max[2] >= sBox.max[2] - 1) && (pBox.max[0] <= sBox.max[0]) && (pBox.max[0] >= sBox.max[0] - 1) && !(*projectile[i]).checkHit(j))
				{
					player[j]->postTrans(glm::translate(vec3(-1, 0.5, 0)));
					player[j]->setHealth(-1);
					(*projectile[i]).setHit(j);
					if (player[j]->getHealth() < 1)
					{
						Window::removeDrawList((*player[j]).getName());
						player.erase(player.begin() + j);
					}
				}
				//[p]
				//[s]
				else if ((pBox.max[0] <= sBox.max[0] + 1) && (pBox.max[0] >= sBox.max[0]) && (pBox.max[2] <= sBox.max[2]) && (pBox.max[2] >= sBox.max[2]) && !(*projectile[i]).checkHit(j))
				{
					player[j]->postTrans(glm::translate(vec3(0, 0.5, -1)));
					player[j]->setHealth(-1);
					(*projectile[i]).setHit(j);
					if (player[j]->getHealth() < 1)
					{
						Window::removeDrawList((*player[j]).getName());
						player.erase(player.begin() + j);
					}
				}
				//[s]
				//[p]
				else if ((pBox.max[0] <= sBox.max[0] + 1) && (pBox.max[0] >= sBox.max[0]) && (pBox.max[2] <= sBox.max[2] + 1) && (pBox.max[2] >= sBox.max[2]) && !(*projectile[i]).checkHit(j))
				{
					player[j]->postTrans(glm::translate(vec3(0, 0.5, 1)));
					player[j]->setHealth(-1);
					(*projectile[i]).setHit(j);
					if (player[j]->getHealth() < 1)
					{
						Window::removeDrawList((*player[j]).getName());
						player.erase(player.begin() + j);
					}
				}
			}
		}
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
			obj1->clearYVelocity();
			onGround1 = true;
			obj2->clearYVelocity();
			onGround2 = true;
		}
		else{//stair effect
			AABB b1 = obj1->getAABB();
			AABB b2 = obj2->getAABB();
			if (b2.max[1] > b1.min[1] && b2.max[1] - b1.min[1] <= 0.11){
				obj1->preTrans(glm::translate(glm::vec3(0.0f, b2.max[1]-b1.min[1]+0.01f, 0.0f)));
			}
		}
	}
	void addPlayer(Object* p){ player.push_back(p); }
	void addStationary(Object* s){ stationary.push_back(s); }
	void addProjectile(Projectile* p){ projectile.push_back(p); }
	void setGravity(vec3& g){ gravity = g; }
	void resolvePlayerRotation(){
		for (uint i = 0; i < player.size(); i++){
			player[i]->postRotate(glm::rotate(mat4(1.0), player[i]->getPendingRote(), vec3(0, 1, 0)));
			player[i]->setPendingRot(0);
		}
	}
	void resolvePlayerTransition(float t){
		for (uint i = 0; i < player.size(); i++){
			player[i]->addVelocity(gravity*t);
			player[i]->postTrans(glm::translate(player[i]->getVelocity()*t));
		}
		for (uint i = 0; i < projectile.size(); i++){
			projectile[i]->addVelocity(gravity*t);
			projectile[i]->postTrans(glm::translate(projectile[i]->getVelocity()*t));
		}
	}

	void setHMove(int playerID, int m){ player[playerID]->setHMove(m); }
	void cancelHMove(int playerID, int m){ player[playerID]->cancelHMove(m); }
	void setVMove(int playerID, int m){ player[playerID]->setVMove(m); }
	void cancelVMove(int playerID, int m){ player[playerID]->cancelVMove(m); }
	void setPendingRot(int playerID, float f){ player[playerID]->setPendingRot(f); }
	void pushRot(int playerID, float f){ player[playerID]->pushRot(f); }
	void jump(int playerID){ player[playerID]->jump(); }

	void basicAttack(int playerID)
	{
		for (uint j = 1; j < player.size(); j++){
			AABB pBox = player[playerID]->getAABB();
			AABB sBox = player[j]->getAABB();
			vector<int> holder;
			//[p][s]
			if ((pBox.max[2] <= sBox.max[2] + 5) && (pBox.max[2] >= sBox.max[2] - 5)  && pBox.max[0] == sBox.min[0])
			{
				player[j]->postTrans(glm::translate(vec3(1, 0.5, 0)));
				player[j]->setHealth(-1);
				if (player[j]->getHealth() < 1)
					player.erase(player.begin() + j);
			}
			//[s][p]
			else if ((pBox.max[2] <= sBox.max[2] + 5) && (pBox.max[2] >= sBox.max[2] - 5) && pBox.min[0] == sBox.max[0])
			{
				player[j]->postTrans(glm::translate(vec3(-1, 0.5, 0)));
				player[j]->setHealth(-1);
				if (player[j]->getHealth() < 1)
					player.erase(player.begin() + j);
			}
			//[p]
			//[s]
			else if ((pBox.max[0] <= sBox.max[0] + 5) && (pBox.max[0] >= sBox.max[0] - 5) && pBox.min[2] == sBox.max[2])
			{
				player[j]->postTrans(glm::translate(vec3(0, 0.5, -1)));
				player[j]->setHealth(-1);
				if (player[j]->getHealth() < 1)
					player.erase(player.begin() + j);
			}
			//[s]
			//[p]
			else if ((pBox.max[0] <= sBox.max[0] + 5) && (pBox.max[0] >= sBox.max[0] - 5) && pBox.max[2] == sBox.min[2])
			{
				//setVMove(j, -1);
				//holder.push_back(j);
				//holder.push_back(1);
				//holder.push_back(-1);
				//prevAttacked.push_back(holder);
				player[j]->postTrans(glm::translate(vec3(0, 0.5, 1)));
				player[j]->setHealth(-1);
				if (player[j]->getHealth() < 1)
					player.erase(player.begin() + j);
			}
		}

	}

	void projectileAttack(int playerID, Camera * cam)
	{
		mat4 test = cam->getCamM();
		vec4 holder = test*vec4(0, 0, -1, 0); //orientation of camera in object space
		mat4 player1 = player[playerID]->getModelM();
		vec4 playerHolder = player1*vec4(0, 0, 0, 1);

		Projectile* cube6 = new Projectile(player.size());
		cube6->setShader(sdrCtl.getShader("basic_reflect_refract"));

		cube6->setShininess(100);

		cube6->setSpeed(5);
		//cube6->postTrans(glm::translate(vec3(playerHolder[0] -2 + ((holder[0]) / 4), playerHolder[1], playerHolder[2] - (holder[2] / 4))));
		cube6->setModelM(player1*glm::translate(vec3(0, 0, -1)));//get the new cube matrix by translating the player0 matrix forward in player0 object space. This way the new matrix will inherit player0 oriantation 
		cube6->setAABB(AABB(vec3(-0.5, -0.5, -0.5), vec3(0.5, 0.5, 0.5)));
		AABB hold = cube6->getAABB();
		cube6->setStartX(hold.max[0]);
		cube6->setStartY(hold.max[2]);

		//Name and type
		cube6->setType("Cube");
		cube6->setName("Test Cube" + std::to_string(projectile_counter));
		projectile_counter++;
		//Add Cube to the draw list
		Window::addDrawList(cube6);
		projectile.push_back(cube6);
		cube6->setSpeed(50);
		//cube6->setHMove((holder[0] / 4));
		cube6->setVelocity(vec3(holder)*40.0f);// set object space velocity to camera oriantation in object space. Since camera always have the same xz oriantation as the object, xz oriantation wouldnt change when camera rotate.
		//cube6->setVMove(1);  //do this if you want the cube to not have vertical velocity. uncomment the above setVelocity.
		//cout << holder[0] << ' ' << holder[1] << ' ' << holder[2] << ' ' << playerHolder[0] << ' ' << playerHolder[2] << endl;
	}

	void despawnProjectile()
	{
		for (uint i = 0; i < projectile.size(); i++)
		{
			float startX = projectile[i]->getStartX();
			float startY = projectile[i]->getStartY();
			AABB curr = projectile[i]->getAABB();
			int distance = sqrt(pow(curr.max[0] - startX, 2) + pow(curr.max[2] - startY, 2));//Pythagorean Theorem

			//cout << startX << " " << curr.max[0] << " " << curr.max[0] - startX << " " << distance << endl;
			if (distance > 30)
			{
				Window::removeDrawList((*projectile[i]).getName());
				projectile.erase(projectile.begin() + i);
			}
		}
	}

	vector<mat4> getPlayerMats(){
		vector<mat4> m;
		for (uint i = 0; i < player.size(); i++){
			m.push_back(player[i]->getModelM());
		}
		return m;
	}

	void initialize(){


		Cube* cube0 = new Cube();
		cube0->setSpeed(5);
		cube0->postTrans(glm::translate(vec3(0, 0.5, 7)));
		cube0->setAABB(AABB(vec3(-0.5, -0.5, -0.5), vec3(0.5, 0.5, 0.5)));
		cube0->setType("Cube");
		cube0->setName("Test cube0");
		addPlayer(cube0);

		Cube* cube1 = new Cube();
		cube1->setSpeed(5);
		cube1->postTrans(glm::translate(vec3(0, 0.5, 7)));
		cube1->setAABB(AABB(vec3(-0.5, -0.5, -0.5), vec3(0.5, 0.5, 0.5)));
		cube1->setType("Cube");
		cube1->setName("Test cube1");
		addPlayer(cube1);

		Cube* cube2 = new Cube();
		cube2->setSpeed(5);
		cube2->postTrans(glm::translate(vec3(0, 0.5, 7)));
		cube2->setAABB(AABB(vec3(-0.5, -0.5, -0.5), vec3(0.5, 0.5, 0.5)));
		cube2->setType("Cube");
		cube2->setName("Test cube2");
		addPlayer(cube2);

		Cube* cube3 = new Cube();
		cube3->setSpeed(5);
		cube3->postTrans(glm::translate(vec3(0, 0.5, 7)));
		cube3->setAABB(AABB(vec3(-0.5, -0.5, -0.5), vec3(0.5, 0.5, 0.5)));
		cube3->setType("Cube");
		cube3->setName("Test cube3");
		addPlayer(cube3);


		Ground* ground = new Ground();
		ground->loadColorTex("img/moon_tex/moon_COLOR.png", "PNG");
		ground->loadDispTex("img/moon_tex/moon_DISP.png", "PNG");
		ground->loadNormalTex("img/moon_tex/moon_NRM.png", "PNG");
		ground->loadOccTex("img/moon_tex/moon_OCC.png", "PNG");
		ground->loadSpecTex("img/moon_tex/moon_SPEC.png", "PNG");
		ground->setDimensionS(40);
		ground->setDimensionT(40);
		ground->setRow(501);
		ground->setColumn(501);
		ground->setHeight(1 / 1.0);
		ground->generate();
		ground->setType("Ground");
		ground->setName("Ground");
		addStationary(ground);

		//m_pMesh2 = new Mesh();
		//m_pMesh2->LoadMesh("Model/monky_04_27_smooth.dae");
		//m_pMesh2->setShader(sdrCtl.getShader("basic_model"));
		//m_pMesh2->setAdjustM(glm::translate(vec3(0.0, 4.1, 0.0))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0))*glm::scale(vec3(0.2, 0.2, 0.2)));
		//m_pMesh2->setAABB();

		MD5Model* md5 = new MD5Model();
		md5->setSpeed(5);
		md5->setAABB(AABB(vec3(-0.25, 0.0, -0.25), vec3(0.25, 1.5, 0.25)));
		md5->setType("Model");
		md5->setName("Player Model");
		addPlayer(md5);

		//md6 = new MD5Model();
		//md6->LoadModel("Model/fleurOptonl.md5mesh");
		//md6->LoadAnim("Model/fleurOptonl.md5anim");
		//md6->setShader(sdrCtl.getShader("basic_texture"));
		//md6->setShininess(30);
		//md6->setAdjustM(glm::translate(vec3(0.0, 1.7, 0.0))*glm::rotate(mat4(1.0), 180.0f, vec3(0.0, 1, 0))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0))*glm::scale(vec3(0.05, 0.05, 0.05)));
		//md6->setModelM(glm::translate(vec3(1.0, 0.0, 0.0)));
		//md6->setType("Model");
		//md6->setName("Player Model");




		counter = 0;
		projectile_counter = 0;
	}

protected:
	vector<Object*> stationary;
	vector<Object*> player;
	vector<Object*> tower;
	vector<Object*> skillShot;
	vector<Object*> virtualTower;
	vector<Projectile*> projectile;
	vec3 gravity;
	vector<vector<int>> prevAttacked;//first element is playerID, second is axis
	int counter;
	int projectile_counter;
};

