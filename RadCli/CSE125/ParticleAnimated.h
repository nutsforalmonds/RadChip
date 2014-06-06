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
		transparency=other.transparency;
		sample_x = other.sample_x;
		sample_y = other.sample_y;
		x_dist = other.x_dist;
		y_dist = other.y_dist;
		start_frame = other.start_frame;
		end_frame = other.end_frame;
		reverse = other.reverse;
		delay = other.delay;
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
		if (row < 0)
			return;
		shader->setUniform(uniformLoc[0], Projection);
		shader->setUniform(uniformLoc[1], View);
		shader->setUniform(uniformLoc[2], vec3((glm::inverse(View)*vec4(0, 0, 0, 1))));
		shader->setUniform(uniformLoc[3], width);
		shader->setUniform(uniformLoc[4], height);
		if (follow){
			shader->setUniform(uniformLoc[5], followee->getModelM()*glm::translate(vertTrans + displace*glm::normalize(vec3(glm::inverse(*view)*vec4(0, 0, 0, 1) - followee->getModelM()*vec4(0, 0, 0, 1)))));
		}
		else{
			shader->setUniform(uniformLoc[5], getModelM());
		}
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
		shader->setUniform(uniformLoc[17], transparency);
		shader->setUniform(uniformLoc[18], sample_x);
		shader->setUniform(uniformLoc[19], sample_y);
		shader->setUniform(uniformLoc[20], x_dist);
		shader->setUniform(uniformLoc[21], y_dist);
		shader->setUniform(uniformLoc[22], blur_strength);
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
		uniformLoc.push_back(shader->getUniformLoc("transparency"));
		uniformLoc.push_back(shader->getUniformLoc("sample_x"));
		uniformLoc.push_back(shader->getUniformLoc("sample_y"));
		uniformLoc.push_back(shader->getUniformLoc("x_dist"));
		uniformLoc.push_back(shader->getUniformLoc("y_dist"));
		uniformLoc.push_back(shader->getUniformLoc("blur_strength"));
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
	void setPosition(vec3& p){ Position = p; }
	vec3 getPosition(){ return Position; }
	void setWidth(float f){ width = f; }
	void setHeight(float f){ height = f; }
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

	void setReverse(bool re){ reverse = re; }
	void setValidFrame(int start_frame, int end_frame){ this->start_frame = start_frame; this->end_frame = end_frame; }

	bool update(){
		QueryPerformanceCounter(&current);
		double anim_time = ((double)current.QuadPart - (double)start_time.QuadPart) / (double)freq.QuadPart - delay;
		if (anim_time > duration){
			return false;
		}
		if (anim_time < 0){
			row = column = -1;
			return true;
		}

		int block_ID;
		double seg_time = duration / (end_frame-start_frame+1);
		if (reverse){
			block_ID = end_frame - (int)floor(anim_time / seg_time);
		}
		else{
			block_ID = (int)floor(anim_time / seg_time) + start_frame;
		}
		row = block_ID / num_column;
		column = block_ID % num_column;
		return true;
	}
	void setType(int t){ type = t; }
	int getType(){ return type; }

	void setFog(Fog& f){ fog = &f; }
	void setTransparency(float t){ transparency = t; }
	void setSampleCount(int x, int y){ sample_x = x; sample_y = y; }
	void setSampleDist(float x, float y){ x_dist = x; y_dist = y; }
	void setBlurStrength(float s){ blur_strength = s; }
	void setDelay(double delay){ this->delay = delay; }
	void setFollow(Object* followee, vec3 vertTrans, float displace, mat4* view ){
		follow = true;
		this->followee = followee;
		this->vertTrans = vertTrans;
		this->displace = displace;
		this->view = view;
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
	int num_column, num_row;
	int column=0, row=0;
	double duration;
	LARGE_INTEGER current, freq, start_time;
	int type;//0: one time 1: continuous
	Fog* fog;
	float transparency=1.0;
	//glow
	int sample_x=0, sample_y=0;
	float x_dist = 0, y_dist = 0;
	int start_frame, end_frame;
	bool reverse = false;
	float blur_strength = 1;
	double delay=0;
	bool follow = false;
	Object* followee;
	vec3 vertTrans;
	float displace;
	mat4* view;
};

#endif	/* PARTICLE_ANIMATED_H */