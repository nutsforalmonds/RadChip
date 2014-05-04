#include "random_texture.h"
//#include "math_3d.h"
#include "ogldev_util.h"


RandomTexture::RandomTexture()
{
	m_textureObj = 0;
}


RandomTexture::~RandomTexture()
{
	if (m_textureObj != 0) {
		glDeleteTextures(1, &m_textureObj);
	}
}

bool RandomTexture::InitRandomTexture(unsigned int Size)
{
	vec3* pRandomData = new vec3[Size];
	for (unsigned int i = 0; i < Size; i++) {
		pRandomData[i].x = RandomFloat();
		pRandomData[i].y = RandomFloat();
		pRandomData[i].z = RandomFloat();
	}

	glGenTextures(1, &m_textureObj);
	glBindTexture(GL_TEXTURE_1D, m_textureObj);
	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, Size, 0, GL_RGB, GL_FLOAT, pRandomData);
	glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	delete[] pRandomData;

	return GLCheckError();
}


void RandomTexture::Bind(GLenum TextureUnit)
{
	glActiveTexture(TextureUnit);
	glBindTexture(GL_TEXTURE_1D, m_textureObj);
}