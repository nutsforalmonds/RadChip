#pragma once
#include "Structures.h"
#include "Cube.h"

class Camera: public Object
{
public:
	Camera(){ pendingRot = 0; prerot = mat4(1.0); postrot = mat4(1.0); }
	~Camera(){}

	void attach(Object* obj){ this->obj = obj; }
	void setCamM(mat4 m){ CamM = m; }
	mat4 getCamM(){ return prerot*CamM*postrot; } // camera space to cube space
	void preRotate(mat4 rot){ prerot=rot*prerot; }
	void postRotate(mat4 rot){ postrot = postrot*rot; }
	void preTrans(mat4 trans){ CamM=trans*CamM; }
	void postTrans(mat4 trans){ CamM=CamM*trans; }
	void setPreRot(mat4 m){ prerot = m; }
	void setPostRot(mat4 m){ postrot = m; }

	void setPendingRot(float f){ pendingRot = f; }
	void pushRot(float f){ pendingRot += f; }
	float getPendingRote(){ return pendingRot; }

	mat4 getViewM(){ return glm::inverse(prerot*CamM*postrot)*glm::inverse(obj->getModelM()); } // world space to camera space

	mat4 getCamToWorldM(){ return obj->getModelM()*(prerot*CamM*postrot); }// camera space to world space

	Object* getObjAppended(){ return obj; }

private:
	mat4 prerot,postrot;
	mat4 CamM;
	Object* obj;
	float pendingRot;
};

