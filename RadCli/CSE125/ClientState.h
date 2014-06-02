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
		switch(State){
			case 0:
				glutSetCursor(GLUT_CURSOR_CROSSHAIR);
				break;
			case 1:
				glutSetCursor(GLUT_CURSOR_NONE);
				break;
			case 2:
				glutSetCursor(GLUT_CURSOR_CROSSHAIR);
				break;
			case 3:
				glutSetCursor(GLUT_CURSOR_DESTROY);
				break;
			case 4:
				glutSetCursor(GLUT_CURSOR_CROSSHAIR);
				break;
			case 5:
				glutSetCursor(GLUT_CURSOR_CROSSHAIR);
				break;
			default:
				break;
		}
	}
	

private:
	int State;

	std::vector<Object*> draw_list;
	std::vector<Object*> player_list;
	std::vector<Object*> stationary_list;
};


#endif	/* CLIENTSTATE_H */