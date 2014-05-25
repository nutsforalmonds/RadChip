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
	//char *c;

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

class UI
{
public:
	UI(){

		//life bars
		life_back = new UI_Panel(x1_life, x2_life, y1_life, y2_life);
		life_back->setColor(vec3(1.0, 0.0, 0.0));
		life_back->setShader(sdrCtl.getShader("basic_2D"));
		//life_back->loadColorTex("img/UI_TEST.png", "PNG");
		life_back->setModelM(glm::scale(vec3(0.1, 0.01, 1.0))*glm::translate(vec3(0.0f, 50.0, -1.0f)));

		life_front = new UI_Panel(x1_life, x2_life, y1_life, y2_life);
		life_front->setColor(vec3(0.0, 1.0, 0.0));
		life_front->setShader(sdrCtl.getShader("basic_2D"));
		//life_front->loadColorTex("img/UI_TEST.png", "PNG");
		life_front->setModelM(glm::scale(vec3(0.1, 0.01, 1.0))*glm::translate(vec3(0.0f, 50.0f, -1.0f)));

		life_frame = new UI_Panel(x1_life, x2_life, y1_life, y2_life);
		life_frame->setColor(vec3(1.0, 0.0, 0.0));
		life_frame->setShader(sdrCtl.getShader("basic_2D"));
		life_frame->loadColorTex("img/UI_FRAME_NEW.png", "PNG");
		life_frame->setTex(true);
		life_frame->setModelM(glm::scale(vec3(0.1, 0.01, 1.0))*glm::translate(vec3(0.0f, 50.0, -1.0f)));

		//overheat bars
		heat_back = new UI_Panel(x1_heat, x2_heat, y1_heat, -1.0*(y2_heat));
		heat_back->setColor(vec3(1.0, 1.0, 1.0));
		heat_back->setShader(sdrCtl.getShader("basic_2D"));
		//heat_back->loadColorTex("img/UI_TEST.png", "PNG");
		heat_back->setModelM(glm::scale(vec3(0.01, 0.1, 1.0))*glm::translate(vec3(-75.0f, 0.0f, -1.0f)));

		heat_front = new UI_Panel(x1_heat, x2_heat, y1_heat, y2_heat);
		heat_front->setColor(vec3(0.0, 1.0, 0.0));
		heat_front->setShader(sdrCtl.getShader("basic_2D"));
		//heat_front->loadColorTex("img/UI_TEST.png", "PNG");
		heat_front->setModelM(glm::scale(vec3(0.005, 0.1, 1.0))*glm::translate(vec3(-150.0f, 0.0f, -1.0f)));

		heat_frame = new UI_Panel(x1_heat, x2_heat, y1_heat, -1.0*(y2_heat));
		heat_frame->setColor(vec3(1.0, 1.0, 1.0));
		heat_frame->setShader(sdrCtl.getShader("basic_2D"));
		heat_frame->loadColorTex("img/UI_FRAME_VERT.png", "PNG");
		heat_frame->setTex(true);
		heat_frame->setModelM(glm::scale(vec3(0.01, 0.1, 1.0))*glm::translate(vec3(-75.0f, 0.0f, -1.0f)));
		
	}
	~UI(){
		life_back->		~UI_Panel();
		life_front->	~UI_Panel();
		life_frame->	~UI_Panel();
		heat_back->		~UI_Panel();
		heat_front->	~UI_Panel();
		heat_frame->	~UI_Panel();
	}

	int draw(){

		//Status Bars
		if (less_life)
		{
			healthBar(damage_taken);
			less_life = 0;
		}

		life_back->draw();
		life_front->draw();
		life_frame->draw();

		overheatBar(shots, overheat, 2);

		heat_back->draw();
		heat_front->draw();
		heat_frame->draw();

		return 0;
	}

	int healthBar(float damage){

		life_front->UI_Panel::~UI_Panel();

		x2_life = x2_life - health_bar_size*damage;

		if (x2_life <= x1_life)
		{
			x2_life = x1_life;
		}

		life_front = new UI_Panel(x1_life, x2_life, y1_life, y2_life);
		life_front->setColor(vec3(0.0, 1.0, 0.0));
		life_front->setShader(sdrCtl.getShader("basic_2D"));
		//life_front->loadColorTex("img/UI_TEST.png", "PNG");
		life_front->setModelM(glm::scale(vec3(0.1, 0.01, 1.0))*glm::translate(vec3(0.0f, 50.0f, -1.0f)));

		return 0;

	}

	int overheatBar(int fired, int hot, int style){

		//style will state what class character is meele or range 1 been meele, more cases can be added later
		if (style == 1)
		{
			if (lock == 0)
			{
				heat_back->UI_Panel::~UI_Panel();
				heat_front->UI_Panel::~UI_Panel();
				lock = 1;
			}
		}

		else
		{
			if (fired == 1 && hot == 0)
			{
				heat_front->UI_Panel::~UI_Panel();

				y2_heat = y2_heat + ((heat_bar_size) / 7.0); //# of shots

				if (y2_heat >= 2.0)
				{
					y2_heat = 2;
					overheat = 1;
				}

				heat_front = new UI_Panel(x1_heat, x2_heat, y1_heat, y2_heat);
				heat_front->setColor(vec3(0.0, 1.0, 0.0));
				heat_front->setShader(sdrCtl.getShader("basic_2D"));
				//heat_front->loadColorTex("img/UI_TEST.png", "PNG");
				heat_front->setModelM(glm::scale(vec3(0.005, 0.1, 1.0))*glm::translate(vec3(-150.0f, 0.0f, -1.0f)));

				over_de = clock();
				shots = 0;
			}


			else if (fired == 0 && hot == 0)
			{
				heat_front->UI_Panel::~UI_Panel();

				if (y2_heat > y1_heat && (clock() - over_de) / (float)CLOCKS_PER_SEC > 0.05)
				{
					y2_heat = y2_heat - ((heat_bar_size) / 60.0);
					over_de = clock();
				}

				if (y2_heat <= y1_heat)
				{
					y2_heat = y1_heat;
				}

				heat_front = new UI_Panel(x1_heat, x2_heat, y1_heat, y2_heat);
				heat_front->setColor(vec3(0.0, 1.0, 0.0));
				heat_front->setShader(sdrCtl.getShader("basic_2D"));
				//heat_front->loadColorTex("img/UI_TEST.png", "PNG");
				heat_front->setModelM(glm::scale(vec3(0.005, 0.1, 1.0))*glm::translate(vec3(-150.0f, 0.0f, -1.0f)));
			}

			else if (hot == 1)
			{
				heat_front->UI_Panel::~UI_Panel();

				if ((clock() - over_de) / (float)CLOCKS_PER_SEC > 0.05)
				{
					y2_heat = y2_heat - ((heat_bar_size) / 60.0);
					over_de = clock();
				}

				if (y2_heat < y1_heat)
				{
					y2_heat = y1_heat;
					overheat = 0;
				}

				heat_front = new UI_Panel(x1_heat, x2_heat, y1_heat, y2_heat);
				heat_front->setColor(vec3(1.0, 0.0, 0.0));
				heat_front->setShader(sdrCtl.getShader("basic_2D"));
				//heat_front->loadColorTex("img/UI_TEST.png", "PNG");
				heat_front->setModelM(glm::scale(vec3(0.005, 0.1, 1.0))*glm::translate(vec3(-150.0f, 0.0f, -1.0f)));

			}
		}

		return 0;
	}

	float getLess_Life(){ return less_life; }
	void setLess_Life(float l){ less_life = l; }

	float getShots(){ return shots; }
	void setShots(float s){ shots = s; }

private:

	UI_Panel* life_back;
	UI_Panel* life_front;
	UI_Panel* life_frame;
	UI_Panel* heat_back;
	UI_Panel* heat_front;
	UI_Panel* heat_frame;

	float x1_life = -2.0; //life
	float x2_life = 2.0;
	float y1_life = -2.0;
	float y2_life = 2.0;

	float x1_heat = -2.0; // overheat bar
	float x2_heat = 2.0;
	float y1_heat = -2.0;
	float y2_heat = -2.0;

	int lock = 0;

	float less_life = 0;
	float overheat = 0;
	float shots = 0;
	float damage_taken = (float)0.1; //set to default 1/7 of the life bar
	float health_bar_size = x2_life - x1_life;
	float heat_bar_size = x2_heat - x1_heat;

	time_t over_de; //rate of decay of overheat bar

};


class MainMenu
{
public:
	MainMenu(){
		menu = new UI_Panel(-1, 1, -1, 1);
		menu->setColor(vec3(1.0, 0.0, 0.0));
		menu->setShader(sdrCtl.getShader("basic_2D"));
		menu->loadColorTex("img/back", "PNG");
		menu->setTex(true);
		menu->setModelM(glm::scale(vec3(0.90, 0.50, 1.0))*glm::translate(vec3(0.0f, 0.0, -1.0f)));

		game_name = new UI_Panel(-1, 1, -1, 1);
		game_name->setColor(vec3(1.0, 0.0, 0.0));
		game_name->setShader(sdrCtl.getShader("basic_2D"));
		game_name->loadColorTex("img/team4", "PNG");
		game_name->setTex(true);
		game_name->setModelM(glm::scale(vec3(0.5, 0.05, 1.0))*glm::translate(vec3(0.0f, 9.0, -1.0f)));

		start_button = new UI_Panel(-1, 1, -1, 1);
		start_button->setColor(vec3(1.0, 0.0, 0.0));
		start_button->setShader(sdrCtl.getShader("basic_2D"));
		start_button->loadColorTex("img/UI_elements/button_stainlessSteel_StartOFF_1.png", "PNG");
		start_button->setTex(true);
		start_button->setModelM(glm::scale(vec3(0.15, 0.05, 1.0))*glm::translate(vec3(0.0f, 2.0, -1.0f)));

		exit_button = new UI_Panel(-1, 1, -1, 1);
		exit_button->setColor(vec3(1.0, 0.0, 0.0));
		exit_button->setShader(sdrCtl.getShader("basic_2D"));
		exit_button->loadColorTex("img/UI_elements/button_stainlessSteel_ExitOFF_1.png", "PNG");
		exit_button->setTex(true);
		exit_button->setModelM(glm::scale(vec3(0.15, 0.05, 1.0))*glm::translate(vec3(0.0f, -6.0, -1.0f)));

		setting_button = new UI_Panel(-1, 1, -1, 1);
		setting_button->setColor(vec3(1.0, 0.0, 0.0));
		setting_button->setShader(sdrCtl.getShader("basic_2D"));
		setting_button->loadColorTex("img/UI_elements/button_stainlessSteel_SettingsOFF.png", "PNG");
		setting_button->setTex(true);
		setting_button->setModelM(glm::scale(vec3(0.15, 0.05, 1.0))*glm::translate(vec3(0.0f, -2.0, -1.0f)));

		selected_start_button = new UI_Panel(-1, 1, -1, 1);
		selected_start_button->setColor(vec3(1.0, 0.0, 0.0));
		selected_start_button->setShader(sdrCtl.getShader("basic_2D"));
		selected_start_button->loadColorTex("img/UI_elements/button_stainlessSteel_StartON_1.png", "PNG");
		selected_start_button->setTex(true);
		selected_start_button->setModelM(glm::scale(vec3(0.15, 0.05, 1.0))*glm::translate(vec3(0.0f, 2.0, -1.0f)));

		selected_end_button = new UI_Panel(-1, 1, -1, 1);
		selected_end_button->setColor(vec3(1.0, 0.0, 0.0));
		selected_end_button->setShader(sdrCtl.getShader("basic_2D"));
		selected_end_button->loadColorTex("img/UI_elements/button_stainlessSteel_ExitON.png", "PNG");
		selected_end_button->setTex(true);
		selected_end_button->setModelM(glm::scale(vec3(0.15, 0.05, 1.0))*glm::translate(vec3(0.0f, -6.0, -1.0f)));

		selected_setting_button = new UI_Panel(-1, 1, -1, 1);
		selected_setting_button->setColor(vec3(1.0, 0.0, 0.0));
		selected_setting_button->setShader(sdrCtl.getShader("basic_2D"));
		selected_setting_button->loadColorTex("img/UI_elements/button_stainlessSteel_SettingsON.png", "PNG");
		selected_setting_button->setTex(true);
		selected_setting_button->setModelM(glm::scale(vec3(0.15, 0.05, 1.0))*glm::translate(vec3(0.0f, -2.0, -1.0f)));
	}
	~MainMenu(){
		menu->					  ~UI_Panel();
		game_name->				  ~UI_Panel();
		start_button->			  ~UI_Panel();
		exit_button->			  ~UI_Panel();
		setting_button->          ~UI_Panel();
		selected_start_button->	  ~UI_Panel();
		selected_end_button->	  ~UI_Panel();
		selected_setting_button-> ~UI_Panel();

	}

	int draw(){

		glDisable(GL_DEPTH_TEST);

		menu->draw();
		game_name->draw();
		start_button->draw();
		exit_button->draw();
		setting_button->draw();
		
		if (drawStartHighlight){
			selected_start_button->draw();
		}

		if (drawEndHighlight){
			selected_end_button->draw();
		}

		if (drawSettingHighlight){
			selected_setting_button->draw();
		}

		glEnable(GL_DEPTH_TEST);

		return 0;
	}

	int checkHighlight(float x, float y){

		//Check the x bounds first cause all buttons are the same width
		if ((x > 0.42) && (x < 0.57)){

			//Spot for first button
			if ((y > 0.35) && (y < 0.47)){
				drawStartHighlight = true;
				drawEndHighlight = false;
				drawSettingHighlight = false;
				
				return 1;
				//cout << "Start Monica!" << endl;
			}

			//Spot for second button
			else if ((y > 0.53) && (y < 0.64)){
				drawSettingHighlight = true;
				drawEndHighlight = false;
				drawStartHighlight = false;

				return 1;
				//cout << "End Monica!" << endl;
			}
			
			//Spot for third button
			else if ((y > 0.71) && (y < 0.81))
			{
				drawEndHighlight = true;
				drawStartHighlight = false;
				drawSettingHighlight = false;

				return 1;
			}

			else{
				drawStartHighlight = false;
				drawEndHighlight = false;
				drawSettingHighlight = false;

				return 0;
			}
		}
		else{
			drawStartHighlight = false;
			drawEndHighlight = false;
			drawSettingHighlight = false;

			return 0;
		}
	}

	int checkClick(float x, float y){

		//Check the x bounds first cause all buttons are the same width
		if ((x > 0.42) && (x < 0.57)){

			//Spot for first button
			if ((y > 0.35) && (y < 0.47)){
				return 1;
			}

			//Spot for second button
			else if ((y > 0.53) && (y < 0.64)){
				return 0;
			}

			else if ((y > 0.71) && (y < 0.81))
			{
				return 2;
			}

			return 0;
		}

		return 0;
	}

private:

	UI_Panel * menu;
	UI_Panel * game_name;
	UI_Panel * start_button;
	UI_Panel * exit_button;
	UI_Panel * setting_button;
	UI_Panel * selected_start_button;
	UI_Panel * selected_end_button;
	UI_Panel * selected_setting_button;

	bool drawStartHighlight = false;
	bool drawEndHighlight = false;
	bool drawSettingHighlight = false;
};

class GameMenu
{
public:
	GameMenu(){


		quit = new UI_Panel(-1, 1, -1, 1);
		quit->setColor(vec3(1.0, 0.0, 0.0));
		quit->setShader(sdrCtl.getShader("basic_2D"));
		quit->loadColorTex("img/UI_elements/button_stainlessSteel_QuitOFF.png", "PNG");
		quit->setTex(true);
		quit->setModelM(glm::scale(vec3(0.15, 0.05, 1.0))*glm::translate(vec3(-2.0f, 0.0, -1.0f)));

		resume = new UI_Panel(-1, 1, -1, 1);
		resume->setColor(vec3(1.0, 0.0, 0.0));
		resume->setShader(sdrCtl.getShader("basic_2D"));
		resume->loadColorTex("img/UI_elements/button_stainlessSteel_ResumeOFF.png", "PNG");
		resume->setTex(true);
		resume->setModelM(glm::scale(vec3(0.15, 0.05, 1.0))*glm::translate(vec3(2.0f, 0.0, -1.0f)));

		selected_resume = new UI_Panel(-1, 1, -1, 1);
		selected_resume->setColor(vec3(1.0, 0.0, 0.0));
		selected_resume->setShader(sdrCtl.getShader("basic_2D"));
		selected_resume->loadColorTex("img/UI_elements/button_stainlessSteel_ResumeON.png", "PNG");
		selected_resume->setTex(true);
		selected_resume->setModelM(glm::scale(vec3(0.15, 0.05, 1.0))*glm::translate(vec3(2.0f, 0.0, -1.0f)));

		selected_quit = new UI_Panel(-1, 1, -1, 1);
		selected_quit->setColor(vec3(1.0, 0.0, 0.0));
		selected_quit->setShader(sdrCtl.getShader("basic_2D"));
		selected_quit->loadColorTex("img/UI_elements/button_stainlessSteel_QuitON.png", "PNG");
		selected_quit->setTex(true);
		selected_quit->setModelM(glm::scale(vec3(0.15, 0.05, 1.0))*glm::translate(vec3(-2.0f, 0.0, -1.0f)));


		frame = new UI_Panel(-1, 1, -1, 1);
		frame->setColor(vec3(1.0, 1.0, 1.0));
		frame->setShader(sdrCtl.getShader("basic_2D"));
		frame->loadColorTex("img/game_menu_back.png", "PNG");
		frame->setTex(true);
		frame->setModelM(glm::scale(vec3(0.5, 0.25, 1.0))*glm::translate(vec3(0.0f, 0.0, -1.0f)));

	}
	~GameMenu(){

		resume->			~UI_Panel();
		quit->				~UI_Panel();
		selected_resume->	~UI_Panel();
		selected_quit->		~UI_Panel();
		frame->				~UI_Panel();
	}

	int draw(){
		glDisable(GL_DEPTH_TEST);

		frame->draw();
		resume->draw();
		quit->draw();

		if (drawStartHighlight){
			selected_resume->draw();
		}

		if (drawEndHighlight){
			selected_quit->draw();
		}

		glEnable(GL_DEPTH_TEST);
		return 0;
	}

	int checkHighlight(float x, float y){

		//Check the x bounds first cause all buttons are the same width
		if ((y > 0.46) && (y < 0.53)){

			//Spot for first button
			if ((x > 0.58) && (x < 0.73)){
				drawStartHighlight = true;
				drawEndHighlight = false;

				return 1;
				//cout << "Start Monica!" << endl;
			}

			//Spot for second button
			else if ((x > 0.26) && (x < 0.41)){
				drawEndHighlight = true;
				drawStartHighlight = false;

				return 1;
				//cout << "End Monica!" << endl;
			}
			else{
				drawStartHighlight = false;
				drawEndHighlight = false;

				return 0;
			}
		}
		else{
			drawStartHighlight = false;
			drawEndHighlight = false;

			return 0;
		}
	}

	int checkClick(float x, float y){

		//Check the x bounds first cause all buttons are the same width
		if ((y > 0.46) && (y < 0.53)){

			//Spot for first button
			if ((x > 0.58) && (x < 0.73)){
				return 1;
			}

			//Spot for second button
			else if ((x > 0.26) && (x < 0.41)){
				return 2;
			}

			return 0;
		}

		return 0;
	}

private:

	float highlightTrans = 0;

	UI_Panel * resume;
	UI_Panel * quit;
	UI_Panel * selected_resume;
	UI_Panel * selected_quit;
	UI_Panel * frame;

	bool drawStartHighlight;
	bool drawEndHighlight;
};

class DeathScreen
{
public:
	DeathScreen(){


	}
	~DeathScreen(){

	

	}

	int draw(){


		return 0;
	}

	void checkHighlight(float x, float y){

		//Check the x bounds first cause all buttons are the same width
		if ((x > 0.2) && (x < 0.8)){

			//Spot for first button
			if ((y > 0.2) && (y < 0.8)){

			}

			//Spot for second button
			if ((y > 0.2) && (y < 0.8)){

			}
		}
	}

	void checkClick(float x, float y){

		//Check the x bounds first cause all buttons are the same width
		if ((x > 0.2) && (x < 0.8)){

			//Spot for first button
			if ((y > 0.2) && (y < 0.8)){

			}

			//Spot for second button
			if ((y > 0.2) && (y < 0.8)){

			}
		}
	}

private:
	float highlightTrans = 0;
};

class Logo
{
public:
	Logo()
	{
		logo = new UI_Panel(-1, 1, -1, 1);
		logo->setColor(vec3(1.0, 0.0, 0.0));
		logo->setShader(sdrCtl.getShader("basic_2D"));
		logo->loadColorTex("img/UI_elements/logoB", "PNG");
		logo->setTex(true);
		logo->setModelM(glm::scale(vec3(0.1, 0.1, 1.0))*glm::translate(vec3(0.0f, -4.5, -1.0f)));
	}
	~Logo()
	{
		logo-> ~UI_Panel();
	}
	int draw()
	{
		glDisable(GL_DEPTH_TEST);

		logo->draw();

		glEnable(GL_DEPTH_TEST);

		return 0;
	}
private:
	UI_Panel * logo;
};