#pragma once
#include "VAO.h"
#include "glslprogram.h"
#include "Structures.h"
#include "Object.h"
#include <array>
#include <vector>
using namespace std;

extern mat4 Projection;
extern mat4 View;

class Quad : public Object
{
public:
	Quad(void){
		generate(-1, 1, -1, 1);
		vao.generate();
		vao.addAttrib(GL_ARRAY_BUFFER, 12 * sizeof(float), &vertex_positions, GL_STATIC_DRAW, 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
		vao.addAttrib(GL_ARRAY_BUFFER, 8 * sizeof(float), &vertex_texCoords, GL_STATIC_DRAW, 1, 2, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
		vao.setDrawMode(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &triangle_indices);
	}
	Quad(float negx, float posx, float negy, float posy){
		generate(negx, posx, negy, posy);
		vao.generate();
		vao.addAttrib(GL_ARRAY_BUFFER, 12 * sizeof(float), &vertex_positions, GL_STATIC_DRAW, 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
		vao.addAttrib(GL_ARRAY_BUFFER, 8 * sizeof(float), &vertex_texCoords, GL_STATIC_DRAW, 1, 2, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
		vao.setDrawMode(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &triangle_indices);
	}
	~Quad(void){}
	void draw(){
		shader->setUniform(uniformLoc[0], TextureUnit);
		shader->use();
		vao.draw();
		glUseProgram(0);
	}
	void draw(mat4& projection, mat4& view){
		shader->setUniform(uniformLoc[0], TextureUnit);
		shader->use();
		vao.draw();
		glUseProgram(0);
	}
	void setShader(GLSLProgram* shader){
		this->shader = shader;
		uniformLoc.push_back(shader->getUniformLoc("texID"));
	}
	void setTextureUnit(int u){ TextureUnit = u; }
	int getTextureUnit(){ return TextureUnit; }

private:
	void generate(float negx, float posx, float negy, float posy){
		float z = 0;
		std::array<float, 12> positions = {
			negx, negy, z,	//bottom left
			negx, posy, z,	//top left
			posx, posy, z,	//top right
			posx, negy, z	//bottom right
		};
		std::array<float, 8> texCoords = {
			0,0,
			0,1,
			1,1,
			1,0
		};
		std::array<int, 6> indices = {
			0, 2, 1,
			0, 3, 2
		};
		vertex_positions = positions;
		vertex_texCoords = texCoords;
		triangle_indices = indices;
	}
	VAO vao;
	GLSLProgram * shader;
	std::array<float, 12> vertex_positions;
	std::array<float, 8> vertex_texCoords;
	std::array<int, 6> triangle_indices;
	int TextureUnit;
	vector<int> uniformLoc;
};
