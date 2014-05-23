#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <boost/asio.hpp>
#include "Client.h"
#include "Window.h"
#include <time.h>
#include <math.h>
#include "VAO.h"
#include "glslprogram.h"
#include "Cube.h"
#include "ShaderController.h"
#include "Ground.h"
#include "Projectile.h"
#include <Qt/QtGui/QImage> 
#include <Qt/QtOpenGL/QGLWidget>
#include "SkyBox.h"
#include "Structures.h"
#include "Sphere.h"
#include "TextureScreen.h"
#include "Camera.h"
#include "Scene.h"
#include "Mesh.h"
#include "Texture.h"
#include "ConfigSettings.h"
#include "Sound.h"
#include "MD5Model.h"
#include "JSON_Parse.h"
#include "billboard_list.h"
#include "UI.h"
#include "ClientState.h"

#include <assert.h>
#include "ParticleSystem.h"
ParticleSystem* particle;
ParticleSystem* particle2;
ParticleSystem* particle3;
ParticleSystem* particle4;
ParticleSystem* particle5;
ParticleSystem* particle6;
ParticleSystem* particle7;
long long m_currentTimeMillis;


enum {
	MENU_LIGHTING = 1,
	MENU_POLYMODE,
	MENU_TEXTURING,
	MENU_EXIT
};

typedef int BOOL;
#define TRUE 1
#define FALSE 0

static BOOL g_bLightingEnabled = TRUE;
static BOOL g_bFillPolygons = TRUE;
static BOOL g_bTexture = FALSE;
static BOOL g_bButton1Down = FALSE;

using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::mat3;
using glm::quat;
using namespace rapidjson;
using namespace std;

FMOD_SYSTEM      *fmodSystem;
FMOD_SOUND       *sound;
FMOD_CHANNEL     *channel = 0;
FMOD_RESULT       result;
int               key;
unsigned int      version;

std::vector<Object*> draw_list;
std::vector<Object*> player_list;
std::vector<Object*> stationary_list;
std::vector<Projectile*> projectile_list;
std::vector<Texture*> texture_list;
std::vector<Sound*> sound_list;
Sound* testSound[6];

BillboardList m_billboardList;
BillboardList m_billboardList2;
BillboardList m_billboardList3;
BillboardList m_billboardList4;

JSON_Parser *map_info;

int Window::width = 1280;   // set window width in pixels here
int Window::height = 720;   // set window height in pixels here
float nearClip = 0.1;
float farClip = 1000.0;
float fov = 55.0;

vec3 EyePoint = vec3(0,0,3);
vec3 CenterPoint = vec3(0,0,0);
mat4 Projection;
mat4 View = glm::lookAt(EyePoint,CenterPoint, vec3(0,1,0));
mat4 MVP;
mat4 LightView;
mat4 LightProjection;
mat4 ScaleBias = mat4(vec4(0.5, 0.0, 0.0, 0.0),
	vec4(0.0, 0.5, 0.0, 0.0),
	vec4(0.0, 0.0, 0.5, 0.0),
	vec4(0.5, 0.5, 0.5, 1.0));

//mat4 ScaleBias = mat4(vec4(0.5, 0.0, 0.0, 0.5),
//	vec4(0.0, 0.5, 0.0, 0.5),
//	vec4(0.0, 0.0, 0.5, 0.5),
//	vec4(0.0, 0.0, 0.0, 1.0));

ShaderController sdrCtl;

int oldX,oldY,mouseDown,mouseButton;

Light light[1];
Fog fog;
vec3 fogColor = vec3(0.9,0.9,0.9);

//Scene* scene;

Cube* cube;
Ground* ground;
SkyBox* skybox;
Sphere* sphere;
TextureScreen* texScreen;
int texScreenWidth = 512;
int texScreenHeight = 512;

Camera* cam;
float cam_sp = 0.1;
float cam_dx = 0;

GLuint fboHandle;
GLuint depth_fbo;
GLsizei depth_texture_width = 1024;
GLsizei depth_texture_height = 1024;
GLuint shadow_map_id = 10;//shadow map stored in GL_TEXTURE10

string configBuf;

//time used in idleCallback
LARGE_INTEGER freq, last, current, loop_begin, loop_end;
double delta;

//Mouse press flags
int left_mouse_up = 1;
int right_mouse_up = 1;
int middle_mouse_up = 1;
int space_up = 1;
int sprint_up = 10;

//bool keyState[4];//up,down,left,right

void keyboard(unsigned char key, int, int);
void keyUp (unsigned char key, int x, int y);
void trackballScale( int width, int height, int fromX, int fromY, int toX, int toY );
void trackballRotation( int width, int height, int fromX, int fromY, int toX, int toY );
void mouseFunc(int button, int state, int x, int y);
void motionFunc(int x, int y);
void passiveMotionFunc(int x, int y);
void specialKeyboardFunc(int key, int x, int y);

void updateShaders();
void setupShaders();
void initialize(int argc, char *argv[]);
void loadTextures();
int loadAudio();
void updateSound();

int counter = 0;

UI * myUI;
MainMenu * myMainMenu;
GameMenu * myGameMenu;
DeathScreen * myDeathScreen;

Texture * shadow;
char buf[255];
int myFPS = 0;

ClientState* myClientState;

// Stuff Erik added
int playerID = -1; // THIS USED TO BE 1 - it gets set by the server
int stateID = -1;
int keyState = 0;
int mouseState = 0;
int projectile_counter = 0;

std::vector <pair<string, mat4>>* sendVec = new vector<pair<string, mat4>>;
std::vector <pair<string, mat4>>* recvVec = new vector<pair<string, mat4>>;

boost::asio::io_service io_service;
tcp_client* cli;

boost::array<mat4, 4> mats;

bool running;
double diff;
int test = 0;
float test2 = 0;

bool connected;

void projectileAttack(int playerID, Camera * cam)
{
	mat4 test = cam->getCamM();
	vec4 holder = test*vec4(0, 0, -1, 0); //orientation of camera in object space
	mat4 player1 = player_list[playerID]->getModelM();
	vec4 playerHolder = player1*vec4(0, 0, 0, 1);

	Projectile* cubeT = new Projectile(player_list.size());
	cubeT->setKd(vec3(0.8, 0.0, 0.0));
	cubeT->setKa(vec3(0.3, 0.0, 0.0));
	cubeT->setKs(vec3(0.4, 0.0, 0.0));
	cubeT->setShininess(100);
	cubeT->setReflectFactor(vec2(0.2, 0.5));
	cubeT->setEta(0.5);
	cubeT->setCubeMapUnit(3);
	cubeT->setSpeed(5);
	cubeT->setShader(sdrCtl.getShader("basic_reflect_refract"));
	//cubeT->postTrans(glm::translate(vec3(playerHolder[0] -2 + ((holder[0]) / 4), playerHolder[1], playerHolder[2] - (holder[2] / 4))));
	cubeT->setModelM(player1*glm::translate(vec3(0, 1, 0)));//get the new cube matrix by translating the player0 matrix forward in player0 object space. This way the new matrix will inherit player0 oriantation 
	cubeT->setAABB(AABB(vec3(-0.5, -0.5, -0.5), vec3(0.5, 0.5, 0.5)));
	AABB hold = cubeT->getAABB();
	cubeT->setStartX(hold.max[0]);
	cubeT->setStartY(hold.max[2]);
	cubeT->setShadowTex(shadow_map_id);

	//Name and type
	cubeT->setType("Cube");
	cubeT->setName("Test Cube" + std::to_string(projectile_counter));
	projectile_counter++;
	//Add Cube to the draw list
	////////////////////////////////////////////////////////Window::addDrawList(cubeT);
	projectile_list.push_back(cubeT);
	cubeT->setSpeed(50);
	//cubeT->setHMove((holder[0] / 4));
	cubeT->setVelocity(vec3(holder)*40.0f);// set object space velocity to camera oriantation in object space. Since camera always have the same xz oriantation as the object, xz oriantation wouldnt change when camera rotate.
	//cubeT->setVMove(1);  //do this if you want the cube to not have vertical velocity. uncomment the above setVelocity.
	//cout << holder[0] << ' ' << holder[1] << ' ' << holder[2] << ' ' << playerHolder[0] << ' ' << playerHolder[2] << endl;
}
void despawnProjectile()
{
	for (int i = 0; i < projectile_list.size(); i++)
	{
		float startX = projectile_list[i]->getStartX();
		float startY = projectile_list[i]->getStartY();
		AABB curr = projectile_list[i]->getAABB();
		int distance = sqrt(pow(curr.max[0] - startX, 2) + pow(curr.max[2] - startY, 2));//Pythagorean Theorem

		//cout << startX << " " << curr.max[0] << " " << curr.max[0] - startX << " " << distance << endl;
		if (distance >= (*projectile_list[i]).getDistance())
		{
			////////////////////////////////////////////////Window::removeDrawList((*projectile[i]).getName());
			projectile_list.erase(projectile_list.begin() + i);
		}
	}
}
void simulateProjectile(float t)
{
	for (int i = 0; i < projectile_list.size(); i++){
		projectile_list[i]->addVelocity(vec3(0.0, -9.8, 0.0)*t);
		projectile_list[i]->postTrans(glm::translate(projectile_list[i]->getVelocity()*t));
	}
}

void Window::idleCallback(void)
{
	static float anim_time = 0;
	vector<mat4> Transforms;
	GLSLProgram* sd;
	vector<mat4> playerMs;

	switch (myClientState->getState()){
	case 0:
		break;
	case 1:
	case 2:
	case 3:
		cam->preRotate(glm::rotate(mat4(1.0), cam->getPendingRote(), vec3(1, 0, 0)));
		if ((cam->getCamM()*vec4(0, 1, 0, 0))[1] < 0){
			cam->setPreRot(glm::rotate(mat4(1.0), -90.0f, vec3(1, 0, 0)));
		}
		cam->setPendingRot(0);
		
		/*
		QueryPerformanceCounter(&current);
		delta = (double)(current.QuadPart - last.QuadPart) / (double)freq.QuadPart;
		last = current;
		anim_time += delta;
		*/

		LARGE_INTEGER ct;
		QueryPerformanceCounter(&ct);
		for (int i = 0; i < player_list.size(); i++){
			//((Mesh*)player_list[i])->BoneTransform(fmod((double)ct.QuadPart / (double)freq.QuadPart, 16.0 / 24), Transforms);
			((Mesh*)player_list[i])->BoneTransform((double)ct.QuadPart / (double)freq.QuadPart, Transforms);

			sd = sdrCtl.getShader("basic_model");
			for (int i = 0; i < Transforms.size(); i++){
				char Name[128];
				memset(Name, 0, sizeof(Name));
				SNPRINTF(Name, sizeof(Name), "gBones[%d]", i);
				sd->setUniform(Name, Transforms[i]);
			}
		}

		//simulateProjectile(delta);

		/*vector<mat4> playerMs = scene->getPlayerMats();
		for (int i = 0; i < player_list.size(); i++){
		player_list[i]->setModelM(playerMs[i]);
		}*/

		if ((keyState & 1 << 2) && (keyState & 1)){//up left
			cam->getObjAppended()->setRotation(glm::rotate(mat4(1.0), 45.0f, vec3(0.0, 1.0, 0.0)));
		}
		else if ((keyState & 1 << 2) && (keyState & 1 << 1)){//up right
			cam->getObjAppended()->setRotation(glm::rotate(mat4(1.0), -45.0f, vec3(0.0, 1.0, 0.0)));
		}
		else if ((keyState & 1 << 3) && (keyState & 1)){//down left
			cam->getObjAppended()->setRotation(glm::rotate(mat4(1.0), 135.0f, vec3(0.0, 1.0, 0.0)));
		}
		else if ((keyState & 1 << 3) && (keyState & 1 << 1)){//down right
			cam->getObjAppended()->setRotation(glm::rotate(mat4(1.0), -135.0f, vec3(0.0, 1.0, 0.0)));
		}
		else if (keyState & 1 << 2){//up
			cam->getObjAppended()->setRotation(glm::rotate(mat4(1.0), 0.0f, vec3(0.0, 1.0, 0.0)));
		}
		else if (keyState & 1 << 3){//down
			cam->getObjAppended()->setRotation(glm::rotate(mat4(1.0), 180.0f, vec3(0.0, 1.0, 0.0)));
		}
		else if (keyState & 1){//left
			cam->getObjAppended()->setRotation(glm::rotate(mat4(1.0), 90.0f, vec3(0.0, 1.0, 0.0)));
		}
		else if (keyState & 1 << 1){//right
			cam->getObjAppended()->setRotation(glm::rotate(mat4(1.0), -90.0f, vec3(0.0, 1.0, 0.0)));
		}

		View = cam->getViewM();

		if (myClientState->getState() == 2){
			myGameMenu->draw();
		}
		else if (myClientState->getState() == 3){
			myDeathScreen->draw();
		}

		break;
	default:
		break;
	}

	updateShaders();
	updateSound();
    displayCallback();  
}
void Window::reshapeCallback(int w, int h)
{
	switch (myClientState->getState()){
	case 0:
		width = w;
		height = h;
		glViewport(0, 0, w, h);  // set new view port size
	case 1:
	case 2:
	case 3:
		width = w;
		height = h;
		glViewport(0, 0, w, h);  // set new view port size
		Projection = glm::perspective(fov, (float)w / h, nearClip, farClip);
		updateShaders();
		break;
	default:
		break;
	}
}
void Window::displayCallback(void)
{
	unsigned char m_Test[] = "Look Ma! I'm printing!";
	unsigned char m_Test2[] = "This is where the menu will go eventually. Press the SpaceBar to Enter the Game.";
	static time_t timer = clock();

	if (clock() - timer >= CLOCKS_PER_SEC){
		//cout<<"FPS: "<<counter<<endl;
		myFPS = counter;
		sprintf_s(buf, "%s %d", "FPS ", myFPS);
		timer = clock();
		counter = 0;
	}
	counter++;
	
	switch (myClientState->getState()){
	case 0:
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		/*
		glDisable(GL_DEPTH_TEST);
		RenderString((Window::width) / 4, (Window::height) / 2, GLUT_BITMAP_HELVETICA_18, m_Test2, vec3(1.0f, 1.0f, 1.0f));
		glEnable(GL_DEPTH_TEST);
		*/
		myMainMenu->draw();
		break;
	case 1:
	case 2:
	case 3:
		///////  1st pass: render into depth map //////////
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, depth_fbo);
		glViewport(0, 0, depth_texture_width, depth_texture_height);
		shadow->Bind(GL_TEXTURE0 + shadow_map_id);
		glClear(GL_DEPTH_BUFFER_BIT);

		//m_pMesh2->draw(LightProjection, LightView);
		for (int i = 0; i < player_list.size(); ++i)
		{
			player_list[i]->draw(LightProjection, LightView);
		}
		for (int i = 0; i < stationary_list.size(); ++i)
		{
			stationary_list[i]->draw(LightProjection, LightView);
		}
		for (int i = 0; i < projectile_list.size(); ++i)
		{
			projectile_list[i]->draw(LightProjection, LightView);
		}
		

		///////  2nd pass: render onto screen ////////////
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, width, height);
		shadow->Bind(GL_TEXTURE0 + shadow_map_id);

		for (int i = 0; i < draw_list.size(); ++i)
		{
			draw_list[i]->draw();
		}
		for (int i = 0; i < player_list.size(); ++i)
		{
			player_list[i]->draw();
		}
		for (int i = 0; i < stationary_list.size(); ++i)
		{
			stationary_list[i]->draw();
		}
		for (int i = 0; i < projectile_list.size(); ++i)
		{
			projectile_list[i]->draw();
		}

		//	md5->draw();

		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glDepthMask(GL_FALSE); // without it some part of model will cover other part of model which looks weird
		//	md6->draw();
		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);

		m_billboardList.Render(Projection, View, vec3((glm::inverse(View)*vec4(0, 0, 0, 1))), (1.0f), mat4(1.0), Projection*View, 0, sdrCtl);
		m_billboardList2.Render(Projection, View, vec3((glm::inverse(View)*vec4(0, 0, 0, 1))), (1.0f), mat4(1.0), Projection*View, 0, sdrCtl);
		m_billboardList3.Render(Projection, View, vec3((glm::inverse(View)*vec4(0, 0, 0, 1))), (1.0f), mat4(1.0), Projection*View, 0, sdrCtl);

		glEnable(GL_POINT_SPRITE);
		glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		particle->draw(Projection, View);
		particle2->draw(Projection, View);
		particle3->draw(Projection, View);
		particle4->draw(Projection, View);
		particle5->draw(Projection, View);
		particle6->draw(Projection, View);
		particle7->draw(Projection, View);
		glDisable(GL_BLEND);

		glDisable(GL_DEPTH_TEST);

		myUI->draw();

		RenderString(2.0f, Window::height - 20, GLUT_BITMAP_HELVETICA_18, (unsigned char*)buf, vec3(1.0f, 0.0f, 0.0f));
		RenderString(4.0f, 4.0f, GLUT_BITMAP_HELVETICA_18, m_Test, vec3(0.0f, 0.0f, 1.0f));

		glEnable(GL_DEPTH_TEST);

		//glFlush();
		if (myClientState->getState() == 2){
			myGameMenu->draw();
		}
		else if (myClientState->getState() == 3){
			myDeathScreen->draw();
		}
		break;
	default:
		break;
	}
	glutSwapBuffers();
}

//LARGE_INTEGER asdf, jkl;
void server_update(int value){
	//QueryPerformanceCounter(&asdf);
	//double fjfj = (double)((double)(asdf.QuadPart - jkl.QuadPart) / (double)freq.QuadPart * 1000);
	//jkl = asdf;
	//cout << fjfj << endl;

	/*
	diff = (double)(current.QuadPart - last.QuadPart) / (double)freq.QuadPart;
	QueryPerformanceCounter(&loop_begin);
	*/

	//This is where we would be doing the stuffs
	// Build send vectors and send
	(*sendVec)[0] = std::make_pair(std::to_string(playerID), mat4((float)keyState));
	(*sendVec)[1] = std::make_pair(std::to_string(playerID), mat4((float)mouseState));
	(*sendVec)[2] = std::make_pair(std::to_string(playerID), cam->getCamM());
	(*sendVec)[3] = std::make_pair(std::to_string(playerID), mat4((float)cam_dx));
	mouseState = 0;
	cli->write(*sendVec);
	io_service.poll();
	cam_dx = 0;

	// RECEIVE STUFF
	recvVec = cli->read();
	io_service.poll();
	
	//std::cout << "pair 0: " << atoi(&((*recvVec)[0].first.c_str())[0]) << std::endl;
	//std::cout << "pair 1: " << atoi(&((*recvVec)[1].first.c_str())[0]) << std::endl;
	//std::cout << "pair 2: " << atoi(&((*recvVec)[2].first.c_str())[0]) << std::endl;
	//std::cout << "pair 3: " << atoi(&((*recvVec)[3].first.c_str())[0]) << std::endl;

	//stateID = atoi(&((*recvVec)[0].first.c_str())[0]);

	if ( (*recvVec)[0].first.c_str()[1] == 's' )
	{
		//std::cout << "Projectile fire" << std::endl;
		projectileAttack(atoi(&((*recvVec)[0].first.c_str())[0]), cam);
	}

	//stateID = ((*recvVec)[1].first.c_str()[0]);

	if ((*recvVec)[1].first.c_str()[1] == 's')
	{
		//std::cout << "Projectile fire" << std::endl;
		projectileAttack(atoi(&((*recvVec)[1].first.c_str())[0]), cam);
	}

//	stateID = ((*recvVec)[2].first.c_str()[0]);

	if ((*recvVec)[2].first.c_str()[1] == 's')
	{
		//std::cout << "Projectile fire" << std::endl;
		projectileAttack(atoi(&((*recvVec)[2].first.c_str())[0]), cam);
	}

	//stateID = ((*recvVec)[3].first.c_str()[0]);

	if ((*recvVec)[3].first.c_str()[1] == 's')
	{
		//std::cout << "Projectile fire" << std::endl;
		projectileAttack(atoi(&((*recvVec)[3].first.c_str())[0]), cam);
	}

	mats[atoi(&((*recvVec)[0].first.c_str())[0])] = (*recvVec)[0].second;
	mats[atoi(&((*recvVec)[1].first.c_str())[0])] = (*recvVec)[1].second;
	mats[atoi(&((*recvVec)[2].first.c_str())[0])] = (*recvVec)[2].second;
	mats[atoi(&((*recvVec)[3].first.c_str())[0])] = (*recvVec)[3].second;

	player_list[0]->setModelM(mats[0]);
	player_list[1]->setModelM(mats[1]);
	player_list[2]->setModelM(mats[2]);
	player_list[3]->setModelM(mats[3]);

	simulateProjectile(diff);

	//Particles are instantly despawning
	//despawnProjectile();

	//Have to reset timer after
	//QueryPerformanceCounter(&loop_end);
	//int diff = (int)((double)(loop_end.QuadPart - loop_begin.QuadPart) / (double)freq.QuadPart *1000);
	//diff = (double)(loop_end.QuadPart - last.QuadPart) / (double)freq.QuadPart * 1000;
}

void SelectFromMenu(int idCommand)
{
	switch (idCommand)
	{
	case MENU_LIGHTING:
		g_bLightingEnabled = !g_bLightingEnabled;
		if (g_bLightingEnabled){

		}
		//	glEnable(GL_LIGHTING);
		else
		//	glDisable(GL_LIGHTING);
		break;
	case MENU_POLYMODE:
		g_bFillPolygons = !g_bFillPolygons;
		//glPolygonMode(GL_FRONT_AND_BACK, g_bFillPolygons ? GL_FILL : GL_LINE);
		break;
	case MENU_TEXTURING:
		g_bTexture = !g_bTexture;
		if (g_bTexture){

		}
		//	glEnable(GL_TEXTURE_2D);
		else
		//	glDisable(GL_TEXTURE_2D);
		break;
	case MENU_EXIT:
		exit(0);
		break;
	}
	// Almost any menu selection requires a redraw
	glutPostRedisplay();
}
int BuildPopupMenu(void)
{
	int menu;
	menu = glutCreateMenu(SelectFromMenu);
	glutAddMenuEntry("Toggle lighting\tl", MENU_LIGHTING);
	glutAddMenuEntry("Toggle polygon fill\tp", MENU_POLYMODE);
	glutAddMenuEntry("Toggle texturing\tt", MENU_TEXTURING);
	glutAddMenuEntry("Exit demo\tEsc", MENU_EXIT);
	return menu;
}

int main(int argc, char *argv[])
{
  ConfigSettings::config->copyMissingSettings();
  ConfigSettings::config->getValue("ScreenWidth", Window::width);
  ConfigSettings::config->getValue("ScreenHeight", Window::height);
  
  glutInit(&argc, argv);      	      	      // initialize GLUT
  glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
  //glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
  glutInitWindowSize(Window::width, Window::height);      // set initial window size
  glutCreateWindow("CSE 125 - Group 4 (RadioactiveChipmunks)");    	      // open window and set window title
  
  bool buf;
  ConfigSettings::config->getValue("FullScreen", buf);
  if (buf){
	glutFullScreen();
  }
  
  glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

  glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
  glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
  //glClearColor(fogColor[0],fogColor[1],fogColor[2],0.0);   	      // set clear color to black
  glClearColor(0, 0, 0, 0);
  //glClearColor(1, 1, 1, 0);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
  glDisable(GL_CULL_FACE);     // disable back face culling to render both sides of polygons
  glShadeModel(GL_SMOOTH);             	      // set shading to smooth

  // Generate material properties:
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
  
  //for white face problem when scaled down
  glEnable(GL_NORMALIZE);

  //more realistic lighting
  glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

  // Install callback functions:
  glutDisplayFunc(Window::displayCallback);
  glutReshapeFunc(Window::reshapeCallback);
  glutIdleFunc(Window::idleCallback);

  glutMouseFunc(mouseFunc);
  glutMotionFunc(motionFunc);
  glutPassiveMotionFunc(passiveMotionFunc);

  //Added for server debuging
  //glutTimerFunc(500, server_update, 0);

  glutKeyboardFunc(keyboard);
  glutKeyboardUpFunc(keyUp);
  glutSpecialFunc(specialKeyboardFunc);

  //glutSetCursor(GLUT_CURSOR_NONE);
  glutSetCursor(GLUT_CURSOR_WAIT);

  BuildPopupMenu();
  glutAttachMenu(GLUT_MIDDLE_BUTTON);

  initialize(argc, argv);  

  //glutMainLoop();

  QueryPerformanceFrequency(&freq);
  QueryPerformanceCounter(&last);

  running = true;
  connected = false;
  myClientState->setState(0);
  do{

	  QueryPerformanceCounter(&current);
	  diff = (double)(current.QuadPart - last.QuadPart) / (double)freq.QuadPart;
	  last = current;

	  glutMainLoopEvent();

	  //printf("LOOP!\n");
	  if (connected){
		  server_update(0);
	  }

	  Window::idleCallback();
	  
	  QueryPerformanceCounter(&loop_end);
	  diff = (double)(loop_end.QuadPart - last.QuadPart) / (double)freq.QuadPart * 1000;

	  if (diff > 15){
		  //glutTimerFunc(0, server_update, 0);
		  //cout << "server_update() exceded 15ms mark" << endl;
		  //cout << diff << endl;
	  }
	  else{
		  //glutTimerFunc(15-diff, server_update, 0);
		  Sleep(15 - diff);
	  }
	  
  } while (running);

  for (int i = 0; i < draw_list.size(); ++i)
  {
	  delete draw_list[i];
  }
  for (int i = 0; i < player_list.size(); ++i)
  {
	  delete player_list[i];
  }
  for (int i = 0; i < stationary_list.size(); ++i)
  {
	  delete stationary_list[i];
  }
  for (int i = 0; i < texture_list.size(); ++i)
  {
	  delete texture_list[i];
  }
  for (int i = 0; i < sound_list.size(); ++i)
  {
	  delete sound_list[i];
  }

  return 0;
}

void keyboard(unsigned char key, int, int){
	switch (myClientState->getState()){
	case 0:
		if (key == ' '){
			if (space_up){
				//testSound[2]->Play(FMOD_CHANNEL_FREE, 0, &channel);
				//myClientState->setState(1);
			}
		}
		break;
	case 1:

		if (key == 'a'){
			keyState = keyState | 1;
		}
		if (key == 'd'){
			keyState = keyState | 1 << 1;
		}
		if (key == 'w'){
			keyState = keyState | 1 << 2;
		}
		if (key == 's'){
			keyState = keyState | 1 << 3;
		}
		if (key == 'W'){
			keyState = keyState | 1 << 5;
		}
		if (key == 27){
			//running = false;
			//exit(0);
			myClientState->setState(2);
		}
		if (key == ' '){
			keyState = keyState | 1 << 4;

			if (space_up){
				space_up = 0;

				testSound[1]->Play(FMOD_CHANNEL_FREE, 0, &channel);
			}
		}

		//Added for sound debugging
		if (key == 'f'){
			testSound[2]->Play(FMOD_CHANNEL_FREE, 0, &channel);
		}
		if (key == 13)
		{
			mat4 player = player_list[playerID]->getModelM();
			vec4 playerHolder = player*vec4(0, 0, 0, 1);

			Cube* cube6 = new Cube();
			cube6->setKd(vec3(0.8, 0.0, 0.0));
			cube6->setKa(vec3(0.3, 0.0, 0.0));
			cube6->setKs(vec3(0.4, 0.0, 0.0));
			cube6->setShininess(100);
			cube6->setReflectFactor(vec2(0.2, 0.5));
			cube6->setEta(0.5);
			cube6->setCubeMapUnit(3);
			cube6->setSpeed(5);
			cube6->postTrans(glm::translate(vec3(playerHolder[0] + 2, playerHolder[1], playerHolder[2] + 2)));
			cube6->setAABB(AABB(vec3(-0.5, -0.5, -0.5), vec3(0.5, 0.5, 0.5)));
			cube6->setShader(sdrCtl.getShader("basic_reflect_refract"));
			cube6->setType("Cube");
			cube6->setName("Test Cube6");
			//player_list.push_back(cube6);
			//scene->addPlayer(cube6);

		}
		if (key == 0x30)
		{
			draw_list.clear();
			initialize(1, (char **)1);
		}

		if (key == 'l'){
			SelectFromMenu(MENU_LIGHTING);
		}
		if (key == 'p'){
			SelectFromMenu(MENU_POLYMODE);
		}
		if (key == 't'){
			SelectFromMenu(MENU_TEXTURING);
		}
		break;
	case 2:
		if (key == 27){
			//running = false;
			//exit(0);
			myClientState->setState(1);
		}
		break;
	case 3:
		if (key == 27){
			//running = false;
			//exit(0);
			myClientState->setState(1);
		}
		break;
	default:
		break;
	}
}
void keyUp (unsigned char key, int x, int y) {  
	
	switch (myClientState->getState()){
	case 0:
		break;
	case 1:

		if (key == 'a'){
			keyState = keyState & ~1;
		}
		if (key == 'd'){
			keyState = keyState & ~(1 << 1);
		}
		if (key == 'w'){
			// These vars need to become arrays for each player
			// and all this needs to move into the server
			if (glutGetModifiers() & GLUT_ACTIVE_SHIFT){
				if (sprint_up >= 10){
					testSound[1]->Play(FMOD_CHANNEL_FREE, 0, &channel);
					//scene->jump(playerID);
				}
				if (sprint_up > 0){
					sprint_up--;
				}
				else{
					sprint_up = 0;
				}
			}
			keyState = keyState & ~(1 << 2);
		}
		if (key == 's'){
			keyState = keyState & ~(1 << 3);
		}
		if (key == 'W'){
			keyState = keyState & ~(1 << 5);
		}
		if (key == ' '){
			keyState = keyState & ~(1 << 4);
			space_up = 1;
		}
		// This goes into server
		if (!(glutGetModifiers() & GLUT_ACTIVE_SHIFT)){
			if (sprint_up < 10){
				sprint_up++;
			}
			else{
				sprint_up = 10;
			}
		}
		break;
	case 2:
		break;
	case 3:
		break;
	default:
		break;
	}
}
void mouseFunc(int button, int state, int x, int y)
{
	oldX=x;
	oldY=y;
	mouseDown = (state == GLUT_DOWN);
	mouseButton = button;
	float newX;
	float newY;
	switch (myClientState->getState()){
	case 0:
		if (state == GLUT_DOWN){
			newX = (float)x / Window::width;
			newY = (float)y / Window::height;
			cout << "CLICK!" << newX << "," << newY << endl;
			int click = myMainMenu->checkClick(newX, newY);
			if (click == 1){
				myClientState->setState(1);
				
				if (!connected){
					
					recvVec->push_back(std::make_pair("initRecvPos_c", mat4(0.0f)));
					recvVec->push_back(std::make_pair("initRecvPos_c", mat4(0.0f)));
					recvVec->push_back(std::make_pair("initRecvPos_c", mat4(0.0f)));
					recvVec->push_back(std::make_pair("initRecvPos_c", mat4(0.0f)));
					sendVec->push_back(std::make_pair("initKey_c", mat4(0.0f)));
					sendVec->push_back(std::make_pair("initMouse_c", mat4(0.0f)));
					sendVec->push_back(std::make_pair("initCam_c", mat4(0.0f)));
					sendVec->push_back(std::make_pair("initCamRot_c", mat4(0.0f)));
					
					try
					{
						cli = new tcp_client(io_service, "localhost", "13");
						io_service.run_one();
						io_service.run_one();
						playerID = cli->pID();
						std::cout << "pid: " << playerID << std::endl;
						//system("pause");
					}
					catch (std::exception& e)
					{
						sprintf_s(buf, "%s", "Error connecting to server!");
						std::cerr << e.what() << std::endl;
					}

					cam = new Camera();
					cam->attach(player_list[playerID]);
					cam->postTrans(glm::translate(vec3(0, 1, 4)));

					connected = true;
				}
			}
			else if (click == 2){
				running = false;
				exit(0);
			}
		}
		break;
	case 1:

		if (state == GLUT_DOWN){
			if (button == GLUT_LEFT_BUTTON){
				if (left_mouse_up){
					left_mouse_up = 0;
					mouseState = mouseState | 1;

					testSound[4]->Play(FMOD_CHANNEL_FREE, 0, &channel);
					///scene->basicAttack(playerID);
					
					//UI testing purposes
					myUI->setLess_Life(1);
					myUI->setShots(1);
				}
				else
				{
					mouseState = mouseState & ~1;
				}
			}
			if (button == GLUT_RIGHT_BUTTON){
				if (right_mouse_up){
					right_mouse_up = 0;
					mouseState = mouseState | 1 << 1;

					testSound[3]->Play(FMOD_CHANNEL_FREE, 0, &channel);

					//projectileAttack(playerID, cam);
					
				}
				else
				{
					mouseState = mouseState & ~(1 << 1);
				}
			}
			if (button == GLUT_MIDDLE_BUTTON){
				if (middle_mouse_up){
					middle_mouse_up = 0;
					mouseState = mouseState | 1 << 2;

					testSound[5]->Play(FMOD_CHANNEL_FREE, 0, &channel);
				}
				else
				{
					mouseState = mouseState & ~(1 << 2);
				}
			}
		}
		if (state == GLUT_UP){
			if (button == GLUT_LEFT_BUTTON){
				mouseState = mouseState & ~1;
				left_mouse_up = 1;
			}
			if (button == GLUT_RIGHT_BUTTON){
				mouseState = mouseState & ~(1 << 1);
				right_mouse_up = 1;
			}
			if (button == GLUT_MIDDLE_BUTTON){
				mouseState = mouseState & ~(1 << 2);
				middle_mouse_up = 1;
			}
		}
		break;
	case 2:
		if (state == GLUT_DOWN){
			newX = (float)x / Window::width;
			newY = (float)y / Window::height;
			cout << "CLICK!" << newX << "," << newY << endl;
			int click = myGameMenu->checkClick(newX, newY);
			if (click == 1){
				myClientState->setState(1);
			}
			if (click == 2){
				myClientState->setState(0);
			}
		}
		break;
	case 3:
		if (state == GLUT_DOWN){
			newX = (float)x / Window::width;
			newY = (float)y / Window::height;
			cout << "CLICK!" << newX << "," << newY << endl;
			myDeathScreen->checkClick(newX, newY);
		}
		break;
	default:
		break;
	}
}
void motionFunc(int x, int y)
{
	switch (myClientState->getState()){
	case 0:
	case 1:
	case 2:
	case 3:
		passiveMotionFunc(x, y);
	default:
		break;
	}
}
void passiveMotionFunc(int x, int y){
	static int lastX = 0;
	static int lastY = 0;

	float dx = x - lastX;
	float dy = lastY - y;
	lastX = x;
	lastY = y;

	float newX;
	float newY;

	switch (myClientState->getState()){
	case 0:
		newX = (float)x / Window::width;
		newY = (float)y / Window::height;
		myMainMenu->checkHighlight(newX, newY);
		break;
	case 1:

		if (fabs(dx) < 250 && fabs(dy) < 250){
			//cam->preRotate(glm::rotate(mat4(1.0), cam_sp*dy, vec3(1, 0, 0)));
			//cube->postRotate(glm::rotate(mat4(1.0), -cam_sp*dx, vec3(0, 1, 0)));
			cam->pushRot(cam_sp*dy);
			cam_dx += dx;
		}

		if (abs(Window::width / 2 - lastX)>25 || abs(Window::height / 2 - lastY)>25){
			lastX = Window::width / 2;
			lastY = Window::height / 2;
			glutWarpPointer(Window::width / 2, Window::height / 2);
		}
		break;
	case 2:
		newX = (float)x / Window::width;
		newY = (float)y / Window::height;
		myGameMenu->checkHighlight(newX, newY);
		break;
	case 3:
		newX = (float)x / Window::width;
		newY = (float)y / Window::height;
		myDeathScreen->checkHighlight(newX, newY);
		break;
	default:
		break;
	}
}
void specialKeyboardFunc(int key, int x, int y){
	
	switch (myClientState->getState()){
	case 0:
		break;
	case 1:
		if (glutGetModifiers() & GLUT_ACTIVE_SHIFT){
			if (sprint_up >= 10){
				testSound[1]->Play(FMOD_CHANNEL_FREE, 0, &channel);
				//scene->jump(playerID);
			}
			if (sprint_up > 0){
				sprint_up--;
			}
			else{
				sprint_up = 0;
			}
		}
		break;
	default:
		break;
	}
}

void updateShaders(){

	GLSLProgram* p[5];
	p[0] = sdrCtl.getShader("basic_reflect_refract");
	p[1] = sdrCtl.getShader("basic_texture");
	p[2] = sdrCtl.getShader("grid_ground");
	p[3] = sdrCtl.getShader("basic_model");
	p[4] = sdrCtl.getShader("ground_tess");
	for (int i = 0; i < 5; i++){
		p[i]->setUniform("light[0].type", light[0].type);
		p[i]->setUniform("light[0].pos", light[0].pos);
		p[i]->setUniform("light[0].specular", light[0].specular);
		p[i]->setUniform("light[0].diffuse", light[0].diffuse);
		p[i]->setUniform("light[0].ambient", light[0].ambient);
		p[i]->setUniform("light[0].dir", light[0].dir);
		p[i]->setUniform("light[0].spotCutOff", light[0].spotCutOff);
	}
}
void setupShaders()
{
	int NumberOfShaders = map_info->GetShaderCount();
	for (int i = 0; i < NumberOfShaders; i++){
		string name = map_info->GetShaderName(i);
		string vert = map_info->GetShaderVert(i);
		string frag = map_info->GetShaderFrag(i);
		printf("Loading Shader: %s...", name.c_str());

		sprintf_s(buf, "%s %s %s", "Loading Shader: ", name.c_str(), "...");

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		RenderString((Window::width) / 4, (Window::height) / 2, GLUT_BITMAP_HELVETICA_18, (unsigned char*)buf, vec3(0.0f, 1.0f, 0.0f));

		glutSwapBuffers();

		sdrCtl.createVFShader(name, vert.c_str(), frag.c_str());
		printf("done!\n");

		printf("Loading Shader: %s...", name.c_str());

		sprintf_s(buf, "%s %s %s", "Loading Shader: ", name.c_str(), "...done!");

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		RenderString((Window::width) / 4, (Window::height) / 2, GLUT_BITMAP_HELVETICA_18, (unsigned char*)buf, vec3(0.0f, 1.0f, 0.0f));

		glutSwapBuffers();
	}

	sdrCtl.createVGFShader("billboard", "Shaders/billboard.vert", "Shaders/billboard.geom", "Shaders/billboard.frag");
	sdrCtl.createVCEFShader("ground_tess", "Shaders/ground_tess.vert", "Shaders/ground_tess.cntl", "Shaders/ground_tess.eval", "Shaders/ground_tess.frag");

	updateShaders();
}
void initialize(int argc, char *argv[])
{
	myClientState = new ClientState();

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&last);

	draw_list.clear();

	GLenum err = glewInit();
	if( GLEW_OK != err )
	{
		fprintf(stderr, "Error initializing GLEW: %s\n", 
			glewGetErrorString(err) );
	}

	//Clear window to black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();

	//Init the JSON parser for the map
	map_info = new JSON_Parser("Maps/Test1.json");
	printf("Loading Map: %s\n", map_info->GetMapName().c_str());
	sprintf_s(buf, "%s %s", "Loading Map:", map_info->GetMapName().c_str());

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	RenderString((Window::width) / 4, (Window::height) / 2, GLUT_BITMAP_HELVETICA_18, (unsigned char*)buf, vec3(0.0f, 1.0f, 0.0f));

	glutSwapBuffers();

	loadTextures();

	
	//depth buffer initialization
	glGenFramebuffers(1, &depth_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, depth_fbo);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadow->getTexID(), 0);
	// Disable writes to the color buffer
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (Status != GL_FRAMEBUFFER_COMPLETE) {
		printf("FB error, status: 0x%x\n", Status);
		system("pause");
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	

	light[0].type=1;
	light[0].pos = vec4(0,40,0,1);
	light[0].specular = vec3(0.1,0.1,0.1);
	light[0].diffuse = vec3(0.9, 0.9, 0.9);
	light[0].ambient = vec3(0.5, 0.5, 0.5);
	light[0].dir = vec4(0,-1,0,1);
	light[0].spotCutOff = cos(10.0/180*M_PI);
	LightView = glm::lookAt(vec3(0,40,0), vec3(0, 0, 0), vec3(1, 0, 0));
	LightProjection = glm::frustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1000.0f);

	//fog.maxDist=4;
	//fog.minDist=3;
	//fog.color = fogColor;

	setupShaders();

	/*Cube* cube0 = new Cube();
	cube0->setKd(vec3(0.8, 0.0, 0.0));
	cube0->setKa(vec3(0.3, 0.0, 0.0));
	cube0->setKs(vec3(0.4, 0.0, 0.0));
	cube0->setShininess(100);
	cube0->setReflectFactor(vec2(0.2, 0.5));
	cube0->setEta(0.5);
	cube0->setCubeMapUnit(3);
	cube0->setSpeed(5);
	cube0->postTrans(glm::translate(vec3(0, 0.5, 7)));
	cube0->setAABB(AABB(vec3(-0.5, -0.5, -0.5), vec3(0.5, 0.5, 0.5)));
	cube0->setShader(sdrCtl.getShader("basic_reflect_refract"));
	cube0->setShadowTex(shadow_map_id);
	cube0->setType("Cube");
	cube0->setName("Test cube0");
	player_list.push_back(cube0);*/

	myUI = new UI();
	myMainMenu = new MainMenu();
	myGameMenu = new GameMenu();
	myDeathScreen = new DeathScreen();

	ground = new Ground();
	ground->setShader(sdrCtl.getShader("ground_tess"));
	ground->loadColorTex("img/moon_tex/moon_COLOR.png", "PNG");
	ground->loadDispTex("img/moon_tex/moon_DISP.png", "PNG");
	ground->loadNormalTex("img/moon_tex/moon_NRM.png", "PNG");
	ground->loadOccTex("img/moon_tex/moon_OCC.png", "PNG");
	ground->loadSpecTex("img/moon_tex/moon_SPEC.png", "PNG");
	ground->setDimensionS(40);
	ground->setDimensionT(40);
	ground->setRow(51);
	ground->setColumn(51);
	ground->setHeight(1 / 1.0);
	ground->setShadowTex(shadow_map_id);
	ground->generate();
	ground->setType("Ground");
	ground->setName("Ground");
	stationary_list.push_back(ground);


	skybox = new SkyBox(-50, 50, -50, 50, -50, 50);
	skybox->setShader(sdrCtl.getShader("basic_skybox"));
	skybox->setTexUnit(3);
	skybox->setType("Skybox");
	skybox->setName("Skybox");
	draw_list.push_back(skybox);

	for (int i = 0; i < 4; i++){
		Mesh* player0 = new Mesh();
		player0->LoadMesh("Model/monky2014_delete2.dae");
		player0->setShader(sdrCtl.getShader("basic_model"));
		player0->setShadowTex(shadow_map_id);
		player0->setAdjustM(glm::translate(vec3(0.0, 1.35, 0.0))*glm::rotate(mat4(1.0), 180.0f, vec3(0, 1.0, 0))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0))*glm::scale(vec3(0.07, 0.07, 0.07)));
		player0->setShininess(30);
		player_list.push_back(player0);
	}


	//m_pMesh2 = new Mesh();
	//m_pMesh2->LoadMesh("Model/2Tower_6_bone.dae");
	//m_pMesh2->setShader(sdrCtl.getShader("basic_model"));
	//m_pMesh2->setShadowTex(shadow_map_id);
	//m_pMesh2->setAdjustM(glm::translate(vec3(0.0, 1.0, 0.0))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0))*glm::scale(vec3(1.0, 1.0, 1.0)));

	//m_pMesh2 = new Mesh();
	//m_pMesh2->LoadMesh("Model/monky_04_27_smooth.dae");
	//m_pMesh2->setShader(sdrCtl.getShader("basic_model"));
	//m_pMesh2->setAdjustM(glm::translate(vec3(10.0, 4.1, 0.0))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0))*glm::scale(vec3(0.2, 0.2, 0.2))); 
	//m_pMesh2->setShadowTex(shadow_map_id);

	///*md5 = new MD5Model();
	//md5->LoadModel("Model/monky_MD5_try1.md5mesh");
	//md5->LoadAnim("Model/monky_MD5_try1.md5anim");
	//md5->setShader(sdrCtl.getShader("basic_texture"));
	//md5->setShininess(30);
	//md5->setAdjustM(glm::translate(vec3(-15.05, 4.1, -1.2))*glm::rotate(mat4(1.0), 180.0f, vec3(0.0, 1, 0))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0))*glm::scale(vec3(0.2, 0.2, 0.2)));
	//md5->setShadowTex(shadow_map_id);
	////player_list.push_back(md5);*/

	//md6 = new MD5Model();
	//md6->LoadModel("Model/fleurOptonl.md5mesh");
	//md6->LoadAnim("Model/fleurOptonl.md5anim");
	//md6->setShader(sdrCtl.getShader("basic_texture"));
	//md6->setShininess(30);
	//md6->setAdjustM(glm::translate(vec3(0.0, 1.7, 0.0))*glm::rotate(mat4(1.0), 180.0f, vec3(0.0, 1, 0))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0))*glm::scale(vec3(0.05, 0.05, 0.05)));
	//md6->setModelM(glm::translate(vec3(10.0, 0.0, 0.0)));
	//md6->setShadowTex(shadow_map_id);
	//md6->setType("Model");
	//md6->setName("Player Model");

	//AUDIO START!
	if (loadAudio()){
		printf("Error with FMOD Init!\n");
	}
	else{
		printf("FMOD Init successful!\n");
	}

	m_billboardList.Init("img/monster_hellknight.png", "PNG");
	m_billboardList.setShader(sdrCtl.getShader("billboard"));
	m_billboardList.AddBoard(vec3(9.0f, 1.0f, 9.0f));
	m_billboardList.AddBoard(vec3(-9.0f, 1.0f, -9.0f));
	m_billboardList.AddBoard(vec3(-9.0f, 1.0f, 9.0f));
	m_billboardList.AddBoard(vec3(9.0f, 1.0f, -9.0f));
	m_billboardList.BindBoards();

	m_billboardList2.Init("img/monster_hellknight.png", "PNG");
	m_billboardList2.setShader(sdrCtl.getShader("billboard"));
	m_billboardList2.AddBoard(vec3(1.0f, 1.0f, 9.0f));
	m_billboardList2.BindBoards();

	m_billboardList3.Init("img/monster_hellknight.png", "PNG");
	m_billboardList3.setShader(sdrCtl.getShader("billboard"));
	m_billboardList3.AddBoard(vec3(1.0f, 1.0f, -9.0f));
	m_billboardList3.BindBoards();

	m_billboardList4.Init("img/monster_hellknight.png", "PNG");
	m_billboardList4.setShader(sdrCtl.getShader("billboard"));
	m_billboardList4.AddBoard(vec3(1.0f, 1.0f, -6.0f));
	m_billboardList4.BindBoards();

	particle = new ParticleSystem();
	particle->setShader(sdrCtl.getShader("emitter"));
	particle->setType("Particle_System");
	particle->setName("Particle_Test");
	particle->setK(24.0f);
	particle->setColor(vec3(1.0, 0.0, 0.0));
	particle->setShade(vec3(1.0, 0.0, 0.0));
	particle->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG");
	
	particle->setTime_Step(1.0);
	particle->setTime_Max(150.0);
	particle->setTime_Min(1.0);
	particle->setTime(0.45);

	particle->setModelM(glm::translate(vec3(0.0f, 2.0f, -40.0f)));

	particle2 = new ParticleSystem();
	particle2->setShader(sdrCtl.getShader("emitter"));
	particle2->setType("Particle_System");
	particle2->setName("Particle_Test");
	particle2->setK(14.0f);
	particle2->setColor(vec3(0.0, 1.0, 0.0));
	particle2->setShade(vec3(0.0, 1.0, 0.0));
	particle2->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG");

	particle2->setTime_Step(0.5);
	particle2->setTime_Max(15.0);
	particle2->setTime_Min(1.5);
	particle2->setTime(7.5);

	particle2->setModelM(glm::translate(vec3(0.0f, 2.0f, -20.0f)));

	particle3 = new ParticleSystem();
	particle3->setShader(sdrCtl.getShader("emitter"));
	particle3->setType("Particle_System");
	particle3->setName("Particle_Test");
	particle3->setK(4.0f);
	particle3->setColor(vec3(0.0, 0.0, 1.0));
	particle3->setShade(vec3(0.0, 0.0, 1.0));
	particle3->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG");

	particle3->setTime(25.0);
	
	particle3->setModelM(glm::translate(vec3(0.0f, 2.0f, -10.0f)));

	particle4 = new ParticleSystem();
	particle4->setShader(sdrCtl.getShader("emitter"));
	particle4->setType("Particle_System");
	particle4->setName("Particle_Test");
	particle4->setK(1.0f);
	particle4->setColor(vec3(1.0, 1.0, 1.0));
	particle4->setShade(vec3(1.0, 1.0, 1.0));
	particle4->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG");

	particle4->setTime(35.0);

	particle4->setModelM(glm::translate(vec3(0.0f, 2.0f, 0.0f))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0)));

	particle5 = new ParticleSystem();
	particle5->setShader(sdrCtl.getShader("emitter"));
	particle5->setType("Particle_System");
	particle5->setName("Particle_Test");
	particle5->setK(4.0f);
	particle5->setColor(vec3(1.0, 1.0, 0.0));
	particle5->setShade(vec3(1.0, 1.0, 0.0));
	particle5->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG");

	particle5->setTime(45.0);

	particle5->setModelM(glm::translate(vec3(0.0f, 2.0f, 10.0f)));

	particle6 = new ParticleSystem();
	particle6->setShader(sdrCtl.getShader("emitter"));
	particle6->setType("Particle_System");
	particle6->setName("Particle_Test");
	particle6->setK(14.0f);
	particle6->setColor(vec3(1.0, 0.0, 1.0));
	particle6->setShade(vec3(1.0, 0.0, 1.0));
	particle6->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG"); 

	particle6->setTime(7.5);

	particle6->setModelM(glm::translate(vec3(0.0f, 2.0f, 20.0f)));

	particle7 = new ParticleSystem();
	particle7->setShader(sdrCtl.getShader("emitter"));
	particle7->setType("Particle_System");
	particle7->setName("Particle_Test");
	particle7->setK(24.0f);
	particle7->setColor(vec3(0.0, 1.0, 1.0));
	particle7->setShade(vec3(0.0, 1.0, 1.0));
	particle7->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG");
	particle7->setModelM(glm::translate(vec3(0.0f, 2.0f, 40.0f)));

	//sprintf_s(buf, "%s", "Attempting to connect to server...");

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//RenderString((Window::width) / 4, (Window::height) / 2, GLUT_BITMAP_HELVETICA_18, (unsigned char*)buf, vec3(0.0f, 1.0f, 0.0f));

	glutSwapBuffers();

}

void updateSound(){
	FMOD_System_Update(fmodSystem);

	{
		unsigned int ms = 0;
		unsigned int lenms = 0;
		int          playing = 0;
		int          paused = 0;
		int          channelsplaying = 0;

		if (channel)
		{
			FMOD_SOUND *currentsound = 0;

			result = FMOD_Channel_IsPlaying(channel, &playing);
			if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
			{
				ERRCHECK(result);
			}

			result = FMOD_Channel_GetPaused(channel, &paused);
			if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
			{
				ERRCHECK(result);
			}

			result = FMOD_Channel_GetPosition(channel, &ms, FMOD_TIMEUNIT_MS);
			if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
			{
				ERRCHECK(result);
			}

			FMOD_Channel_GetCurrentSound(channel, &currentsound);
			if (currentsound)
			{
				result = FMOD_Sound_GetLength(currentsound, &lenms, FMOD_TIMEUNIT_MS);
				if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
				{
					ERRCHECK(result);
				}
			}
		}
		/*
		result = FMOD_Sound_GetLength(sound, &lenms, FMOD_TIMEUNIT_MS);
		if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
		{
			ERRCHECK(result);
		}
		*/
		FMOD_System_GetChannelsPlaying(fmodSystem, &channelsplaying);


		//printf("Time %02d:%02d:%02d/%02d:%02d:%02d : %s : Channels Playing %2d\r", ms / 1000 / 60, ms / 1000 % 60, ms / 10 % 100, lenms / 1000 / 60, lenms / 1000 % 60, lenms / 10 % 100, paused ? "Paused " : playing ? "Playing" : "Stopped", channelsplaying);

		//printf("\n");
	}
}

int loadAudio(){

	/*
	Create a System object and initialize.
	*/
	result = FMOD_System_Create(&fmodSystem);
	ERRCHECK(result);

	result = FMOD_System_GetVersion(fmodSystem, &version);
	ERRCHECK(result);

	if (version < FMOD_VERSION)
	{
		printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
		return 1;
	}

	result = FMOD_System_Init(fmodSystem, 32, FMOD_INIT_NORMAL, NULL);
	ERRCHECK(result);

	int NumberOfAudio = map_info->GetAudioCount();
	for (int i = 0; i < NumberOfAudio; i++){
		string name = map_info->GetAudioName(i);
		string path = map_info->GetAudioPath(i);
		printf("Loading %s Audio File...", name.c_str());

		//Print to game Window
		sprintf_s(buf, "%s %s %s", "Loading ", name.c_str(), "Audio File...");

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		RenderString((Window::width) / 4, (Window::height) / 2, GLUT_BITMAP_HELVETICA_18, (unsigned char*)buf, vec3(0.0f, 1.0f, 0.0f));

		glutSwapBuffers();

		testSound[i] = new Sound(fmodSystem, path.c_str(), FMOD_HARDWARE, 0, &sound);
		sound_list.push_back(testSound[0]);
		printf("done!\n");

		//Print to game window
		sprintf_s(buf, "%s %s %s", "Loading ", name.c_str(), "Audio File...done!");

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		RenderString((Window::width) / 4, (Window::height) / 2, GLUT_BITMAP_HELVETICA_18, (unsigned char*)buf, vec3(0.0f, 1.0f, 0.0f));

		glutSwapBuffers();
	}

	return 0;

}

void loadTextures(){

	int NumberOfTextures = map_info->GetTextureCount();
	for (int i = 0; i < NumberOfTextures; i++){
		string name = map_info->GetTextureName(i);
		string path = map_info->GetTexturePath(i);
		string type = map_info->GetTextureType(i);
		string ext = map_info->GetTextureExt(i);
		bool cube	= map_info->GetTextureCube(i);
		printf("Loading %s Texture File...", name.c_str());
		
		//Printing to game window
		sprintf_s(buf, "%s %s %s", "Loading ", name.c_str(), "Texture File...");

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		RenderString((Window::width) / 4, (Window::height) / 2, GLUT_BITMAP_HELVETICA_18, (unsigned char*)buf, vec3(0.0f, 1.0f, 0.0f));

		glutSwapBuffers();

		if (cube){
			Texture* testTexture = new Texture(GL_TEXTURE_CUBE_MAP, path.c_str(), type.c_str());
			testTexture->Bind(GL_TEXTURE0 + i);
			testTexture->LoadCube(path.c_str(), ext.c_str());
			texture_list.push_back(testTexture);
		}
		else{
			Texture* testTexture = new Texture(GL_TEXTURE_2D, path.c_str(), type.c_str());
			testTexture->Bind(GL_TEXTURE0 + i);
			testTexture->Load();
			texture_list.push_back(testTexture);
		}
		printf("done!\n");
		sprintf_s(buf, "%s %s %s", "Loading ", name.c_str(), "Texture File...done!");

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		RenderString((Window::width) / 4, (Window::height) / 2, GLUT_BITMAP_HELVETICA_18, (unsigned char*)buf, vec3(0.0f, 1.0f, 0.0f));

		glutSwapBuffers();
	}
	
	shadow = new Texture(GL_TEXTURE_2D);
	shadow->LoadDepthTexture(depth_texture_width, depth_texture_height);
	//shadow->LoadDepthTexture(Window::width, Window::height);
	shadow->Bind(GL_TEXTURE0 + shadow_map_id);
	
}

void Window::addDrawList(Object* obj)
{
	draw_list.push_back(obj);
}

void Window::removeDrawList(const std::string& name)
{
	for (int j = 0; j< draw_list.size(); j++)
	{
		if ((*draw_list[j]).getName() == name)
			draw_list.erase(draw_list.begin() + j);
	}
}


