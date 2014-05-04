#include "ogldev_util.h"
#include "particle_system.h"

#define MAX_PARTICLES 1000
#define PARTICLE_LIFETIME 10.0f

#define PARTICLE_TYPE_LAUNCHER 0.0f
#define PARTICLE_TYPE_SHELL 1.0f
#define PARTICLE_TYPE_SECONDARY_SHELL 2.0f

#define RANDOM_TEXTURE_UNIT_INDEX 3
#define RANDOM_TEXTURE_UNIT GL_TEXTURE3
#define COLOR_TEXTURE_UNIT_INDEX 0
#define COLOR_TEXTURE_UNIT GL_TEXTURE0

struct Particle
{
	float Type;
	vec3 Pos;
	vec3 Vel;
	float LifetimeMillis;
};


ParticleSystem::ParticleSystem()
{
	m_currVB = 0;
	m_currTFB = 1;
	m_isFirst = true;
	m_time = 0;
	m_pTexture = NULL;

	ZERO_MEM(m_transformFeedback);
	ZERO_MEM(m_particleBuffer);
}


ParticleSystem::~ParticleSystem()
{
	SAFE_DELETE(m_pTexture);

	if (m_transformFeedback[0] != 0) {
		glDeleteTransformFeedbacks(2, m_transformFeedback);
	}

	if (m_particleBuffer[0] != 0) {
		glDeleteBuffers(2, m_particleBuffer);
	}
}


bool ParticleSystem::InitParticleSystem(const vec3& Pos, ShaderController &sd)
{
	Particle Particles[MAX_PARTICLES];
	ZERO_MEM(Particles);

	Particles[0].Type = PARTICLE_TYPE_LAUNCHER;
	Particles[0].Pos = Pos;
	Particles[0].Vel = vec3(0.0f, 0.0001f, 0.0f);
	Particles[0].LifetimeMillis = 0.0f;

	glGenTransformFeedbacks(2, m_transformFeedback);
	glGenBuffers(2, m_particleBuffer);

	for (unsigned int i = 0; i < 2; i++) {
		glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, m_transformFeedback[i]);
		glBindBuffer(GL_ARRAY_BUFFER, m_particleBuffer[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Particles), Particles, GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, m_particleBuffer[i]);
	}

	//UNNEEDED INIT FOR PARTICLE SHADER
	/*
	if (!m_updateTechnique.Init()) {
		return false;
	}
	*/

	const GLchar* Varyings[4];
	Varyings[0] = "Type1";
	Varyings[1] = "Position1";
	Varyings[2] = "Velocity1";
	Varyings[3] = "Age1";

	glTransformFeedbackVaryings(sd.getShader("ps_update")->getHandle(), 4, Varyings, GL_INTERLEAVED_ATTRIBS);

	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };

	glLinkProgram(sd.getShader("ps_update")->getHandle());

	glGetProgramiv(sd.getShader("ps_update")->getHandle(), GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(sd.getShader("ps_update")->getHandle(), sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		return false;
	}

	glValidateProgram(sd.getShader("ps_update")->getHandle());
	glGetProgramiv(sd.getShader("ps_update")->getHandle(), GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(sd.getShader("ps_update")->getHandle(), sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
		return false;
	}


	//BIND
	//m_updateTechnique.Enable();
	//m_updateTechnique.SetRandomTextureUnit(RANDOM_TEXTURE_UNIT_INDEX);
	//m_updateTechnique.SetLauncherLifetime(100.0f);
	//m_updateTechnique.SetShellLifetime(10000.0f);
	//m_updateTechnique.SetSecondaryShellLifetime(2500.0f);

	sd.getShader("ps_update")->setUniform("gRandomTexture", RANDOM_TEXTURE_UNIT_INDEX);
	sd.getShader("ps_update")->setUniform("gLauncherLifetime", 100.0f);
	sd.getShader("ps_update")->setUniform("gShellLifetime", 10000.0f);
	sd.getShader("ps_update")->setUniform("gSecondaryShellLifetime", 2500.0f);
	sd.getShader("ps_update")->use();



	if (!m_randomTexture.InitRandomTexture(1000)) {
		return false;
	}

	m_randomTexture.Bind(RANDOM_TEXTURE_UNIT);

	//UNNEEDED INIT FOR BILLBOARD SHADER
	/*
	if (!m_billboardTechnique.Init()) {
		return false;
	}
	*/

	//BIND
	//m_billboardTechnique.Enable();
	//m_billboardTechnique.SetColorTextureUnit(COLOR_TEXTURE_UNIT_INDEX);
	//m_billboardTechnique.SetBillboardSize(0.01f);

	sd.getShader("billboard")->setUniform("gBillboardSize", 0.01f);
	sd.getShader("billboard")->setUniform("texUnit", COLOR_TEXTURE_UNIT_INDEX);
	sd.getShader("billboard")->use();

	m_pTexture = new Texture(GL_TEXTURE_2D, "img/fireworks_red.jpg", "JPG");

	if (!m_pTexture->Load()) {
		return false;
	}

	return GLCheckError();
}


void ParticleSystem::Render(int DeltaTimeMillis, const mat4 Projection, const mat4& viewM, const vec3& CameraPos, float size, const mat4 MM, const mat4 MVP, int tex, ShaderController &sd)
{
	m_time += DeltaTimeMillis;

	UpdateParticles(DeltaTimeMillis, sd);

	RenderParticles(Projection, viewM, CameraPos, MM, MVP, tex, sd);

	m_currVB = m_currTFB;
	m_currTFB = (m_currTFB + 1) & 0x1;
}


void ParticleSystem::UpdateParticles(int DeltaTimeMillis, ShaderController &sd)
{
	//BIND THE PARTICAL SHADER WITH INFO!
	//m_updateTechnique.Enable();
	//m_updateTechnique.SetTime(m_time);
	//m_updateTechnique.SetDeltaTimeMillis(DeltaTimeMillis);
	sd.getShader("ps_update")->setUniform("gTime", m_time);
	sd.getShader("ps_update")->setUniform("gDeltaTimeMillis", DeltaTimeMillis);
	sd.getShader("ps_update")->use();

	m_randomTexture.Bind(RANDOM_TEXTURE_UNIT);

	glEnable(GL_RASTERIZER_DISCARD);

	glBindBuffer(GL_ARRAY_BUFFER, m_particleBuffer[m_currVB]);
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, m_transformFeedback[m_currTFB]);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), 0);                          // type
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (const GLvoid*)4);         // position
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (const GLvoid*)16);        // velocity
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (const GLvoid*)28);          // lifetime

	glBeginTransformFeedback(GL_POINTS);

	if (m_isFirst) {
		glDrawArrays(GL_POINTS, 0, 1);

		m_isFirst = false;
	}
	else {
		glDrawTransformFeedback(GL_POINTS, m_transformFeedback[m_currVB]);
	}

	glEndTransformFeedback();

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
}


void ParticleSystem::RenderParticles(const mat4 Projection, const mat4& viewM, const vec3& CameraPos, const mat4 MM, const mat4 MVP, int tex, ShaderController &sd)
{
	//BIND THE BILLBOARD SHADER WITH INFO!
	//m_billboardTechnique.Enable();
	//m_billboardTechnique.SetCameraPosition(CameraPos);
	//m_billboardTechnique.SetVP(VP);
	sd.getShader("billboard")->setUniform("ProjectionMatrix", Projection);
	sd.getShader("billboard")->setUniform("ViewMatrix", viewM);
	sd.getShader("billboard")->setUniform("gCameraPos", CameraPos);
	sd.getShader("billboard")->setUniform("ModelMatrix", MM);
	sd.getShader("billboard")->setUniform("MVP", MVP);
	sd.getShader("billboard")->setUniform("texUnit", tex);
	sd.getShader("billboard")->use();
	m_pTexture->Bind(COLOR_TEXTURE_UNIT);

	glDisable(GL_RASTERIZER_DISCARD);

	glBindBuffer(GL_ARRAY_BUFFER, m_particleBuffer[m_currTFB]);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (const GLvoid*)4);  // position

	glDrawTransformFeedback(GL_POINTS, m_transformFeedback[m_currTFB]);

	glDisableVertexAttribArray(0);
}