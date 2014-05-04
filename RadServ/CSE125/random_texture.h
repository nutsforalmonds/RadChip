#ifndef RANDOM_TEXTURE_H
#define	RANDOM_TEXTURE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::mat3;

class RandomTexture
{
public:
	RandomTexture();

	~RandomTexture();

	bool InitRandomTexture(unsigned int Size);

	void Bind(GLenum TextureUnit);

private:
	GLuint m_textureObj;

	float RandomFloat()
	{
		float Max = RAND_MAX;
		return ((float)rand() / Max);
	}
};



#endif	/* RANDOM_TEXTURE_H */