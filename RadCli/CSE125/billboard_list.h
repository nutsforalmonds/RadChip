#ifndef BILLBOARD_LIST_H
#define	BILLBOARD_LIST_H

#include <string>
#include "ShaderController.h"
#include "Texture.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::mat3;

class BillboardList
{
public:
	BillboardList();
	~BillboardList();

	bool Init(const std::string& TexFilename, const char* FileType);

	void Render(const mat4 Projection, const mat4& viewM, const vec3& CameraPos, float size, const mat4 MM, const mat4 MVP, int tex, ShaderController &sd);

private:
	void CreatePositionBuffer();

	GLuint m_VB;
	Texture* m_pTexture;
	GLuint m_vao;
};


#endif	/* BILLBOARD_LIST_H */