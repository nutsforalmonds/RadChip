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

	CreatePositionBuffer();

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
}


void BillboardList::Render(const mat4 Projection, const mat4& viewM, const vec3& CameraPos, float size, const mat4 MM, const mat4 MVP, int tex, ShaderController &sd)
{
	sd.getShader("billboard")->setUniform("ProjectionMatrix", Projection);
	sd.getShader("billboard")->setUniform("ViewMatrix", viewM);
	sd.getShader("billboard")->setUniform("gCameraPos", CameraPos);
	sd.getShader("billboard")->setUniform("gBillboardSize", size);
	sd.getShader("billboard")->setUniform("ModelMatrix", MM);
	sd.getShader("billboard")->setUniform("MVP", MVP);
	sd.getShader("billboard")->setUniform("texUnit", tex);
	sd.getShader("billboard")->use();
	m_pTexture->Bind(COLOR_TEXTURE_UNIT);

	glBindVertexArray(m_vao);
	glDrawArrays(GL_POINTS, 0, NUM_ROWS * NUM_COLUMNS);
}

