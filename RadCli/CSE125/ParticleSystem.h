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
extern mat4 LightView;
extern mat4 LightProjection;
extern mat4 ScaleBias;

#define NUM_PARTICLES 1000

typedef struct Particle
{
	float theta;
	vec3 shade;
}
Particle;

typedef struct Emitter
{
	Particle particles[NUM_PARTICLES];
	float k;
	vec3 color;
}
Emitter;


class ParticleSystem : public Object
{
public:
	ParticleSystem(GLenum mode){

		awesome_time = 1.5;
		time_Max = 50.0;
		time_Min = 1.5;
		time_Step = 1.0;
		current_loop = 0;
		loopInf = false;
		float myTheta, myPhi;

		for (int i = 0; i<NUM_PARTICLES; i++)
		{
			myTheta = randomFloatBetween(0.0, 360.00);
			myPhi = randomFloatBetween(0.0, 180.00);
			// Assign each particle its theta value (in radians)
			//p_theta[i] = i*(3.14159265359 / 180);
			//emitter.particles[i].theta = i*(3.14159265359 / 180);
			emitter.particles[i].theta = ((((float)i / (float)NUM_PARTICLES)*360.0f)*(3.14159265359 / 180));
			//emitter.particles[i].theta = (myTheta*(3.14159265359 / 180));
			emitter.particles[i].shade.x = randomFloatBetween(-0.5f, 0.5f);
			emitter.particles[i].shade.y = randomFloatBetween(-0.5f, 0.5f);
			emitter.particles[i].shade.z = randomFloatBetween(-0.5f, 0.5f);
		}

		vao.generate();
		vao.addAttrib(GL_ARRAY_BUFFER, sizeof(emitter.particles), &emitter.particles, GL_STATIC_DRAW, 0, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)(offsetof(Particle, theta)));
		vao.addAttrib(GL_ARRAY_BUFFER, sizeof(emitter.particles), &emitter.particles, GL_STATIC_DRAW, 1, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)(offsetof(Particle, shade)));

		//vao.setDrawMode(GL_LINE_STRIP, 0, NUM_PARTICLES);
		//vao.setDrawMode(GL_POINTS, 0, NUM_PARTICLES);
		vao.setDrawMode(mode, 0, NUM_PARTICLES);
	}
	
	~ParticleSystem(void){}
	void draw(){

		if (current_loop < loop_count || loopInf){

			updateTime();

			shader->setUniform(uniformLoc[0], View);
			shader->setUniform(uniformLoc[1], Projection);
			shader->setUniform(uniformLoc[2], getModelM());
			shader->setUniform(uniformLoc[3], emitter.k);
			shader->setUniform(uniformLoc[4], awesome_time / 4);
			shader->setUniform(uniformLoc[5], emitter.color);
			shader->setUniform(uniformLoc[6], p_shade);
			shader->setUniform(uniformLoc[7], 0);
			shader->setUniform(uniformLoc[8], fog->maxDist);
			shader->setUniform(uniformLoc[9], fog->minDist);
			shader->setUniform(uniformLoc[10], fog->color);
			shader->setUniform(uniformLoc[11], fog->visibility);
			shader->setUniform(uniformLoc[12], fog->maxHeight);
			shader->setUniform(uniformLoc[13], fog->minHeight);
			m_Texture->Bind(GL_TEXTURE0);

			/*
			shader->setUniform(uniformLoc[4], Projection*View*getModelM());
			shader->setUniform(uniformLoc[5], material.Kd);
			shader->setUniform(uniformLoc[6], material.Ka);
			shader->setUniform(uniformLoc[7], material.Ks);
			shader->setUniform(uniformLoc[8], material.Shininess);
			shader->setUniform(uniformLoc[9], material.ReflectFactor);
			shader->setUniform(uniformLoc[10], material.Eta);
			shader->setUniform(uniformLoc[11], CubeMapUnit);
			shader->setUniform(uniformLoc[12], color);
			shader->setUniform(uniformLoc[13], shadowTex);
			shader->setUniform(uniformLoc[14], LightView);
			shader->setUniform(uniformLoc[15], LightProjection);
			shader->setUniform(uniformLoc[16], ScaleBias);
			*/
			shader->use();
			vao.draw();
			glUseProgram(0);
		}
	}
	void draw(mat4& projection, mat4& view){
		
		if (current_loop < loop_count || loopInf){

			updateTime();

			shader->setUniform(uniformLoc[0], view);
			shader->setUniform(uniformLoc[1], projection);
			shader->setUniform(uniformLoc[2], getModelM());
			shader->setUniform(uniformLoc[3], emitter.k);
			shader->setUniform(uniformLoc[4], awesome_time / 4);
			shader->setUniform(uniformLoc[5], emitter.color);
			shader->setUniform(uniformLoc[6], p_shade);
			shader->setUniform(uniformLoc[7], 0);
			shader->setUniform(uniformLoc[8], fog->maxDist);
			shader->setUniform(uniformLoc[9], fog->minDist);
			shader->setUniform(uniformLoc[10], fog->color);
			shader->setUniform(uniformLoc[11], fog->visibility);
			shader->setUniform(uniformLoc[12], fog->maxHeight);
			shader->setUniform(uniformLoc[13], fog->minHeight);
			m_Texture->Bind(GL_TEXTURE0);

			shader->use();
			//glLineWidth(time);
			vao.draw();
			glUseProgram(0);
		}
	}
	void setShader(GLSLProgram* shader){
		this->shader = shader;
		uniformLoc.push_back(shader->getUniformLoc("ViewMatrix"));
		uniformLoc.push_back(shader->getUniformLoc("ProjectionMatrix"));
		uniformLoc.push_back(shader->getUniformLoc("ModelMatrix"));
		uniformLoc.push_back(shader->getUniformLoc("uK"));
		uniformLoc.push_back(shader->getUniformLoc("uTime"));
		uniformLoc.push_back(shader->getUniformLoc("uColor"));
		uniformLoc.push_back(shader->getUniformLoc("aShade"));
		uniformLoc.push_back(shader->getUniformLoc("uTexture"));
		uniformLoc.push_back(shader->getUniformLoc("fog.maxDist"));
		uniformLoc.push_back(shader->getUniformLoc("fog.minDist"));
		uniformLoc.push_back(shader->getUniformLoc("fog.color"));
		uniformLoc.push_back(shader->getUniformLoc("fog.visibility"));
		uniformLoc.push_back(shader->getUniformLoc("fog.maxHeight"));
		uniformLoc.push_back(shader->getUniformLoc("fog.minHeight"));
		
	}
	
	void setColor(vec3 c){ emitter.color = c; }
	void setShade(vec3 s){ p_shade = s; }

	void setTexture(GLenum TextureTarget, const char* FileName, const char* FileType){
		m_Texture = new Texture(TextureTarget, FileName, FileType);
		m_Texture->Load();
	}

	void setK(float input){ emitter.k = input; }
	float getK(float input){ return emitter.k; }
	
	void setTime_Step(float s){ time_Step = s; }
	float getTime_Step(){ return awesome_time; }

	void setTime_Max(float ma){ time_Max = ma; }
	float getTime_Max(){ return time_Max; }

	void setTime_Min(float mi){ time_Min = mi; }
	float getTime_Min(){ return time_Min; }
	
	void setTime(float t){ awesome_time = t; }
	float getTime(){ return awesome_time; }
	
	void setFog(Fog& f){ fog = &f; }

	void setLoopCount(int l){ loop_count = l; }
	int getLoopCount(){ return loop_count; }

	void setCurrentLoopCount(int l){ current_loop = l; }
	int getCurrentLoopCount(){ return current_loop; }

	void setLoopInf(bool b){ loopInf = b; }
	bool getLoopInf(){ return loopInf; }

	void StartLoop(){
		current_loop = 0;
		awesome_time = time_Min;
	}

private:
	void generate(){
	
	}
	float randomFloatBetween(float min, float max)
	{
		float range = max - min;
		return (((float)(rand() % ((unsigned)RAND_MAX + 1)) / RAND_MAX) * range) + min;
	}

	void updateTime(){
		awesome_time += time_Step;
		if (awesome_time > time_Max){
			current_loop++;
			if (current_loop < loop_count){
				awesome_time = time_Min;
			}
			else if (loopInf){
				current_loop = 0;
				awesome_time = time_Min;
			}
		}
	}

	VAO vao;
	GLSLProgram * shader;
	Emitter emitter;
	//vec3 e_color;
	vec3 p_shade;
	vector<int> uniformLoc;
	std::vector<Texture*> m_Textures;
	Texture* m_Texture;
	float awesome_time;

	float time_Max;
	float time_Min;
	float time_Step;


	Fog* fog;

	bool start_loop;
	int loop_count;
	int current_loop;
	bool loopInf;

};