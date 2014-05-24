#pragma once
#include "VAO.h"
#include "glslprogram.h"
#include <array>
#include "Texture.h"
#include <vector>
#include <iostream>
#include "Structures.h"
using namespace std;

extern mat4 Projection;
extern mat4 View;
extern mat4 LightView;
extern mat4 LightProjection;
extern mat4 ScaleBias;

double ground_positionsf[] ={-10,0,10,
	-10,0,-10,
	10,0,-10,
	10,0,10};	 
double ground_normalsf[] =  {0,1,0,
	0,1,0,
	0,1,0,
	0,1,0};
double ground_texCoordsf[] = {
	0, 0,
	0, 1,
	1, 1,
	1, 0
};
int ground_indicesf[] = {0,2,1,
	0,3,2};

class Ground: public Object
{
public:
	Ground(void){
	}
	~Ground(void){
		delete colorTex;
		delete normalTex;
		delete displacementTex;
		delete occlusionTex;
		delete specularTex;
	}
	void setShader(GLSLProgram* shader){
		this->shader=shader;
		uniformLoc.push_back(shader->getUniformLoc("ViewMatrix"));
		uniformLoc.push_back(shader->getUniformLoc("ProjectionMatrix"));
		uniformLoc.push_back(shader->getUniformLoc("ModelMatrix"));
		uniformLoc.push_back(shader->getUniformLoc("MVP"));
		uniformLoc.push_back(shader->getUniformLoc("dispHeight"));
		uniformLoc.push_back(shader->getUniformLoc("colorTex"));
		uniformLoc.push_back(shader->getUniformLoc("normalTex"));
		uniformLoc.push_back(shader->getUniformLoc("displacementTex"));
		uniformLoc.push_back(shader->getUniformLoc("occlusionTex"));
		uniformLoc.push_back(shader->getUniformLoc("specularTex"));
		uniformLoc.push_back(shader->getUniformLoc("shadowMap"));
		uniformLoc.push_back(shader->getUniformLoc("LightView"));
		uniformLoc.push_back(shader->getUniformLoc("LightProjection"));
		uniformLoc.push_back(shader->getUniformLoc("ScaleBias"));
		uniformLoc.push_back(shader->getUniformLoc("CamPos"));
		uniformLoc.push_back(shader->getUniformLoc("fog.maxDist"));
		uniformLoc.push_back(shader->getUniformLoc("fog.minDist"));
		uniformLoc.push_back(shader->getUniformLoc("fog.color"));
		uniformLoc.push_back(shader->getUniformLoc("fog.visibility"));
		uniformLoc.push_back(shader->getUniformLoc("fog.maxHeight"));
		uniformLoc.push_back(shader->getUniformLoc("fog.minHeight"));
		//uniformLoc.push_back(shader->getUniformLoc(""));
	}
	void draw(){
		shader->setUniform(uniformLoc[0], View);
		shader->setUniform(uniformLoc[1], Projection);
		shader->setUniform(uniformLoc[2], mat4(1.0));
		shader->setUniform(uniformLoc[3], Projection*View);
		shader->setUniform(uniformLoc[4], dispHeight);
		shader->setUniform(uniformLoc[5], 0);
		shader->setUniform(uniformLoc[6], 1);//vertex shader
		shader->setUniform(uniformLoc[7], 2);//vertex shader
		shader->setUniform(uniformLoc[8], 3);
		shader->setUniform(uniformLoc[9], 4);
		shader->setUniform(uniformLoc[10], shadowTex);
		shader->setUniform(uniformLoc[11], LightView);
		shader->setUniform(uniformLoc[12], LightProjection);
		shader->setUniform(uniformLoc[13], ScaleBias);
		shader->setUniform(uniformLoc[14], vec3(glm::inverse(View)*vec4(0, 0, 0, 1)));
		shader->setUniform(uniformLoc[15], fog->maxDist);
		shader->setUniform(uniformLoc[16], fog->minDist);
		shader->setUniform(uniformLoc[17], fog->color);
		shader->setUniform(uniformLoc[18], fog->visibility);
		shader->setUniform(uniformLoc[19], fog->maxHeight);
		shader->setUniform(uniformLoc[20], fog->minHeight);
		//shader->setUniform(uniformLoc[], );
		colorTex->Bind(GL_TEXTURE0);
		normalTex->Bind(GL_TEXTURE1);
		displacementTex->Bind(GL_TEXTURE2);
		occlusionTex->Bind(GL_TEXTURE3);
		specularTex->Bind(GL_TEXTURE4);
		shader->use();
		glPatchParameteri(GL_PATCH_VERTICES, 3);
		vao.draw();
		glUseProgram(0);
	}
	void draw(mat4& projection, mat4& view){
		shader->setUniform(uniformLoc[0], view);
		shader->setUniform(uniformLoc[1], projection);
		shader->setUniform(uniformLoc[2], mat4(1.0));
		shader->setUniform(uniformLoc[3], projection*view);
		shader->setUniform(uniformLoc[4], dispHeight);
		shader->setUniform(uniformLoc[5], 0);
		shader->setUniform(uniformLoc[6], 1);//vertex shader
		shader->setUniform(uniformLoc[7], 2);//vertex shader
		shader->setUniform(uniformLoc[8], 3);
		shader->setUniform(uniformLoc[9], 4);
		shader->setUniform(uniformLoc[10], shadowTex);
		shader->setUniform(uniformLoc[11], LightView);
		shader->setUniform(uniformLoc[12], LightProjection);
		shader->setUniform(uniformLoc[13], ScaleBias);
		shader->setUniform(uniformLoc[15], fog->maxDist);
		shader->setUniform(uniformLoc[16], fog->minDist);
		shader->setUniform(uniformLoc[17], fog->color);
		shader->setUniform(uniformLoc[19], fog->maxHeight);
		shader->setUniform(uniformLoc[20], fog->minHeight);
		//shader->setUniform(uniformLoc[], );
		colorTex->Bind(GL_TEXTURE0);
		normalTex->Bind(GL_TEXTURE1);
		displacementTex->Bind(GL_TEXTURE2);
		occlusionTex->Bind(GL_TEXTURE3);
		specularTex->Bind(GL_TEXTURE4);
		shader->use();
		glPatchParameteri(GL_PATCH_VERTICES, 3);
		vao.draw();
		glUseProgram(0);
	}
	void setKd(vec3 v){
		Kd=v;
	}
	void setKa(vec3 v){
		Ka=v;
	}
	void setKs(vec3 v){
		Ks=v;
	}
	void setShininess(float f){
		Shininess = f;
	}
	void setProjectorTex(int i){ProjectorTex=i;}
	void setProjectorMatrix(mat4 m){ProjectorMatrix=m;}
	void loadColorTex(const char* FileName, const char* FileType){
		colorTex = new Texture(GL_TEXTURE_2D, FileName, FileType);
		colorTex->Load();
	}
	void loadNormalTex(const char* FileName, const char* FileType){
		normalTex = new Texture(GL_TEXTURE_2D, FileName, FileType);
		normalTex->Load();
	}
	void loadDispTex(const char* FileName, const char* FileType){
		displacementTex = new Texture(GL_TEXTURE_2D, FileName, FileType);
		displacementTex->Load();

		displacementTex->Bind(GL_TEXTURE2);
		glActiveTexture(GL_TEXTURE2);

		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &DispW);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &DispH);

		DispIMG = new GLubyte[DispW*DispH*4];
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, DispIMG);
	}
	void loadOccTex(const char* FileName, const char* FileType){
		occlusionTex = new Texture(GL_TEXTURE_2D, FileName, FileType);
		occlusionTex->Load();
	}
	void loadSpecTex(const char* FileName, const char* FileType){
		specularTex = new Texture(GL_TEXTURE_2D, FileName, FileType);
		specularTex->Load();
	}
	void setDimensionS(float s){ dimensionS = s; }
	void setDimensionT(float t){ dimensionT = t; }
	void setRow(int r){ row = r; }
	void setColumn(int c){ column = c; }
	void generate(){
		float dispS = 2.0*dimensionS / (column - 1);
		float dispT = 2.0*dimensionT / (row - 1);

		for (int i = 0; i < row; i++){
			for (int k = 0; k < column; k++){
				ground_positions.push_back(k*dispS-dimensionS);
				ground_positions.push_back(0);
				ground_positions.push_back(i*dispT - dimensionT);

				ground_normals.push_back(0);
				ground_normals.push_back(1);
				ground_normals.push_back(0);

				ground_texCoords.push_back((double)k / (column - 1));
				ground_texCoords.push_back((double)(row - i - 1) / (row - 1));
			}
		}

		for (int i = 0; i < row - 1; i++){
			for (int k = 0; k < column - 1; k++){
				ground_indices.push_back(i*column+k);
				ground_indices.push_back((i+1)*column+k);
				ground_indices.push_back((i+1)*column+k+1);
				ground_indices.push_back(i*column+k);
				ground_indices.push_back((i+1)*column+k+1);
				ground_indices.push_back(i*column+k+1);
			}
		}

		vao.generate();
		vao.addAttrib(GL_ARRAY_BUFFER, ground_positions.size()*sizeof(double), &ground_positions[0], GL_STATIC_DRAW, 0, 3, GL_DOUBLE, GL_FALSE, 0, (GLubyte*)NULL);
		vao.addAttrib(GL_ARRAY_BUFFER, ground_normals.size()*sizeof(double), &ground_normals[0], GL_STATIC_DRAW, 1, 3, GL_DOUBLE, GL_FALSE, 0, (GLubyte*)NULL);
		vao.addAttrib(GL_ARRAY_BUFFER, ground_texCoords.size()* sizeof(double), &ground_texCoords[0], GL_STATIC_DRAW, 2, 2, GL_DOUBLE, GL_FALSE, 0, (GLubyte*)NULL);
		vao.setDrawMode(GL_PATCHES, ground_indices.size(), GL_UNSIGNED_INT, &ground_indices[0]);
	}

	float getDispY(float x, float z){
		GLint s = floor((x + dimensionS) / (2 * dimensionS)*DispW);
		GLint t = floor((z + dimensionT) / (2 * dimensionT)*DispH);
		if (s > DispW-1 || s<0 || t>DispH-1 || t < 0){
			return -1;
		}

		return (uint)(DispIMG[4 * ((DispH-1-t)*DispW + s)]) / 255.0 *dispHeight;
	}
	void setHeight(float f){ dispHeight = f; }
	void setShadowTex(int t){ shadowTex = t; }
	void setFog(Fog& f){ fog = &f; }

private:
	VAO vao;
	GLSLProgram * shader;
	vec3 Kd,Ka,Ks;
	float Shininess;
	int ProjectorTex;
	mat4 ProjectorMatrix;
	Texture * colorTex;
	Texture * normalTex;
	Texture * displacementTex;
	Texture * occlusionTex;
	Texture * specularTex;
	float dimensionS, dimensionT; //half dimension.
	int row, column;
	vector<double> ground_positions;
	vector<double> ground_normals;
	vector<double> ground_texCoords;
	vector<int> ground_indices;
	GLint DispW, DispH;
	GLubyte* DispIMG;
	float dispHeight;
	int shadowTex;
	vector<int> uniformLoc;
	Fog* fog;
};

