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

#define NUM_PARTICLES 360

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
	ParticleSystem(void){

		for (int i = 0; i<NUM_PARTICLES; i++)
		{
			// Assign each particle its theta value (in radians)
			//p_theta[i] = i*(3.14159265359 / 180);
			emitter.particles[i].theta = i*(3.14159265359 / 180);
			emitter.particles[i].shade.x = randomFloatBetween(-0.5f, 0.5f);
			emitter.particles[i].shade.y = randomFloatBetween(-0.5f, 0.5f);
			emitter.particles[i].shade.z = randomFloatBetween(-0.5f, 0.5f);
		}

		vao.generate();
		vao.addAttrib(GL_ARRAY_BUFFER, sizeof(emitter.particles), &emitter.particles, GL_STATIC_DRAW, 0, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)(offsetof(Particle, theta)));
		vao.addAttrib(GL_ARRAY_BUFFER, sizeof(emitter.particles), &emitter.particles, GL_STATIC_DRAW, 1, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)(offsetof(Particle, shade)));

		//vao.setDrawMode(GL_LINE_STRIP, 0, NUM_PARTICLES);
		vao.setDrawMode(GL_POINTS, 0, NUM_PARTICLES);
	}
	
	~ParticleSystem(void){}

	void draw(float time){

		shader->setUniform(uniformLoc[0], View);
		shader->setUniform(uniformLoc[1], Projection);
		shader->setUniform(uniformLoc[2], getModelM());
		shader->setUniform(uniformLoc[3], emitter.k);
		shader->setUniform(uniformLoc[4], time / 4);
		shader->setUniform(uniformLoc[5], emitter.color);
		shader->setUniform(uniformLoc[6], p_shade);
		shader->setUniform(uniformLoc[7], 0);
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
	void draw(mat4& projection, mat4& view, float time){
		
		shader->setUniform(uniformLoc[0], view);
		shader->setUniform(uniformLoc[1], projection);
		shader->setUniform(uniformLoc[2], getModelM());
		shader->setUniform(uniformLoc[3], emitter.k);
		shader->setUniform(uniformLoc[4], time/4);
		shader->setUniform(uniformLoc[5], emitter.color);
		shader->setUniform(uniformLoc[6], p_shade);
		shader->setUniform(uniformLoc[7], 0);
		m_Texture->Bind(GL_TEXTURE0);
		
		shader->use();
		//glLineWidth(time);
		vao.draw();
		glUseProgram(0);
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
		
	}
	
	void setColor(vec3 c){ emitter.color = c; }
	void setShade(vec3 s){ p_shade = s; }

	void setTexture(GLenum TextureTarget, const char* FileName, const char* FileType){
		m_Texture = new Texture(TextureTarget, FileName, FileType);
		m_Texture->Load();
	}

	void setK(float input){ emitter.k = input; }
	float getK(float input){ return emitter.k; }
	
private:
	void generate(){
	
	}
	float randomFloatBetween(float min, float max)
	{
		float range = max - min;
		return (((float)(rand() % ((unsigned)RAND_MAX + 1)) / RAND_MAX) * range) + min;
	}

	VAO vao;
	GLSLProgram * shader;
	Emitter emitter;
	//vec3 e_color;
	vec3 p_shade;
	vector<int> uniformLoc;
	std::vector<Texture*> m_Textures;
	Texture* m_Texture;
};