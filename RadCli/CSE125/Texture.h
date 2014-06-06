#ifndef TEXTURE_H
#define	TEXTURE_H

#include <string>

#include <GL/glew.h>
#include <Qt/QtGui/QImage> 
#include <Qt/QtOpenGL/QGLWidget>

class Texture
{
public:
	Texture(GLenum TextureTarget);//constructor that'll be used for depth texture
	Texture(GLenum TextureTarget, const char* FileName, const char* FileType);
	bool Load();
	bool LoadCube(const char* FilePre, const char* FileSuf);
	bool LoadDepthTexture(GLsizei width,GLsizei height);
	bool LoadRenderTexture(GLsizei width, GLsizei height);

	void Bind(GLenum TextureUnit);

	GLuint getTexID(){
		return m_textureObj;
	}

private:
	const char* m_fileName;
	const char* m_fileType;
	GLenum m_textureTarget;
	GLuint m_textureObj;
	QImage timg;
};

#endif	/* TEXTURE_H */