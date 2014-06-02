#pragma once
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
#include "Mesh_Static.h"
#include "Texture.h"
#include "ConfigSettings.h"
#include "Sound.h"
#include "MD5Model.h"
#include "JSON_Parse.h"
#include "billboard_list.h"
#include "UI.h"
#include "ClientState.h"
#include "AnimController.h"
#include "ParticleAnimated.h"

#include "gameState.h"
#include "CXBOXController.h"
#include "ParseOpts.h"

#include <assert.h>
#include "ParticleSystem.h"
#include "ParticleSystem2.h"

ParticleSystem* particle;
ParticleSystem* particle2;
ParticleSystem* particle3;
ParticleSystem* particle4;
ParticleSystem* particle5;
ParticleSystem* particle6;
ParticleSystem* particle7;
ParticleSystem* particle8;

ParticleSystem2* t0_ps_01;
ParticleSystem2* t0_ps_02;
ParticleSystem2* t0_ps_03;
ParticleSystem2* t1_ps_01;
ParticleSystem2* t1_ps_02;
ParticleSystem2* t1_ps_03;
ParticleSystem* t2_ps_01;
ParticleSystem* t2_ps_02;
ParticleSystem* t2_ps_03;
ParticleSystem* t3_ps_01;
ParticleSystem* t3_ps_02;
ParticleSystem* t3_ps_03;
long long m_currentTimeMillis;

ParticleSystem2* testSystem;

std::vector<ParticleSystem2*> explosion_list;

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

SoundSystem *mySoundSystem;
Music *menuMusic;
Music *gameMusic;
Sound* testSound[10];
FMOD_VECTOR myPosition;
FMOD_VECTOR myVelocity;
Sound* posTestSound;
Sound* posTestSound2;
Music* posTestMusic;

std::vector<Object*> draw_list;
std::vector<Object*> player_list;
std::vector<Object*> tower_list;
std::vector<Object*> stationary_list;
std::vector<Projectile*> projectile_list;
std::vector<Texture*> texture_list;
std::vector<Sound*> sound_list;
std::vector<ParticleAnimated*> panim_list;

Mesh_Static* tryThis;

BillboardList m_billboardList;
BillboardList m_billboardList2;
BillboardList m_billboardList3;
BillboardList m_billboardList4;

JSON_Parser *map_info;

int Window::width = 1280;   // set window width in pixels here
int Window::height = 720;   // set window height in pixels here
float nearClip = (float)0.1;
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
Fog fog(150, 10, 40, 0, 0.9f, vec3(0.8, 0.8, 1));
Fog emptyFog(1,0,1,0,0.0f,vec3(0,0,0));

//Scene* scene;

Cube* cube;
Ground* ground;
SkyBox* skybox;
Sphere* sphere;
TextureScreen* texScreen;

struct Mother{
	Mesh* mother_of_wrench;
	Mesh* mother_of_banana;
	Mesh* mother_of_nut;
	ParticleAnimated* mother_of_p_anim;
}MOM;

int texScreenWidth = 512;
int texScreenHeight = 512;

Camera* cam;
float cam_sp = (float)0.1;
float cam_dx = 0;

GLuint fboHandle;
GLuint depth_fbo;
GLsizei depth_texture_width = 2048;//4096
GLsizei depth_texture_height = 2048;
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
float randomFloatBetween(float min, float max);
void update3DSound();

void updateShaders();
void setupShaders();
void initialize(int argc, char *argv[]);
void loadTextures();
int loadAudio();

int counter = 0;

UI * myUI;
MainMenu * myMainMenu;
GameMenu * myGameMenu;
DeathScreen * myDeathScreen;
Settings * settings;
End_Screen * endScreen;
Logo * logo;

Texture * shadow;
char buf[255];
int myFPS = 0;

ClientState* myClientState;

bool alive = true;
bool first_change = true;

// Stuff Erik added
int playerID = -1; // THIS USED TO BE 1 - it gets set by the server
int stateID = -1;
int keyState = 0;
int mouseState = 0;
int projectile_counter = 0;

std::vector <pair<string, mat4>>* sendVec = new vector<pair<string, mat4>>;
std::vector <pair<string, mat4>>* recvVec = new vector<pair<string, mat4>>;
ParseOpts* parseOpts;
bool recvValid = false;

boost::asio::io_service io_service;
tcp_client* cli;

boost::array<mat4, 4> mats;

bool running;
double diff;
int test = 0;
float test2 = 0;

const int m_lenght = 25;
unsigned char ip_adress[m_lenght];
int but_up = 1;
int m_pos = 0;
int text_flag = 0;

bool connected;
std::string out;
gameState gs;
int i = 0;

int inMenuBox = false;

CXBOXController* Player1;
bool LL = false;
bool LR = false;
bool LU = false;
bool LD = false;

bool RL = false;
bool RR = false;
bool RU = false;
bool RD = false;

bool JMP = false;
bool ATT1 = false;
bool ATT2 = false;
bool ESC = false;
bool SPT = false;

bool STR = false;
bool FLS = false;

bool USE_JOYSTICK = false;
int Vibrate_Frame_Num = 0;

const __int64 DELTA_EPOCH_IN_MICROSECS = 11644473600000000;
struct timezone2
{
	__int32  tz_minuteswest; /* minutes W of Greenwich */
	bool  tz_dsttime;     /* type of dst correction */
};

struct timeval2 {
	__int32    tv_sec;         /* seconds */
	__int32    tv_usec;        /* microseconds */
};

int gettimeofday(struct timeval2 *tv/*in*/, struct timezone2 *tz/*in*/)
{
	FILETIME ft;
	__int64 tmpres = 0;
	TIME_ZONE_INFORMATION tz_winapi;
	int rez = 0;

	ZeroMemory(&ft, sizeof(ft));
	ZeroMemory(&tz_winapi, sizeof(tz_winapi));

	GetSystemTimeAsFileTime(&ft);

	tmpres = ft.dwHighDateTime;
	tmpres <<= 32;
	tmpres |= ft.dwLowDateTime;

	/*converting file time to unix epoch*/
	tmpres /= 10;  /*convert into microseconds*/
	tmpres -= DELTA_EPOCH_IN_MICROSECS;
	tv->tv_sec = (__int32)(tmpres*0.000001);
	tv->tv_usec = (tmpres % 1000000);


	//_tzset(),don't work properly, so we use GetTimeZoneInformation
	rez = GetTimeZoneInformation(&tz_winapi);
	tz->tz_dsttime = (rez == 2) ? true : false;
	tz->tz_minuteswest = tz_winapi.Bias + ((rez == 2) ? tz_winapi.DaylightBias : 0);

	return 0;
}

void createExplosion(){

	float x = randomFloatBetween(-90.0, 90.0);
	float y = randomFloatBetween(5.0, 90.0);
	float z = randomFloatBetween(-90.0, 90.0);

	float s = randomFloatBetween(0, 40);

	ParticleSystem2* temp = new ParticleSystem2();
	temp->setShader(sdrCtl.getShader("pe_system"));
	temp->setType("Particle_System");
	temp->setName("Particle_Test");
	//temp->setLoopInf(false);
	//temp->setLoopCount(1);
	temp->setLoopInf(true);
	temp->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG");
	temp->setFog(fog);
	temp->setModelM(glm::translate(vec3(x, y, z)));
	temp->setTime(s);
	explosion_list.push_back(temp);

	cout << "BOOM! (" << x << "," << y << "," << z << ") t=" << s << endl;	
}

void stopVibrate(int i){
	Player1->Vibrate(0, 0);
}
void Vibrate(int L, int R, int time){
	if (USE_JOYSTICK){
		Player1->Vibrate(65535, 65535);
		glutTimerFunc(500, stopVibrate, 0);
	}
}

void projectileAttack(int playerID, Camera * cam)
{
	mat4 test = cam->getCamToWorldM();
	vec4 holder = test*vec4(0, 0, -1, 0); //orientation of camera in object space
	mat4 player1 = player_list[playerID]->getModelM();
	vec4 playerHolder = player1*vec4(0, 0, 0, 1);

	Projectile* pjt = new Projectile(player_list.size());
	if (playerID % 2){//monkey throws
		pjt->setVAO(MOM.mother_of_banana->getVAO());
		pjt->setEntries(MOM.mother_of_banana->getEntries());
		pjt->setTextures(MOM.mother_of_banana->getTextures());
		pjt->setAdjustM(MOM.mother_of_banana->getAdjustM());
	}
	else{//chipmonk throws
		pjt->setVAO(MOM.mother_of_nut->getVAO());
		pjt->setEntries(MOM.mother_of_nut->getEntries());
		pjt->setTextures(MOM.mother_of_nut->getTextures());
		pjt->setAdjustM(MOM.mother_of_nut->getAdjustM());
	}
	pjt->setShader(sdrCtl.getShader("basic_model"));
	pjt->setShininess(30);
	pjt->setFog(fog);

	//cubeT->postTrans(glm::translate(vec3(playerHolder[0] -2 + ((holder[0]) / 4), playerHolder[1], playerHolder[2] - (holder[2] / 4))));
	pjt->setModelM(player1*glm::translate(vec3(0, 1, 0)));//get the new cube matrix by translating the player0 matrix forward in player0 object space. This way the new matrix will inherit player0 oriantation 
	pjt->setAABB(AABB(vec3(-0.5, -0.5, -0.5), vec3(0.5, 0.5, 0.5)));
	AABB hold = pjt->getAABB();
	pjt->setStartX(hold.max[0]);
	pjt->setStartY(hold.max[2]);
	pjt->setDistance(20);
	pjt->setShadowTex(shadow_map_id);

	//Name and type
	pjt->setType("Cube");
	pjt->setName("Test Cube" + std::to_string(projectile_counter));
	projectile_counter++;
	//Add Cube to the draw list
	////////////////////////////////////////////////////////Window::addDrawList(cubeT);
	projectile_list.push_back(pjt);
	pjt->setSpeed(50);
	//cubeT->setHMove((holder[0] / 4));
	pjt->setVelocity(vec3(holder)*50.0f);// set object space velocity to camera oriantation in object space. Since camera always have the same xz oriantation as the object, xz oriantation wouldnt change when camera rotate.
	//cubeT->setVMove(1);  //do this if you want the cube to not have vertical velocity. uncomment the above setVelocity.
	//cout << holder[0] << ' ' << holder[1] << ' ' << holder[2] << ' ' << playerHolder[0] << ' ' << playerHolder[2] << endl;
}
void despawnProjectile()
{
	for (uint i = 0; i < projectile_list.size(); i++)
	{
		float startX = projectile_list[i]->getStartX();
		float startY = projectile_list[i]->getStartY();
		AABB curr = projectile_list[i]->getAABB();
		int distance = sqrt(pow(curr.max[0] - startX, 2) + pow(curr.max[2] - startY, 2));//Pythagorean Theorem

		//cout << startX << " " << curr.max[0] << " " << curr.max[0] - startX << " " << distance << endl;
		if (distance >= (*projectile_list[i]).getDistance())
		{
			////////////////////////////////////////////////Window::removeDrawList((*projectile[i]).getName());
			delete projectile_list[i];
			projectile_list.erase(projectile_list.begin() + i);
		}
	}
}
void simulateProjectile(float t)
{
	for (uint i = 0; i < projectile_list.size(); i++){
		projectile_list[i]->addVelocity(vec3(0.0, -9.8, 0.0)*t);
		projectile_list[i]->preTrans(glm::translate(projectile_list[i]->getVelocity()*t));
		projectile_list[i]->setAdjustM(glm::rotate(mat4(1.0), t*360.0f, vec3(-1.0, 0, 0))*projectile_list[i]->getAdjustM());
	}
}

void Window::idleCallback(void)
{
	static float anim_time = 0;
	vector<mat4> Transforms;
	//GLSLProgram* sd;
	vector<mat4> playerMs;

	switch (myClientState->getState()){
	case 0:
		if (!menuMusic->getFadeDone()){
			menuMusic->fadeUpdate();
		}
		break;
	case 1:
	case 2:
	case 3:
		
		if (alive){
			first_change = true;
			cam->setCamM(mat4(1.0));
			cam->setCamMode(0);
		}
		else if(first_change){
			cam->setCamM(glm::translate(vec3(0,100,0))*glm::rotate(mat4(1.0),-90.0f,vec3(1,0,0)));
			cam->setCamMode(1);
			first_change = false;
		}
		cam->update();

		/*
		QueryPerformanceCounter(&current);
		delta = (double)(current.QuadPart - last.QuadPart) / (double)freq.QuadPart;
		last = current;
		anim_time += delta;
		*/

		LARGE_INTEGER ct;
		QueryPerformanceCounter(&ct);
		for (uint i = 0; i < player_list.size(); i++){
			((Mesh*)player_list[i])->BoneTransform(player_list[i]->getAnimation((double)ct.QuadPart / (double)freq.QuadPart), Transforms);
			((Mesh*)player_list[i])->setTransforms(Transforms);
		}

		//particle animation
		for (uint i = 0; i < panim_list.size(); i++){
			if (!panim_list[i]->update()){
				if (panim_list[i] == 0){//one time
					delete panim_list[i];
					panim_list.erase(panim_list.begin() + i);
					i--;
				}
				else{//continuous
					panim_list[i]->setStartTime(ct);
				}
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

		despawnProjectile();

		break;
	default:
		break;
	}

	if (USE_JOYSTICK){

		//Gamepad Input Handeling Main Menu
		if (myClientState->getState() == 0){
			short LX = Player1->GetState().Gamepad.sThumbLX;
			short LY = Player1->GetState().Gamepad.sThumbLY;

			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_START)
			{
				if (!STR){
					STR = true;
					int fakeX = 0.5 * Window::width;
					int fakeY = 0.4 * Window::height;
					mouseFunc(GLUT_LEFT_BUTTON, GLUT_DOWN, fakeX, fakeY);
				}
			}
			else{
				if (STR){
					STR = false;
				}
			}

			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
			{
				if (!FLS){
					FLS = true;
					int fakeX = 0.5 * Window::width;
					int fakeY = 0.75 * Window::height;
					mouseFunc(GLUT_LEFT_BUTTON, GLUT_DOWN, fakeX, fakeY);
				}
			}
			else{
				if (FLS){
					FLS = false;
				}
			}

		}
		
		//Gamepad Input Handeling Game
		if (myClientState->getState() == 1){
			short LX = Player1->GetState().Gamepad.sThumbLX;
			short LY = Player1->GetState().Gamepad.sThumbLY;
			short RX = Player1->GetState().Gamepad.sThumbRX;
			short RY = Player1->GetState().Gamepad.sThumbRY;

			float leftTrigger = (float)Player1->GetState().Gamepad.bLeftTrigger / 255;
			float rightTrigger = (float)Player1->GetState().Gamepad.bRightTrigger / 255;
			bool LT = false;
			bool RT = false;
			if (leftTrigger > 0.2){ LT = true; }
			if (rightTrigger > 0.2){ RT = true; }

			if (LX > 15000){
				//cout << "Left Stick X: RIGHT!" << endl;
				if (!LR){
					LR = true;
					keyboard('d', 0, 0);
				}
			}
			else if (LX < -15000){
				//cout << "Left Stick X: LEFT!" << endl;
				if (!LL){
					LL = true;
					keyboard('a', 0, 0);
				}
			}
			else{
				//cout << "Left Stick X: CENTER!" << endl;
				if (LR){
					LR = false;
					keyUp('d', 0, 0);
				}
				if (LL){
					LL = false;
					keyUp('a', 0, 0);
				}
			}

			if (LY > 15000){
				//cout << "Left Stick Y: UP!" << endl;
				if (!LU){
					LU = true;
					keyboard('w', 0, 0);
				}
			}
			else if (LY < -15000){
				//cout << "Left Stick Y: DOWN!" << endl;
				if (!LD){
					LD = true;
					keyboard('s', 0, 0);
				}
			}
			else{
				//cout << "Left Stick Y: CENTER!" << endl;
				if (LU){
					LU = false;
					keyUp('w', 0, 0);
				}
				if (LD){
					LD = false;
					keyUp('s', 0, 0);
				}
			}

			int x = 0.5 * Window::width;
			int y = 0.5 * Window::height;

			if (RX > 15000){
				//cout << "Right Stick X: RIGHT!" << endl;
				x = 0.54 * Window::width;
				//motionFunc(x, y);
			}
			else if (RX < -15000){
				//cout << "Right Stick X: LEFT!" << endl;
				x = 0.46 * Window::width;
				//motionFunc(x, y);
			}
			else{
				//cout << "Right Stick X: CENTER!" << endl;
				x = 0.5 * Window::width;
				//motionFunc(x, y);
			}

			if (RY > 15000){
				//	cout << "Right Stick Y: UP!" << endl;
				y = 0.46 * Window::height;
				//motionFunc(x, y);
			}
			else if (RY < -15000){
				//cout << "Right Stick Y: DOWN!" << endl;
				y = 0.54 * Window::height;
				//motionFunc(x, y);
			}
			else{
				//cout << "Right Stick Y: CENTER!" << endl;
				y = 0.5 * Window::height;
				//motionFunc(x, y);
			}
			//Pass the sudo mouse cords to the mouse update function
			motionFunc(x, y);

			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_START)
			{
				//Player1->Vibrate(65535, 0);
				if (!ESC){
					ESC = true;
					keyboard(27, 0, 0);
				}
			}
			else{
				if (ESC){
					ESC = false;
					keyUp(27, 0, 0);
				}
			}

			if ((Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER))
			{
				//Player1->Vibrate(65535, 0);
				if (!SPT){
					SPT = true;
					//keyboard(' ', 0, 0);
					//SPRINT STUFF HERE PLZ
				}
			}
			else{
				if (SPT){
					SPT = false;
					//keyUp(' ', 0, 0);
				}
			}

			if ((Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A) || (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER))
			{
				//Player1->Vibrate(65535, 0);
				if (!JMP){
					JMP = true;
					keyboard(' ', 0, 0);
				}
			}
			else{
				if (JMP){
					JMP = false;
					keyUp(' ', 0, 0);
				}
			}

			if ((Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_X) || LT)
			{
				//Player1->Vibrate(65535, 0);
				if (!ATT1){
					ATT1 = true;
					//keyboard(' ', 0, 0);
					mouseFunc(GLUT_LEFT_BUTTON, GLUT_DOWN, x, y);
				}
			}
			else{
				if (ATT1){
					ATT1 = false;
					mouseFunc(GLUT_LEFT_BUTTON, GLUT_UP, x, y);
				}
			}

			if ((Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_B) || RT)
			{
				//Player1->Vibrate(65535, 0);
				if (!ATT2){
					ATT2 = true;
					mouseFunc(GLUT_RIGHT_BUTTON, GLUT_DOWN, x, y);
				}
			}
			else{
				if (ATT2){
					ATT2 = false;
					mouseFunc(GLUT_RIGHT_BUTTON, GLUT_UP, x, y);
				}
			}
		}

		//Gamepad Input Handeling Game Menu
		if (myClientState->getState() == 2){
			short LX = Player1->GetState().Gamepad.sThumbLX;
			short LY = Player1->GetState().Gamepad.sThumbLY;

			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_START)
			{
				if (!STR){
					STR = true;
					int fakeX = 0.6 * Window::width;
					int fakeY = 0.5 * Window::height;
					mouseFunc(GLUT_LEFT_BUTTON, GLUT_DOWN, fakeX, fakeY);
				}
			}
			else{
				if (STR){
					STR = false;
				}
			}

			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
			{
				if (!FLS){
					FLS = true;
					int fakeX = 0.3 * Window::width;
					int fakeY = 0.5 * Window::height;
					mouseFunc(GLUT_LEFT_BUTTON, GLUT_DOWN, fakeX, fakeY);
				}
			}
			else{
				if (FLS){
					FLS = false;
				}
			}
		}

		//Gamepad Input Handeling Death Screen
		if (myClientState->getState() == 3){
			short LX = Player1->GetState().Gamepad.sThumbLX;
			short LY = Player1->GetState().Gamepad.sThumbLY;
		}
	}

	//createExplosion();
	mySoundSystem->update();
	updateShaders();
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
		logo->draw();

		glDisable(GL_DEPTH_TEST);
		RenderString((Window::width) * .41, (Window::height) * .78, GLUT_BITMAP_HELVETICA_18, ip_adress, vec3(1.0f, 1.0f, 1.0f));
		glEnable(GL_DEPTH_TEST);
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
		for (uint i = 0; i < player_list.size(); ++i)
		{
			player_list[i]->draw(LightProjection, LightView);
		}
		for (uint i = 0; i < tower_list.size(); ++i)
		{
			tower_list[i]->draw(LightProjection, LightView);
		}
		for (uint i = 0; i < stationary_list.size(); ++i)
		{
			if (stationary_list[i] == ground)
				continue;
			stationary_list[i]->draw(LightProjection, LightView);
		}
		for (uint i = 0; i < projectile_list.size(); ++i)
		{
			projectile_list[i]->draw(LightProjection, LightView);
		}		
		
		///////  2nd pass: render onto screen ////////////
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, width, height);
		shadow->Bind(GL_TEXTURE0 + shadow_map_id);

		for (uint i = 0; i < draw_list.size(); ++i)
		{
			draw_list[i]->draw();
		}
		for (uint i = 0; i < player_list.size(); ++i)
		{
			player_list[i]->draw();
		}
		for (uint i = 0; i < tower_list.size(); ++i)
		{
			tower_list[i]->draw();
		}
		for (uint i = 0; i < stationary_list.size(); ++i)
		{
			stationary_list[i]->draw();
		}
		for (uint i = 0; i < projectile_list.size(); ++i)
		{
			projectile_list[i]->draw();
		}
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		for (uint i = 0; i < panim_list.size(); i++){
			panim_list[i]->draw();
		}
		glDisable(GL_BLEND);

		//	md5->draw();

		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glDepthMask(GL_FALSE); // without it some part of model will cover other part of model which looks weird
		//	md6->draw();
		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);

		m_billboardList.Render(Projection, View, 1.0f);
		m_billboardList2.Render(Projection, View, 1.0f);
		m_billboardList3.Render(Projection, View, 1.0f);

		glEnable(GL_POINT_SPRITE);
		glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthMask(GL_FALSE);
		//particle->draw(Projection, View);
		//particle2->draw(Projection, View);
		//particle3->draw(Projection, View);
		//particle4->draw(Projection, View);
		//particle5->draw(Projection, View);
		//particle6->draw(Projection, View);
		//particle7->draw(Projection, View);
		//particle8->draw();
		t0_ps_01->draw(Projection, View);
		t0_ps_02->draw(Projection, View);
		t0_ps_03->draw(Projection, View);

		t1_ps_01->draw(Projection, View);
		t1_ps_02->draw(Projection, View);
		t1_ps_03->draw(Projection, View);

		t2_ps_01->draw(Projection, View);
		t2_ps_02->draw(Projection, View);
		t2_ps_03->draw(Projection, View);

		t3_ps_01->draw(Projection, View);
		t3_ps_02->draw(Projection, View);
		t3_ps_03->draw(Projection, View);

		testSystem->draw(Projection, View);

		for (uint i = 0; i < explosion_list.size(); ++i)
		{
			explosion_list[i]->draw(Projection, View);
		}
		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);
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
	case 4:
		settings->draw();
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
	
	cli->write(*sendVec);
	io_service.poll();
	//mouseState = 0;
	cam_dx = 0;

	// RECEIVE STUFF
	//recvVec = cli->read();
	out = cli->read();
	io_service.poll();

	//std::cout << out << std::endl;

	if (out[0] == '[')
	{
		unsigned pos = out.find("\n");
		out = out.substr(0, pos);
		recvVec = gs.parsePosString(out);
		recvValid = true;
		//cout << "size: " << recvVec->size() << endl;
		//for (int i = 0; i < 6; i++){
			//cout << i << " : " << (*recvVec)[i].first.c_str() << endl;
		//}
	}
	else
		recvValid = false;
	
	//std::cout << "pair 0: " << atoi(&((*recvVec)[0].first.c_str())[0]) << std::endl;
	//std::cout << "pair 1: " << atoi(&((*recvVec)[1].first.c_str())[0]) << std::endl;
	//std::cout << "pair 2: " << atoi(&((*recvVec)[2].first.c_str())[0]) << std::endl;
	//std::cout << "pair 3: " << atoi(&((*recvVec)[3].first.c_str())[0]) << std::endl;

	//cout << "size: " << recvVec->size() << endl;
	//for (int i = 0; i < 6; i++){
	//	cout <<i<<" : "<< (*recvVec)[i].first.c_str()<<endl;
	//}
	bool p0f = false;
	bool p1f = false;
	bool p2f = false;
	bool p3f = false;
	//stateID = atoi(&((*recvVec)[0].first.c_str())[0]);
	if (recvValid)
	{
		// get shoot bit from recvVec for player 0
		if (parseOpts->getShoot(recvVec, 0))
		{
			//std::cout << "Projectile fire" << std::endl;
			projectileAttack(0, cam);
			if (playerID == 0)
			{
				myUI->setShots(1);
			}
			cout << "FIRE 0!" << endl;
			p0f = true;
		}

		if (parseOpts->getShoot(recvVec, 1))
		{
			//std::cout << "Projectile fire" << std::endl;
			projectileAttack(1, cam);
			if (playerID == 1)
			{
				myUI->setShots(1);
			}
			cout << "FIRE 1!" << endl;
			p1f = true;
		}

		if (parseOpts->getShoot(recvVec, 2))
		{
			//std::cout << "Projectile fire" << std::endl;
			projectileAttack(2, cam);
			if (playerID == 2)
			{
				myUI->setShots(1);
			}
			cout << "FIRE 2!" << endl;
			p2f = true;
		}

		if (parseOpts->getShoot(recvVec, 3))
		{
			//std::cout << "Projectile fire" << std::endl;
			projectileAttack(3, cam);
			if (playerID == 3)
			{
				myUI->setShots(1);
			}
			cout << "FIRE 3!" << endl;
			p3f = true;
		}

		mats[atoi(&((*recvVec)[0].first.c_str())[0])] = (*recvVec)[0].second;
		mats[atoi(&((*recvVec)[1].first.c_str())[0])] = (*recvVec)[1].second;
		mats[atoi(&((*recvVec)[2].first.c_str())[0])] = (*recvVec)[2].second;
		mats[atoi(&((*recvVec)[3].first.c_str())[0])] = (*recvVec)[3].second;

		player_list[0]->setModelM(mats[0]);
		player_list[1]->setModelM(mats[1]);
		player_list[2]->setModelM(mats[2]);
		player_list[3]->setModelM(mats[3]);

		tower_list[atoi(&((*recvVec)[4].first.c_str())[1])]->setModelM((*recvVec)[4].second);
		tower_list[atoi(&((*recvVec)[5].first.c_str())[1])]->setModelM((*recvVec)[5].second);
		tower_list[atoi(&((*recvVec)[6].first.c_str())[1])]->setModelM((*recvVec)[6].second);
		tower_list[atoi(&((*recvVec)[7].first.c_str())[1])]->setModelM((*recvVec)[7].second);
		/*
		mats[atoi(&((*recvVec)[8].first.c_str())[0])]  = (*recvVec)[8].second;
		mats[atoi(&((*recvVec)[9].first.c_str())[0])]  = (*recvVec)[9].second;
		mats[atoi(&((*recvVec)[10].first.c_str())[0])] = (*recvVec)[10].second;
		mats[atoi(&((*recvVec)[11].first.c_str())[0])] = (*recvVec)[11].second;
		*/
		i++;

		vec4 temp(0.0, 0.0, 0.0, 1.0);
		if (p0f && (playerID!=0)){
			temp = player_list[0]->getModelM() *temp;
			FMOD_VECTOR pt = { temp.x, temp.y, temp.z };
			posTestSound2->setPosition(pt);
			posTestSound2->Play3D(View);
		}
		if (p1f && (playerID != 1)){
			temp = player_list[1]->getModelM() * temp;
			FMOD_VECTOR pt = { temp.x, temp.y, temp.z };
			posTestSound2->setPosition(pt);
			posTestSound2->Play3D(View);
		}
		if (p2f && (playerID != 2)){
			temp = player_list[2]->getModelM() * temp;
			FMOD_VECTOR pt = { temp.x, temp.y, temp.z };
			posTestSound2->setPosition(pt);
			posTestSound2->Play3D(View);
		}
		if (p3f && (playerID != 3)){
			temp = player_list[3]->getModelM() * temp;
			FMOD_VECTOR pt = { temp.x, temp.y, temp.z };
			posTestSound2->setPosition(pt);
			posTestSound2->Play3D(View);
		}

		simulateProjectile(diff);

	}

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
  ConfigSettings::config->getValue("Gamepad", USE_JOYSTICK);

  struct timeval2 tv;
  struct timezone2 tz;
  ZeroMemory(&tv, sizeof(tv));
  ZeroMemory(&tz, sizeof(tz));
  gettimeofday(&tv, &tz); // call gettimeofday()
  srand(tv.tv_usec * tv.tv_sec);

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
  glEnable(GL_CULL_FACE);     // disable back face culling to render both sides of polygons
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

  FMOD_VECTOR pt = { 0.0f, 0.0f, 0.0f };
  FMOD_VECTOR vt = { 0.0f, 0.0f, 0.0f };

  posTestSound = new Sound(mySoundSystem, "Sound/hard_hit.ogg", true);
  posTestSound->setVolume(0.5);
  posTestSound->setPosition(pt);
  posTestSound->setVelocity(vt);
  posTestSound->setMinDistance(5.0f);
  posTestSound->setMaxDistance(10000.0f);

  posTestSound2 = new Sound(mySoundSystem, "Sound/disc_fire.ogg", true);
  posTestSound2->setVolume(0.5);
  posTestSound2->setPosition(pt);
  posTestSound2->setVelocity(vt);
  posTestSound2->setMinDistance(5.0f);
  posTestSound2->setMaxDistance(10000.0f);  

  posTestMusic = new Music(mySoundSystem, "Sound/prepunch1.ogg", true);
  posTestMusic->setLoopCount(-1);
  posTestMusic->setVolume(0.75);
  posTestMusic->setPosition(pt);
  posTestMusic->setVelocity(vt);
  posTestMusic->setMinDistance(5.0f);
  posTestMusic->setMaxDistance(10000.0f);
  
  if (buf){
	  int screen_width = glutGet(GLUT_WINDOW_WIDTH);
	  int screen_height = glutGet(GLUT_WINDOW_HEIGHT);
	  Window::width = screen_width;
	  Window::height = screen_height;
	  glViewport(0, 0, screen_width, screen_height);  // set new view port size
	  Projection = glm::perspective(fov, (float)screen_width / screen_height, nearClip, farClip);
  }

  do{
	  QueryPerformanceCounter(&current);
	  diff = (double)(current.QuadPart - last.QuadPart) / (double)freq.QuadPart;
	  last = current;

	  glutMainLoopEvent();
	  
	  Window::idleCallback();

	  //printf("LOOP!\n");
	  if (connected){
		  server_update(0);
	  }
	  
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

  for (uint i = 0; i < draw_list.size(); ++i)
  {
	  delete draw_list[i];
  }
  for (uint i = 0; i < player_list.size(); ++i)
  {
	  delete player_list[i];
  }
  for (uint i = 0; i < stationary_list.size(); ++i)
  {
	  delete stationary_list[i];
  }
  for (uint i = 0; i < texture_list.size(); ++i)
  {
	  delete texture_list[i];
  }
  for (uint i = 0; i < sound_list.size(); ++i)
  {
	  delete sound_list[i];
  }

  return 0;
}

LARGE_INTEGER time_track;
void keyboard(unsigned char key, int, int){
	QueryPerformanceCounter(&time_track);
	double time = (double)time_track.QuadPart / (double)freq.QuadPart;
	switch (myClientState->getState()){
	case 0:
		if (key == ' '){
			if (space_up){
				testSound[2]->Play();
				//myClientState->setState(1);
			}
		}

		if (((key > 96 && key < 123) || (key > 47 && key < 58) || key == 46) && text_flag){
			if (but_up && m_pos < m_lenght - 1){
				but_up = 0;
				ip_adress[m_pos] = key;
				m_pos++;

				if (m_pos < m_lenght)
				{
					ip_adress[m_pos] = '|';
				}
			}
		}

		if (key == 8 && text_flag){
			if (but_up && m_pos >= 1){
				
				but_up = 0;

				if (m_pos < m_lenght)
				{
					ip_adress[m_pos] = 0;
				}

				m_pos--;
				ip_adress[m_pos] = '|';
			}
		}

		if (key == 13 && text_flag){
			if (but_up){
				text_flag = 0;
			}
		}
		break;
	case 1:

		if (key == 'a'){
			if (!(keyState & 1)){
				keyState = keyState | 1;
				player_list[playerID]->setAnimLoop(1, time);
			}
		}
		if (key == 'd'){
			if (!(keyState & 1<<1)){
				keyState = keyState | 1 << 1;
				player_list[playerID]->setAnimLoop(1, time);
			}
		}
		if (key == 'w'){
			if (!(keyState & 1<<2)){
				keyState = keyState | 1 << 2;
				player_list[playerID]->setAnimLoop(1, time);
			}
		}
		if (key == 's'){
			if (!(keyState & 1<<3)){
				keyState = keyState | 1 << 3;
				player_list[playerID]->setAnimLoop(1, time);
			}
		}
		if (key == 'W'){
			if (!(keyState & 1<<5)){
				keyState = keyState | 1 << 5;
				player_list[playerID]->setAnimLoop(1, time);
			}
		}

		//This calls the player damaged effects
		if (key == 'm'){
			particle8->StartLoop();
			Vibrate(65535, 65535, 500);
		}
		//This creates random explosion
		if (key == 'n'){
			createExplosion();
		}

		//This plays sound at <0,0,0>
		if (key == 'i'){
			cout << posTestSound->getVolume() << "," << posTestSound->getMinDistance() << "," << posTestSound->getMaxDistance() << endl;

			posTestSound->Play3D(View);

			cout << "Playing Sound!" << endl;
		}

		//This creates looping music at <0,0,0>
		if (key == 'o'){
			posTestMusic->Play3D();

			cout << "Playing Music!" << endl;
		}

		if (key == 27){
			//running = false;
			//exit(0);
			myClientState->setState(2);
		}
		if (key == ' '){
			keyState = keyState | 1 << 4;
			player_list[playerID]->setAnimOnce(2, time);

			if (space_up){
				space_up = 0;

				testSound[1]->Play();
			}
		}

		//Added for sound debugging
		if (key == 'f'){
			testSound[2]->Play();
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
	case 4:
		if (key == 27){
			myClientState->setState(0);
		}
		break;
	default:
		break;
	}
}
void keyUp (unsigned char key, int x, int y) {  
	QueryPerformanceCounter(&time_track);
	double time = (double)time_track.QuadPart / (double)freq.QuadPart;
	switch (myClientState->getState()){
	case 0:
		if ((key > 96 && key < 123) || (key > 47 && key < 58) || key == 46){
			but_up = 1;
		}
		if (key == 8){
			but_up = 1;
		}
		break;
	case 1:

		if (key == 'a'){
			keyState = keyState & ~1;
			player_list[playerID]->unsetAnimLoop(1, time);
		}
		if (key == 'd'){
			keyState = keyState & ~(1 << 1);
			player_list[playerID]->unsetAnimLoop(1, time);
		}
		if (key == 'w'){
			// These vars need to become arrays for each player
			// and all this needs to move into the server
			if (glutGetModifiers() & GLUT_ACTIVE_SHIFT){
				if (sprint_up >= 10){
				//	testSound[1]->Play(FMOD_CHANNEL_FREE, 0, &channel);
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
			player_list[playerID]->unsetAnimLoop(1, time);
		}
		if (key == 's'){
			keyState = keyState & ~(1 << 3);
			player_list[playerID]->unsetAnimLoop(1, time);
		}
		if (key == 'W'){
			keyState = keyState & ~(1 << 5);
			player_list[playerID]->unsetAnimLoop(1, time);
		}
		if (key == ' '){
			keyState = keyState & ~(1 << 4);
			space_up = 1;
		}
		if (key == 'l'){
			alive = !alive;
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
	case 4:
		break;
	default:
		break;
	}
}
void mouseFunc(int button, int state, int x, int y)
{
	QueryPerformanceCounter(&time_track);
	double time = (double)time_track.QuadPart / (double)freq.QuadPart;

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
				testSound[7]->Play();
				if (!connected){
					
					//Player mats
					recvVec->push_back(std::make_pair("initRecvPos_c", mat4(0.0f)));
					recvVec->push_back(std::make_pair("initRecvPos_c", mat4(0.0f)));
					recvVec->push_back(std::make_pair("initRecvPos_c", mat4(0.0f)));
					recvVec->push_back(std::make_pair("initRecvPos_c", mat4(0.0f)));

					//Tower mats
					recvVec->push_back(std::make_pair("initRecvPos_c", mat4(0.0f)));
					recvVec->push_back(std::make_pair("initRecvPos_c", mat4(0.0f)));
					recvVec->push_back(std::make_pair("initRecvPos_c", mat4(0.0f)));
					recvVec->push_back(std::make_pair("initRecvPos_c", mat4(0.0f)));
					/*
					//Player cam mats
					recvVec->push_back(std::make_pair("initRecvPos_c", mat4(0.0f)));
					recvVec->push_back(std::make_pair("initRecvPos_c", mat4(0.0f)));
					recvVec->push_back(std::make_pair("initRecvPos_c", mat4(0.0f)));
					recvVec->push_back(std::make_pair("initRecvPos_c", mat4(0.0f)));
					*/
					sendVec->push_back(std::make_pair("initKey_c", mat4(0.0f)));
					sendVec->push_back(std::make_pair("initMouse_c", mat4(0.0f)));
					sendVec->push_back(std::make_pair("initCam_c", mat4(0.0f)));
					sendVec->push_back(std::make_pair("initCamRot_c", mat4(0.0f)));

					parseOpts = new ParseOpts();

					std::string	mine = ConvertAddress(ip_adress);
					try
					{
						cli = new tcp_client(io_service, mine, "13");
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
					//cam->postTrans(glm::translate(vec3(0, 2.5, 6)));
					cam->init(1.0,1.5, 6, 1.0);

					connected = true;
				}
				menuMusic->Stop();
			//	gameMusic->setFade(0.75, 0.005);
				gameMusic->Play();
				server_update(0);
			}
			else if (click == 2){
				testSound[7]->Play();
				Sleep(1250);
				running = false;
				exit(0);
			}

			else if (click == 3){
				myClientState->setState(4);
			}
			else if (click == 4){
				text_flag = 1;
			}
		}

		break;
	case 1:

		if (state == GLUT_DOWN){
			if (button == GLUT_LEFT_BUTTON){
				if (left_mouse_up){
					left_mouse_up = 0;
					mouseState = mouseState | 1;

					testSound[4]->Play();
					///scene->basicAttack(playerID);
					
					//UI testing purposes
					myUI->setLess_Life(1);
					myUI->setShots(1);

					player_list[playerID]->setAnimOnce(3, time);
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

					testSound[3]->Play();

					//projectileAttack(playerID, cam);
					player_list[playerID]->setAnimOnce(3, time);
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

					testSound[5]->Play();
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
				testSound[7]->Play();
				myClientState->setState(1);
			}
			if (click == 2){
				testSound[7]->Play();
				myClientState->setState(0);
				gameMusic->Stop();
				menuMusic->setFade(0.75, 0.005);
				menuMusic->Play();
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
	case 4:
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
		int sound;
		sound = myMainMenu->checkHighlight(newX, newY);
		if (sound){
			if (!inMenuBox){
				testSound[6]->Play();
			}
			inMenuBox = true;
		}
		else{
			inMenuBox = false;
		}
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
		int sound2;
		sound2 = myGameMenu->checkHighlight(newX, newY);
		if (sound2){
			if (!inMenuBox){
				testSound[6]->Play();
			}
			inMenuBox = true;
		}
		else{
			inMenuBox = false;
		}
		break;
		break;
	case 3:
		newX = (float)x / Window::width;
		newY = (float)y / Window::height;
		myDeathScreen->checkHighlight(newX, newY);
		break;
	case 4:
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
			//	testSound[1]->Play(FMOD_CHANNEL_FREE, 0, &channel);
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
		sprintf_s(buf, "%s %s %s", "Loading Shader: ", name.c_str(), "...done!");

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		RenderString((Window::width) / 4, (Window::height) / 2, GLUT_BITMAP_HELVETICA_18, (unsigned char*)buf, vec3(0.0f, 1.0f, 0.0f));

		glutSwapBuffers();
	}

	sdrCtl.createVGFShader("billboard", "Shaders/billboard.vert", "Shaders/billboard.geom", "Shaders/billboard.frag");
	sdrCtl.createVGFShader("billboard_anim", "Shaders/billboard_anim.vert", "Shaders/billboard_anim.geom", "Shaders/billboard_anim.frag");
	sdrCtl.createVCEFShader("ground_tess", "Shaders/ground_tess.vert", "Shaders/ground_tess.cntl", "Shaders/ground_tess.eval", "Shaders/ground_tess.frag");

	updateShaders();
}
void initialize(int argc, char *argv[])
{

	myClientState = new ClientState();

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&last);

	draw_list.clear();

	Player1 = new CXBOXController(1);

	//Init the JSON parser for the map
	map_info = new JSON_Parser("Maps/Test1.json");
	printf("Loading Map: %s\n", map_info->GetMapName().c_str());
	sprintf_s(buf, "%s %s", "Loading Map:", map_info->GetMapName().c_str());

	GLenum err = glewInit();
	if( GLEW_OK != err )
	{
		fprintf(stderr, "Error initializing GLEW: %s\n", 
			glewGetErrorString(err) );
	}

	//Clear window to black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();

	//AUDIO START!
	if (loadAudio()){
		printf("Error with FMOD Init!\n");
	}
	else{
		printf("FMOD Init successful!\n");
	}

	FMOD_VECTOR myPosition = { 0.0f, 0.0f, 0.0f };
	FMOD_VECTOR myVelocity = { 0.0f, 0.0f, 0.0f };
	mySoundSystem->setListenerPosVel(myPosition, myVelocity);
	mySoundSystem->updateListener();

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
	light[0].pos = vec4(0,200,0,1);
	light[0].specular = vec3(0.1,0.1,0.1);
	light[0].diffuse = vec3(0.9, 0.9, 0.9);
	light[0].ambient = vec3(0.35, 0.35, 0.35);
	light[0].dir = vec4(0,-1,0,1);
	light[0].spotCutOff = cos(10.0/180*M_PI);
	LightView = glm::lookAt(vec3(light[0].pos), vec3(0, 0, 0), vec3(1, 0, 0));
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
	settings = new Settings();
	endScreen = new End_Screen();
	logo = new Logo();

	ground = new Ground();
	ground->setShader(sdrCtl.getShader("ground_tess"));
	ground->loadColorTex("img/moon_tex/moon_COLOR.png", "PNG");
	ground->loadDispTex("img/moon_tex/moon_DISP.png", "PNG");
	ground->loadNormalTex("img/moon_tex/moon_NRM.png", "PNG");
	ground->loadOccTex("img/moon_tex/moon_OCC.png", "PNG");
	ground->loadSpecTex("img/moon_tex/moon_SPEC.png", "PNG");
	ground->setDimensionS(200);
	ground->setDimensionT(200);
	ground->setRow(100);
	ground->setColumn(100);
	ground->setHeight(6);
	ground->setShadowTex(shadow_map_id);
	ground->setFog(fog);
	ground->generate();
	ground->setType("Ground");
	ground->setName("Ground");
	stationary_list.push_back(ground);

	skybox = new SkyBox(-200, 200, -200, 200, -200, 200);
	skybox->setShader(sdrCtl.getShader("basic_skybox"));
	skybox->setTexUnit(3);
	skybox->setFog(fog);
	skybox->setType("Skybox");
	skybox->setName("Skybox");
	draw_list.push_back(skybox);

	//mother of all wrenches. initialize once cause loading mesh is slow. All other wrenches are the copies of mother
	MOM.mother_of_wrench = new Mesh();
	MOM.mother_of_wrench->LoadMesh("Model/newWrench_animated.dae", false);
	MOM.mother_of_wrench->setShader(sdrCtl.getShader("basic_model"));
	MOM.mother_of_wrench->setShadowTex(shadow_map_id);
	MOM.mother_of_wrench->setAdjustM(glm::translate(vec3(0.0, 0.5, 0.0))*glm::rotate(mat4(1.0), 90.0f, vec3(0, 1.0, 0))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0))*glm::scale(vec3(0.07, 0.07, 0.07)));
	MOM.mother_of_wrench->setShininess(30);
	MOM.mother_of_wrench->setFog(fog);

	MOM.mother_of_banana = new Mesh();
	MOM.mother_of_banana->LoadMesh("Model/banana_animated.dae", false);
	MOM.mother_of_banana->setShader(sdrCtl.getShader("basic_model"));
	MOM.mother_of_banana->setShadowTex(shadow_map_id);
	MOM.mother_of_banana->setAdjustM(glm::translate(vec3(0.0, 0.0, 0.0))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0))*glm::scale(vec3(0.1, 0.1, 0.1)));
	MOM.mother_of_banana->setShininess(30);
	MOM.mother_of_banana->setFog(fog);

	MOM.mother_of_nut = new Mesh();
	MOM.mother_of_nut->LoadMesh("Model/nut_animated.dae", false);
	MOM.mother_of_nut->setShader(sdrCtl.getShader("basic_model"));
	MOM.mother_of_nut->setShadowTex(shadow_map_id);
	MOM.mother_of_nut->setAdjustM(glm::translate(vec3(0.0, -0.5, 0.5))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0))*glm::scale(vec3(0.20, 0.20, 0.20)));
	MOM.mother_of_nut->setShininess(30);
	MOM.mother_of_nut->setFog(fog);

	AnimController monkeyAnimController;
	monkeyAnimController.add(20 / 24.0, 5 / 24.0);//stand
	monkeyAnimController.add(0 / 24.0, 16 / 24.0);//walk
	monkeyAnimController.add(25 / 24.0, 10 / 24.0);//jump
	monkeyAnimController.add(40 / 24.0, 20 / 24.0);//attack
	monkeyAnimController.setDefault(0);//stand is the default animation
	AnimController chipmonkAnimController;
	chipmonkAnimController.add(0 / 24.0, 5 / 24.0);//stand
	chipmonkAnimController.add(10 / 24.0, 20 / 24.0);//walk
	chipmonkAnimController.add(35 / 24.0, 10 / 24.0);//jump
	chipmonkAnimController.add(50 / 24.0, 15 / 24.0);//attack
	chipmonkAnimController.setDefault(0);//stand is the default animation
	for (int i = 0; i < 4; i++){
		if (i % 2){
			Mesh* player0 = new Mesh();
			player0->LoadMesh("Model/monky2014_delete2.dae");
			//player0->LoadMesh("Model/nut_animated.dae",false);
			player0->setAnimController(monkeyAnimController);
			player0->setShader(sdrCtl.getShader("basic_model"));
			player0->setShadowTex(shadow_map_id);
			player0->setAdjustM(glm::translate(vec3(0.0, 1.35, 0.0))*glm::rotate(mat4(1.0), 180.0f, vec3(0, 1.0, 0))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0))*glm::scale(vec3(0.07, 0.07, 0.07)));
			//player0->setAdjustM(glm::translate(vec3(0.0, 0.0, 0.0))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0))*glm::scale(vec3(0.20, 0.20, 0.20)));
			player0->setShininess(30);
			player0->setFog(fog);
			player_list.push_back(player0);
		}
		else{
			Mesh* player0 = new Mesh();
			player0->LoadMesh("Model/chipmunkOculus_animated_all3.dae");
			player0->setAnimController(chipmonkAnimController);
			player0->setShader(sdrCtl.getShader("basic_model"));
			player0->setShadowTex(shadow_map_id);
			player0->setAdjustM(glm::translate(vec3(0.0, 1.05, 0.0))*glm::rotate(mat4(1.0), 180.0f, vec3(0, 1.0, 0))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0))*glm::scale(vec3(0.15, 0.15, 0.15)));
			player0->setShininess(30);
			player0->setFog(fog);
			player_list.push_back(player0);
		}
	}

	Mesh* tower0 = new Mesh();
	tower0->LoadMesh("Model/2Tower_6_bone.dae",false);
	tower0->setShader(sdrCtl.getShader("basic_model"));
	tower0->setShadowTex(shadow_map_id);
	tower0->setAdjustM(glm::translate(vec3(0.0, 1.0, 0.0))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0))*glm::scale(vec3(1.0, 1.0, 1.0)));
	tower0->setModelM(glm::translate(vec3(-30.0,0.0,-30.0)));
	tower0->setShininess(30);
	tower0->setFog(fog);
	tower_list.push_back(tower0);

	t0_ps_01 = new ParticleSystem2((float)1.0, (float)0.25, (float)0.25, (float)4.0, (float)0.5, (float)0.0, (float)360.0, (float)0.0, (float)360.0, (float)0.0);
	t0_ps_01->setShader(sdrCtl.getShader("pe_torus"));
	t0_ps_01->setType("Particle_System");
	t0_ps_01->setName("Particle_Test");
	t0_ps_01->setLoopInf(true);
	t0_ps_01->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG");
	t0_ps_01->setFog(fog);
	t0_ps_01->setBlastRadius(1.0f);// Blast radius
	t0_ps_01->setExplosionVelocity(0.5f);// Explosion velocity
	t0_ps_01->setExplosionDecay(10.0f);// Explosion decay
	t0_ps_01->setFragStartSize(12.0f);// Fragment start size
	t0_ps_01->setFragEndSize(1.0f);// Fragment end size
	t0_ps_01->setFragStartColor(vec3(0.0, 0.5, 1.0));// Fragment start color
	t0_ps_01->setFragEndColor(vec3(0.0, 0.125, 0.25));// Fragment end color
	t0_ps_01->setTime_Step(0.1f);
	t0_ps_01->setTime_Max(100.0);
	t0_ps_01->setTime_Min(0.0);
	t0_ps_01->setTime(0.0);
	//t0_ps_01->setEmitterPosition();// Emitter position
	t0_ps_01->setModelM(glm::translate(vec3(-32.0, 8.5f, -30.0))*glm::rotate(mat4(1.0), 90.0f, vec3(0.0, 1.0, 0.0)));

	t0_ps_02 = new ParticleSystem2((float)1.0, (float)0.25, (float)0.25, (float)4.0, (float)0.5, (float)0.0, (float)360.0, (float)0.0, (float)360.0, (float)0.0);
	t0_ps_02->setShader(sdrCtl.getShader("pe_torus"));
	t0_ps_02->setType("Particle_System");
	t0_ps_02->setName("Particle_Test");
	t0_ps_02->setLoopInf(true);
	t0_ps_02->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG");
	t0_ps_02->setFog(fog);
	t0_ps_02->setBlastRadius(1.0f);// Blast radius
	t0_ps_02->setExplosionVelocity(0.5f);// Explosion velocity
	t0_ps_02->setExplosionDecay(10.0f);// Explosion decay
	t0_ps_02->setFragStartSize(12.0f);// Fragment start size
	t0_ps_02->setFragEndSize(1.0f);// Fragment end size
	t0_ps_02->setFragStartColor(vec3(0.0, 0.5, 1.0));// Fragment start color
	t0_ps_02->setFragEndColor(vec3(0.0, 0.125, 0.25));// Fragment end color
	t0_ps_02->setTime_Step(0.1f);
	t0_ps_02->setTime_Max(100.0);
	t0_ps_02->setTime_Min(0.0);
	t0_ps_02->setTime(33.0);
	//t0_ps_02->setEmitterPosition();// Emitter position
	t0_ps_02->setModelM(glm::translate(vec3(-29.5, 8.5f, -28)));

	t0_ps_03 = new ParticleSystem2((float)1.0, (float)0.25, (float)0.25, (float)4.0, (float)0.5, (float)0.0, (float)360.0, (float)0.0, (float)360.0, (float)0.0);
	t0_ps_03->setShader(sdrCtl.getShader("pe_torus"));
	t0_ps_03->setType("Particle_System");
	t0_ps_03->setName("Particle_Test");
	t0_ps_03->setLoopInf(true);
	t0_ps_03->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG");
	t0_ps_03->setFog(fog);
	t0_ps_03->setBlastRadius(1.0f);// Blast radius
	t0_ps_03->setExplosionVelocity(0.5f);// Explosion velocity
	t0_ps_03->setExplosionDecay(10.0f);// Explosion decay
	t0_ps_03->setFragStartSize(12.0f);// Fragment start size
	t0_ps_03->setFragEndSize(1.0f);// Fragment end size
	t0_ps_03->setFragStartColor(vec3(0.0, 0.5, 1.0));// Fragment start color
	t0_ps_03->setFragEndColor(vec3(0.0, 0.125, 0.25));// Fragment end color
	t0_ps_03->setTime_Step(0.1f);
	t0_ps_03->setTime_Max(100.0);
	t0_ps_03->setTime_Min(0.0);
	t0_ps_03->setTime(66.0);
	//t0_ps_03->setEmitterPosition();// Emitter position
	t0_ps_03->setModelM(glm::translate(vec3(-28.5, 8.5f, -31.5)));

	Mesh* tower1 = new Mesh();
	tower1->LoadMesh("Model/2Tower_6_bone.dae", false);
	tower1->setShader(sdrCtl.getShader("basic_model"));
	tower1->setShadowTex(shadow_map_id);
	tower1->setAdjustM(glm::translate(vec3(0.0, 1.0, 0.0))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0))*glm::scale(vec3(1.0, 1.0, 1.0)));
	tower1->setModelM(glm::translate(vec3(30.0, 0.0, -30.0)));
	tower1->setShininess(30);
	tower1->setFog(fog);
	tower_list.push_back(tower1);

	t1_ps_01 = new ParticleSystem2((float)1.0, (float)0.25, (float)0.25, (float)4.0, (float)0.5, (float)0.0, (float)360.0, (float)0.0, (float)360.0, (float)0.0);
	t1_ps_01->setShader(sdrCtl.getShader("pe_torus"));
	t1_ps_01->setType("Particle_System");
	t1_ps_01->setName("Particle_Test");
	t1_ps_01->setLoopInf(true);
	t1_ps_01->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG");
	t1_ps_01->setFog(fog);
	t1_ps_01->setBlastRadius(1.0f);// Blast radius
	t1_ps_01->setExplosionVelocity(0.5f);// Explosion velocity
	t1_ps_01->setExplosionDecay(10.0f);// Explosion decay
	t1_ps_01->setFragStartSize(12.0f);// Fragment start size
	t1_ps_01->setFragEndSize(1.0f);// Fragment end size
	t1_ps_01->setFragStartColor(vec3(0.0, 0.5, 1.0));// Fragment start color
	t1_ps_01->setFragEndColor(vec3(0.0, 0.125, 0.25));// Fragment end color
	t1_ps_01->setTime_Step(0.1f);
	t1_ps_01->setTime_Max(100.0);
	t1_ps_01->setTime_Min(0.0);
	t1_ps_01->setTime(0.0);
	//t1_ps_01->setEmitterPosition();// Emitter position
	t1_ps_01->setModelM(glm::translate(vec3(28.0, 6.5f, -30.0))*glm::rotate(mat4(1.0), 90.0f, vec3(0.0, 1.0, 0.0)));

	t1_ps_02 = new ParticleSystem2((float)1.0, (float)0.25, (float)0.25, (float)4.0, (float)0.5, (float)0.0, (float)360.0, (float)0.0, (float)360.0, (float)0.0);
	t1_ps_02->setShader(sdrCtl.getShader("pe_torus"));
	t1_ps_02->setType("Particle_System");
	t1_ps_02->setName("Particle_Test");
	t1_ps_02->setLoopInf(true);
	t1_ps_02->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG");
	t1_ps_02->setFog(fog);
	t1_ps_02->setBlastRadius(1.0f);// Blast radius
	t1_ps_02->setExplosionVelocity(0.5f);// Explosion velocity
	t1_ps_02->setExplosionDecay(10.0f);// Explosion decay
	t1_ps_02->setFragStartSize(12.0f);// Fragment start size
	t1_ps_02->setFragEndSize(1.0f);// Fragment end size
	t1_ps_02->setFragStartColor(vec3(0.0, 0.5, 1.0));// Fragment start color
	t1_ps_02->setFragEndColor(vec3(0.0, 0.125, 0.25));// Fragment end color
	t1_ps_02->setTime_Step(0.1f);
	t1_ps_02->setTime_Max(100.0);
	t1_ps_02->setTime_Min(0.0);
	t1_ps_02->setTime(33.0);
	//t1_ps_02->setEmitterPosition();// Emitter position
	t1_ps_02->setModelM(glm::translate(vec3(30.5, 6.5f, -28)));

	t1_ps_03 = new ParticleSystem2((float)1.0, (float)0.25, (float)0.25, (float)4.0, (float)0.5, (float)0.0, (float)360.0, (float)0.0, (float)360.0, (float)0.0);
	t1_ps_03->setShader(sdrCtl.getShader("pe_torus"));
	t1_ps_03->setType("Particle_System");
	t1_ps_03->setName("Particle_Test");
	t1_ps_03->setLoopInf(true);
	t1_ps_03->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG");
	t1_ps_03->setFog(fog);
	t1_ps_03->setBlastRadius(1.0f);// Blast radius
	t1_ps_03->setExplosionVelocity(0.5f);// Explosion velocity
	t1_ps_03->setExplosionDecay(10.0f);// Explosion decay
	t1_ps_03->setFragStartSize(12.0f);// Fragment start size
	t1_ps_03->setFragEndSize(1.0f);// Fragment end size
	t1_ps_03->setFragStartColor(vec3(0.0, 0.5, 1.0));// Fragment start color
	t1_ps_03->setFragEndColor(vec3(0.0, 0.125, 0.25));// Fragment end color
	t1_ps_03->setTime_Step(0.1f);
	t1_ps_03->setTime_Max(100.0);
	t1_ps_03->setTime_Min(0.0);
	t1_ps_03->setTime(66.0);
	//t1_ps_03->setEmitterPosition();// Emitter position
	t1_ps_03->setModelM(glm::translate(vec3(31.5, 6.5f, -31.5)));

	Mesh* tower2 = new Mesh();
	tower2->LoadMesh("Model/OctopusTower1_10_bone2.dae", false);
	tower2->setShader(sdrCtl.getShader("basic_model"));
	tower2->setShadowTex(shadow_map_id);
	tower2->setAdjustM(glm::translate(vec3(0.0, 3.7, 0.0))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0))*glm::scale(vec3(0.6, 0.6, 0.6)));
	tower2->setModelM(glm::translate(vec3(30.0, 2.5, 30.0)));
	tower2->setShininess(30);
	tower2->setFog(fog);
	tower_list.push_back(tower2);

	t2_ps_01 = new ParticleSystem(GL_POINTS);
	t2_ps_01->setShader(sdrCtl.getShader("halo"));
	t2_ps_01->setType("Particle_System");
	t2_ps_01->setName("Particle_Test");
	t2_ps_01->setK(1.0f);
	t2_ps_01->setColor(vec3(1.0, 1.0, 1.0));
	t2_ps_01->setShade(vec3(1.0, 1.0, 1.0));
	t2_ps_01->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG");
	t2_ps_01->setFog(fog);
	t2_ps_01->setTime_Step(0.25);
	t2_ps_01->setTime_Max(53.0);
	t2_ps_01->setTime_Min(5.0);
	t2_ps_01->setTime((float)5.0);
	t2_ps_01->setLoopInf(true);
	t2_ps_01->setModelM(glm::translate(vec3(30.0f, 7.f, 30.0f))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0)));

	t2_ps_02 = new ParticleSystem(GL_POINTS);
	t2_ps_02->setShader(sdrCtl.getShader("halo"));
	t2_ps_02->setType("Particle_System");
	t2_ps_02->setName("Particle_Test");
	t2_ps_02->setK(1.0f);
	t2_ps_02->setColor(vec3(1.0, 1.0, 1.0));
	t2_ps_02->setShade(vec3(1.0, 1.0, 1.0));
	t2_ps_02->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG");
	t2_ps_02->setFog(fog);
	t2_ps_02->setTime_Step(0.25);
	t2_ps_02->setTime_Max(53.0);
	t2_ps_02->setTime_Min(5.0);
	t2_ps_02->setTime((float)21.0);
	t2_ps_02->setLoopInf(true);
	t2_ps_02->setModelM(glm::translate(vec3(30.0f, 7.f, 30.0f))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0)));

	t2_ps_03 = new ParticleSystem(GL_POINTS);
	t2_ps_03->setShader(sdrCtl.getShader("halo"));
	t2_ps_03->setType("Particle_System");
	t2_ps_03->setName("Particle_Test");
	t2_ps_03->setK(1.0f);
	t2_ps_03->setColor(vec3(1.0, 1.0, 1.0));
	t2_ps_03->setShade(vec3(1.0, 1.0, 1.0));
	t2_ps_03->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG");
	t2_ps_03->setFog(fog);
	t2_ps_03->setTime_Step(0.25);
	t2_ps_03->setTime_Max(53.0);
	t2_ps_03->setTime_Min(5.0);
	t2_ps_03->setTime((float)37.0);
	t2_ps_03->setLoopInf(true);
	t2_ps_03->setModelM(glm::translate(vec3(30.0f, 7.f, 30.0f))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0)));

	Mesh* tower3 = new Mesh();
	tower3->LoadMesh("Model/OctopusTower1_10_bone2.dae", false);
	tower3->setShader(sdrCtl.getShader("basic_model"));
	tower3->setShadowTex(shadow_map_id);
	tower3->setAdjustM(glm::translate(vec3(0.0, 3.7, 0.0))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0))*glm::scale(vec3(0.6, 0.6, 0.6)));
	tower3->setModelM(glm::translate(vec3(-30.0, 2.5, 30.0)));
	tower3->setShininess(30);
	tower3->setFog(fog);
	tower_list.push_back(tower3);

	t3_ps_01 = new ParticleSystem(GL_POINTS);
	t3_ps_01->setShader(sdrCtl.getShader("halo"));
	t3_ps_01->setType("Particle_System");
	t3_ps_01->setName("Particle_Test");
	t3_ps_01->setK(1.0f);
	t3_ps_01->setColor(vec3(1.0, 1.0, 1.0));
	t3_ps_01->setShade(vec3(1.0, 1.0, 1.0));
	t3_ps_01->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG");
	t3_ps_01->setFog(fog);
	t3_ps_01->setTime_Step(0.25);
	t3_ps_01->setTime_Max(53.0);
	t3_ps_01->setTime_Min(5.0);
	t3_ps_01->setTime((float)5.0);
	t3_ps_01->setLoopInf(true);
	t3_ps_01->setModelM(glm::translate(vec3(-30.0f, 7.3f, 30.0f))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0)));

	t3_ps_02 = new ParticleSystem(GL_POINTS);
	t3_ps_02->setShader(sdrCtl.getShader("halo"));
	t3_ps_02->setType("Particle_System");
	t3_ps_02->setName("Particle_Test");
	t3_ps_02->setK(1.0f);
	t3_ps_02->setColor(vec3(1.0, 1.0, 1.0));
	t3_ps_02->setShade(vec3(1.0, 1.0, 1.0));
	t3_ps_02->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG");
	t3_ps_02->setFog(fog);
	t3_ps_02->setTime_Step(0.25);
	t3_ps_02->setTime_Max(53.0);
	t3_ps_02->setTime_Min(5.0);
	t3_ps_02->setTime((float)21.0);
	t3_ps_02->setLoopInf(true);
	t3_ps_02->setModelM(glm::translate(vec3(-30.0f, 7.3f, 30.0f))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0)));

	t3_ps_03 = new ParticleSystem(GL_POINTS);
	t3_ps_03->setShader(sdrCtl.getShader("halo"));
	t3_ps_03->setType("Particle_System");
	t3_ps_03->setName("Particle_Test");
	t3_ps_03->setK(1.0f);
	t3_ps_03->setColor(vec3(1.0, 1.0, 1.0));
	t3_ps_03->setShade(vec3(1.0, 1.0, 1.0));
	t3_ps_03->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG");
	t3_ps_03->setFog(fog);
	t3_ps_03->setTime_Step(0.25);
	t3_ps_03->setTime_Max(53.0);
	t3_ps_03->setTime_Min(5.0);
	t3_ps_03->setTime((float)37.0);
	t3_ps_03->setLoopInf(true);
	t3_ps_03->setModelM(glm::translate(vec3(-30.0f, 7.3f, 30.0f))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0)));

	//Bottom Mid Platform
	Cube* platform_01 = new Cube(-10.0, 10.0, -0.5, 0.5, -10.0, 10.0);
	//platform_01->setSpeed(5);
	platform_01->setKd(vec3(0.8, 0.0, 0.0));
	platform_01->setKa(vec3(0.3, 0.0, 0.0));
	platform_01->setKs(vec3(0.4, 0.0, 0.0));
	platform_01->setShininess(100);
	platform_01->setFog(fog);
	platform_01->setReflectFactor(vec2(0.2, 0.5));
	platform_01->setEta(0.5);
	platform_01->setCubeMapUnit(3);
	platform_01->setSpeed(5);
	platform_01->postTrans(glm::translate(vec3(0, 13.0, 0)));
	//platform_01->setAABB(AABB(vec3(-10.0, -0.5, -10.0), vec3(10.0, 0.5, 10.0)));
	platform_01->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_01->setShadowTex(shadow_map_id);
	platform_01->setType("Cube");
	platform_01->setName("Test Platform");
	stationary_list.push_back(platform_01);

	//1st Bottom Side Step Platform
	Cube* platform_02 = new Cube(-1.5, 1.5, -0.5, 0.5, -5.0, 5.0);
	//platform_01->setSpeed(5);
	platform_02->setKd(vec3(0.15, 0.15, 0.92));
	platform_02->setKa(vec3(0.0, 0.0, 0.3));
	platform_02->setKs(vec3(0.0, 0.0, 0.4));
	platform_02->setShininess(100);
	platform_02->setFog(fog);
	platform_02->setReflectFactor(vec2(0.2, 0.5));
	platform_02->setEta(0.5);
	platform_02->setCubeMapUnit(3);
	platform_02->setSpeed(5);
	platform_02->postTrans(glm::translate(vec3(20.0, 8.0, 0)));
	//platform_02->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0)));
	platform_02->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_02->setShadowTex(shadow_map_id);
	platform_02->setType("Cube");
	platform_02->setName("Test Platform");
	stationary_list.push_back(platform_02);

	//2nd Bottom Side Step Platform
	Cube* platform_03 = new Cube(-1.5, 1.5, -0.5, 0.5, -5.0, 5.0);
	//platform_01->setSpeed(5);
	platform_03->setKd(vec3(0.11, 0.67, 0.09));
	platform_03->setKa(vec3(0.0, 0.2, 0.0));
	platform_03->setKs(vec3(0.0, 0.3, 0.0));
	platform_03->setShininess(100);
	platform_03->setFog(fog);
	platform_03->setReflectFactor(vec2(0.2, 0.5));
	platform_03->setEta(0.5);
	platform_03->setCubeMapUnit(3);
	platform_03->setSpeed(5);
	platform_03->postTrans(glm::translate(vec3(-20.0, 8.0, 0)));
	//platform_03->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0)));
	platform_03->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_03->setShadowTex(shadow_map_id);
	platform_03->setType("Cube");
	platform_03->setName("Test Platform");
	stationary_list.push_back(platform_03);

	//Platform Steps 1-1
	Cube* platform_04 = new Cube(-5.0, 5.0, -0.5, 0.5, -1.5, 1.5);
	//platform_01->setSpeed(5);
	platform_04->setKd(vec3(0.8, 0.8, 0.0));
	platform_04->setKa(vec3(0.3, 0.3, 0.0));
	platform_04->setKs(vec3(0.4, 0.4, 0.0));
	platform_04->setShininess(100);
	platform_04->setFog(fog);
	platform_04->setReflectFactor(vec2(0.2, 0.5));
	platform_04->setEta(0.5);
	platform_04->setCubeMapUnit(3);
	platform_04->setSpeed(5);
	platform_04->postTrans(glm::translate(vec3(0.0, 18.0, 20.0)));
	//platform_04->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0)));
	platform_04->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_04->setShadowTex(shadow_map_id);
	platform_04->setType("Cube");
	platform_04->setName("Test Platform");
	stationary_list.push_back(platform_04);

	//Platform Steps 1-2
	Cube* platform_05 = new Cube(-5.0, 5.0, -0.5, 0.5, -5.0, 5.0);
	//platform_05->setSpeed(5);
	platform_05->setKd(vec3(0.0, 0.8, 0.8));
	platform_05->setKa(vec3(0.0, 0.3, 0.3));
	platform_05->setKs(vec3(0.0, 0.4, 0.4));
	platform_05->setShininess(100);
	platform_05->setFog(fog);
	platform_05->setReflectFactor(vec2(0.2, 0.5));
	platform_05->setEta(0.5);
	platform_05->setCubeMapUnit(3);
	platform_05->setSpeed(5);
	platform_05->postTrans(glm::translate(vec3(0.0, 23.0, 40.0)));
	//platform_05->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0)));
	platform_05->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_05->setShadowTex(shadow_map_id);
	platform_05->setType("Cube");
	platform_05->setName("Test Platform");
	stationary_list.push_back(platform_05);

	//Platform Steps 1-3
	Cube* platform_06 = new Cube(-5.0, 5.0, -0.5, 0.5, -1.5, 1.5);
	//platform_06->setSpeed(5);
	platform_06->setKd(vec3(0.8, 0.0, 0.8));
	platform_06->setKa(vec3(0.3, 0.0, 0.3));
	platform_06->setKs(vec3(0.4, 0.0, 0.4));
	platform_06->setShininess(100);
	platform_06->setFog(fog);
	platform_06->setReflectFactor(vec2(0.2, 0.5));
	platform_06->setEta(0.5);
	platform_06->setCubeMapUnit(3);
	platform_06->setSpeed(5);
	platform_06->postTrans(glm::translate(vec3(0.0, 28.0, 60.0)));
	//platform_06->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0)));
	platform_06->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_06->setShadowTex(shadow_map_id);
	platform_06->setType("Cube");
	platform_06->setName("Test Platform");
	stationary_list.push_back(platform_06);

	//Platform Steps 2-1
	Cube* platform_07 = new Cube(-5.0, 5.0, -0.5, 0.5, -1.5, 1.5);
	//platform_07->setSpeed(5);
	platform_07->setKd(vec3(0.8, 0.0, 0.8));
	platform_07->setKa(vec3(0.3, 0.0, 0.3));
	platform_07->setKs(vec3(0.4, 0.0, 0.4));
	platform_07->setShininess(100);
	platform_07->setFog(fog);
	platform_07->setReflectFactor(vec2(0.2, 0.5));
	platform_07->setEta(0.5);
	platform_07->setCubeMapUnit(3);
	platform_07->setSpeed(5);
	platform_07->postTrans(glm::translate(vec3(0.0, 18.0, -20.0)));
	//platform_07->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0)));
	platform_07->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_07->setShadowTex(shadow_map_id);
	platform_07->setType("Cube");
	platform_07->setName("Test Platform");
	stationary_list.push_back(platform_07);

	//Platform Steps 2-2
	Cube* platform_08 = new Cube(-5.0, 5.0, -0.5, 0.5, -5.0, 5.0);
	//platform_08->setSpeed(5);
	platform_08->setKd(vec3(0.0, 0.8, 0.8));
	platform_08->setKa(vec3(0.0, 0.3, 0.3));
	platform_08->setKs(vec3(0.0, 0.4, 0.4));
	platform_08->setShininess(100);
	platform_08->setFog(fog);
	platform_08->setReflectFactor(vec2(0.2, 0.5));
	platform_08->setEta(0.5);
	platform_08->setCubeMapUnit(3);
	platform_08->setSpeed(5);
	platform_08->postTrans(glm::translate(vec3(0.0, 23.0, -40.0)));
	//platform_08->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0)));
	platform_08->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_08->setShadowTex(shadow_map_id);
	platform_08->setType("Cube");
	platform_08->setName("Test Platform");
	stationary_list.push_back(platform_08);

	//Platform Steps 2-3
	Cube* platform_09 = new Cube(-5.0, 5.0, -0.5, 0.5, -1.5, 1.5);
	//platform_09->setSpeed(5);
	platform_09->setKd(vec3(0.8, 0.8, 0.0));
	platform_09->setKa(vec3(0.3, 0.3, 0.0));
	platform_09->setKs(vec3(0.4, 0.4, 0.0));
	platform_09->setShininess(100);
	platform_09->setFog(fog);
	platform_09->setReflectFactor(vec2(0.2, 0.5));
	platform_09->setEta(0.5);
	platform_09->setCubeMapUnit(3);
	platform_09->setSpeed(5);
	platform_09->postTrans(glm::translate(vec3(0.0, 28.0, -60.0)));
	//platform_03->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0)));
	platform_09->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_09->setShadowTex(shadow_map_id);
	platform_09->setType("Cube");
	platform_09->setName("Test Platform");
	stationary_list.push_back(platform_09);

	//Trampoline
	Cube* tramp_01 = new Cube(-2.0,2.0,-0.5,0.5,-2.0,2.0);
	tramp_01->setKd(vec3(0.0, 0.0, 0.0));
	tramp_01->setKa(vec3(0.0, 0.0, 0.0));
	tramp_01->setKs(vec3(0.0, 0.0, 0.0));
	tramp_01->setShininess(100);
	tramp_01->setFog(fog);
	tramp_01->setReflectFactor(vec2(0.2, 0.5));
	tramp_01->setEta(0.5);
	tramp_01->setCubeMapUnit(3);
	tramp_01->postTrans(glm::translate(vec3(20, 8.0, 20)));
	tramp_01->setShader(sdrCtl.getShader("basic_reflect_refract"));
	tramp_01->setShadowTex(shadow_map_id);
	tramp_01->setType("Trampoline");
	tramp_01->setName("Test Trampoline");
	stationary_list.push_back(tramp_01);


	/*
	float temp_x = randomFloatBetween(0.0, 1.0);
	float temp_y = randomFloatBetween(0.0, 1.0);
	float temp_z = randomFloatBetween(0.0, 1.0);
	Cube* platform_04 = new Cube(0.0, 0.0, -0.5, 0.5, -5.0, 5.0);
	//platform_01->setSpeed(5);
	platform_04->setKd(vec3(temp_x, temp_y, temp_z));
	platform_04->setKa(vec3(temp_x*0.2, temp_y*0.2, temp_z*0.2));
	platform_04->setKs(vec3(temp_x*0.3, temp_y*0.3, temp_z*0.3));
	platform_04->setShininess(100);
	platform_04->setFog(fog);
	platform_04->setReflectFactor(vec2(0.2, 0.5));
	platform_04->setEta(0.5);
	platform_04->setCubeMapUnit(3);
	platform_04->setSpeed(5);
	platform_04->postTrans(glm::translate(vec3(0.0, 2.5, 0)));
	//platform_03->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0)));
	platform_04->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_04->setShadowTex(shadow_map_id);
	platform_04->setType("Cube");
	platform_04->setName("Test Platform");
	stationary_list.push_back(platform_04);
	*/

	//m_pMesh2 = new Mesh();
	//m_pMesh2->LoadMesh("Model/monky_04_27_smooth.dae");
	//m_pMesh2->setShader(sdrCtl.getShader("basic_model"));
	//m_pMesh2->setAdjustM(glm::translate(vec3(10.0, 4.1, 0.0))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0))*glm::scale(vec3(0.2, 0.2, 0.2))); 
	//m_pMesh2->setShadowTex(shadow_map_id);

	tryThis = new Mesh_Static();
	tryThis->LoadMesh("Model/2Tower_6_bone.dae");
	tryThis->setShader(sdrCtl.getShader("basic_model"));
	tryThis->setShadowTex(shadow_map_id);
	tryThis->setAdjustM(glm::translate(vec3(0.0, 1.0, 0.0))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0))*glm::scale(vec3(1.0, 1.0, 1.0)));

	m_billboardList.Init("img/monster_hellknight.png", "PNG");
	m_billboardList.setShader(sdrCtl.getShader("billboard"));
	m_billboardList.AddBoard(vec3(9.0f, 7.0f, 9.0f));
	m_billboardList.AddBoard(vec3(-9.0f, 7.0f, -9.0f));
	m_billboardList.AddBoard(vec3(-9.0f, 7.0f, 9.0f));
	m_billboardList.AddBoard(vec3(9.0f, 7.0f, -9.0f));
	m_billboardList.BindBoards();

	m_billboardList2.Init("img/monster_hellknight.png", "PNG");
	m_billboardList2.setShader(sdrCtl.getShader("billboard"));
	m_billboardList2.AddBoard(vec3(1.0f, 7.0f, 9.0f));
	m_billboardList2.BindBoards();

	m_billboardList3.Init("img/monster_hellknight.png", "PNG");
	m_billboardList3.setShader(sdrCtl.getShader("billboard"));
	m_billboardList3.AddBoard(vec3(1.0f, 7.0f, -9.0f));
	m_billboardList3.BindBoards();

	m_billboardList4.Init("img/monster_hellknight.png", "PNG");
	m_billboardList4.setShader(sdrCtl.getShader("billboard"));
	m_billboardList4.AddBoard(vec3(1.0f, 7.0f, -6.0f));
	m_billboardList4.BindBoards();

	MOM.mother_of_p_anim = new ParticleAnimated();
	MOM.mother_of_p_anim->Init("img/sprite_sheets/effect_002.png", "PNG");
	MOM.mother_of_p_anim->setShader(sdrCtl.getShader("billboard_anim"));
	MOM.mother_of_p_anim->setPosition(vec3(0.0f, 0.0f, 0.0f));
	MOM.mother_of_p_anim->setWidth(2.0f);
	MOM.mother_of_p_anim->setHeight(2.0f);
	MOM.mother_of_p_anim->setNumColumn(5);
	MOM.mother_of_p_anim->setNumRow(4);
	MOM.mother_of_p_anim->setDuration(1);
	MOM.mother_of_p_anim->Bind();

	ParticleAnimated* p_anim = new ParticleAnimated(*MOM.mother_of_p_anim);
	p_anim->setModelM(glm::translate(vec3(0, 15, 0)));
	p_anim->setType(1);
	LARGE_INTEGER time_p_anim;
	QueryPerformanceCounter(&time_p_anim);
	p_anim->setStartTime(time_p_anim);
	panim_list.push_back(p_anim);

	particle = new ParticleSystem(GL_POINTS);
	particle->setShader(sdrCtl.getShader("emitter"));
	particle->setType("Particle_System");
	particle->setName("Particle_Test");
	particle->setK(24.0f);
	particle->setColor(vec3(1.0, 0.0, 0.0));
	particle->setShade(vec3(1.0, 0.0, 0.0));
	particle->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG");
	particle->setFog(fog);
	particle->setTime_Step(1.0);
	particle->setTime_Max(150.0);
	particle->setTime_Min(1.0);
	particle->setTime((float)0.45);
	particle->setLoopInf(true);
	particle->setModelM(glm::translate(vec3(0.0f, 2.0f, -40.0f)));

	particle2 = new ParticleSystem(GL_POINTS);
	particle2->setShader(sdrCtl.getShader("emitter"));
	particle2->setType("Particle_System");
	particle2->setName("Particle_Test");
	particle2->setK(14.0f);
	particle2->setColor(vec3(0.0, 1.0, 0.0));
	particle2->setShade(vec3(0.0, 1.0, 0.0));
	particle2->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG");
	particle2->setFog(fog);
	particle2->setTime_Step(0.5);
	particle2->setTime_Max(15.0);
	particle2->setTime_Min(1.5);
	particle2->setTime(7.5);
	particle2->setLoopInf(true);
	particle2->setModelM(glm::translate(vec3(0.0f, 2.0f, -20.0f)));

	particle3 = new ParticleSystem(GL_POINTS);
	particle3->setShader(sdrCtl.getShader("emitter"));
	particle3->setType("Particle_System");
	particle3->setName("Particle_Test");
	particle3->setK(4.0f);
	particle3->setColor(vec3(0.0, 0.0, 1.0));
	particle3->setShade(vec3(0.0, 0.0, 1.0));
	particle3->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG");
	particle3->setFog(fog);
	particle3->setTime(25.0);
	particle3->setLoopInf(true);
	particle3->setModelM(glm::translate(vec3(0.0f, 2.0f, -10.0f)));

	particle4 = new ParticleSystem(GL_POINTS);
	particle4->setShader(sdrCtl.getShader("halo"));
	particle4->setType("Particle_System");
	particle4->setName("Particle_Test");
	particle4->setK(1.0f);
	particle4->setColor(vec3(1.0, 1.0, 1.0));
	particle4->setShade(vec3(1.0, 1.0, 1.0));
	particle4->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG");
	particle4->setFog(fog);
	particle4->setTime(35.0);
	particle4->setLoopInf(true);
	particle4->setModelM(glm::translate(vec3(0.0f, 2.0f, 0.0f))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0)));

	particle5 = new ParticleSystem(GL_POINTS);
	particle5->setShader(sdrCtl.getShader("emitter"));
	particle5->setType("Particle_System");
	particle5->setName("Particle_Test");
	particle5->setK(4.0f);
	particle5->setColor(vec3(1.0, 1.0, 0.0));
	particle5->setShade(vec3(1.0, 1.0, 0.0));
	particle5->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG");
	particle5->setFog(fog);
	particle5->setTime(45.0);
	particle5->setLoopInf(true);
	particle5->setModelM(glm::translate(vec3(0.0f, 2.0f, 10.0f)));

	particle6 = new ParticleSystem(GL_POINTS);
	particle6->setShader(sdrCtl.getShader("emitter"));
	particle6->setType("Particle_System");
	particle6->setName("Particle_Test");
	particle6->setK(14.0f);
	particle6->setColor(vec3(1.0, 0.0, 1.0));
	particle6->setShade(vec3(1.0, 0.0, 1.0));
	particle6->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG"); 
	particle6->setFog(fog);
	particle6->setTime(7.5);
	particle6->setLoopInf(true);
	particle6->setModelM(glm::translate(vec3(0.0f, 2.0f, 20.0f)));

	particle7 = new ParticleSystem(GL_POINTS);
	particle7->setShader(sdrCtl.getShader("emitter"));
	particle7->setType("Particle_System");
	particle7->setName("Particle_Test");
	particle7->setK(24.0f);
	particle7->setColor(vec3(0.0, 1.0, 1.0));
	particle7->setShade(vec3(0.0, 1.0, 1.0));
	particle7->setLoopInf(true);
	particle7->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG");
	particle7->setFog(fog);
	particle7->setModelM(glm::translate(vec3(0.0f, 2.0f, 40.0f)));

	particle8 = new ParticleSystem(GL_POINTS);
	particle8->setShader(sdrCtl.getShader("ui_particle"));
	particle8->setType("Particle_System");
	particle8->setName("Particle_Test");
	particle8->setK(24.0f);
	particle8->setColor(vec3(1.0, 0.0, 0.0));
	particle8->setShade(vec3(0.0, 0.0, 1.0));
	particle8->setLoopCount(1);
	particle8->setCurrentLoopCount(1);
	particle8->setTime_Step(0.5);
	particle8->setTime_Max(40.0);
	particle8->setTime_Min(20.0);
	particle8->setTime(20.0);
	particle8->setTexture(GL_TEXTURE_2D, "img/UI_elements/minusSign.png", "PNG");
	particle8->setFog(emptyFog);

	testSystem = new ParticleSystem2();
	testSystem->setShader(sdrCtl.getShader("pe_system"));
	testSystem->setType("Particle_System");
	testSystem->setName("Particle_Test");
	testSystem->setLoopInf(true);
	testSystem->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG");
	testSystem->setFog(fog);
	testSystem->setModelM(glm::translate(vec3(0.0f, 9.0f, 0.0f)));

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//RenderString((Window::width) / 4, (Window::height) / 2, GLUT_BITMAP_HELVETICA_18, (unsigned char*)buf, vec3(0.0f, 1.0f, 0.0f));

	glutSwapBuffers();

}



int loadAudio(){

	/*
	Create a System object and initialize.
	*/

	mySoundSystem = new SoundSystem();
	//mySoundSystem->createMusic();
	menuMusic = new Music(mySoundSystem, "Music/backgroundMenu.wav", false);
	menuMusic->setLoopCount(-1);
	menuMusic->setVolume(0.75);
	menuMusic->Play();

	gameMusic = new Music(mySoundSystem, "Music/background_music.mp3", false);
	gameMusic->setLoopCount(-1);
	gameMusic->setVolume(0.9);
	//gameMusic->Play();

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

		testSound[i] = new Sound(mySoundSystem, path.c_str(), false);
		testSound[i]->setVolume(0.5);
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
	for (uint j = 0; j< draw_list.size(); j++)
	{
		if ((*draw_list[j]).getName() == name)
			draw_list.erase(draw_list.begin() + j);
	}
}

float randomFloatBetween(float min, float max)
{
	float myRand = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
	return myRand;
}

void update3DSound(){
	myPosition = myPosition;
	myVelocity = myVelocity;
}

void printLoadingString(string s){
	sprintf_s(buf, "%s %s %s", "Loaded texture: '", s.c_str(), "'");

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	RenderString((Window::width) / 4, (Window::height) / 2, GLUT_BITMAP_HELVETICA_18, (unsigned char*)buf, vec3(0.0f, 1.0f, 0.0f));

	glutSwapBuffers();
}


