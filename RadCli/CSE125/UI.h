#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::mat3;


void glWindowPos4fMESAemulate(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	GLfloat fx, fy;
	/* Push current matrix mode and viewport attributes. */

	glPushAttrib(GL_TRANSFORM_BIT | GL_VIEWPORT_BIT);
	/* Setup projection parameters. */

	glMatrixMode(GL_PROJECTION);

	glPushMatrix();

	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();

	glLoadIdentity();

	glDepthRange(z, z);

	glViewport((int)x - 1, (int)y - 1, 2, 2);

	/* Set the raster (window) position. */

	fx = x - (int)x;

	fy = y - (int)y;

	glRasterPos4f(fx, fy, 0.0, w);

	/* Restore matrices, viewport and matrix mode. */

	glPopMatrix();

	glMatrixMode(GL_PROJECTION);

	glPopMatrix();

	glPopAttrib();

}
void
glWindowPos2fMESAemulate(GLfloat x, GLfloat y)

{

	glWindowPos4fMESAemulate(x, y, 0, 1);

}

// (0,0) is the bottom left of the window regardless of size
void RenderString(float x, float y, void *font, const unsigned char* string, vec3 const& rgb)
{
	char *c;

	glColor3f(rgb.r, rgb.g, rgb.b);
	//glColor4f(0.0f, 0.0f, 1.0f, 1.0f);

	//glVertex2i(x, y);
	//glRasterPos2f(x, y);
	glWindowPos2fMESAemulate(x, y);

	glutBitmapString(font, string);
}

class UI_Panel : public Object
{
public:
	UI_Panel(void){
		generate(-0.5, 0.5, -0.5, 0.5, -0.5, 0.5);
		setModelM(mat4(1.0));
		jumpVelocity = 0;
		vao.generate();
		vao.addAttrib(GL_ARRAY_BUFFER, 72 * sizeof(float), &vertex_positions, GL_STATIC_DRAW, 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
		vao.addAttrib(GL_ARRAY_BUFFER, 72 * sizeof(float), &vertex_normals, GL_STATIC_DRAW, 1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
		vao.setDrawMode(GL_TRIANGLES, 36, GL_UNSIGNED_INT, &triangle_indices);
	}
	UI_Panel(float negx, float posx, float negy, float posy, float negz, float posz){
		generate(negx, posx, negy, posy, negz, posz);
		setModelM(mat4(1.0));
		jumpVelocity = 0;
		vao.generate();
		vao.addAttrib(GL_ARRAY_BUFFER, 72 * sizeof(float), &vertex_positions, GL_STATIC_DRAW, 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
		vao.addAttrib(GL_ARRAY_BUFFER, 72 * sizeof(float), &vertex_normals, GL_STATIC_DRAW, 1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
		vao.setDrawMode(GL_TRIANGLES, 36, GL_UNSIGNED_INT, &triangle_indices);
	}
	~UI_Panel(void){}
	void draw(){
		shader->setUniform(uniformLoc[0], View);
		shader->setUniform(uniformLoc[1], Projection);
		shader->setUniform(uniformLoc[2], getModelM());
		shader->setUniform(uniformLoc[3], Projection*View*getModelM());
		shader->setUniform(uniformLoc[4], material.Kd);
		shader->setUniform(uniformLoc[5], material.Ka);
		shader->setUniform(uniformLoc[6], material.Ks);
		shader->setUniform(uniformLoc[7], material.Shininess);
		shader->setUniform(uniformLoc[8], material.ReflectFactor);
		shader->setUniform(uniformLoc[9], material.Eta);
		shader->setUniform(uniformLoc[10], CubeMapUnit);
		shader->setUniform(uniformLoc[11], color);
		shader->setUniform(uniformLoc[12], shadowTex);
		shader->setUniform(uniformLoc[13], LightView);
		shader->setUniform(uniformLoc[14], LightProjection);
		shader->setUniform(uniformLoc[15], ScaleBias);
		shader->use();
		vao.draw();
		glUseProgram(0);
	}
	void draw(mat4& projection, mat4& view){
		shader->setUniform(uniformLoc[0], view);
		shader->setUniform(uniformLoc[1], projection);
		shader->setUniform(uniformLoc[2], getModelM());
		shader->setUniform(uniformLoc[3], projection*view*getModelM());
		shader->setUniform(uniformLoc[4], material.Kd);
		shader->setUniform(uniformLoc[5], material.Ka);
		shader->setUniform(uniformLoc[6], material.Ks);
		shader->setUniform(uniformLoc[7], material.Shininess);
		shader->setUniform(uniformLoc[8], material.ReflectFactor);
		shader->setUniform(uniformLoc[9], material.Eta);
		shader->setUniform(uniformLoc[10], CubeMapUnit);
		shader->setUniform(uniformLoc[11], color);
		shader->setUniform(uniformLoc[12], shadowTex);
		shader->setUniform(uniformLoc[13], LightView);
		shader->setUniform(uniformLoc[14], LightProjection);
		shader->setUniform(uniformLoc[15], ScaleBias);
		shader->use();
		vao.draw();
		glUseProgram(0);
	}
	void setShader(GLSLProgram* shader){
		this->shader = shader;
		uniformLoc.push_back(shader->getUniformLoc("ViewMatrix"));
		uniformLoc.push_back(shader->getUniformLoc("ProjectionMatrix"));
		uniformLoc.push_back(shader->getUniformLoc("ModelMatrix"));
		uniformLoc.push_back(shader->getUniformLoc("MVP"));
		uniformLoc.push_back(shader->getUniformLoc("material.Kd"));
		uniformLoc.push_back(shader->getUniformLoc("material.Ka"));
		uniformLoc.push_back(shader->getUniformLoc("material.Ks"));
		uniformLoc.push_back(shader->getUniformLoc("material.Shininess"));
		uniformLoc.push_back(shader->getUniformLoc("material.ReflectFactor"));
		uniformLoc.push_back(shader->getUniformLoc("material.Eta"));
		uniformLoc.push_back(shader->getUniformLoc("CubeMapTex"));
		uniformLoc.push_back(shader->getUniformLoc("color"));
		uniformLoc.push_back(shader->getUniformLoc("shadowMap"));
		uniformLoc.push_back(shader->getUniformLoc("LightView"));
		uniformLoc.push_back(shader->getUniformLoc("LightProjection"));
		uniformLoc.push_back(shader->getUniformLoc("ScaleBias"));
	}
	void setKd(vec3 v){ material.Kd = v; }
	vec3 getKd(){ return material.Kd; }
	void setKa(vec3 v){ material.Ka = v; }
	vec3 getKa(){ return material.Ka; }
	void setKs(vec3 v){ material.Ks = v; }
	vec3 getKs(){ return material.Ks; }
	void setShininess(float f){ material.Shininess = f; }
	float getShininess(){ return material.Shininess; }
	void setReflectFactor(vec2 v){ material.ReflectFactor = v; }
	vec2 getReflectFactor(){ return material.ReflectFactor; }
	void setEta(float f){ material.Eta = f; }
	float getEta(){ return material.Eta; }
	void setCubeMapUnit(int u){ CubeMapUnit = u; }
	int getCubeMapUnit(){ return CubeMapUnit; }
	void setColor(vec3 c){ color = c; }

	void physicsSimulation(float time, float substep){
		if ((modelM*vec4(0, -0.5, 0, 1))[1] == 0.0 && jumpVelocity == 0)
			return;
		while (time > substep)
		{
			time -= substep;
			float dy = jumpVelocity*substep;
			jumpVelocity -= 9.8*substep;
			preTrans(glm::translate(vec3(0, dy, 0)));
			if ((modelM*vec4(0, -0.5, 0, 1))[1] < 0.0){
				preTrans(glm::translate(vec3(0, -(modelM*vec4(0, -0.5, 0, 1))[1], 0)));
				jumpVelocity = 0;
				return;
			}
		}
		float dy = jumpVelocity*time;
		jumpVelocity -= 9.8*time;
		preTrans(glm::translate(vec3(0, dy, 0)));
		if ((modelM*vec4(0, -0.5, 0, 1))[1] < 0.0){
			preTrans(glm::translate(vec3(0, -(modelM*vec4(0, -0.5, 0, 1))[1], 0)));
			jumpVelocity = 0;
			return;
		}
	}
	void setShadowTex(int t){ shadowTex = t; }
private:
	void generate(float negx, float posx, float negy, float posy, float negz, float posz){
		std::array<float, 72> positions = {
			negx, posy, posz, negx, posy, posz, negx, posy, posz,  //ftl
			negx, negy, posz, negx, negy, posz, negx, negy, posz,  //fbl
			posx, negy, posz, posx, negy, posz, posx, negy, posz,  //fbr
			posx, posy, posz, posx, posy, posz, posx, posy, posz,  //ftr
			negx, posy, negz, negx, posy, negz, negx, posy, negz,  //btl
			negx, negy, negz, negx, negy, negz, negx, negy, negz,  //bbl
			posx, negy, negz, posx, negy, negz, posx, negy, negz,  //bbr
			posx, posy, negz, posx, posy, negz, posx, posy, negz }; //btr

		std::array<float, 72> normals = {
			0, 0, 1, 0, 1, 0, -1, 0, 0,   //  0: 1A,  1: 1B,  2: 1D
			0, 0, 1, 0, -1, 0, -1, 0, 0,   //  3: 2A,  4: 2E,  5: 2D
			0, 0, 1, 0, -1, 0, 1, 0, 0,   //  6: 3A,  7: 3E,  8: 3C
			0, 0, 1, 0, 1, 0, 1, 0, 0,	//  9: 4A, 10: 4B, 11: 4C
			0, 0, -1, 0, 1, 0, -1, 0, 0,   // 12: 5F, 13: 5B, 14: 5D
			0, 0, -1, 0, -1, 0, -1, 0, 0,   // 15: 6F, 16: 6E, 17: 6D
			0, 0, -1, 0, -1, 0, 1, 0, 0,   // 18: 7F, 19: 7E, 20: 7C
			0, 0, -1, 0, 1, 0, 1, 0, 0 };  // 21: 8F, 22: 8B, 23: 8C

		std::array<int, 36> indices = {
			0, 3, 6, 0, 6, 9,      //front
			12, 18, 15, 12, 21, 18,   //back
			2, 14, 5, 17, 5, 14,    //left
			8, 23, 11, 8, 20, 23,    //right
			1, 22, 13, 1, 10, 22,    //top
			4, 16, 19, 4, 19, 7 };    //bottom
		vertex_positions = positions;
		vertex_normals = normals;
		triangle_indices = indices;
	}
	VAO vao;
	GLSLProgram * shader;
	Material material;
	std::array<float, 72> vertex_positions;
	std::array<float, 72> vertex_normals;
	std::array<int, 36> triangle_indices;
	int CubeMapUnit;
	vec3 color;
	int shadowTex;
	vector<int> uniformLoc;
};