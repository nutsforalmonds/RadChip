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
		QueryPerformanceFrequency(&freq);
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
		num_column = other.num_column;
		num_row = other.num_row;
		column = other.column;
		row = other.row;
		duration = other.duration;
		current = other.current;
		freq = other.freq;
		type = other.type;
		fog = other.fog;
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
		shader->setUniform(uniformLoc[7], column);
		shader->setUniform(uniformLoc[8], row);
		shader->setUniform(uniformLoc[9], num_column);
		shader->setUniform(uniformLoc[10], num_row);
		shader->setUniform(uniformLoc[11], fog->maxDist);
		shader->setUniform(uniformLoc[12], fog->minDist);
		shader->setUniform(uniformLoc[13], fog->color);
		shader->setUniform(uniformLoc[14], fog->visibility);
		shader->setUniform(uniformLoc[15], fog->maxHeight);
		shader->setUniform(uniformLoc[16], fog->minHeight);
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
		uniformLoc.push_back(shader->getUniformLoc("column"));
		uniformLoc.push_back(shader->getUniformLoc("row"));
		uniformLoc.push_back(shader->getUniformLoc("num_column"));
		uniformLoc.push_back(shader->getUniformLoc("num_row"));
		uniformLoc.push_back(shader->getUniformLoc("fog.maxDist"));
		uniformLoc.push_back(shader->getUniformLoc("fog.minDist"));
		uniformLoc.push_back(shader->getUniformLoc("fog.color"));
		uniformLoc.push_back(shader->getUniformLoc("fog.visibility"));
		uniformLoc.push_back(shader->getUniformLoc("fog.maxHeight"));
		uniformLoc.push_back(shader->getUniformLoc("fog.minHeight"));
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
	void setStartTime(LARGE_INTEGER& t){ start_time = t; }
	LARGE_INTEGER getStartTime(){ return start_time; }
	void setDuration(double d){ duration = d; }
	double getDuration(){ return duration; }
	void setNumColumn(int c){ num_column = c; }
	int getNumColumn(){ return num_column; }
	void setNumRow(int r){ num_row = r; }
	int getNumRow(){ return num_row; }
	void setColumn(int c){ column = c; }
	int getColumn(){ return column; }
	void setRow(int r){ row = r; }
	int getRow(){ return row; }

	bool update(){
		QueryPerformanceCounter(&current);
		double anim_time = ((double)current.QuadPart - (double)start_time.QuadPart) / (double)freq.QuadPart;
		if (anim_time > duration)
			return false;

		double seg_time = duration / (num_column*num_row);
		int block_ID = (int)floor(anim_time/seg_time);
		row = block_ID / num_column;
		column = block_ID % num_column;
		return true;
	}
	void setType(int t){ type = t; }
	int getType(){ return type; }

	void setFog(Fog& f){ fog = &f; }

private:
	GLuint m_VB;
	Texture* m_pTexture;
	GLuint m_vao;
	GLSLProgram* shader;
	vector<int> uniformLoc;
	float width;
	float height;
	vec3 Position=vec3(0,0,0);
	LARGE_INTEGER start_time;
	int num_column, num_row;
	int column=0, row=0;
	double duration;
	LARGE_INTEGER current, freq;
	int type;//0: one time 1: continuous
	Fog* fog;
};

#endif	/* PARTICLE_ANIMATED_H */