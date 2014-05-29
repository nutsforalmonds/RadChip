#ifndef MESH_H
#define	MESH_H

#include <map>
#include <unordered_map>
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
#include "ParticleSystem.h"
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
#include "Structures.h"

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

	bool LoadMesh(const std::string& Filename, bool anim=true);

	void draw();
	void draw(mat4& projection, mat4& view);

	uint NumBones() const
	{
		return m_NumBones;
	}

	void BoneTransform(double TimeInSeconds, vector<mat4>& Transforms);

	void setShader(GLSLProgram* s);
	void setShininess(int s){ shininess = s; }
	void setAdjustM(mat4& m){ adjustM = m; }
	void setShadowTex(int t){ shadowTex = t; }
	void setTransforms(vector<mat4>& t){ transforms = t; }
	void setParticleSystem(ParticleSystem* p){ pSystem = p; }
	void setFog(Fog& f){ fog = &f; }

#define INVALID_MATERIAL 0xFFFFFFFF
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

	mat4& getAdjustM(){ return adjustM; }
	GLuint& getVAO(){ return m_VAO; }
	void setVAO(GLuint& vao){ m_VAO = vao; }
	std::vector<MeshEntry>& getEntries(){ return m_Entries; }
	void setEntries(std::vector<MeshEntry>& en){ m_Entries = en; }
	std::vector<Texture*>& getTextures(){ return m_Textures; }
	void setTextures(std::vector<Texture*>& tx){ m_Textures = tx; }

private:

	void InitTranslationTransform(float& x, float& y, float& z, glm::mat4 &to) {
		to = glm::translate(vec3(x, y, z));
	}

	void InitScaleTransform(float& ScaleX, float& ScaleY, float& ScaleZ, glm::mat4 &to) {
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



#define NUM_BONES_PER_VEREX 8

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
		int count = 0;

		VertexBoneData()
		{
			for (uint i = 0; i < NUM_BONES_PER_VEREX; i++){
				IDs[i] = -1;
				Weights[i] = 0;
			}
			Reset();
		};

		void Reset()
		{
			ZERO_MEM(IDs);
			ZERO_MEM(Weights);
			count = 0;
		}

		void AddBoneData(float BoneID, float Weight)
		{
			for (uint i = 0; i < NUM_BONES_PER_VEREX; i++) {
				if (Weights[i] == 0.0) {
					IDs[i] = BoneID;
					Weights[i] = Weight;
					count++;
					return;
				}
			}
			// should never get here - more bones than we have space for
			assert(0);
		}

		int getCount(){
			return count;
		}
	};

	void CalcInterpolatedScaling(aiVector3D& Out, double AnimationTime, const aiNodeAnim* pNodeAnim);
	void CalcInterpolatedRotation(aiQuaternion& Out, double AnimationTime, const aiNodeAnim* pNodeAnim);
	void CalcInterpolatedPosition(aiVector3D& Out, double AnimationTime, const aiNodeAnim* pNodeAnim);
	uint FindScaling(double AnimationTime, const aiNodeAnim* pNodeAnim);
	uint FindRotation(double AnimationTime, const aiNodeAnim* pNodeAnim);
	uint FindPosition(double AnimationTime, const aiNodeAnim* pNodeAnim);
	const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const string NodeName);
	void ReadNodeHeirarchy(double AnimationTime, aiNode* pNode, const mat4& ParentTransform);

	bool InitFromScene(const aiScene* pScene, const std::string& Filename);
	bool CreateAnimationMap(aiNode* pNode);
	bool CreateNameMap(aiNode* pNode);
	bool CreateNodeMap(aiNode* pNode);

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

	std::vector<MeshEntry> m_Entries;
	std::vector<Texture*> m_Textures;

	map<aiNode*, uint> m_BoneMapping; // maps a bone name to its index
	uint m_NumBones;
	vector<BoneInfo> m_BoneInfo;
	mat4 m_GlobalInverseTransform;

	const aiScene* m_pScene;
	Assimp::Importer m_Importer;

	GLSLProgram* shader;
	mat4 adjustM;
	int shininess;

	int shadowTex;
	vector<int> uniformLoc;

	map<aiNode*, const aiNodeAnim*> anim_map;
	map<aiNode*, string> name_map;
	map<string, aiNode*> node_map;

	vector<mat4> transforms;
	ParticleSystem* pSystem;
	
	Fog* fog;
};


#endif	/* MESH_H */