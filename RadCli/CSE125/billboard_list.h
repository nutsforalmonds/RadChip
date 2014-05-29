#ifndef BILLBOARD_LIST_H
#define	BILLBOARD_LIST_H

#include <string>
#include "ShaderController.h"
#include "Texture.h"
#include "Object.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::mat3;

class BillboardList : public Object
{
public:
	BillboardList();
	~BillboardList();

	bool Init(const std::string& TexFilename, const char* FileType);

	void Render(const mat4 Projection, const mat4& viewM, float size);

	void setShader(GLSLProgram* shader);

	void CreatePositionBuffer();
	void CreateSinglePositionBuffer(vec3 pos);
	void BindBoards();
	void AddBoard(vec3 pos);

private:
	

	GLuint m_VB;
	Texture* m_pTexture;
	GLuint m_vao;
	GLSLProgram* shader;
	vector<int> uniformLoc;
	vector<vec3> mBoardList;
	int num_of_boards;
};


#endif	/* BILLBOARD_LIST_H */