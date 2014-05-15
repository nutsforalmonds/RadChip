#ifndef CLIENTSTATE_H
#define	CLIENTSTATE_H

#include "Object.h"

#include <string>
#include "ShaderController.h"
#include "Texture.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::mat3;

class ClientState
{
public:
	ClientState(){
		State = 0;
	}
	~ClientState();

	int getState(){
		return State;
	}

	void setState(int NewState){
		State = NewState;
	}
	

private:
	int State;

	std::vector<Object*> draw_list;
	std::vector<Object*> player_list;
	std::vector<Object*> stationary_list;
};


#endif	/* CLIENTSTATE_H */