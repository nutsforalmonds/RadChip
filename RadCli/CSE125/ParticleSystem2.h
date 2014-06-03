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

#define NUM_PARTICLES2 1000

typedef struct Particle2
{
	float       pID;
	float       pID2;
	float       pRadiusOffset;
	float       pVelocityOffset;
	float       pDecayOffset;
	float       pSizeOffset;
	vec3		pColorOffset;
}
Particle2;

typedef struct Emitter2
{
	Particle2    eParticles[NUM_PARTICLES2];
	float       eRadius;
	float       eVelocity;
	float       eDecay;
	float       eSizeStart;
	float       eSizeEnd;
	vec3		eColorStart;
	vec3		eColorEnd;
	vec3		ePosition;
}
Emitter2;


class ParticleSystem2 : public Object
{
public:
	ParticleSystem2(void){

		gravity = vec2(0.0f, 0.0f);
		life = 0.0f;
		//time = 0.0f;

		// Offset bounds
		float oRadius = 0.25f;      // 0.0 = circle; 1.0 = ring
		float oVelocity = 0.50f;    // Speed
		float oDecay = 0.25f;       // Time
		float oSize = 8.00f;        // Pixels
		float oColor = 0.25f;       // 0.5 = 50% shade offset

		awesome_time = 0.0;
		time_Max = 40.0;
		time_Min = 0.0;
		time_Step = 0.5;
		current_loop = 0;
		loopInf = false;
		float myTheta, myPhi;

		// Load Particles
		for (int i = 0; i<NUM_PARTICLES2; i++)
		{
			myTheta = randomFloatBetween(0.0, 360.00);
			myPhi = randomFloatBetween(0.0, 180.00);
			myEmitter.eParticles[i].pID = (myTheta*(3.14159265359 / 180));
			myEmitter.eParticles[i].pID2 = (myPhi*(3.14159265359 / 180));
			// Assign a unique ID to each particle, between 0 and 360 (in radians)
			//myEmitter.eParticles[i].pID = ((((float)i/(float)NUM_PARTICLES2)*360.0f)*(3.14159265359 / 180));
			//myEmitter.eParticles[i].pID2 = ((((float)i / (float)NUM_PARTICLES2)*360.0f)*(3.14159265359 / 180));
			// Assign random offsets within bounds
			myEmitter.eParticles[i].pRadiusOffset = oRadius + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0 - oRadius)));
			myEmitter.eParticles[i].pVelocityOffset = (-oVelocity) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (oVelocity - (-oVelocity))));
			myEmitter.eParticles[i].pDecayOffset = (-oDecay) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / ((oDecay) - (-oDecay))));
			myEmitter.eParticles[i].pSizeOffset = (-oSize) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / ((oSize) - (-oSize))));
			float r = (-oColor) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / ((oColor)-(-oColor))));
			float g = (-oColor) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / ((oColor)-(-oColor))));
			float b = (-oColor) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / ((oColor)-(-oColor))));
			myEmitter.eParticles[i].pColorOffset = vec3(r, g, b);
		}

		// Load Properties
		myEmitter.eRadius = 3.75f;							// Blast radius
		myEmitter.eVelocity = 3.00f;                        // Explosion velocity
		myEmitter.eDecay = 4.00f;                           // Explosion decay
		myEmitter.eSizeStart = 32.00f;                      // Fragment start size
		myEmitter.eSizeEnd = 8.00f;                         // Fragment end size
		myEmitter.eColorStart = vec3(1.00f, 0.50f, 0.00f);  // Fragment start color
		myEmitter.eColorEnd = vec3(0.25f, 0.00f, 0.00f);    // Fragment end color
		myEmitter.ePosition = vec3(0.00f, 0.00f, 0.00f);    // Emitter position

		// Set global factors
		float growth = myEmitter.eRadius / myEmitter.eVelocity;       // Growth time
		life = growth + myEmitter.eDecay + oDecay;                    // Simulation lifetime
	
		float drag = 10.00f;                                   // Drag (air resistance)
		gravity = vec2(0.00f, -9.81f*(1.0f / drag));           // World gravity

		vao.generate();
		vao.addAttrib(GL_ARRAY_BUFFER, sizeof(myEmitter.eParticles), &myEmitter.eParticles, GL_STATIC_DRAW, 0, 1, GL_FLOAT, GL_FALSE, sizeof(Particle2), (void*)(offsetof(Particle2, pID)));
		vao.addAttrib(GL_ARRAY_BUFFER, sizeof(myEmitter.eParticles), &myEmitter.eParticles, GL_STATIC_DRAW, 1, 1, GL_FLOAT, GL_FALSE, sizeof(Particle2), (void*)(offsetof(Particle2, pID2)));
		vao.addAttrib(GL_ARRAY_BUFFER, sizeof(myEmitter.eParticles), &myEmitter.eParticles, GL_STATIC_DRAW, 2, 1, GL_FLOAT, GL_FALSE, sizeof(Particle2), (void*)(offsetof(Particle2, pRadiusOffset)));
		vao.addAttrib(GL_ARRAY_BUFFER, sizeof(myEmitter.eParticles), &myEmitter.eParticles, GL_STATIC_DRAW, 3, 1, GL_FLOAT, GL_FALSE, sizeof(Particle2), (void*)(offsetof(Particle2, pVelocityOffset)));
		vao.addAttrib(GL_ARRAY_BUFFER, sizeof(myEmitter.eParticles), &myEmitter.eParticles, GL_STATIC_DRAW, 4, 1, GL_FLOAT, GL_FALSE, sizeof(Particle2), (void*)(offsetof(Particle2, pDecayOffset)));
		vao.addAttrib(GL_ARRAY_BUFFER, sizeof(myEmitter.eParticles), &myEmitter.eParticles, GL_STATIC_DRAW, 5, 1, GL_FLOAT, GL_FALSE, sizeof(Particle2), (void*)(offsetof(Particle2, pSizeOffset)));
		vao.addAttrib(GL_ARRAY_BUFFER, sizeof(myEmitter.eParticles), &myEmitter.eParticles, GL_STATIC_DRAW, 6, 3, GL_FLOAT, GL_FALSE, sizeof(Particle2), (void*)(offsetof(Particle2, pColorOffset)));

		//vao.setDrawMode(GL_LINE_STRIP, 0, NUM_PARTICLES2);
		vao.setDrawMode(GL_POINTS, 0, NUM_PARTICLES2);
	}

	ParticleSystem2(float oRadius, float oVelocity, float oDecay, float oSize, float oColor, float theta_min, float theta_max, float phi_min, float phi_max, float drag){

		gravity = vec2(0.0f, 0.0f);
		life = 0.0f;
		//time = 0.0f;

		// Offset bounds
		//float oRadius = 0.25f;      // 0.0 = circle; 1.0 = ring
		//float oVelocity = 0.50f;    // Speed
		//float oDecay = 0.25f;       // Time
		//float oSize = 8.00f;        // Pixels
		//float oColor = 0.25f;       // 0.5 = 50% shade offset

		awesome_time = 0.0;
		time_Max = 40.0;
		time_Min = 0.0;
		time_Step = 0.5;
		current_loop = 0;
		loopInf = false;
		float myTheta, myPhi;

		// Load Particles
		for (int i = 0; i<NUM_PARTICLES2; i++)
		{
			myTheta = randomFloatBetween(theta_min, theta_max);
			myPhi = randomFloatBetween(phi_min, phi_max);
			myEmitter.eParticles[i].pID = (myTheta*(3.14159265359 / 180));
			myEmitter.eParticles[i].pID2 = (myPhi*(3.14159265359 / 180));
			// Assign a unique ID to each particle, between 0 and 360 (in radians)
			//myEmitter.eParticles[i].pID = ((((float)i/(float)NUM_PARTICLES2)*360.0f)*(3.14159265359 / 180));
			//myEmitter.eParticles[i].pID2 = ((((float)i / (float)NUM_PARTICLES2)*360.0f)*(3.14159265359 / 180));
			// Assign random offsets within bounds
			myEmitter.eParticles[i].pRadiusOffset = oRadius + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0 - oRadius)));
			myEmitter.eParticles[i].pVelocityOffset = (-oVelocity) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (oVelocity - (-oVelocity))));
			myEmitter.eParticles[i].pDecayOffset = (-oDecay) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / ((oDecay)-(-oDecay))));
			myEmitter.eParticles[i].pSizeOffset = (-oSize) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / ((oSize)-(-oSize))));
			float r = (-oColor) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / ((oColor)-(-oColor))));
			float g = (-oColor) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / ((oColor)-(-oColor))));
			float b = (-oColor) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / ((oColor)-(-oColor))));
			myEmitter.eParticles[i].pColorOffset = vec3(r, g, b);
		}

		// Load Properties
		myEmitter.eRadius = 3.75f;							// Blast radius
		myEmitter.eVelocity = 3.00f;                        // Explosion velocity
		myEmitter.eDecay = 4.00f;                           // Explosion decay
		myEmitter.eSizeStart = 32.00f;                      // Fragment start size
		myEmitter.eSizeEnd = 8.00f;                         // Fragment end size
		myEmitter.eColorStart = vec3(1.00f, 0.50f, 0.00f);  // Fragment start color
		myEmitter.eColorEnd = vec3(0.25f, 0.00f, 0.00f);    // Fragment end color
		myEmitter.ePosition = vec3(0.00f, 0.00f, 0.00f);    // Emitter position

		// Set global factors
		float growth = myEmitter.eRadius / myEmitter.eVelocity;       // Growth time
		life = growth + myEmitter.eDecay + oDecay;                    // Simulation lifetime

		//float drag = 10.00f;                                   // Drag (air resistance)
		gravity = vec2(0.00f, -9.81f*(1.0f / drag));           // World gravity

		vao.generate();
		vao.addAttrib(GL_ARRAY_BUFFER, sizeof(myEmitter.eParticles), &myEmitter.eParticles, GL_STATIC_DRAW, 0, 1, GL_FLOAT, GL_FALSE, sizeof(Particle2), (void*)(offsetof(Particle2, pID)));
		vao.addAttrib(GL_ARRAY_BUFFER, sizeof(myEmitter.eParticles), &myEmitter.eParticles, GL_STATIC_DRAW, 1, 1, GL_FLOAT, GL_FALSE, sizeof(Particle2), (void*)(offsetof(Particle2, pID2)));
		vao.addAttrib(GL_ARRAY_BUFFER, sizeof(myEmitter.eParticles), &myEmitter.eParticles, GL_STATIC_DRAW, 2, 1, GL_FLOAT, GL_FALSE, sizeof(Particle2), (void*)(offsetof(Particle2, pRadiusOffset)));
		vao.addAttrib(GL_ARRAY_BUFFER, sizeof(myEmitter.eParticles), &myEmitter.eParticles, GL_STATIC_DRAW, 3, 1, GL_FLOAT, GL_FALSE, sizeof(Particle2), (void*)(offsetof(Particle2, pVelocityOffset)));
		vao.addAttrib(GL_ARRAY_BUFFER, sizeof(myEmitter.eParticles), &myEmitter.eParticles, GL_STATIC_DRAW, 4, 1, GL_FLOAT, GL_FALSE, sizeof(Particle2), (void*)(offsetof(Particle2, pDecayOffset)));
		vao.addAttrib(GL_ARRAY_BUFFER, sizeof(myEmitter.eParticles), &myEmitter.eParticles, GL_STATIC_DRAW, 5, 1, GL_FLOAT, GL_FALSE, sizeof(Particle2), (void*)(offsetof(Particle2, pSizeOffset)));
		vao.addAttrib(GL_ARRAY_BUFFER, sizeof(myEmitter.eParticles), &myEmitter.eParticles, GL_STATIC_DRAW, 6, 3, GL_FLOAT, GL_FALSE, sizeof(Particle2), (void*)(offsetof(Particle2, pColorOffset)));

		//vao.setDrawMode(GL_LINE_STRIP, 0, NUM_PARTICLES2);
		vao.setDrawMode(GL_POINTS, 0, NUM_PARTICLES2);
	}

	void updateLifeCycle(float timeElapsed){

	}

	~ParticleSystem2(void){}
	void draw(){

		if (current_loop < loop_count || loopInf){

			updateTime();
			updateSprite();

			shader->setUniform(uniformLoc[0], View);
			shader->setUniform(uniformLoc[1], Projection);
			shader->setUniform(uniformLoc[2], getModelM());
			shader->setUniform(uniformLoc[3], gravity);
			shader->setUniform(uniformLoc[4], awesome_time/4);
			shader->setUniform(uniformLoc[5], myEmitter.eRadius);
			shader->setUniform(uniformLoc[6], myEmitter.eVelocity);
			shader->setUniform(uniformLoc[7], myEmitter.eDecay);
			shader->setUniform(uniformLoc[8], myEmitter.eSizeStart);
			shader->setUniform(uniformLoc[9], myEmitter.eSizeEnd);
			shader->setUniform(uniformLoc[10], myEmitter.eColorStart);
			shader->setUniform(uniformLoc[11], myEmitter.eColorEnd);
			shader->setUniform(uniformLoc[12], 0);
			shader->setUniform(uniformLoc[13], myEmitter.ePosition);

			shader->setUniform(uniformLoc[14], time_Max);
			shader->setUniform(uniformLoc[15], time_Min);
			shader->setUniform(uniformLoc[16], time_Step);
			shader->setUniform(uniformLoc[17], col);
			shader->setUniform(uniformLoc[18], row);
			shader->setUniform(uniformLoc[19], num_col);
			shader->setUniform(uniformLoc[20], num_row);

			shader->setUniform(uniformLoc[21], fog->maxDist);
			shader->setUniform(uniformLoc[22], fog->minDist);
			shader->setUniform(uniformLoc[23], fog->color);
			shader->setUniform(uniformLoc[24], fog->visibility);
			shader->setUniform(uniformLoc[25], fog->maxHeight);
			shader->setUniform(uniformLoc[26], fog->minHeight);
			m_Texture->Bind(GL_TEXTURE0);

			shader->use();
			vao.draw();
			glUseProgram(0);
		}
	}
	void draw(mat4& projection, mat4& view){

		if (current_loop < loop_count || loopInf){

			updateTime();
			updateSprite();

			shader->setUniform(uniformLoc[0], view);
			shader->setUniform(uniformLoc[1], projection);
			shader->setUniform(uniformLoc[2], getModelM());
			shader->setUniform(uniformLoc[3], gravity);
			shader->setUniform(uniformLoc[4], awesome_time/4);
			shader->setUniform(uniformLoc[5], myEmitter.eRadius);
			shader->setUniform(uniformLoc[6], myEmitter.eVelocity);
			shader->setUniform(uniformLoc[7], myEmitter.eDecay);
			shader->setUniform(uniformLoc[8], myEmitter.eSizeStart);
			shader->setUniform(uniformLoc[9], myEmitter.eSizeEnd);
			shader->setUniform(uniformLoc[10], myEmitter.eColorStart);
			shader->setUniform(uniformLoc[11], myEmitter.eColorEnd);
			shader->setUniform(uniformLoc[12], 0);
			shader->setUniform(uniformLoc[13], myEmitter.ePosition);

			shader->setUniform(uniformLoc[14], time_Max);
			shader->setUniform(uniformLoc[15], time_Min);
			shader->setUniform(uniformLoc[16], time_Step);
			shader->setUniform(uniformLoc[17], col);
			shader->setUniform(uniformLoc[18], row);
			shader->setUniform(uniformLoc[19], num_col);
			shader->setUniform(uniformLoc[20], num_row);

			shader->setUniform(uniformLoc[21], fog->maxDist);
			shader->setUniform(uniformLoc[22], fog->minDist);
			shader->setUniform(uniformLoc[23], fog->color);
			shader->setUniform(uniformLoc[24], fog->visibility);
			shader->setUniform(uniformLoc[25], fog->maxHeight);
			shader->setUniform(uniformLoc[26], fog->minHeight);
			m_Texture->Bind(GL_TEXTURE0);

			shader->use();
			//glLineWidth(time);
			vao.draw();
			glUseProgram(0);
		}
	}
	void setShader(GLSLProgram* shader){
		this->shader = shader;
		uniformLoc.push_back(shader->getUniformLoc("u_ViewMatrix"));
		uniformLoc.push_back(shader->getUniformLoc("u_ProjectionMatrix"));
		uniformLoc.push_back(shader->getUniformLoc("u_ModelMatrix"));
		uniformLoc.push_back(shader->getUniformLoc("u_Gravity"));
		uniformLoc.push_back(shader->getUniformLoc("u_Time"));
		uniformLoc.push_back(shader->getUniformLoc("u_eRadius"));
		uniformLoc.push_back(shader->getUniformLoc("u_eVelocity"));
		uniformLoc.push_back(shader->getUniformLoc("u_eDecay"));
		uniformLoc.push_back(shader->getUniformLoc("u_eSizeStart"));
		uniformLoc.push_back(shader->getUniformLoc("u_eSizeEnd"));
		uniformLoc.push_back(shader->getUniformLoc("u_eColorStart"));
		uniformLoc.push_back(shader->getUniformLoc("u_eColorEnd"));
		uniformLoc.push_back(shader->getUniformLoc("u_Texture"));
		uniformLoc.push_back(shader->getUniformLoc("u_ePosition"));

		uniformLoc.push_back(shader->getUniformLoc("time_Max"));
		uniformLoc.push_back(shader->getUniformLoc("time_Min"));
		uniformLoc.push_back(shader->getUniformLoc("time_Step"));
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

	void setTexture(GLenum TextureTarget, const char* FileName, const char* FileType){
		m_Texture = new Texture(TextureTarget, FileName, FileType);
		m_Texture->Load();
	}

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

	// Blast radius
	void setBlastRadius(float br){ myEmitter.eRadius = br; }
	float getBlastRadius(){ return myEmitter.eRadius; }

	// Explosion velocity
	void setExplosionVelocity(float ev){ myEmitter.eVelocity = ev; }
	float getExplosionVelocity(){ return myEmitter.eVelocity; }

	// Explosion decay
	void setExplosionDecay(float ed){ myEmitter.eDecay = ed; }
	float getExplosionDecay(){ return myEmitter.eDecay; }
	
	// Fragment start size
	void setFragStartSize(float fss){ myEmitter.eSizeStart = fss; }
	float getFragStartSize(){ return myEmitter.eSizeStart; }

	// Fragment end size
	void setFragEndSize(float fes){ myEmitter.eSizeEnd = fes; }
	float getFragEndSize(){ return myEmitter.eSizeEnd; }

	// Fragment start color
	void setFragStartColor(vec3 fsc){ myEmitter.eColorStart = fsc; }
	vec3 getFragStartColor(){ return myEmitter.eColorStart; }
                 
	// Fragment end color
	void setFragEndColor(vec3 fec){ myEmitter.eColorEnd = fec; }
	vec3 getFragEndColor(){ return myEmitter.eColorEnd; }

	// Emitter position
	void setEmitterPosition(vec3 ep){ myEmitter.ePosition = ep; }
	vec3 getEmitterPosition(){ return myEmitter.ePosition; }

	void setTexCol(int c){ col = c; }
	int getTexCol(){ return col; }

	void setTexNumCol(int cn){ num_col = cn; }
	int getTexNumCol(){ return num_col; }

	void setTexRow(int r){ row = r; }
	int getTexRow(){ return row; }

	void setTexNumRow(int rn){ num_row = rn; }
	int getTexNumRow(){ return num_row; }

	void setupSprite(){
		num_Sprites = num_col*num_row;
	}

	void updateSprite(){
		float total_time = time_Max - time_Min;
		float sprite_Time = total_time / num_Sprites;
		float temp = sprite_Time;
		int index = 0;

		for (;awesome_time > temp;){
			temp += sprite_Time;
			index++;
			
			if (col < num_col){
				col++;
			}
			else{
				col = 0;

				if (row < num_row){
					row++;
				}
				else{
					row = 0;
				}
			}
		}
		
	}

private:
	void generate(){

	}
	float randomFloatBetween(float min, float max)
	{
		float myRand = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
		return myRand;
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
	Emitter2 myEmitter;
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

	float width;
	float height;

	int col, row, num_col, num_row;

	vec2 gravity;
	float life;
	//float time;

	int num_Sprites;

};