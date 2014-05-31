#include <assert.h>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <time.h>
#include <stdint.h>
#include "mesh.h"

using namespace std;

#define POSITION_LOCATION      0
#define TEX_COORD_LOCATION     1
#define NORMAL_LOCATION        2
#define BONE_ID_1_LOCATION     3
#define BONE_ID_2_LOCATION     4
#define BONE_WEIGHT_1_LOCATION 5
#define BONE_WEIGHT_2_LOCATION 6
#define BONE_COUNT_LOCATION    7

extern mat4 Projection;
extern mat4 View;
extern mat4 LightView;
extern mat4 LightProjection;
extern mat4 ScaleBias;
extern void printLoadingString(string s);
/*
Mesh::MeshEntry::MeshEntry()
{
VB = INVALID_OGL_VALUE;
IB = INVALID_OGL_VALUE;
NumIndices = 0;
MaterialIndex = INVALID_MATERIAL;
};*/

Mesh::MeshEntry::~MeshEntry()
{
	if (VB != INVALID_OGL_VALUE)
	{
		glDeleteBuffers(1, &VB);
	}

	if (IB != INVALID_OGL_VALUE)
	{
		glDeleteBuffers(1, &IB);
	}
}

void Mesh::MeshEntry::Init(const std::vector<float>& pos, const std::vector<float>& tex, const std::vector<float>& norm, std::vector<unsigned int>& ind)
{
	NumIndices = ind.size();
	NumVertices = pos.size();
	inds = ind;

	vao.generate();
	vao.addAttrib(GL_ARRAY_BUFFER, pos.size() * sizeof(float), &pos[0], GL_STATIC_DRAW, 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	vao.addAttrib(GL_ARRAY_BUFFER, tex.size() * sizeof(float), &tex[0], GL_STATIC_DRAW, 1, 2, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	vao.addAttrib(GL_ARRAY_BUFFER, norm.size() * sizeof(float), &norm[0], GL_STATIC_DRAW, 2, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	vao.setDrawMode(GL_TRIANGLES, ind.size(), GL_UNSIGNED_INT, &inds[0]);
}

Mesh::Mesh()
{
	m_VAO = 0;
	ZERO_MEM(m_Buffers);
	m_NumBones = 0;
	m_pScene = NULL;
}


Mesh::~Mesh()
{
	//Clear();
}


void Mesh::Clear()
{
	for (uint i = 0; i < m_Textures.size(); i++) {
		SAFE_DELETE(m_Textures[i]);
	}

	if (m_Buffers[0] != 0) {
		glDeleteBuffers(ARRAY_SIZE_IN_ELEMENTS(m_Buffers), m_Buffers);
	}

	if (m_VAO != 0) {
		glDeleteVertexArrays(1, &m_VAO);
		m_VAO = 0;
	}
}


bool Mesh::LoadMesh(const std::string& Filename, bool anim)
{
	// Release the previously loaded mesh (if it exists)
	Clear();

	// Create the VAO
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	// Create the buffers for the vertices attributes
	glGenBuffers(ARRAY_SIZE_IN_ELEMENTS(m_Buffers), m_Buffers);

	bool Ret = false;

	//Assimp::Importer Importer;
	//const aiScene* pScene = Importer.ReadFile(Filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals);

	m_pScene = m_Importer.ReadFile(Filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals);//aiProcess_GenSmoothNormals


	if (m_pScene) {
		//m_GlobalInverseTransform = m_pScene->mRootNode->mTransformation;
		//m_GlobalInverseTransform.Inverse();

		CopyaiMat4x4(&m_pScene->mRootNode->mTransformation, m_GlobalInverseTransform);

		m_GlobalInverseTransform = glm::inverse(m_GlobalInverseTransform);

		CreateNodeMap(m_pScene->mRootNode);

		Ret = InitFromScene(m_pScene, Filename);
	}
	else {
		printf("Error parsing '%s': '%s'\n", Filename.c_str(), m_Importer.GetErrorString());
	}

	// Make sure the VAO is not changed from the outside
	glBindVertexArray(0);

	CreateAnimationMap(m_pScene->mRootNode);
	CreateNameMap(m_pScene->mRootNode);

	if (!anim){
		vector<mat4> Transformations;
		BoneTransform(0, Transformations);
		setTransforms(Transformations);
	}

	return Ret;
}

bool Mesh::CreateAnimationMap(aiNode* pNode){
	string NodeName(pNode->mName.data);

	const aiAnimation* pAnimation = m_pScene->mAnimations[0];

	const aiNodeAnim* pNodeAnim = FindNodeAnim(pAnimation, NodeName);

	anim_map[pNode] = pNodeAnim;

	for (uint i = 0; i < pNode->mNumChildren; i++) {
		CreateAnimationMap(pNode->mChildren[i]);
	}

	return true;
}

bool Mesh::CreateNameMap(aiNode* pNode){
	string NodeName(pNode->mName.data);

	assert(name_map.find(pNode) == name_map.end());

	name_map[pNode] = NodeName;

	//name_map_inverse[NodeName] = uintptr_t(pNode);

	//cout << NodeName << " : " << uintptr_t(pNode) << endl;

	for (uint i = 0; i < pNode->mNumChildren; i++) {
		CreateNameMap(pNode->mChildren[i]);
	}

	return true;
}

bool Mesh::CreateNodeMap(aiNode* pNode){
	string NodeName(pNode->mName.data);

	assert(node_map.find(NodeName) == node_map.end());

	node_map[NodeName] = pNode;

	for (uint i = 0; i < pNode->mNumChildren; i++) {
		CreateNodeMap(pNode->mChildren[i]);
	}

	return true;
}

bool Mesh::InitFromScene(const aiScene* pScene, const std::string& Filename)
{
	m_Entries.resize(pScene->mNumMeshes);
	m_Textures.resize(pScene->mNumMaterials);

	vector<vec3> Positions;
	vector<vec3> Normals;
	vector<vec2> TexCoords;
	vector<VertexBoneData> Bones;
	vector<uint> Indices;

	uint NumVertices = 0;
	uint NumIndices = 0;

	// Count the number of vertices and indices
	for (uint i = 0; i < m_Entries.size(); i++) {
		m_Entries[i].MaterialIndex = pScene->mMeshes[i]->mMaterialIndex;
		m_Entries[i].NumIndices = pScene->mMeshes[i]->mNumFaces * 3;
		m_Entries[i].BaseVertex = NumVertices;
		m_Entries[i].BaseIndex = NumIndices;

		NumVertices += pScene->mMeshes[i]->mNumVertices;
		NumIndices += m_Entries[i].NumIndices;
	}

	// Reserve space in the vectors for the vertex attributes and indices
	Positions.reserve(NumVertices);
	Normals.reserve(NumVertices);
	TexCoords.reserve(NumVertices);
	Bones.resize(NumVertices);
	Indices.reserve(NumIndices);

	// Initialize the meshes in the scene one by one
	for (uint i = 0; i < m_Entries.size(); i++) {
		const aiMesh* paiMesh = pScene->mMeshes[i];
		InitMesh(i, paiMesh, Positions, Normals, TexCoords, Bones, Indices);
	}

	if (!InitMaterials(pScene, Filename)) {
		return false;
	}

	// Generate and populate the buffers with vertex attributes and the indices
	glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[POS_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Positions[0]) * Positions.size(), &Positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(POSITION_LOCATION);
	glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TexCoords[0]) * TexCoords.size(), &TexCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(TEX_COORD_LOCATION);
	glVertexAttribPointer(TEX_COORD_LOCATION, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Normals[0]) * Normals.size(), &Normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(NORMAL_LOCATION);
	glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[BONE_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Bones[0]) * Bones.size(), &Bones[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(BONE_ID_1_LOCATION);
	glVertexAttribIPointer(BONE_ID_1_LOCATION, 4, GL_INT, sizeof(VertexBoneData), (const GLvoid*)0);
	glEnableVertexAttribArray(BONE_ID_2_LOCATION);
	glVertexAttribIPointer(BONE_ID_2_LOCATION, 4, GL_INT, sizeof(VertexBoneData), (const GLvoid*)16);
	glEnableVertexAttribArray(BONE_WEIGHT_1_LOCATION);
	glVertexAttribPointer(BONE_WEIGHT_1_LOCATION, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), (const GLvoid*)32);
	glEnableVertexAttribArray(BONE_WEIGHT_2_LOCATION);
	glVertexAttribPointer(BONE_WEIGHT_2_LOCATION, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), (const GLvoid*)48);
	glEnableVertexAttribArray(BONE_COUNT_LOCATION);
	glVertexAttribIPointer(BONE_COUNT_LOCATION, 1, GL_INT, sizeof(VertexBoneData), (const GLvoid*)64);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffers[INDEX_BUFFER]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices[0]) * Indices.size(), &Indices[0], GL_STATIC_DRAW);

	return GLCheckError();
}
/*
void Mesh::InitMesh(unsigned int Index, const aiMesh* paiMesh)
{
m_Entries[Index].MaterialIndex = paiMesh->mMaterialIndex;

std::vector<Vertex> Vertices;
std::vector<unsigned int> Indices;
std::vector<float> pos;
std::vector<float> tex;
std::vector<float> norm;
std::vector<unsigned int> ind;

const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
const aiVector3D* pPos = &(paiMesh->mVertices[i]);
const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

pos.push_back(pPos->x);
pos.push_back(pPos->y);
pos.push_back(pPos->z);
tex.push_back(pTexCoord->x);
tex.push_back(pTexCoord->y);
norm.push_back(pNormal->x);
norm.push_back(pNormal->y);
norm.push_back(pNormal->z);
}

for (unsigned int i = 0; i < paiMesh->mNumFaces; i++) {
const aiFace& Face = paiMesh->mFaces[i];
assert(Face.mNumIndices == 3);
ind.push_back(Face.mIndices[0]);
ind.push_back(Face.mIndices[1]);
ind.push_back(Face.mIndices[2]);
}
m_Entries[Index].Init(pos, tex, norm, ind);
}*/

void Mesh::InitMesh(uint MeshIndex,
	const aiMesh* paiMesh,
	vector<vec3>& Positions,
	vector<vec3>& Normals,
	vector<vec2>& TexCoords,
	vector<VertexBoneData>& Bones,
	vector<uint>& Indices)
{
	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

	// Populate the vertex attribute vectors
	for (uint i = 0; i < paiMesh->mNumVertices; i++) {
		const aiVector3D* pPos = &(paiMesh->mVertices[i]);
		const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
		const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

		Positions.push_back(vec3(pPos->x, pPos->y, pPos->z));
		Normals.push_back(vec3(pNormal->x, pNormal->y, pNormal->z));
		TexCoords.push_back(vec2(pTexCoord->x, pTexCoord->y));
	}

	LoadBones(MeshIndex, paiMesh, Bones);

	// Populate the index buffer
	for (uint i = 0; i < paiMesh->mNumFaces; i++) {
		const aiFace& Face = paiMesh->mFaces[i];
		assert(Face.mNumIndices == 3);
		Indices.push_back(Face.mIndices[0]);
		Indices.push_back(Face.mIndices[1]);
		Indices.push_back(Face.mIndices[2]);
	}
}


void Mesh::LoadBones(uint MeshIndex, const aiMesh* pMesh, vector<VertexBoneData>& Bones)
{
	for (uint i = 0; i < pMesh->mNumBones; i++) {
		uint BoneIndex = 0;
		string BoneName(pMesh->mBones[i]->mName.data);

		if (m_BoneMapping.find(node_map[BoneName]) == m_BoneMapping.end()) {
			// Allocate an index for a new bone
			BoneIndex = m_NumBones;
			m_NumBones++;
			BoneInfo bi;
			m_BoneInfo.push_back(bi);
			//m_BoneInfo[BoneIndex].BoneOffset = pMesh->mBones[i]->mOffsetMatrix;
			CopyaiMat4x4(&pMesh->mBones[i]->mOffsetMatrix, m_BoneInfo[BoneIndex].BoneOffset);
			m_BoneMapping[node_map[BoneName]] = BoneIndex;
		}
		else {
			assert(false);
			BoneIndex = m_BoneMapping[node_map[BoneName]];
		}

		for (uint j = 0; j < pMesh->mBones[i]->mNumWeights; j++) {
			uint VertexID = m_Entries[MeshIndex].BaseVertex + pMesh->mBones[i]->mWeights[j].mVertexId;
			float Weight = pMesh->mBones[i]->mWeights[j].mWeight;
			Bones[VertexID].AddBoneData(BoneIndex, Weight);
		}
	}
}

bool Mesh::InitMaterials(const aiScene* pScene, const std::string& Filename)
{
	// Extract the directory part from the file name
	std::string::size_type SlashIndex = Filename.find_last_of("/");
	std::string Dir;

	if (SlashIndex == std::string::npos) {
		Dir = ".";
	}
	else if (SlashIndex == 0) {
		Dir = "/";
	}
	else {
		Dir = Filename.substr(0, SlashIndex);
	}

	bool Ret = true;

	// Initialize the materials
	for (unsigned int i = 0; i < pScene->mNumMaterials; i++) {
		const aiMaterial* pMaterial = pScene->mMaterials[i];

		m_Textures[i] = NULL;

		if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
			aiString Path;
			//string kk(Path.data);
			//cout << "woerjiiweofjeo: " << kk << endl;

			if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
				string p(Path.data);

				//std::string FullPath = Dir + "/" + Path.data;
				//m_Textures[i] = new Texture(GL_TEXTURE_2D, FullPath.c_str(), "PNG");
				//std::cout << FullPath << endl;

				if (p.substr(0, 2) == ".\\") {
					p = p.substr(2, p.size() - 2);
				}
				
				string FullPath = Dir + "/" + p;
				string FixedPath = FullPath.substr(0, FullPath.find_last_of("."))+".png";

				//m_Textures[i] = new Texture(GL_TEXTURE_2D, FullPath.c_str());
				m_Textures[i] = new Texture(GL_TEXTURE_2D, FixedPath.c_str(), "PNG");

				//cout <<"woerjiiweofjeo: "<< FullPath.c_str() << endl;

				if (!m_Textures[i]->Load()) {
					printf("Error loading texture '%s'\n", FixedPath.c_str());
					delete m_Textures[i];
					m_Textures[i] = NULL;
					Ret = false;
				}
				else {
					printf("Loaded texture '%s'\n", FixedPath.c_str());
					printLoadingString(FixedPath);
				}
			}
		}

		// Load a white texture in case the model does not include its own texture
		if (!m_Textures[i]) {
			m_Textures[i] = new Texture(GL_TEXTURE_2D, "img/white.png", "PNG");

			Ret = m_Textures[i]->Load();
		}
	}

	return Ret;
}

void Mesh::setShader(GLSLProgram* s)
{
	shader = s;
	uniformLoc.push_back(shader->getUniformLoc("Projection"));
	uniformLoc.push_back(shader->getUniformLoc("View"));
	uniformLoc.push_back(shader->getUniformLoc("Model"));
	uniformLoc.push_back(shader->getUniformLoc("material.Shininess"));
	uniformLoc.push_back(shader->getUniformLoc("TexID"));
	uniformLoc.push_back(shader->getUniformLoc("shadowMap"));
	uniformLoc.push_back(shader->getUniformLoc("LightView"));
	uniformLoc.push_back(shader->getUniformLoc("LightProjection"));
	uniformLoc.push_back(shader->getUniformLoc("ScaleBias"));
	uniformLoc.push_back(shader->getUniformLoc("fog.maxDist"));
	uniformLoc.push_back(shader->getUniformLoc("fog.minDist"));
	uniformLoc.push_back(shader->getUniformLoc("fog.color"));
	uniformLoc.push_back(shader->getUniformLoc("fog.visibility"));
	uniformLoc.push_back(shader->getUniformLoc("fog.maxHeight"));
	uniformLoc.push_back(shader->getUniformLoc("fog.minHeight"));
	//uniformLoc.push_back(shader->getUniformLoc(""));
}

void Mesh::draw()
{
	shader->setUniform(uniformLoc[0], Projection);
	shader->setUniform(uniformLoc[1], View);
	shader->setUniform(uniformLoc[2], getModelM()*getRotation()*adjustM);
	shader->setUniform(uniformLoc[3], shininess);
	shader->setUniform(uniformLoc[4], 0);
	shader->setUniform(uniformLoc[5], shadowTex);
	shader->setUniform(uniformLoc[6], LightView);
	shader->setUniform(uniformLoc[7], LightProjection);
	shader->setUniform(uniformLoc[8], ScaleBias);
	shader->setUniform(uniformLoc[9], fog->maxDist);
	shader->setUniform(uniformLoc[10], fog->minDist);
	shader->setUniform(uniformLoc[11], fog->color);
	shader->setUniform(uniformLoc[12], fog->visibility);
	shader->setUniform(uniformLoc[13], fog->maxHeight);
	shader->setUniform(uniformLoc[14], fog->minHeight);
	//shader->setUniform(uniformLoc[], );
	for (uint i = 0; i < transforms.size(); i++){
		char Name[128];
		memset(Name, 0, sizeof(Name));
		SNPRINTF(Name, sizeof(Name), "gBones[%d]", i);
		shader->setUniform(Name, transforms[i]);
	}
	shader->use();

	glBindVertexArray(m_VAO);

	for (unsigned int i = 0; i < m_Entries.size(); i++) {
		const unsigned int MaterialIndex = m_Entries[i].MaterialIndex;

		assert(MaterialIndex < m_Textures.size());

		//		if (MaterialIndex < m_Textures.size() && m_Textures[MaterialIndex]) {
		//			m_Textures[MaterialIndex]->Bind(GL_TEXTURE0);
		//		}

		//		m_Entries[i].draw();

		if (m_Textures[MaterialIndex]) {
			m_Textures[MaterialIndex]->Bind(GL_TEXTURE0);
		}

		glDrawElementsBaseVertex(GL_TRIANGLES,
			m_Entries[i].NumIndices,
			GL_UNSIGNED_INT,
			(void*)(sizeof(uint)* m_Entries[i].BaseIndex),
			m_Entries[i].BaseVertex);
	}

	// Make sure the VAO is not changed from the outside    
	glBindVertexArray(0);
	glUseProgram(0);
}

void Mesh::draw(mat4& projection, mat4& view)
{
	shader->setUniform(uniformLoc[0], projection);
	shader->setUniform(uniformLoc[1], view);
	shader->setUniform(uniformLoc[2], getModelM()*getRotation()*adjustM);
	shader->setUniform(uniformLoc[3], shininess);
	shader->setUniform(uniformLoc[4], 0);
	shader->setUniform(uniformLoc[5], shadowTex);
	shader->setUniform(uniformLoc[6], LightView);
	shader->setUniform(uniformLoc[7], LightProjection);
	shader->setUniform(uniformLoc[8], ScaleBias);
	shader->setUniform(uniformLoc[9], fog->maxDist);
	shader->setUniform(uniformLoc[10], fog->minDist);
	shader->setUniform(uniformLoc[11], fog->color);
	shader->setUniform(uniformLoc[12], fog->visibility);
	shader->setUniform(uniformLoc[13], fog->maxHeight);
	shader->setUniform(uniformLoc[14], fog->minHeight);
	//shader->setUniform(uniformLoc[], );
	for (uint i = 0; i < transforms.size(); i++){
		char Name[128];
		memset(Name, 0, sizeof(Name));
		SNPRINTF(Name, sizeof(Name), "gBones[%d]", i);
		shader->setUniform(Name, transforms[i]);
	}
	shader->use();

	glBindVertexArray(m_VAO);

	for (unsigned int i = 0; i < m_Entries.size(); i++) {
		const unsigned int MaterialIndex = m_Entries[i].MaterialIndex;

		assert(MaterialIndex < m_Textures.size());

		//		if (MaterialIndex < m_Textures.size() && m_Textures[MaterialIndex]) {
		//			m_Textures[MaterialIndex]->Bind(GL_TEXTURE0);
		//		}

		//		m_Entries[i].draw();

		if (m_Textures[MaterialIndex]) {
			m_Textures[MaterialIndex]->Bind(GL_TEXTURE0);
		}

		glDrawElementsBaseVertex(GL_TRIANGLES,
			m_Entries[i].NumIndices,
			GL_UNSIGNED_INT,
			(void*)(sizeof(uint)* m_Entries[i].BaseIndex),
			m_Entries[i].BaseVertex);
	}

	// Make sure the VAO is not changed from the outside    
	glBindVertexArray(0);
	glUseProgram(0);
}

uint Mesh::FindPosition(double AnimationTime, const aiNodeAnim* pNodeAnim)
{
	for (uint i = 0; i < pNodeAnim->mNumPositionKeys - 1; i++) {
		if (AnimationTime < (double)pNodeAnim->mPositionKeys[i + 1].mTime) {
			return i;
		}
	}

	assert(0);

	return 0;
}


uint Mesh::FindRotation(double AnimationTime, const aiNodeAnim* pNodeAnim)
{
	assert(pNodeAnim->mNumRotationKeys > 0);

	for (uint i = 0; i < pNodeAnim->mNumRotationKeys - 1; i++) {
		if (AnimationTime < (double)pNodeAnim->mRotationKeys[i + 1].mTime) {
			return i;
		}
	}

	assert(0);

	return 0;
}


uint Mesh::FindScaling(double AnimationTime, const aiNodeAnim* pNodeAnim)
{

	assert(pNodeAnim->mNumScalingKeys > 0);

	for (uint i = 0; i < pNodeAnim->mNumScalingKeys - 1; i++) {
		if (AnimationTime < (double)pNodeAnim->mScalingKeys[i + 1].mTime) {
			return i;
		}
	}

	assert(0);

	return 0;
}


void Mesh::CalcInterpolatedPosition(aiVector3D& Out, double AnimationTime, const aiNodeAnim* pNodeAnim)
{
	if (pNodeAnim->mNumPositionKeys == 1) {
		Out = pNodeAnim->mPositionKeys[0].mValue;
		return;
	}

	uint PositionIndex = FindPosition(AnimationTime, pNodeAnim);
	uint NextPositionIndex = (PositionIndex + 1);
	assert(NextPositionIndex < pNodeAnim->mNumPositionKeys);
	float DeltaTime = (float)(pNodeAnim->mPositionKeys[NextPositionIndex].mTime - pNodeAnim->mPositionKeys[PositionIndex].mTime);
	double Factor = (AnimationTime - (double)pNodeAnim->mPositionKeys[PositionIndex].mTime) / DeltaTime;
	assert(Factor >= 0.0f && Factor <= 1.0f);
	const aiVector3D& Start = pNodeAnim->mPositionKeys[PositionIndex].mValue;
	const aiVector3D& End = pNodeAnim->mPositionKeys[NextPositionIndex].mValue;
	aiVector3D Delta = End - Start;
	Out = Start + (float)Factor * Delta;
}


void Mesh::CalcInterpolatedRotation(aiQuaternion& Out, double AnimationTime, const aiNodeAnim* pNodeAnim)
{
	// we need at least two values to interpolate...
	if (pNodeAnim->mNumRotationKeys == 1) {
		Out = pNodeAnim->mRotationKeys[0].mValue;
		return;
	}

	uint RotationIndex = FindRotation(AnimationTime, pNodeAnim);
	uint NextRotationIndex = (RotationIndex + 1);
	assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);
	float DeltaTime = (float)(pNodeAnim->mRotationKeys[NextRotationIndex].mTime - pNodeAnim->mRotationKeys[RotationIndex].mTime);
	double Factor = (AnimationTime - (double)pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
	assert(Factor >= 0.0f && Factor <= 1.0f);
	const aiQuaternion& StartRotationQ = pNodeAnim->mRotationKeys[RotationIndex].mValue;
	const aiQuaternion& EndRotationQ = pNodeAnim->mRotationKeys[NextRotationIndex].mValue;
	aiQuaternion::Interpolate(Out, StartRotationQ, EndRotationQ, Factor);
	Out = Out.Normalize();
}


void Mesh::CalcInterpolatedScaling(aiVector3D& Out, double AnimationTime, const aiNodeAnim* pNodeAnim)
{
	if (pNodeAnim->mNumScalingKeys == 1) {
		Out = pNodeAnim->mScalingKeys[0].mValue;
		return;
	}

	uint ScalingIndex = FindScaling(AnimationTime, pNodeAnim);
	uint NextScalingIndex = (ScalingIndex + 1);
	assert(NextScalingIndex < pNodeAnim->mNumScalingKeys);
	float DeltaTime = (float)(pNodeAnim->mScalingKeys[NextScalingIndex].mTime - pNodeAnim->mScalingKeys[ScalingIndex].mTime);
	double Factor = (AnimationTime - (double)pNodeAnim->mScalingKeys[ScalingIndex].mTime) / DeltaTime;
	assert(Factor >= 0.0f && Factor <= 1.0f);
	const aiVector3D& Start = pNodeAnim->mScalingKeys[ScalingIndex].mValue;
	const aiVector3D& End = pNodeAnim->mScalingKeys[NextScalingIndex].mValue;
	aiVector3D Delta = End - Start;
	Out = Start + (float)Factor * Delta;
}

void Mesh::ReadNodeHeirarchy(double AnimationTime, aiNode* pNode, const mat4& ParentTransform)
{
	const aiAnimation* pAnimation = m_pScene->mAnimations[0];

	mat4 NodeTransformation;
	CopyaiMat4x4c(&pNode->mTransformation, NodeTransformation);

	const aiNodeAnim* pNodeAnim = anim_map[pNode];

	if (pNodeAnim) {
		// Interpolate scaling and generate scaling transformation matrix
		aiVector3D Scaling;
		CalcInterpolatedScaling(Scaling, AnimationTime, pNodeAnim);
		mat4 ScalingM;;
		InitScaleTransform(Scaling.x, Scaling.y, Scaling.z, ScalingM);

		aiQuaternion RotationQ;
		CalcInterpolatedRotation(RotationQ, AnimationTime, pNodeAnim);
		mat4 RotationM;
		CopyaiMat3x3tf(&RotationQ.GetMatrix(), RotationM);

		aiVector3D Translation;
		CalcInterpolatedPosition(Translation, AnimationTime, pNodeAnim);
		mat4 TranslationM;
		InitTranslationTransform(Translation.x, Translation.y, Translation.z, TranslationM);

		NodeTransformation = TranslationM * RotationM * ScalingM;
	}

	mat4 GlobalTransformation = ParentTransform * NodeTransformation;

	if (m_BoneMapping.find(pNode) != m_BoneMapping.end()) {
		uint BoneIndex = m_BoneMapping[pNode];
		m_BoneInfo[BoneIndex].FinalTransformation = m_GlobalInverseTransform * GlobalTransformation * m_BoneInfo[BoneIndex].BoneOffset;
	}

	for (uint i = 0; i < pNode->mNumChildren; i++) {
		ReadNodeHeirarchy(AnimationTime, pNode->mChildren[i], GlobalTransformation);
	}
}


void Mesh::BoneTransform(double TimeInSeconds, vector<mat4>& Transforms)
{
	mat4 Identity = mat4(1.0);

	double TicksPerSecond = (double)(m_pScene->mAnimations[0]->mTicksPerSecond != 0 ? m_pScene->mAnimations[0]->mTicksPerSecond : 25.0f);
	double TimeInTicks = TimeInSeconds * TicksPerSecond;
	double AnimationTime = fmod(TimeInTicks, (double)m_pScene->mAnimations[0]->mDuration);

	ReadNodeHeirarchy(AnimationTime, m_pScene->mRootNode, Identity);

	Transforms.resize(m_NumBones);

	for (uint i = 0; i < m_NumBones; i++) {
		Transforms[i] = m_BoneInfo[i].FinalTransformation;
	}
}


const aiNodeAnim* Mesh::FindNodeAnim(const aiAnimation* pAnimation, const string NodeName)
{
	for (uint i = 0; i < pAnimation->mNumChannels; i++) {
		const aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];

		if (string(pNodeAnim->mNodeName.data) == NodeName) {
			return pNodeAnim;
		}
	}

	return NULL;
}