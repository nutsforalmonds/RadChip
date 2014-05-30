#pragma once
#include "Structures.h"
#include "Cube.h"

class Camera: public Object
{
public:
	Camera(){ pendingRot = 0; prerot = mat4(1.0); postrot = mat4(1.0); pretrans = mat4(1.0); posttrans = mat4(1.0); }
	~Camera(){}

	void attach(Object* obj){ this->obj = obj; }
	void setCamM(mat4& m){ CamM = m; }
	mat4 getCamM(){ return pretrans*prerot*CamM*posttrans*postrot; } // camera space to cube space
	void preRotate(mat4& rot){ prerot=rot*prerot; }
	void postRotate(mat4& rot){ postrot = postrot*rot; }
	void preTrans(mat4& trans){ pretrans=trans*pretrans; }
	void postTrans(mat4& trans){ posttrans=posttrans*trans; }
	void setPreRot(mat4& m){ prerot = m; }
	void setPostRot(mat4& m){ postrot = m; }
	void setPreTrans(mat4& m){ pretrans = m; }
	void setPostTrans(mat4& m){ posttrans = m; }
	void setPendingRot(float f){ pendingRot = f; }
	void pushRot(float f){ 
		pendingRot += f; 
		if (pendingRot > 90){
			pendingRot = 90;
		}
		if (pendingRot < -90){
			pendingRot = -90;
		}
	}
	float getPendingRote(){ return pendingRot; }

	void init(float right, float up, float back, float bottom){
		this->right = right;
		this->up = up;
		this->back = back;
		this->bottom = bottom;
		angle_limit = asin(bottom / back)/M_PI*180.0;
	}

	void update(){
		if (CamMode == 0){
			setPreRot(glm::rotate(mat4(1.0), pendingRot, vec3(1, 0, 0)));

			if (pendingRot > angle_limit){
				setPostTrans(glm::translate(vec3(0, 0, bottom / sin(pendingRot / 180.0*M_PI))));
				setPreTrans(glm::translate(vec3(right, up, 0)));
			}
			else{
				setPostTrans(glm::translate(vec3(0, 0, back)));
				setPreTrans(glm::translate(vec3(right, up, 0)));
			}
		}
		else if (CamMode == 1){
			setPreRot(mat4(1.0));
			setPostTrans(mat4(1.0));
			setPreTrans(mat4(1.0));
		}
	}

	mat4 getViewM(){ return glm::inverse(pretrans*prerot*CamM*posttrans*postrot)*glm::inverse(obj->getModelM()); } // world space to camera space

	mat4 getCamToWorldM(){ return obj->getModelM()*(pretrans*prerot*CamM*posttrans*postrot); }// camera space to world space

	Object* getObjAppended(){ return obj; }

	void setCamMode(int i){ CamMode = i; }

private:
	mat4 prerot,postrot;
	mat4 pretrans, posttrans;
	mat4 CamM;
	Object* obj;
	float pendingRot;
	float up;
	float back;
	float bottom;
	float angle_limit;
	float right;
	int CamMode;//0: normal 1: death view
};

