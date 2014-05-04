#ifndef MESH_H
#define	MESH_H

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

struct Vertex
{
	vec3 m_pos;
	vec2 m_tex;
	vec3 m_normal;

	Vertex() {}

	Vertex(const vec3& pos, const vec2& tex, const vec3& normal)
	{
		m_pos = pos;
		m_tex = tex;
		m_normal = normal;
	}
};

class Mesh : public Object
{
public:
	Mesh();

	~Mesh();

	bool LoadMesh(const std::string& Filename);

	void draw();

	uint NumBones() const
	{
		return m_NumBones;
	}

	void BoneTransform(float TimeInSeconds, vector<mat4>& Transforms);

	void setShader(GLSLProgram* s){ shader = s; }
	void setAdjustM(mat4 m){ adjustM = m; }

private:

	void InitTranslationTransform(float x, float y, float z, glm::mat4 &to) {
		to = glm::translate(vec3(x, y, z));
	}

	void InitScaleTransform(float ScaleX, float ScaleY, float ScaleZ, glm::mat4 &to) {
		to = glm::scale(vec3(ScaleX, ScaleY, ScaleZ));
	}

	void CopyaiMat4x4(aiMatrix4x4 *from, glm::mat4 &to) {
		to = glm::make_mat4((*from)[0]);
		to = glm::transpose(to);
	}

	void CopyaiMat4x4c(const aiMatrix4x4 *from, glm::mat4 &to) {
		to = glm::make_mat4((*from)[0]);
		to = glm::transpose(to);
	}

	void CopyaiMat3x3(aiMatrix3x3 *from, glm::mat4 &to) {
		to = mat4(glm::make_mat3((*from)[0]));
		to = glm::transpose(to);
	}

	void CopyaiMat3x3tf(aiMatrix3x3t<float> *from, glm::mat4 &to) {
		to = mat4(glm::make_mat3((*from)[0]));
		to = glm::transpose(to);
	}



#define NUM_BONES_PER_VEREX 4

	struct BoneInfo
	{
		mat4 BoneOffset;
		mat4 FinalTransformation;

		BoneInfo()
		{
			BoneOffset = mat4(0.0);
			FinalTransformation = mat4(0.0);
		}
	};

	struct VertexBoneData
	{
		uint IDs[NUM_BONES_PER_VEREX];
		float Weights[NUM_BONES_PER_VEREX];

		VertexBoneData()
		{
			Reset();
		};

		void Reset()
		{
			ZERO_MEM(IDs);
			ZERO_MEM(Weights);
		}

		void AddBoneData(uint BoneID, float Weight);
	};

	void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
	void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
	void CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
	uint FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);
	uint FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);
	uint FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim);
	const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const string NodeName);
	void ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const mat4& ParentTransform);

	bool InitFromScene(const aiScene* pScene, const std::string& Filename);

	//void InitMesh(unsigned int Index, const aiMesh* paiMesh);
	void InitMesh(uint MeshIndex,
		const aiMesh* paiMesh,
		vector<vec3>& Positions,
		vector<vec3>& Normals,
		vector<vec2>& TexCoords,
		vector<VertexBoneData>& Bones,
		vector<unsigned int>& Indices);

	void LoadBones(uint MeshIndex, const aiMesh* paiMesh, vector<VertexBoneData>& Bones);

	bool InitMaterials(const aiScene* pScene, const std::string& Filename);
	void Clear();

#define INVALID_MATERIAL 0xFFFFFFFF

	enum VB_TYPES {
		INDEX_BUFFER,
		POS_VB,
		NORMAL_VB,
		TEXCOORD_VB,
		BONE_VB,
		NUM_VBs
	};

	GLuint m_VAO;
	GLuint m_Buffers[NUM_VBs];

	struct MeshEntry {
		MeshEntry()
		{
			NumIndices = 0;
			BaseVertex = 0;
			BaseIndex = 0;
			MaterialIndex = INVALID_MATERIAL;
		}

		~MeshEntry();

		void Init(const std::vector<float>& pos, const std::vector<float>& tex, const std::vector<float>& norm, std::vector<unsigned int>& ind);
		void draw(){ vao.draw(); }

		GLuint VB;
		GLuint IB;
		unsigned int NumIndices;
		unsigned int MaterialIndex;
		unsigned int NumVertices;
		VAO vao;
		vector<unsigned int> inds;

		unsigned int BaseVertex;
		unsigned int BaseIndex;

	};

	std::vector<MeshEntry> m_Entries;
	std::vector<Texture*> m_Textures;

	map<string, uint> m_BoneMapping; // maps a bone name to its index
	uint m_NumBones;
	vector<BoneInfo> m_BoneInfo;
	mat4 m_GlobalInverseTransform;

	const aiScene* m_pScene;
	Assimp::Importer m_Importer;

	GLSLProgram* shader;
	mat4 adjustM;
};


#endif	/* MESH_H */