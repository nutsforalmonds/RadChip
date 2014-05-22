#ifndef MESH_STATIC_H
#define	MESH_STATIC_H

#include <map>
#include <vector>
#include <GL/glew.h>
// assimp include files. These three are usually needed.
#include "assimp/Importer.hpp"	//OO version Header!
#include "assimp/PostProcess.h"
#include "assimp/Scene.h"

#include "ogldev_util.h"
#include "Texture.h"

#include "VAO.h"

#include <glm/glm.hpp>
using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::mat3;

#include "VAO.h"
#include "glslprogram.h"
#include "Structures.h"
#include <array>
#include "Object.h"

struct Vertex_Static
{
	vec3 m_pos;
	vec2 m_tex;
	vec3 m_normal;

	Vertex_Static() {}

	Vertex_Static(const vec3& pos, const vec2& tex, const vec3& normal)
	{
		m_pos = pos;
		m_tex = tex;
		m_normal = normal;
	}
};


class Mesh_Static: public Object
{
public:
	Mesh_Static();

	~Mesh_Static();

	bool LoadMesh(const std::string& Filename);

	void draw();

	void setShader(GLSLProgram* s);
	void setShadowTex(int t){ shadowTex = t; }
	void setAdjustM(mat4 m){ adjustM = m; }

private:
	bool InitFromScene(const aiScene* pScene, const std::string& Filename);
	void InitMesh(unsigned int Index, const aiMesh* paiMesh);
	bool InitMaterials(const aiScene* pScene, const std::string& Filename);
	void Clear();

#define INVALID_MATERIAL 0xFFFFFFFF

	struct Mesh_StaticEntry {
		Mesh_StaticEntry();

		~Mesh_StaticEntry();

		void Init(const std::vector<float>& pos, const std::vector<float>& tex, const std::vector<float>& norm, std::vector<unsigned int>& ind);
		void draw(){ vao.draw(); }

		GLuint VB;
		GLuint IB;
		unsigned int NumIndices;
		unsigned int MaterialIndex;
		unsigned int NumVertices;
		VAO vao;
		vector<unsigned int> inds;
	};

	std::vector<Mesh_StaticEntry> m_Entries;
	std::vector<Texture*> m_Textures;

	const aiScene* m_pScene;
	Assimp::Importer m_Importer;

	GLSLProgram* shader;
	mat4 adjustM;

	int shadowTex;
	vector<int> uniformLoc;
};


#endif	/* MESH_STATIC_H */