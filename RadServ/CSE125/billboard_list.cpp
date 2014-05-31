#include "ogldev_util.h"
#include "billboard_list.h"

#define NUM_ROWS 10
#define NUM_COLUMNS 10

#define COLOR_TEXTURE_UNIT GL_TEXTURE0
#define SHADOW_TEXTURE_UNIT GL_TEXTURE1
#define NORMAL_TEXTURE_UNIT GL_TEXTURE2


BillboardList::BillboardList()
{
	m_pTexture = NULL;
	m_VB = INVALID_OGL_VALUE;
}


BillboardList::~BillboardList()
{
	SAFE_DELETE(m_pTexture);

	if (m_VB != INVALID_OGL_VALUE)
	{
		glDeleteBuffers(1, &m_VB);
	}
}


bool BillboardList::Init(const std::string& TexFilename, const char* FileType)
{
	m_pTexture = new Texture(GL_TEXTURE_2D, TexFilename.c_str(), FileType);

	if (!m_pTexture->Load()) {
		return false;
	}

	//CreatePositionBuffer();

	return true;
}

void BillboardList::CreatePositionBuffer()
{
	vec3 Positions[NUM_ROWS * NUM_COLUMNS];

	for (unsigned int j = 0; j < NUM_ROWS; j++) {
		for (unsigned int i = 0; i < NUM_COLUMNS; i++) {
			vec3 Pos((float)i, 1.0f, (float)j);
			Positions[j * NUM_COLUMNS + i] = Pos;
		}
	}
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &m_VB);
	glBindBuffer(GL_ARRAY_BUFFER, m_VB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Positions), &Positions[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	num_of_boards = NUM_ROWS * NUM_COLUMNS;
}

void BillboardList::CreateSinglePositionBuffer(vec3 pos)
{
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &m_VB);
	glBindBuffer(GL_ARRAY_BUFFER, m_VB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos), &pos, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	num_of_boards = 1;
}

void BillboardList::BindBoards()
{
	vec3 Temp[10];

	for (int i = 0; i < num_of_boards; i++) {
		Temp[i] = mBoardList[i];
	}
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &m_VB);
	glBindBuffer(GL_ARRAY_BUFFER, m_VB);
	glBufferData(GL_ARRAY_BUFFER, 12 * num_of_boards, &Temp[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void BillboardList::AddBoard(vec3 pos)
{
	num_of_boards++;
	mBoardList.push_back(pos);
}

void BillboardList::Render(const mat4 Projection, const mat4& viewM, const vec3& CameraPos, float size, const mat4 MM, const mat4 MVP, int tex, ShaderController &sd)
{
	shader->setUniform(uniformLoc[0], Projection);
	shader->setUniform(uniformLoc[1], viewM);
	shader->setUniform(uniformLoc[2], CameraPos);
	shader->setUniform(uniformLoc[3], size);
	shader->setUniform(uniformLoc[4], MM);
	shader->setUniform(uniformLoc[5], MVP);
	shader->setUniform(uniformLoc[6], tex);
	shader->use();
	m_pTexture->Bind(COLOR_TEXTURE_UNIT);

	glBindVertexArray(m_vao);
	glDrawArrays(GL_POINTS, 0, num_of_boards);
	glUseProgram(0);
}

void BillboardList::setShader(GLSLProgram* shader)
{
	this->shader = shader;
	uniformLoc.push_back(shader->getUniformLoc("ProjectionMatrix"));
	uniformLoc.push_back(shader->getUniformLoc("ViewMatrix"));
	uniformLoc.push_back(shader->getUniformLoc("gCameraPos"));
	uniformLoc.push_back(shader->getUniformLoc("gBillboardSize"));
	uniformLoc.push_back(shader->getUniformLoc("ModelMatrix"));
	uniformLoc.push_back(shader->getUniformLoc("MVP"));
	uniformLoc.push_back(shader->getUniformLoc("texUnit"));
}


vector<vec3> * BillboardList::getPos()
{
	return &mBoardList;
}