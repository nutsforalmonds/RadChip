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

void glWindowPos2fMESAemulate(GLfloat x, GLfloat y)
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
		texBool = 0;
		generate(-0.5, 0.5, -0.5, 0.5);
		setModelM(mat4(1.0));
		vao.generate();
		vao.addAttrib(GL_ARRAY_BUFFER, 8 * sizeof(float), &vertex_positions, GL_STATIC_DRAW, 0, 2, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
		vao.addAttrib(GL_ARRAY_BUFFER, 8 * sizeof(float), &tex_positions, GL_STATIC_DRAW, 1, 2, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
		vao.setDrawMode(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &triangle_indices);
	}
	UI_Panel(float negx, float posx, float negy, float posy){
		texBool = 0;
		generate(negx, posx, negy, posy);
		setModelM(mat4(1.0));
		vao.generate();
		vao.addAttrib(GL_ARRAY_BUFFER, 8 * sizeof(float), &vertex_positions, GL_STATIC_DRAW, 0, 2, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
		vao.addAttrib(GL_ARRAY_BUFFER, 8 * sizeof(float), &tex_positions, GL_STATIC_DRAW, 1, 2, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
		vao.setDrawMode(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &triangle_indices);
	}
	~UI_Panel(void){}
	void draw(){
		shader->setUniform(uniformLoc[0], View);
		shader->setUniform(uniformLoc[1], Projection);
		shader->setUniform(uniformLoc[2], getModelM());
		shader->setUniform(uniformLoc[3], Projection*View*getModelM());
		shader->setUniform(uniformLoc[4], color);
		shader->setUniform(uniformLoc[5], 0);
		shader->setUniform(uniformLoc[6], texBool);
		if (texBool == 1){
			colorTex->Bind(GL_TEXTURE0);
		}		
		shader->use();
		vao.draw();
		glUseProgram(0);
	}
	void draw(mat4& projection, mat4& view){
		shader->setUniform(uniformLoc[0], view);
		shader->setUniform(uniformLoc[1], projection);
		shader->setUniform(uniformLoc[2], getModelM());
		shader->setUniform(uniformLoc[3], projection*view*getModelM());
		shader->setUniform(uniformLoc[4], color);
		shader->setUniform(uniformLoc[5], 0);
		shader->setUniform(uniformLoc[6], texBool);
		if (texBool == 1){
			colorTex->Bind(GL_TEXTURE0);
		}
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
		uniformLoc.push_back(shader->getUniformLoc("color"));
		uniformLoc.push_back(shader->getUniformLoc("colorTex"));
		uniformLoc.push_back(shader->getUniformLoc("textureMeBaby"));
	}
	void setColor(vec3 c){ color = c; }
	
	void loadColorTex(const char* FileName, const char* FileType){
		colorTex = new Texture(GL_TEXTURE_2D, FileName, FileType);
		colorTex->Load();
	}

	void setTex(bool b){
		if (b){
			texBool = 1;
		}
		else{
			texBool = 0;
		}
	}
private:
	void generate(float negx, float posx, float negy, float posy){
		std::array<float, 8> positions = {negx, posy, negx, negy, posx, posy, posx, negy}; 
		std::array<float, 8> texCord = { 0, 1, 0, 0, 1, 1, 1, 0 };
		std::array<int, 6> indices = {0, 1, 2, 1, 2, 3};    
		vertex_positions = positions;
		tex_positions = texCord;
		triangle_indices = indices;
	}
	VAO vao;
	GLSLProgram * shader;
	std::array<float, 8> vertex_positions;
	std::array<float, 8> tex_positions;
	std::array<int, 6> triangle_indices;
	int CubeMapUnit;
	vec3 color;
	vector<int> uniformLoc;
	Texture * colorTex;
	int texBool;
};