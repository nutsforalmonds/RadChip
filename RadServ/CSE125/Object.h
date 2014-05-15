#pragma once
#include "VAO.h"
#include "glslprogram.h"
#include "Structures.h"
#include <array>

class Object
{
public:
	Object(void){
		velocity = vec3(0.0);
		modelM = mat4(1.0);
		Rotation = mat4(1.0);
		onGround = true;
		health = 15;
	}
	Object(string n, string t){
		name = n;
		type = t;
		velocity = vec3(0.0);
		modelM = mat4(1.0);
		onGround = true;
		health = 15;
	}
	~Object(){}
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

	void jump(){
		if (onGround){
			velocity[1] = 10;
		}
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

	void setHealth(int i){ health--; }

	void setRotation(mat4 m){ Rotation = m; }
	mat4 getRotation(){ return Rotation; }

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
};