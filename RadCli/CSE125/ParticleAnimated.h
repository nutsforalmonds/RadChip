#ifndef PARTICLE_ANIMATED_H
#define	PARTICLE_ANIMATED_H

#include <string>
#include "ShaderController.h"
#include "Texture.h"
#include "Object.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "ogldev_util.h"
#include "billboard_list.h"
using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::mat3;

#define NUM_ROWS 10
#define NUM_COLUMNS 10

#define COLOR_TEXTURE_UNIT GL_TEXTURE0
#define SHADOW_TEXTURE_UNIT GL_TEXTURE1
#define NORMAL_TEXTURE_UNIT GL_TEXTURE2

extern mat4 Projection;
extern mat4 View;

class ParticleAnimated : public Object
{
public:
	ParticleAnimated(){
		m_pTexture = NULL;
		m_VB = INVALID_OGL_VALUE;
		setModelM(mat4(1.0));
	}
	~ParticleAnimated(){//commented out because only mother of animated particles needs to be deleted
		//SAFE_DELETE(m_pTexture);

		//if (m_VB != INVALID_OGL_VALUE)
		//{
		//	glDeleteBuffers(1, &m_VB);
		//}
	}
	ParticleAnimated(const ParticleAnimated& other){
		*this = other;
	}

	ParticleAnimated& operator = (const ParticleAnimated& other){
		m_VB = other.m_VB;
		m_pTexture = other.m_pTexture;
		m_vao = other.m_vao;
		shader = other.shader;
		uniformLoc = other.uniformLoc;
		width = other.width;
		height = other.height;
		Position = other.Position;
		return *this;
	}

	bool Init(const std::string& TexFilename, const char* FileType){
		m_pTexture = new Texture(GL_TEXTURE_2D, TexFilename.c_str(), FileType);

		if (!m_pTexture->Load()) {
			return false;
		}
		return true;
	}

	void draw(){
		shader->setUniform(uniformLoc[0], Projection);
		shader->setUniform(uniformLoc[1], View);
		shader->setUniform(uniformLoc[2], vec3((glm::inverse(View)*vec4(0, 0, 0, 1))));
		shader->setUniform(uniformLoc[3], width);
		shader->setUniform(uniformLoc[4], height);
		shader->setUniform(uniformLoc[5], getModelM());
		shader->setUniform(uniformLoc[6], 0);
		shader->use();
		m_pTexture->Bind(COLOR_TEXTURE_UNIT);

		glBindVertexArray(m_vao);
		glDrawArrays(GL_POINTS, 0, 1);
		glUseProgram(0);
	}

	void setShader(GLSLProgram* shader){
		this->shader = shader;
		uniformLoc.push_back(shader->getUniformLoc("ProjectionMatrix"));
		uniformLoc.push_back(shader->getUniformLoc("ViewMatrix"));
		uniformLoc.push_back(shader->getUniformLoc("gCameraPos"));
		uniformLoc.push_back(shader->getUniformLoc("width"));
		uniformLoc.push_back(shader->getUniformLoc("height"));
		uniformLoc.push_back(shader->getUniformLoc("ModelMatrix"));
		uniformLoc.push_back(shader->getUniformLoc("texUnit"));
	}

	void Bind(){
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);
		glEnableVertexAttribArray(0);

		glGenBuffers(1, &m_VB);
		glBindBuffer(GL_ARRAY_BUFFER, m_VB);
		glBufferData(GL_ARRAY_BUFFER, 3*sizeof(float), &Position, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}
	void setPosition(vec3& p){
		Position = p;
	}
	void setWidth(float f){
		width = f;
	}
	void setHeight(float f){
		height = f;
	}

private:
	GLuint m_VB;
	Texture* m_pTexture;
	GLuint m_vao;
	GLSLProgram* shader;
	vector<int> uniformLoc;
	float width;
	float height;
	vec3 Position=vec3(0,0,0);
};

#endif	/* PARTICLE_ANIMATED_H */