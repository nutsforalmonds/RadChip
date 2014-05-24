#pragma once
#include "VAO.h"
#include "glslprogram.h"
#include <array>
#include "Structures.h"

extern mat4 Projection;
extern mat4 View;

class SkyBox : public Object
{
public:
	SkyBox(float negx, float posx, float negy, float posy, float negz, float posz){
		generate(negx, posx, negy, posy, negz, posz);
		vao.generate();
		vao.addAttrib(GL_ARRAY_BUFFER, 24 * sizeof(float), &skybox_positions, GL_STATIC_DRAW, 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
		vao.setDrawMode(GL_TRIANGLES, 36, GL_UNSIGNED_INT, &skybox_indices);
	}
	~SkyBox(void){}
	void setShader(GLSLProgram* shader){
		this->shader = shader;
		uniformLoc.push_back(shader->getUniformLoc("ViewMatrix"));
		uniformLoc.push_back(shader->getUniformLoc("ProjectionMatrix"));
		uniformLoc.push_back(shader->getUniformLoc("CubeMapTex"));
		uniformLoc.push_back(shader->getUniformLoc("fog.maxDist"));
		uniformLoc.push_back(shader->getUniformLoc("fog.minDist"));
		uniformLoc.push_back(shader->getUniformLoc("fog.color"));
		uniformLoc.push_back(shader->getUniformLoc("fog.visibility"));
		uniformLoc.push_back(shader->getUniformLoc("fog.maxHeight"));
		uniformLoc.push_back(shader->getUniformLoc("fog.minHeight"));
		//uniformLoc.push_back(shader->getUniformLoc(""));
	}
	void setTexUnit(int u){ texUnit = u; }
	int getTexUnit(){ return texUnit; }
	void draw(){
		shader->setUniform(uniformLoc[0], View);
		shader->setUniform(uniformLoc[1], Projection);
		shader->setUniform(uniformLoc[2], texUnit);
		shader->setUniform(uniformLoc[3], fog->maxDist);
		shader->setUniform(uniformLoc[4], fog->minDist);
		shader->setUniform(uniformLoc[5], fog->color);
		shader->setUniform(uniformLoc[6], fog->visibility);
		shader->setUniform(uniformLoc[7], fog->maxHeight);
		shader->setUniform(uniformLoc[8], fog->minHeight);
		//shader->setUniform(uniformLoc[], );
		shader->use();
		vao.draw();
		glUseProgram(0);
	}
	void setFog(Fog& f){ this->fog = &f; }

private:
	void generate(float negx, float posx, float negy, float posy, float negz, float posz){
		std::array<float, 24> positions = {
			negx, posy, posz,
			negx, negy, posz,
			posx, negy, posz,
			posx, posy, posz,
			negx, posy, negz,
			negx, negy, negz,
			posx, negy, negz,
			posx, posy, negz };
		std::array<int, 36> indices = {
			1, 0, 3,
			1, 3, 2,
			4, 5, 7,
			7, 5, 6,
			3, 7, 6,
			3, 6, 2,
			0, 1, 5,
			0, 5, 4,
			0, 7, 3,
			0, 4, 7,
			1, 2, 6,
			1, 6, 5
		};
		skybox_positions = positions;
		skybox_indices = indices;
	}
	VAO vao;
	GLSLProgram * shader;
	std::array<float, 24> skybox_positions;
	std::array<int, 36> skybox_indices;
	int texUnit;
	vector<int> uniformLoc;
	Fog* fog;
};

