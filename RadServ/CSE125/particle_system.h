#ifndef PARTICLE_SYSTEM_H
#define	PARTICLE_SYSTEM_H

#include <GL/glew.h>

#include "random_texture.h"

#include "ShaderController.h"
#include "Texture.h"
#include <glm/glm.hpp>
using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::mat3;

class ParticleSystem
{
public:
	ParticleSystem();

	~ParticleSystem();

	bool InitParticleSystem(const vec3& Pos, ShaderController &sd);

	void Render(int DeltaTimeMillis, const mat4 Projection, const mat4& viewM, const vec3& CameraPos, float size, const mat4 MM, const mat4 MVP, int tex, ShaderController &sd);

private:

	void UpdateParticles(int DeltaTimeMillis, ShaderController &sd);
	void RenderParticles(const mat4 Projection, const mat4& viewM, const vec3& CameraPos, const mat4 MM, const mat4 MVP, int tex, ShaderController &sd);

	bool m_isFirst;
	unsigned int m_currVB;
	unsigned int m_currTFB;
	GLuint m_particleBuffer[2];
	GLuint m_transformFeedback[2];
	//PSUpdateTechnique m_updateTechnique;
	//BillboardTechnique m_billboardTechnique;
	RandomTexture m_randomTexture;
	Texture* m_pTexture;
	int m_time;
};

#endif	/* PARTICLE_SYSTEM_H */