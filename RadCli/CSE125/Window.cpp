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
#include "JSON_Parse.h"
#include "billboard_list.h"
#include "UI.h"
#include "ClientState.h"
#include "AnimController.h"
#include "ParticleAnimated.h"
#include "LightningGenerator.h"
#include "BillboardProjectile.h"
#include "Quad.h"

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
ParticleSystem2* t4_ps_01;
ParticleSystem2* t4_ps_02;
ParticleSystem2* t4_ps_03;

ParticleSystem* t2_ps_01;
ParticleSystem* t2_ps_02;
ParticleSystem* t2_ps_03;
ParticleSystem* t3_ps_01;
ParticleSystem* t3_ps_02;
ParticleSystem* t3_ps_03;
ParticleSystem* t5_ps_01;
ParticleSystem* t5_ps_02;
ParticleSystem* t5_ps_03;
long long m_currentTimeMillis;

ParticleSystem2* testSystem;

std::vector<ParticleSystem2*> explosion_list;

Quad* screen_quad;

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
Music *gameThunder;
Sound* testSound[NumberOfSounds];
Sound* gameThunder2;
FMOD_VECTOR myPosition;
FMOD_VECTOR myVelocity;
Sound* posTestSound;
Sound* sound_3d_Throw;
Sound* sound_3d_hit;
Sound* sound_3d_light;
Sound* sound_3d_death;
Sound* sound_3d_death2;
Sound* sound_3d_tramp;
Sound* sound_3d_tele;
Sound* sound_3d_pick;
Sound* sound_3d_tower_shoot;
Sound* sound_3d_tower_explosion;
Music* posTestMusic;

std::vector<Object*> draw_list;
std::vector<Object*> elevator_list;
std::vector<Object*> player_list;
std::vector<Object*> tower_list;
std::vector<Object*> stationary_list;
std::vector<Projectile*> projectile_list;
std::vector<BillboardProjectile*> tower_projectile_list;
std::vector<Texture*> texture_list;
std::vector<Sound*> sound_list;
std::vector<ParticleAnimated*> panim_list;
std::vector<ParticleAnimated*> lightning_list;

LightningGenerator lightning_generator;

Mesh_Static* tryThis;


bool bVis[6];
BillboardList m_billboardList;
BillboardList m_billboardList2;
BillboardList m_billboardList3;
BillboardList m_billboardList4;
BillboardList m_billboardList5;
BillboardList m_billboardList6;

JSON_Parser *map_info;

int Window::width = 1280;   // set window width in pixels here
int Window::height = 720;   // set window height in pixels here
float nearClip = (float)0.1;
float farClip = 1000.0;
float fov = 55.0;

ParticleAnimated* force_field[2];

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
	ParticleAnimated* mother_of_p_anim;//blue fire
	ParticleAnimated* mother_of_lightning;
	ParticleAnimated* mother_of_tower_shoot_1;
	ParticleAnimated* mother_of_tower_damage_1;
	ParticleAnimated* mother_of_tower_explosion_1;
	ParticleAnimated* mother_of_health_potion;
	ParticleAnimated* mother_of_red_arrow;
	ParticleAnimated* mother_of_green_arrow;
	ParticleAnimated* mother_of_tramp_effect;
	ParticleAnimated* mother_of_portal_effect;
	ParticleAnimated* mother_of_orange_mark;
	ParticleAnimated* mother_of_blue_mark;
	ParticleAnimated* mother_of_force_field;
}MOM;

int texScreenWidth = 512;
int texScreenHeight = 512;

Camera* cam[4];
float cam_sp = (float)0.1;
float cam_dx = 0;

GLuint fboHandle;
GLuint depth_fbo;
GLuint render_fbo;
GLsizei depth_texture_width = 2048;//4096
GLsizei depth_texture_height = 2048;
GLuint shadow_map_id = 10;//shadow map stored in GL_TEXTURE10
GLuint render_tex_id = 11;//blur texture stored in GL_TEXTURE11

string configBuf;

//time used in idleCallback
LARGE_INTEGER freq, last, current, loop_begin, loop_end;
double delta;
LARGE_INTEGER idleCallbackTime;

//Mouse press flags
int left_mouse_up = 1;
int right_mouse_up = 1;
int middle_mouse_up = 1;
int space_up = 1;
int sprint_up = 10;

//bool keyState[4];//up,down,left,right

void initializeMOM();
void initializePlayerMark(int main_player_ID);

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
Texture * render_tex;
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
float max_health = 7.0;
bool dead[4];
bool baseOpen = false;

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

bool kill_count = false;
float offset = 0.2f;

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

float nextThunderTimeSec = 90.0;
float currThunderTimeSec = 90.0;

float nextBackgroundMusicTimeSec = 345.0;
float currBackgroundMusicTimeSec = 345.0;

float nextSoundEventTimeSec = 2.5;
float currSoundEventTimeSec = 0.0;

vector<Sound*> SoundEvents;
vector<int> SoundEventsIcon;
vector<std::string> SoundEventsString;

float nextPickupSound = 10.0;
float currPickupSound = 0.0;

int Player0_Powerup = 0;
int Player1_Powerup = 0;
int Player2_Powerup = 0;
int Player3_Powerup = 0;

FMOD_VECTOR player0_sound_vec_curr = { 0.0, 0.0, 0.0 };
FMOD_VECTOR player1_sound_vec_curr = { 0.0, 0.0, 0.0 };
FMOD_VECTOR player2_sound_vec_curr = { 0.0, 0.0, 0.0 };
FMOD_VECTOR player3_sound_vec_curr = { 0.0, 0.0, 0.0 };

FMOD_VECTOR player0_sound_vec_last = { 0.0, 0.0, 0.0 };
FMOD_VECTOR player1_sound_vec_last = { 0.0, 0.0, 0.0 };
FMOD_VECTOR player2_sound_vec_last = { 0.0, 0.0, 0.0 };
FMOD_VECTOR player3_sound_vec_last = { 0.0, 0.0, 0.0 };

FMOD_VECTOR player0_sound_vec_lasterest = { 0.0, 0.0, 0.0 };
FMOD_VECTOR player1_sound_vec_lasterest = { 0.0, 0.0, 0.0 };
FMOD_VECTOR player2_sound_vec_lasterest = { 0.0, 0.0, 0.0 };
FMOD_VECTOR player3_sound_vec_lasterest = { 0.0, 0.0, 0.0 };

//endgame stuff
bool gameOver;
int winner;
int wins;
bool winCountToggle = false;
bool playerReady = true;
int displayWinner = 0;
int enemyWins = 0;

int powerUp = 0;
int Player0_KillSpree = 0;
int Player1_KillSpree = 0;
int Player2_KillSpree = 0;
int Player3_KillSpree = 0;

int Player0_KillSpreeLast = 0;
int Player1_KillSpreeLast = 0;
int Player2_KillSpreeLast = 0;
int Player3_KillSpreeLast = 0;

int Player0_KillCount = 0;
int Player1_KillCount = 0;
int Player2_KillCount = 0;
int Player3_KillCount = 0;

int Player0_KillCountLast = 0;
int Player1_KillCountLast = 0;
int Player2_KillCountLast = 0;
int Player3_KillCountLast = 0;

int Player0_DoubleKillTime = 0;
int Player1_DoubleKillTime = 0;
int Player2_DoubleKillTime = 0;
int Player3_DoubleKillTime = 0;

bool drawPortThingFuck = false;
int portPlayer = NOT_A_PLAYER;
string portString = "";

bool endingFlag = false;

int TowerHP[] = {20, 20, 20, 20, 20, 20};
int TowerState[] = { 0, 0, 0, 0, 0, 0 };

bool FirstBloodTrigger = true;

string doubleKill = "DOUBLE KILL";
string killingSpree = "KILLING SPREE";
string rampage = "RAMPAGE";
string unstoppable = "UNSTOPPABLE";
string dominating = "DOMINATING";
string godlike = "GODLIKE";
string legendary = "LEGENDARY";
string shut_down = "SHUTDOWN";

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

void spawnDamageParticle(int id)
{
	ParticleSystem2 * damagePart = new ParticleSystem2();
	damagePart->setShader(sdrCtl.getShader("pe_system"));
	damagePart->setType("Particle_System");
	damagePart->setName("Particle_Test");
	damagePart->setLoopInf(false);
	damagePart->setLoopCount(1);
	damagePart->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG");
	damagePart->setFog(fog);
	damagePart->setModelM(player_list[id]->getModelM());
	explosion_list.push_back(damagePart);
}

void spawnDeathParticle(float x, float y, float z)
{
	ParticleSystem2* deathPart = new ParticleSystem2();
	deathPart->setShader(sdrCtl.getShader("pe_system"));
	deathPart->setType("Particle_System");
	deathPart->setName("Particle_Test");
	deathPart->setLoopInf(false);
	deathPart->setLoopCount(1);
	deathPart->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG");
	deathPart->setTime_Step(0.5);
	deathPart->setTime_Max(375.0);
	deathPart->setTime_Min(0.0);
	deathPart->setTime(0.0);
	deathPart->setBlastRadius(20.0);
	deathPart->setExplosionVelocity(0.7f);
	deathPart->setExplosionDecay(2.0);
	deathPart->setFragStartColor(vec3(1.0, 0.2, 0.2));
	deathPart->setFragEndColor(vec3(0.6, 0, 0));
	deathPart->setFog(fog);
	deathPart->setModelM(glm::translate(vec3(x, y, z)));
	explosion_list.push_back(deathPart);
}

void PlayThunderSound(float diff){
	if (myClientState->getState() > 0){
		currThunderTimeSec += diff;
		if (nextThunderTimeSec <= currThunderTimeSec){
			currThunderTimeSec = 0;
			gameThunder2->Play();
		}
	}
}

void PlayBackgroundMusic(float diff){
	if (myClientState->getState() > 0){
		currBackgroundMusicTimeSec += diff;
		if (nextBackgroundMusicTimeSec <= currBackgroundMusicTimeSec){
			currBackgroundMusicTimeSec = 0;
			gameMusic->Stop();
			delete gameMusic;
			gameMusic = new Music(mySoundSystem, "Music/background_music.mp3", false);
			gameMusic->setLoopCount(-1);
			gameMusic->setVolume(0.9);
			gameMusic->Play();
		}
	}
}

void PlayAnnouncerEvents(float diff){
	if (myClientState->getState() > 0){
		currSoundEventTimeSec += diff;
		if (nextSoundEventTimeSec <= currSoundEventTimeSec){
			currSoundEventTimeSec = 0;
			if (!SoundEvents.empty()){
				
				if (!SoundEventsIcon.empty() && !SoundEventsString.empty()){
					drawPortThingFuck = true;
					portPlayer = SoundEventsIcon[0];
					portString = SoundEventsString[0];
				}

				SoundEvents[0]->Play();

				SoundEvents.erase(SoundEvents.begin());
				SoundEventsIcon.erase(SoundEventsIcon.begin());
				SoundEventsString.erase(SoundEventsString.begin());
			}
			else{
				drawPortThingFuck = false;
				//SoundEventsIcon.clear();
				//SoundEventsString.clear();
			}
		}
	}
}

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

void projectileAttack(int playerID, Camera * cam, int shootID)
{
	mat4 test = cam->getCamToWorldM();
	vec4 holder = test*vec4(0, 0, -1, 0); //orientation of camera in object space
	mat4 player1 = player_list[playerID]->getModelM();
	vec4 playerHolder = player1*vec4(0, 0, 0, 1);
	int dist = 40;
	float speed = 50.0;

	if (powerUp == FASTERSHOOT)
		speed = 70.0;
	else if (powerUp == FARTHERSHOOT)
		dist = 70;

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
	pjt->setModelM(player1*glm::translate(vec3(0, 2, 0)));//get the new cube matrix by translating the player0 matrix forward in player0 object space. This way the new matrix will inherit player0 oriantation 
	pjt->setAABB(AABB(vec3(-0.5, -0.5, -0.5), vec3(0.5, 0.5, 0.5)));
	AABB hold = pjt->getAABB();
	pjt->setStartX(hold.max[0]);
	pjt->setStartY(hold.max[2]);
	pjt->setDistance(dist);
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
	pjt->setVelocity(vec3(holder)*speed);// set object space velocity to camera oriantation in object space. Since camera always have the same xz oriantation as the object, xz oriantation wouldnt change when camera rotate.
	//cubeT->setVMove(1);  //do this if you want the cube to not have vertical velocity. uncomment the above setVelocity.
	//cout << holder[0] << ' ' << holder[1] << ' ' << holder[2] << ' ' << playerHolder[0] << ' ' << playerHolder[2] << endl;
	pjt->setShootID(shootID);
}
void towerProjectileAttack(int towerID, int projectileID, vec3 direction){

	BillboardProjectile* pjt = new BillboardProjectile(*(MOM.mother_of_tower_shoot_1));
	pjt->setModelM(tower_list[towerID]->getModelM()*glm::translate(vec3(0, 5, 0)));//get the new cube matrix by translating the player0 matrix forward in player0 object space. This way the new matrix will inherit player0 oriantation 
	pjt->setAABB(AABB(vec3(-0.5, -0.5, -0.5), vec3(0.5, 0.5, 0.5)));
	AABB hold = pjt->getAABB();
	pjt->setStartX(hold.max[0]);
	pjt->setStartY(hold.max[2]);
	pjt->setDistance(30);
	//Name and type
	pjt->setName("Tower Projectile");
	pjt->setSpeed(60);
	pjt->setVelocity(glm::normalize(direction)*60.0f);// set object space velocity to camera oriantation in object space. Since camera always have the same xz oriantation as the object, xz oriantation wouldnt change when camera rotate.
	//cubeT->setVMove(1);  //do this if you want the cube to not have vertical velocity. uncomment the above setVelocity.
	//cout << holder[0] << ' ' << holder[1] << ' ' << holder[2] << ' ' << playerHolder[0] << ' ' << playerHolder[2] << endl;
	pjt->setShootID(projectileID);
	LARGE_INTEGER ct;
	QueryPerformanceCounter(&ct);
	pjt->setStartTime(ct);
	tower_projectile_list.push_back(pjt);
	//sound
	vec4 pos = tower_list[towerID]->getModelM()*vec4(0, 0, 0, 1);
	FMOD_VECTOR tpos = { pos.x, pos.y, pos.z };
	sound_3d_tower_shoot->setPosition(tpos);
	sound_3d_tower_shoot->Play3D(View);
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
	for (uint i = 0; i < tower_projectile_list.size(); i++)
	{
		float startX = tower_projectile_list[i]->getStartX();
		float startY = tower_projectile_list[i]->getStartY();
		AABB curr = tower_projectile_list[i]->getAABB();
		int distance = sqrt(pow(curr.max[0] - startX, 2) + pow(curr.max[2] - startY, 2));//Pythagorean Theorem

		//cout << startX << " " << curr.max[0] << " " << curr.max[0] - startX << " " << distance << endl;
		if (distance >= (*tower_projectile_list[i]).getDistance())
		{
			////////////////////////////////////////////////Window::removeDrawList((*projectile[i]).getName());
			delete tower_projectile_list[i];
			tower_projectile_list.erase(tower_projectile_list.begin() + i);
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
	for (uint i = 0; i < tower_projectile_list.size(); i++){
		tower_projectile_list[i]->preTrans(glm::translate(tower_projectile_list[i]->getVelocity()*t));
	}
}
void towerDamage(int towerID){
	ParticleAnimated* tower_dmg = new ParticleAnimated(*(MOM.mother_of_tower_damage_1));
	tower_dmg->setModelM(tower_list[towerID]->getModelM()*glm::translate(vec3(0, 3, 0) + 1.0f*glm::normalize(vec3(glm::inverse(View)*vec4(0, 0, 0, 1) - tower_list[towerID]->getModelM()*vec4(0,0,0,1)))));
	LARGE_INTEGER ct;
	QueryPerformanceCounter(&ct);
	tower_dmg->setStartTime(ct);
	panim_list.push_back(tower_dmg);
	//sound
	vec4 pos = tower_list[towerID]->getModelM()*vec4(0, 0, 0, 1);
	FMOD_VECTOR tpos = { pos.x, pos.y, pos.z };
	sound_3d_hit->setPosition(tpos);
	sound_3d_hit->Play3D(View);
}
void towerKill(int towerID){
	ParticleAnimated* tower_exp = new ParticleAnimated(*(MOM.mother_of_tower_explosion_1));
	tower_exp->setModelM(tower_list[towerID]->getModelM()*glm::translate(vec3(0, 3, 0) + 1.0f*glm::normalize(vec3(glm::inverse(View)*vec4(0, 0, 0, 1) - tower_list[towerID]->getModelM()*vec4(0, 0, 0, 1)))));
	LARGE_INTEGER ct;
	QueryPerformanceCounter(&ct);
	tower_exp->setStartTime(ct);
	panim_list.push_back(tower_exp);

	ParticleAnimated* tower_exp_2 = new ParticleAnimated(*(MOM.mother_of_tower_damage_1));
	tower_exp_2->setModelM(tower_list[towerID]->getModelM()*glm::translate(vec3(0, 3, 0) + 1.0f*glm::normalize(vec3(glm::inverse(View)*vec4(0, 0, 0, 1) - tower_list[towerID]->getModelM()*vec4(0, 0, 0, 1)))));
	tower_exp_2->setValidFrame(0, 19);
	tower_exp_2->setStartTime(ct);
	tower_exp_2->setDelay(0.5);
	tower_exp_2->setDuration(0.3);
	tower_exp_2->setWidth(20.0);
	tower_exp_2->setHeight(10.0);
	panim_list.push_back(tower_exp_2);
	//sound
	vec4 pos = tower_list[towerID]->getModelM()*vec4(0, 0, 0, 1);
	FMOD_VECTOR tpos = { pos.x, pos.y, pos.z };
	sound_3d_tower_explosion->setPosition(tpos);
	sound_3d_tower_explosion->Play3D(View);

	if (towerID < 2 || towerID == 5){
		myUI->setTowers('c');
	}
	else if (towerID == 2 || towerID ==  3 || towerID == 4)
	{
		myUI->setTowers('m');
	}
}
void powerUpAnimation(int playerID){
	ParticleAnimated* power_up = new ParticleAnimated(*(MOM.mother_of_health_potion));
	power_up->setFollow(player_list[playerID], vec3(0, 1.2, 0), 0.6f, &View);
	LARGE_INTEGER ct;
	QueryPerformanceCounter(&ct);
	power_up->setStartTime(ct);
	panim_list.push_back(power_up);
}

void Window::idleCallback(void)
{
	static float anim_time = 0;
	vector<mat4> Transforms;
	double dt;
	vector<mat4> playerMs;
	vector<vec2> lightning_pos;

	switch (myClientState->getState()){
	case 0:
		if (!menuMusic->getFadeDone()){
			menuMusic->fadeUpdate();
		}
		break;
	case 1:
	case 2:
	case 5:
	case 3:
		if (alive){
			first_change = true;
			cam[playerID]->setCamM(mat4(1.0));
			cam[playerID]->setCamMode(0);
		}
		else if(first_change){
			cam[playerID]->setCamM(glm::translate(vec3(0,120,0))*glm::rotate(mat4(1.0),-90.0f,vec3(1,0,0)));
			cam[playerID]->setCamMode(1);
			first_change = false;
		}
		cam[playerID]->update();

		/*
		QueryPerformanceCounter(&current);
		delta = (double)(current.QuadPart - last.QuadPart) / (double)freq.QuadPart;
		last = current;
		anim_time += delta;
		*/

		//player animation
		LARGE_INTEGER ct;
		QueryPerformanceCounter(&ct);
		dt = ((double)ct.QuadPart - (double)idleCallbackTime.QuadPart) / (double)freq.QuadPart;
		idleCallbackTime = ct;
		for (uint i = 0; i < player_list.size(); i++){
			((Mesh*)player_list[i])->BoneTransform(player_list[i]->getAnimation((double)ct.QuadPart / (double)freq.QuadPart), Transforms);
			((Mesh*)player_list[i])->setTransforms(Transforms);
		}

		//particle animation
		for (uint i = 0; i < panim_list.size(); i++){
			if (!panim_list[i]->update()){
				if (panim_list[i]->getType() == 0){//one time
					delete panim_list[i];
					panim_list.erase(panim_list.begin() + i);
					i--;
				}
				else{//continuous
					panim_list[i]->setStartTime(ct);
					panim_list[i]->update();
				}
			}
		}
		//tower projectile animatioin
		for (uint i = 0; i < tower_projectile_list.size(); i++){
			if (!tower_projectile_list[i]->update()){
				if (tower_projectile_list[i]->getType() == 0){//one time
					delete tower_projectile_list[i];
					tower_projectile_list.erase(tower_projectile_list.begin() + i);
					i--;
				}
				else{//continuous
					tower_projectile_list[i]->setStartTime(ct);
					tower_projectile_list[i]->update();
				}
			}
		}

		for (uint i = 0; i < 2; i++){
			if (!force_field[i]->update()){
				force_field[i]->setStartTime(ct);
				force_field[i]->update();
			}
		}

		

		//lightning
		if (lightning_generator.generate(lightning_pos,3)){//generates 3 bolts per lightning generation
			for (uint i = 0; i < lightning_pos.size(); i++){
				//lightning
				ParticleAnimated* new_lightning = new ParticleAnimated(*MOM.mother_of_lightning);
				new_lightning->setModelM(glm::translate(vec3(lightning_pos[i][0], ground->getDispY(lightning_pos[i][0], lightning_pos[i][1]) + 84, lightning_pos[i][1])));
				new_lightning->setType(0);
				new_lightning->setWidth(10);
				new_lightning->setHeight(200);
				new_lightning->setDuration(0.5);
				new_lightning->setTransparency(0.8f);
				new_lightning->setSampleCount(3, 3);
				new_lightning->setSampleDist(0.001f, 0.005f);
				LARGE_INTEGER time_lightning;
				QueryPerformanceCounter(&time_lightning);
				new_lightning->setStartTime(time_lightning);
				lightning_list.push_back(new_lightning);
				//lightning explosion
				ParticleAnimated* p_anim = new ParticleAnimated(*MOM.mother_of_p_anim);
				p_anim->setModelM(glm::translate(vec3(lightning_pos[i][0], ground->getDispY(lightning_pos[i][0], lightning_pos[i][1])+0.3, lightning_pos[i][1])));
				p_anim->setType(0);
				p_anim->setDuration(0.7);
				p_anim->setWidth(10);
				p_anim->setHeight(10);
				p_anim->setSampleCount(3, 3);
				p_anim->setSampleDist(0.005f, 0.005f);
				LARGE_INTEGER time_p_anim;
				QueryPerformanceCounter(&time_p_anim);
				p_anim->setStartTime(time_p_anim);
				panim_list.push_back(p_anim);
			}
		}
		for (uint i = 0; i < lightning_list.size(); i++){
			if (!lightning_list[i]->update()){
				if (lightning_list[i]->getType() == 0){//one time
					delete lightning_list[i];
					lightning_list.erase(lightning_list.begin() + i);
					i--;
				}
				else{//continuous
					lightning_list[i]->setStartTime(ct);
				}
			}
		}

		//simulateProjectile(delta);

		/*vector<mat4> playerMs = scene->getPlayerMats();
		for (int i = 0; i < player_list.size(); i++){
		player_list[i]->setModelM(playerMs[i]);
		}*/

		if ((keyState & 1 << 2) && (keyState & 1)){//up left
			cam[playerID]->getObjAppended()->setRotation(glm::rotate(mat4(1.0), 45.0f, vec3(0.0, 1.0, 0.0)));
		}
		else if ((keyState & 1 << 2) && (keyState & 1 << 1)){//up right
			cam[playerID]->getObjAppended()->setRotation(glm::rotate(mat4(1.0), -45.0f, vec3(0.0, 1.0, 0.0)));
		}
		else if ((keyState & 1 << 3) && (keyState & 1)){//down left
			cam[playerID]->getObjAppended()->setRotation(glm::rotate(mat4(1.0), 135.0f, vec3(0.0, 1.0, 0.0)));
		}
		else if ((keyState & 1 << 3) && (keyState & 1 << 1)){//down right
			cam[playerID]->getObjAppended()->setRotation(glm::rotate(mat4(1.0), -135.0f, vec3(0.0, 1.0, 0.0)));
		}
		else if (keyState & 1 << 2){//up
			cam[playerID]->getObjAppended()->setRotation(glm::rotate(mat4(1.0), 0.0f, vec3(0.0, 1.0, 0.0)));
		}
		else if (keyState & 1 << 3){//down
			cam[playerID]->getObjAppended()->setRotation(glm::rotate(mat4(1.0), 180.0f, vec3(0.0, 1.0, 0.0)));
		}
		else if (keyState & 1){//left
			cam[playerID]->getObjAppended()->setRotation(glm::rotate(mat4(1.0), 90.0f, vec3(0.0, 1.0, 0.0)));
		}
		else if (keyState & 1 << 1){//right
			cam[playerID]->getObjAppended()->setRotation(glm::rotate(mat4(1.0), -90.0f, vec3(0.0, 1.0, 0.0)));
		}

		View = cam[playerID]->getViewM();

		if (myClientState->getState() == 2){
			myGameMenu->draw();
		}
		else if (myClientState->getState() == 3){
			myDeathScreen->draw();
		}
		else if (myClientState->getState() == 5){
			endScreen->draw(0, wins);
		}
		simulateProjectile(dt);
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
	string s = "It was the best of times, it was the worst of times";
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
		//logo->draw();
		
		offset = .08f;

		if ((float)Window::width / (float)Window::height <= 1.5)
		{
			offset = 0;
		}
		glDisable(GL_DEPTH_TEST);
		RenderString((Window::width) * (.7225 - offset), (Window::height) * .06, GLUT_BITMAP_HELVETICA_18, ip_adress, vec3(1.0f, 1.0f, 1.0f));
		glEnable(GL_DEPTH_TEST);
		break;
	case 1:
	case 2:
	case 5: //End screen
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
		//for (uint i = 0; i < tower_projectile_list.size(); ++i)
		//{
		//	tower_projectile_list[i]->draw(LightProjection, LightView);
		//}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		///////  2nd pass: render onto texture ////////////
		glBindFramebuffer(GL_FRAMEBUFFER, render_fbo);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, width, height);
		shadow->Bind(GL_TEXTURE0 + shadow_map_id);
		render_tex->Bind(GL_TEXTURE0 + render_tex_id);

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
		for (uint i = 0; i < projectile_list.size(); ++i)
		{
			projectile_list[i]->draw();
		}
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		for (uint i = 0; i < stationary_list.size(); ++i)
		{
			stationary_list[i]->draw();
		}
		glDepthMask(GL_FALSE);
		for (uint i = 0; i < tower_projectile_list.size(); ++i)
		{
			tower_projectile_list[i]->draw();
		}
		for (uint i = 0; i < panim_list.size(); i++){
			panim_list[i]->draw();
		}
		for (uint i = 0; i < lightning_list.size(); i++){
			lightning_list[i]->draw();
		
			//WAY TOO LAGGY! 16fps
			//vec3 temp = lightning_list[i]->getPosition();
			//FMOD_VECTOR pt = { temp.x, temp.y, temp.z };
			//sound_3d_light->setPosition(pt);
			//sound_3d_light->Play3D(View);
		}
		if (TowerHP[2]>0 || TowerHP[3]>0){
			force_field[0]->draw();
		}
		if (TowerHP[0]>0 || TowerHP[1]>0){
			force_field[1]->draw();
		}
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);

		//	md5->draw();

		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glDepthMask(GL_FALSE); // without it some part of model will cover other part of model which looks weird
		//	md6->draw();
		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);

		if (bVis[SPEEDUP])
			m_billboardList.Render(Projection, View, 1.0f);
		if (bVis[DOUBLEDAMAGE])
			m_billboardList2.Render(Projection, View, 1.0f);
		if (bVis[HEALTHBOOST])
			m_billboardList3.Render(Projection, View, 1.0f);
		if (bVis[FASTERSHOOT])
			m_billboardList4.Render(Projection, View, 1.0f);
		if (bVis[FARTHERSHOOT])
			m_billboardList5.Render(Projection, View, 1.0f);

		//m_billboardList6.Render(Projection, View, 1.0f);

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
		//damagePart->draw(Projection, View);


		for (uint i = 0; i < explosion_list.size(); ++i)
		{
			explosion_list[i]->draw(Projection, View);
			if (explosion_list[i]->getCurrentLoopCount() == explosion_list[i]->getLoopCount())
			{
				delete explosion_list[i];
				explosion_list.erase(explosion_list.begin() + i);
			}
		}
		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);
		glDisable(GL_DEPTH_TEST);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		///////  3rd pass: render onto screen ////////////
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, width, height);
		render_tex->Bind(GL_TEXTURE0 + render_tex_id);
		screen_quad->draw();

		///////////////////////////////////////////////// UI Divide /////////////////////////////////////////////////////////

		myUI->draw();
		if (drawPortThingFuck){
			myUI->drawPortrait(portPlayer, portString);
		}

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

		else if (myClientState->getState() == 5){
			//ENDGAME
			if (winner == 1 && (playerID % 2) == 0)
			{
				if (!winCountToggle)
				{
					displayWinner = 1;
					wins++;
					myGameMenu->setRoundWon('c', wins);
					winCountToggle = !winCountToggle;
					SoundEvents.push_back(testSound[SoundVictory]);
					SoundEventsIcon.push_back(NOT_A_PLAYER);
					SoundEventsString.push_back("");
					//cout << "Total Wins: " << wins << endl;
				}
			}
			else if (winner == 0 && (playerID % 2) == 1)
			{
				if (!winCountToggle)
				{
					displayWinner = 1;
					wins++;
					myGameMenu->setRoundWon('m', wins);
					winCountToggle = !winCountToggle;
					SoundEvents.push_back(testSound[SoundVictory]);
					SoundEventsIcon.push_back(NOT_A_PLAYER);
					SoundEventsString.push_back("");
					//cout << "Total Wins: " << wins << endl;
				}
			}
			else  if (winner == 1 && (playerID % 2) == 1)
			{
				if (!winCountToggle)
				{
					displayWinner = 0;
					enemyWins++;
					myGameMenu->setRoundWon('c', enemyWins);
					winCountToggle = !winCountToggle;
					SoundEvents.push_back(testSound[SoundDefeat]);
					SoundEventsIcon.push_back(NOT_A_PLAYER);
					SoundEventsString.push_back("");
					//cout << "Total Wins: " << wins << endl;
				}
			}
			else  if (winner == 0 && (playerID % 2) == 0)
			{
				if (!winCountToggle)
				{
					displayWinner = 0;
					enemyWins++;
					myGameMenu->setRoundWon('m', enemyWins);
					winCountToggle = !winCountToggle;
					SoundEvents.push_back(testSound[SoundDefeat]);
					SoundEventsIcon.push_back(NOT_A_PLAYER);
					SoundEventsString.push_back("");
					//cout << "Total Wins: " << wins << endl;
				}
			}
			endScreen->draw(displayWinner, wins);
		}

		else if (kill_count){
			myGameMenu->killDraw();
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

LARGE_INTEGER time_track;
//LARGE_INTEGER asdf, jkl;
void server_update(int value){
	//This is where we would be doing the stuffs
	// Build send vectors and send
	(*sendVec)[0] = std::make_pair(std::to_string(playerID), mat4((float)keyState));
	(*sendVec)[1] = std::make_pair(std::to_string(playerID), mat4((float)mouseState));
	(*sendVec)[2] = std::make_pair(std::to_string(playerID), cam[playerID]->getCamM());
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
	else{
		recvValid = false;
	}

	bool p0f = false;
	bool p1f = false;
	bool p2f = false;
	bool p3f = false;
	//stateID = atoi(&((*recvVec)[0].first.c_str())[0]);
	if (recvValid)
	{
		// get shoot bit from recvVec for player 0
		int shootID;
		if (parseOpts->getShoot(recvVec, PLAYER0, shootID))
		{
			//std::cout << "Projectile fire" << std::endl;
			projectileAttack(PLAYER0, cam[PLAYER0], shootID);
			if (playerID == PLAYER0)
			{
				myUI->setShots(1);
			}
			//cout << "FIRE 0!" << endl;
			p0f = true;
		}

		if (parseOpts->getShoot(recvVec, PLAYER1, shootID))
		{
			//std::cout << "Projectile fire" << std::endl;
			projectileAttack(PLAYER1, cam[PLAYER1], shootID);
			if (playerID == PLAYER1)
			{
				myUI->setShots(1);
			}
			//cout << "FIRE 1!" << endl;
			p1f = true;
		}

		if (parseOpts->getShoot(recvVec, PLAYER2, shootID))
		{
			//std::cout << "Projectile fire" << std::endl;
			projectileAttack(PLAYER2, cam[PLAYER2], shootID);
			if (playerID == PLAYER2)
			{
				myUI->setShots(1);
			}
			//cout << "FIRE 2!" << endl;
			p2f = true;
		}

		if (parseOpts->getShoot(recvVec, PLAYER3, shootID))
		{
			//std::cout << "Projectile fire" << std::endl;
			projectileAttack(PLAYER3, cam[PLAYER3], shootID);
			if (playerID == PLAYER3)
			{
				myUI->setShots(1);
			}
			//cout << "FIRE 3!" << endl;
			p3f = true;
		}

		//tower shoot
		vector<TowerShootInfoClient> tsi;
		parseOpts->getTowerShoot(recvVec, tsi);
		for (uint i = 0; i < tsi.size(); i++){
			towerProjectileAttack(tsi[i].towerID, tsi[i].projectileID, tsi[i].direction);
		}
		for (int i = 0; i < NUM_TOWERS; i++){
			if (parseOpts->getTowerDamaged(recvVec, i)){
				towerDamage(i);
			}
			if (parseOpts->getTowerKill(recvVec, i)){
				towerKill(i);
			}
			TowerHP[i] = parseOpts->getTowerHealth(recvVec, i);
			if ((TowerHP[i] <= 0) && (TowerState[i] < TOWER_0_HP)){
				//play tower dead
				TowerState[i] = TOWER_0_HP;
				if ((i == TEAM_C_LEFT_TOWER) || (i == TEAM_C_RIGHT_TOWER) || (i == TEAM_C_MID_TOWER)){
					if ((playerID == PLAYER0) || (playerID == PLAYER2)){
						//Play your tower shit
						SoundEvents.push_back(testSound[SoundTurretDieYourTeam]);
						SoundEventsIcon.push_back(NOT_A_PLAYER);
						SoundEventsString.push_back("One of your turrets was destroyed!");
					}
					else{
						//Play enemy tower shit
						//SoundEvents.push_back(testSound[SoundFirstBlood]);
					}
				}
				else{
					if ((playerID == PLAYER0) || (playerID == PLAYER2)){
						//Play enemy tower shit
						//SoundEvents.push_back(testSound[SoundFirstBlood]);
					}
					else{
						//Play your tower shit
						SoundEvents.push_back(testSound[SoundTurretDieYourTeam]);
						SoundEventsIcon.push_back(NOT_A_PLAYER);
						SoundEventsString.push_back("One of your turrets was destroyed!");
					}
				}
			}
			else if ((TowerHP[i] <= 2) && (TowerState[i] < TOWER_10P_HP)){
				//play tower almost dead
				TowerState[i] = TOWER_10P_HP;
				if ((i == TEAM_C_LEFT_TOWER) || (i == TEAM_C_RIGHT_TOWER) || (i == TEAM_C_MID_TOWER)){
					if ((playerID == PLAYER0) || (playerID == PLAYER2)){
						//Play your tower shit
						SoundEvents.push_back(testSound[SoundTurretAlmostKillYour]);
						SoundEventsIcon.push_back(NOT_A_PLAYER);
						SoundEventsString.push_back("One of your turrets is nearly destroyed!");
					}
					else{
						//Play enemy tower shit
						SoundEvents.push_back(testSound[SoundTurretAlmostKillEne]);
						SoundEventsIcon.push_back(NOT_A_PLAYER);
						SoundEventsString.push_back("One of the enemy turrets is nearly destroyed!");
					}
				}
				else{
					if ((playerID == PLAYER0) || (playerID == PLAYER2)){
						//Play enemy tower shit
						SoundEvents.push_back(testSound[SoundTurretAlmostKillEne]);
						SoundEventsIcon.push_back(NOT_A_PLAYER);
						SoundEventsString.push_back("One of the enemy turrets is nearly destroyed!");
					}
					else{
						//Play your tower shit
						SoundEvents.push_back(testSound[SoundTurretAlmostKillYour]);
						SoundEventsIcon.push_back(NOT_A_PLAYER);
						SoundEventsString.push_back("One of your turrets is nearly destroyed!");
					}
				}
			}
			else if ((TowerHP[i] <= 10) && (TowerState[i] < TOWER_HALF_HP)){
				//play tower half dead
				TowerState[i] = TOWER_HALF_HP;
				if ((i == TEAM_C_LEFT_TOWER) || (i == TEAM_C_RIGHT_TOWER) || (i == TEAM_C_MID_TOWER)){
					if ((playerID == PLAYER0) || (playerID == PLAYER2)){
						//Play your tower shit
						SoundEvents.push_back(testSound[SoundTurretHalfKillYourT]);
						SoundEventsIcon.push_back(NOT_A_PLAYER);
						SoundEventsString.push_back("One of your turrets is at half health!");
					}
					else{
						//Play enemy tower shit
						SoundEvents.push_back(testSound[SoundTurretHalfKillEnemy]);
						SoundEventsIcon.push_back(NOT_A_PLAYER);
						SoundEventsString.push_back("One of the enemy turrets is at half health!");
					}
				}
				else{
					if ((playerID == PLAYER0) || (playerID == PLAYER2)){
						//Play enemy tower shit
						SoundEvents.push_back(testSound[SoundTurretHalfKillEnemy]);
						SoundEventsIcon.push_back(NOT_A_PLAYER);
						SoundEventsString.push_back("One of the enemy turrets is at half health!");
					}
					else{
						//Play your tower shit
						SoundEvents.push_back(testSound[SoundTurretHalfKillYourT]);
						SoundEventsIcon.push_back(NOT_A_PLAYER);
						SoundEventsString.push_back("One of your turrets is at half health!");
					}
				}
			}
			else if ((TowerHP[i] <= 18) && (TowerState[i] < TOWER_90P_HP)){
				//play tower hit
				TowerState[i] = TOWER_90P_HP;
				if ((i == TEAM_C_LEFT_TOWER) || (i == TEAM_C_RIGHT_TOWER) || (i == TEAM_C_MID_TOWER)){
					if ((playerID == PLAYER0) || (playerID == PLAYER2)){
						//Play your tower shit
						SoundEvents.push_back(testSound[SoundTurretAttackedYourT]);
						SoundEventsIcon.push_back(NOT_A_PLAYER);
						SoundEventsString.push_back("One of your turrets is under attack!");
					}
					else{
						//Play enemy tower shit
						//SoundEvents.push_back(testSound[SoundFirstBlood]);
					}
				}
				else{
					if ((playerID == PLAYER0) || (playerID == PLAYER2)){
						//Play enemy tower shit
						//SoundEvents.push_back(testSound[SoundFirstBlood]);
					}
					else{
						//Play your tower shit
						SoundEvents.push_back(testSound[SoundTurretAttackedYourT]);
						SoundEventsIcon.push_back(NOT_A_PLAYER);
						SoundEventsString.push_back("One of your turrets is under attack!");
					}
				}
			}
			
		}

		//despawn projectiles from hit
		vector<int> ppdl = parseOpts->getPPDL(recvVec);
		for (uint i = 0; i < ppdl.size(); i++){
			//cout << "despawn: " << ppdl[i] << endl;
			for (uint k = 0; k < projectile_list.size(); k++){
				if (projectile_list[k]->getShootID() == ppdl[i]){
					delete projectile_list[k];
					projectile_list.erase(projectile_list.begin() + k);
					break;
				}
			}
		}

		std::vector<std::pair<int, bool>> platformDamage = parseOpts->getPlatformDamage(recvVec);
		std::vector<std::pair<int, bool>> platformDead = parseOpts->getPlatformDead(recvVec);
		std::vector<std::pair<int, int>> platformHealth = parseOpts->getPlatformHealth(recvVec);
		//cout << stationary_list.size() << " " << platformDamage.size() << " " << platformDead.size() << " " << platformHealth.size() << endl;
		//cout << (*recvVec)[PLATFORM_STATUS].first << endl;
		for (uint i = 0; i < platformDead.size(); i++)
		{
			if (platformDead[i].second)
			{
				stationary_list[platformDead[i].first]->setModelM(stationary_list[platformDead[i].first]->getModelM()*glm::translate(vec3(1000, 1000, 1000)));
			}
			else
			{
				stationary_list[platformDead[i].first]->setModelM(stationary_list[platformDead[i].first]->getAliveModelM());
				stationary_list[platformDead[i].first]->setHealth(7);
			}
			if (platformDamage[i].second)
			{
				stationary_list[platformDead[i].first]->setHealth(-1);
			}
			//cout << platformDead[i].first << " " << platformHealth[i].second<< " ";
			((Cube *)stationary_list[platformDead[i].first])->setTransparency(((float)platformHealth[i].second) / 7.00);

			//((Cube *)stationary_list[57])->setTransparency(0);
		}
		//cout << endl;
		mats[PLAYER0] = (*recvVec)[PLAYER_MAT_BEGIN + PLAYER0].second;
		mats[PLAYER1] = (*recvVec)[PLAYER_MAT_BEGIN + PLAYER1].second;
		mats[PLAYER2] = (*recvVec)[PLAYER_MAT_BEGIN + PLAYER2].second;
		mats[PLAYER3] = (*recvVec)[PLAYER_MAT_BEGIN + PLAYER3].second;

		player_list[PLAYER0]->setModelM(mats[PLAYER0]);
		player_list[PLAYER1]->setModelM(mats[PLAYER1]);
		player_list[PLAYER2]->setModelM(mats[PLAYER2]);
		player_list[PLAYER3]->setModelM(mats[PLAYER3]);

		//Finding each players pos vec for 3D sound
		player0_sound_vec_lasterest = player0_sound_vec_last;
		player1_sound_vec_lasterest = player1_sound_vec_last;
		player2_sound_vec_lasterest = player2_sound_vec_last;
		player3_sound_vec_lasterest = player3_sound_vec_last;

		player0_sound_vec_last = player0_sound_vec_curr;
		player1_sound_vec_last = player1_sound_vec_curr;
		player2_sound_vec_last = player2_sound_vec_curr;
		player3_sound_vec_last = player3_sound_vec_curr;
		vec4 temp0(0.0, 0.0, 0.0, 1.0);
		vec4 temp1(0.0, 0.0, 0.0, 1.0);
		vec4 temp2(0.0, 0.0, 0.0, 1.0);
		vec4 temp3(0.0, 0.0, 0.0, 1.0);
		temp0 = player_list[PLAYER0]->getModelM() *temp0;
		temp1 = player_list[PLAYER1]->getModelM() *temp1;
		temp2 = player_list[PLAYER2]->getModelM() *temp2;
		temp3 = player_list[PLAYER3]->getModelM() *temp3;
		player0_sound_vec_curr = { temp0.x, temp0.y, temp0.z };
		player1_sound_vec_curr = { temp1.x, temp1.y, temp1.z };
		player2_sound_vec_curr = { temp2.x, temp2.y, temp2.z };
		player3_sound_vec_curr = { temp3.x, temp3.y, temp3.z };

		/////////////////////////////////////////////////////////displaying particle effect///////////////////////////////////////////////////////
		if (parseOpts->getDamaged(recvVec, PLAYER0))
		{
			//cout << "damaged 0" << endl;
			spawnDamageParticle(PLAYER0);
			sound_3d_hit->setPosition(player0_sound_vec_curr);
			sound_3d_hit->Play3D(View);
			myUI->setLess_Life(1);
		}

		if (parseOpts->getDamaged(recvVec, PLAYER1))
		{
			//cout << "damaged 1" << endl;
			spawnDamageParticle(PLAYER1);
			sound_3d_hit->setPosition(player0_sound_vec_curr);
			sound_3d_hit->Play3D(View);
			myUI->setLess_Life(1);
		}

		if (parseOpts->getDamaged(recvVec, PLAYER2))
		{
			//cout << "damaged 2" << endl;
			spawnDamageParticle(PLAYER2);
			sound_3d_hit->setPosition(player0_sound_vec_curr);
			sound_3d_hit->Play3D(View);
			myUI->setLess_Life(1);
		}

		if (parseOpts->getDamaged(recvVec, PLAYER3))
		{
			//cout << "damaged 3" << endl;
			spawnDamageParticle(PLAYER3);
			sound_3d_hit->setPosition(player0_sound_vec_curr);
			sound_3d_hit->Play3D(View);
			myUI->setLess_Life(1);
		}

		//KILLS
		if (parseOpts->getKilled(recvVec, PLAYER0))
		{
			//cout << "Killed 0" << endl;
			if (!dead[PLAYER0])
			{
				if (Player0_KillSpree > 2){
					SoundEvents.push_back(testSound[SoundShutdown]);
					SoundEventsIcon.push_back(PLAYER0);
					SoundEventsString.push_back("Player 1 Shut Down!");
				}
				Player0_KillSpree = 0;
				Player0_KillSpreeLast = 0;
				spawnDeathParticle(player0_sound_vec_lasterest.x, player0_sound_vec_lasterest.y, player0_sound_vec_lasterest.z);
				sound_3d_death->setPosition(player0_sound_vec_lasterest);
				sound_3d_death->Play3D(View);
				sound_3d_death2->setPosition(player0_sound_vec_lasterest);
				sound_3d_death2->Play3D(View);
				myGameMenu->setDeath(PLAYER0);
				dead[PLAYER0] = true;
			}
		}
		else
			dead[PLAYER0] = false;

		if (parseOpts->getKilled(recvVec, PLAYER1))
		{
			//cout << "Killed 1" << endl;
			if (!dead[PLAYER1])
			{
				if (Player1_KillSpree > 2){
					SoundEvents.push_back(testSound[SoundShutdown]);
					SoundEventsIcon.push_back(PLAYER1);
					SoundEventsString.push_back("Player 2 Shut Down!");
				}
				Player1_KillSpree = 0;
				Player1_KillSpreeLast = 0;
				spawnDeathParticle(player1_sound_vec_lasterest.x, player1_sound_vec_lasterest.y, player1_sound_vec_lasterest.z);
				sound_3d_death->setPosition(player1_sound_vec_lasterest);
				sound_3d_death->Play3D(View);
				sound_3d_death2->setPosition(player1_sound_vec_lasterest);
				sound_3d_death2->Play3D(View);
				myGameMenu->setDeath(PLAYER1);
				dead[PLAYER1] = true;
			}
		}
		else
			dead[PLAYER1] = false;

		if (parseOpts->getKilled(recvVec, PLAYER2))
		{
			//cout << "Killed 2" << endl;
			if (!dead[PLAYER2])
			{
				if (Player2_KillSpree > 2){
					SoundEvents.push_back(testSound[SoundShutdown]);
					SoundEventsIcon.push_back(PLAYER2);
					SoundEventsString.push_back("Player 3 Shut Down!");
				}
				Player2_KillSpree = 0;
				Player2_KillSpreeLast = 0;
				spawnDeathParticle(player2_sound_vec_lasterest.x, player2_sound_vec_lasterest.y, player2_sound_vec_lasterest.z);
				sound_3d_death->setPosition(player2_sound_vec_lasterest);
				sound_3d_death->Play3D(View);
				sound_3d_death2->setPosition(player2_sound_vec_lasterest);
				sound_3d_death2->Play3D(View);
				myGameMenu->setDeath(PLAYER2);
				dead[PLAYER2] = true;
			}
		}
		else
			dead[PLAYER2] = false;

		if (parseOpts->getKilled(recvVec, PLAYER3))
		{
			//cout << "Killed 3" << endl;
			if (!dead[PLAYER3])
			{
				if (Player3_KillSpree > 2){
					SoundEvents.push_back(testSound[SoundShutdown]);
					SoundEventsIcon.push_back(PLAYER3);
					SoundEventsString.push_back("Player 4 Shut Down!");
				}
				Player3_KillSpree = 0;
				Player3_KillSpreeLast = 0;
				spawnDeathParticle(player3_sound_vec_lasterest.x, player3_sound_vec_lasterest.y, player3_sound_vec_lasterest.z);
				sound_3d_death->setPosition(player3_sound_vec_lasterest);
				sound_3d_death->Play3D(View);
				sound_3d_death2->setPosition(player3_sound_vec_lasterest);
				sound_3d_death2->Play3D(View);
				myGameMenu->setDeath(PLAYER3);
				dead[PLAYER3] = true;
			}
		}
		else
			dead[PLAYER3] = false;

		if (parseOpts->getKilled(recvVec, playerID))
		{
			//myDeathScreen->setDeathClock(clock());
			//myClientState->setState(3);
			alive = false;
		}
		if (!alive && !parseOpts->getKilled(recvVec, playerID))
		{
			alive = true;
		}


		// TODO link up health to UI
		myUI->healthBar((float)parseOpts->getPHealth(recvVec, playerID)/max_health);

		// TODO display kills somewhere
		Player0_KillCountLast = Player0_KillCount;
		Player1_KillCountLast = Player1_KillCount;
		Player2_KillCountLast = Player2_KillCount;
		Player3_KillCountLast = Player3_KillCount;

		Player0_KillCount = parseOpts->getPKills(recvVec, PLAYER0);
		Player1_KillCount = parseOpts->getPKills(recvVec, PLAYER1);
		Player2_KillCount = parseOpts->getPKills(recvVec, PLAYER2);
		Player3_KillCount = parseOpts->getPKills(recvVec, PLAYER3);

		if (FirstBloodTrigger){
			if (Player0_KillCount){
				FirstBloodTrigger = false;
				SoundEvents.push_back(testSound[SoundFirstBlood]);
				SoundEventsIcon.push_back(PLAYER0);
				SoundEventsString.push_back("Player 1 First Blood!");
			}
			else if (Player1_KillCount){
				FirstBloodTrigger = false;
				SoundEvents.push_back(testSound[SoundFirstBlood]);
				SoundEventsIcon.push_back(PLAYER1);
				SoundEventsString.push_back("Player 2 First Blood!");
			}
			else if (Player2_KillCount){
				FirstBloodTrigger = false;
				SoundEvents.push_back(testSound[SoundFirstBlood]);
				SoundEventsIcon.push_back(PLAYER2);
				SoundEventsString.push_back("Player 3 First Blood!");
			}
			else if (Player3_KillCount){
				FirstBloodTrigger = false;
				SoundEvents.push_back(testSound[SoundFirstBlood]);
				SoundEventsIcon.push_back(PLAYER3);
				SoundEventsString.push_back("Player 4 First Blood!");
			}
		}

		if (Player0_DoubleKillTime > 30){
			Player0_DoubleKillTime -= 30;
		}
		else{
			Player0_DoubleKillTime = 0;
		}

		if (Player1_DoubleKillTime > 30){
			Player1_DoubleKillTime -= 30;
		}
		else{
			Player1_DoubleKillTime = 0;
		}

		if (Player2_DoubleKillTime > 30){
			Player2_DoubleKillTime -= 30;
		}
		else{
			Player2_DoubleKillTime = 0;
		}

		if (Player3_DoubleKillTime > 30){
			Player3_DoubleKillTime -= 30;
		}
		else{
			Player3_DoubleKillTime = 0;
		}

		if (Player0_KillCount > Player0_KillCountLast){
			if (Player0_DoubleKillTime || Player0_KillCount >= (Player0_KillCountLast + 2)){
				//Play Double Kill Sound
				if (playerID == PLAYER0 || playerID == PLAYER2)
				{
					//testSound[SoundDoubleKillY]->Play();
					SoundEvents.push_back(testSound[SoundDoubleKillY]);
					SoundEventsIcon.push_back(PLAYER0);
					SoundEventsString.push_back("Player 1 Double Kill!");
				}
				else{
					//testSound[SoundDoubleKillE]->Play();
					SoundEvents.push_back(testSound[SoundDoubleKillE]);
					SoundEventsIcon.push_back(PLAYER0);
					SoundEventsString.push_back("Player 1 Double Kill!");
				}
			}
			Player0_KillSpreeLast = Player0_KillSpree;
			Player0_KillSpree += (Player0_KillCount - Player0_KillCountLast);
			Player0_DoubleKillTime = 3000;
		}
		if (Player1_KillCount > Player1_KillCountLast){
			if (Player1_DoubleKillTime || (Player1_KillCount >= (Player1_KillCountLast + 2))){
				if (playerID == PLAYER1 || playerID == PLAYER3)
				{
					//testSound[SoundDoubleKillY]->Play();
					SoundEvents.push_back(testSound[SoundDoubleKillY]);
					SoundEventsIcon.push_back(PLAYER1);
					SoundEventsString.push_back("Player 2 Double Kill!");
				}
				else{
					//testSound[SoundDoubleKillE]->Play();
					SoundEvents.push_back(testSound[SoundDoubleKillE]);
					SoundEventsIcon.push_back(PLAYER1);
					SoundEventsString.push_back("Player 2 Double Kill!");
				}
			}
			Player1_KillSpreeLast = Player1_KillSpree;
			Player1_KillSpree += (Player1_KillCount - Player1_KillCountLast);
			Player1_DoubleKillTime = 3000;
		}
		if (Player2_KillCount > Player2_KillCountLast){
			if (Player2_DoubleKillTime || (Player2_KillCount >= (Player2_KillCountLast + 2))){
				if (playerID == PLAYER0 || playerID == PLAYER2)
				{
					//testSound[SoundDoubleKillY]->Play();
					SoundEvents.push_back(testSound[SoundDoubleKillY]);
					SoundEventsIcon.push_back(PLAYER2);
					SoundEventsString.push_back("Player 3 Double Kill!");
				}
				else{
					//testSound[SoundDoubleKillE]->Play();
					SoundEvents.push_back(testSound[SoundDoubleKillE]);
					SoundEventsIcon.push_back(PLAYER2);
					SoundEventsString.push_back("Player 3 Double Kill!");
				}
			}
			Player2_KillSpreeLast = Player2_KillSpree;
			Player2_KillSpree += (Player2_KillCount - Player2_KillCountLast);
			Player2_DoubleKillTime = 3000;
		}
		if (Player3_KillCount > Player3_KillCountLast){
			if (Player3_DoubleKillTime || (Player3_KillCount >= (Player3_KillCountLast + 2))){
				if (playerID == PLAYER1 || playerID == PLAYER3)
				{
					//testSound[SoundDoubleKillY]->Play();
					SoundEvents.push_back(testSound[SoundDoubleKillY]);
					SoundEventsIcon.push_back(PLAYER3);
					SoundEventsString.push_back("Player 4 Double Kill!");
				}
				else{
					//testSound[SoundDoubleKillE]->Play();
					SoundEvents.push_back(testSound[SoundDoubleKillE]);
					SoundEventsIcon.push_back(PLAYER3);
					SoundEventsString.push_back("Player 4 Double Kill!");
				}
			}
			Player3_KillSpreeLast = Player3_KillSpree;
			Player3_KillSpree += (Player3_KillCount - Player3_KillCountLast);
			Player3_DoubleKillTime = 3000;
		}

		
		if ((Player0_KillSpree > Player0_KillSpreeLast) && (Player0_KillSpree > 2)){
			SoundEventsIcon.push_back(PLAYER0);
			if (Player0_KillSpree > 8){
				Player0_KillSpree = 8;
			}
			Player0_KillSpreeLast = Player0_KillSpree;
			if (playerID == PLAYER0) 
			{
				switch (Player0_KillSpree){
				case 3:
					SoundEventsString.push_back("Player 1 Killing Spree!");
					SoundEvents.push_back(testSound[SoundKillingSpreeU]);
					break;
				case 4:
					SoundEventsString.push_back("Player 1 Rampage!");
					SoundEvents.push_back(testSound[SoundKillingSpree2U]);
					break;
				case 5:
					SoundEventsString.push_back("Player 1 is Unstoppable!");
					SoundEvents.push_back(testSound[SoundKillingSpree3U]);
					break;
				case 6:
					SoundEvents.push_back(testSound[SoundKillingSpree4U]);
					SoundEventsString.push_back("Player 1 is Dominating!");
					break;
				case 7:
					SoundEvents.push_back(testSound[SoundKillingSpree5U]);
					SoundEventsString.push_back("Player 1 is God Like!");
					break;
				case 8:
					SoundEvents.push_back(testSound[SoundKillingSpree6U]);
					SoundEventsString.push_back("Player 1 is Legendary!");
					break;
				default:
					break;
				}
			}
			else if (playerID == PLAYER2){
				switch (Player0_KillSpree){
				case 3:
					SoundEventsString.push_back("Player 1 Killing Spree!");
					SoundEvents.push_back(testSound[SoundKillingSpreeY]);
					break;
				case 4:
					SoundEventsString.push_back("Player 1 Rampage!");
					SoundEvents.push_back(testSound[SoundKillingSpree2Y]);
					break;
				case 5:
					SoundEventsString.push_back("Player 1 is Unstoppable!");
					SoundEvents.push_back(testSound[SoundKillingSpree3Y]);
					break;
				case 6:
					SoundEventsString.push_back("Player 1 is Dominating!");
					SoundEvents.push_back(testSound[SoundKillingSpree4Y]);
					break;
				case 7:
					SoundEventsString.push_back("Player 1 is God Like!");
					SoundEvents.push_back(testSound[SoundKillingSpree5Y]);
					break;
				case 8:
					SoundEventsString.push_back("Player 1 is Legendary!");
					SoundEvents.push_back(testSound[SoundKillingSpree6Y]);
					break;
				default:
					break;
				}
			}
			else{
				switch (Player0_KillSpree){
				case 3:
					SoundEventsString.push_back("Player 1 Killing Spree!");
					SoundEvents.push_back(testSound[SoundKillingSpreeE]);
					break;
				case 4:
					SoundEventsString.push_back("Player 1 Rampage!");
					SoundEvents.push_back(testSound[SoundKillingSpree2E]);
					break;
				case 5:
					SoundEventsString.push_back("Player 1 is Unstoppable!");
					SoundEvents.push_back(testSound[SoundKillingSpree3E]);
					break;
				case 6:
					SoundEventsString.push_back("Player 1 is Dominating!");
					SoundEvents.push_back(testSound[SoundKillingSpree4E]);
					break;
				case 7:
					SoundEventsString.push_back("Player 1 is God Like!");
					SoundEvents.push_back(testSound[SoundKillingSpree5E]);
					break;
				case 8:
					SoundEventsString.push_back("Player 1 is Legendary!");
					SoundEvents.push_back(testSound[SoundKillingSpree6E]);
					break;
				default:
					break;
				}
			}
		}
		if ((Player1_KillSpree > Player1_KillSpreeLast) && (Player1_KillSpree > 2)){
			SoundEventsIcon.push_back(PLAYER1);
			if (Player1_KillSpree > 8){
				Player1_KillSpree = 8;
			}
			Player1_KillSpreeLast = Player1_KillSpree;
			if (playerID == PLAYER1)
			{
				switch (Player1_KillSpree){
				case 3:
					SoundEventsString.push_back("Player 2 Killing Spree!");
					SoundEvents.push_back(testSound[SoundKillingSpreeU]);
					break;
				case 4:
					SoundEventsString.push_back("Player 2 Rampage!");
					SoundEvents.push_back(testSound[SoundKillingSpree2U]);
					break;
				case 5:
					SoundEventsString.push_back("Player 2 is Unstoppable!");
					SoundEvents.push_back(testSound[SoundKillingSpree3U]);
					break;
				case 6:
					SoundEvents.push_back(testSound[SoundKillingSpree4U]);
					SoundEventsString.push_back("Player 2 is Dominating!");
					break;
				case 7:
					SoundEvents.push_back(testSound[SoundKillingSpree5U]);
					SoundEventsString.push_back("Player 2 is God Like!");
					break;
				case 8:
					SoundEvents.push_back(testSound[SoundKillingSpree6U]);
					SoundEventsString.push_back("Player 2 is Legendary!");
					break;
				default:
					break;
				}
			}
			else if (playerID == PLAYER3){
				switch (Player1_KillSpree){
				case 3:
					SoundEventsString.push_back("Player 2 Killing Spree!");
					SoundEvents.push_back(testSound[SoundKillingSpreeY]);
					break;
				case 4:
					SoundEventsString.push_back("Player 2 Rampage!");
					SoundEvents.push_back(testSound[SoundKillingSpree2Y]);
					break;
				case 5:
					SoundEventsString.push_back("Player 2 is Unstoppable!");
					SoundEvents.push_back(testSound[SoundKillingSpree3Y]);
					break;
				case 6:
					SoundEventsString.push_back("Player 2 is Dominating!");
					SoundEvents.push_back(testSound[SoundKillingSpree4Y]);
					break;
				case 7:
					SoundEventsString.push_back("Player 2 is God Like!");
					SoundEvents.push_back(testSound[SoundKillingSpree5Y]);
					break;
				case 8:
					SoundEventsString.push_back("Player 2 is Legendary!");
					SoundEvents.push_back(testSound[SoundKillingSpree6Y]);
					break;
				default:
					break;
				}
			}
			else{
				switch (Player1_KillSpree){
				case 3:
					SoundEventsString.push_back("Player 2 Killing Spree!");
					SoundEvents.push_back(testSound[SoundKillingSpreeE]);
					break;
				case 4:
					SoundEventsString.push_back("Player 2 Rampage!");
					SoundEvents.push_back(testSound[SoundKillingSpree2E]);
					break;
				case 5:
					SoundEventsString.push_back("Player 2 is Unstoppable!");
					SoundEvents.push_back(testSound[SoundKillingSpree3E]);
					break;
				case 6:
					SoundEventsString.push_back("Player 2 is Dominating!");
					SoundEvents.push_back(testSound[SoundKillingSpree4E]);
					break;
				case 7:
					SoundEventsString.push_back("Player 2 is God Like!");
					SoundEvents.push_back(testSound[SoundKillingSpree5E]);
					break;
				case 8:
					SoundEventsString.push_back("Player 2 is Legendary!");
					SoundEvents.push_back(testSound[SoundKillingSpree6E]);
					break;
				default:
					break;
				}
			}
		}
		if ((Player2_KillSpree > Player2_KillSpreeLast) && (Player2_KillSpree > 2)){
			SoundEventsIcon.push_back(PLAYER2);
			if (Player2_KillSpree > 8){
				Player2_KillSpree = 8;
			}
			Player2_KillSpreeLast = Player2_KillSpree;
			if (playerID == PLAYER2)
			{
				switch (Player2_KillSpree){
				case 3:
					SoundEventsString.push_back("Player 3 Killing Spree!");
					SoundEvents.push_back(testSound[SoundKillingSpreeU]);
					break;
				case 4:
					SoundEventsString.push_back("Player 3 Rampage!");
					SoundEvents.push_back(testSound[SoundKillingSpree2U]);
					break;
				case 5:
					SoundEventsString.push_back("Player 3 is Unstoppable!");
					SoundEvents.push_back(testSound[SoundKillingSpree3U]);
					break;
				case 6:
					SoundEvents.push_back(testSound[SoundKillingSpree4U]);
					SoundEventsString.push_back("Player 3 is Dominating!");
					break;
				case 7:
					SoundEvents.push_back(testSound[SoundKillingSpree5U]);
					SoundEventsString.push_back("Player 3 is God Like!");
					break;
				case 8:
					SoundEvents.push_back(testSound[SoundKillingSpree6U]);
					SoundEventsString.push_back("Player 3 is Legendary!");
					break;
				default:
					break;
				}
			}
			else if (playerID == PLAYER0){
				switch (Player2_KillSpree){
				case 3:
					SoundEventsString.push_back("Player 3 Killing Spree!");
					SoundEvents.push_back(testSound[SoundKillingSpreeY]);
					break;
				case 4:
					SoundEventsString.push_back("Player 3 Rampage!");
					SoundEvents.push_back(testSound[SoundKillingSpree2Y]);
					break;
				case 5:
					SoundEventsString.push_back("Player 3 is Unstoppable!");
					SoundEvents.push_back(testSound[SoundKillingSpree3Y]);
					break;
				case 6:
					SoundEventsString.push_back("Player 3 is Dominating!");
					SoundEvents.push_back(testSound[SoundKillingSpree4Y]);
					break;
				case 7:
					SoundEventsString.push_back("Player 3 is God Like!");
					SoundEvents.push_back(testSound[SoundKillingSpree5Y]);
					break;
				case 8:
					SoundEventsString.push_back("Player 3 is Legendary!");
					SoundEvents.push_back(testSound[SoundKillingSpree6Y]);
					break;
				default:
					break;
				}
			}
			else{
				switch (Player2_KillSpree){
				case 3:
					SoundEventsString.push_back("Player 3 Killing Spree!");
					SoundEvents.push_back(testSound[SoundKillingSpreeE]);
					break;
				case 4:
					SoundEventsString.push_back("Player 3 Rampage!");
					SoundEvents.push_back(testSound[SoundKillingSpree2E]);
					break;
				case 5:
					SoundEventsString.push_back("Player 3 is Unstoppable!");
					SoundEvents.push_back(testSound[SoundKillingSpree3E]);
					break;
				case 6:
					SoundEventsString.push_back("Player 3 is Dominating!");
					SoundEvents.push_back(testSound[SoundKillingSpree4E]);
					break;
				case 7:
					SoundEventsString.push_back("Player 3 is God Like!");
					SoundEvents.push_back(testSound[SoundKillingSpree5E]);
					break;
				case 8:
					SoundEventsString.push_back("Player 3 is Legendary!");
					SoundEvents.push_back(testSound[SoundKillingSpree6E]);
					break;
				default:
					break;
				}
			}
		}
		if ((Player3_KillSpree > Player3_KillSpreeLast) && (Player3_KillSpree > 2)){
			SoundEventsIcon.push_back(PLAYER3);
			if (Player3_KillSpree > 8){
				Player3_KillSpree = 8;
			}
			Player3_KillSpreeLast = Player3_KillSpree;
			if (playerID == PLAYER3)
			{
				switch (Player3_KillSpree){
				case 3:
					SoundEventsString.push_back("Player 4 Killing Spree!");
					SoundEvents.push_back(testSound[SoundKillingSpreeU]);
					break;
				case 4:
					SoundEventsString.push_back("Player 4 Rampage!");
					SoundEvents.push_back(testSound[SoundKillingSpree2U]);
					break;
				case 5:
					SoundEventsString.push_back("Player 4 is Unstoppable!");
					SoundEvents.push_back(testSound[SoundKillingSpree3U]);
					break;
				case 6:
					SoundEvents.push_back(testSound[SoundKillingSpree4U]);
					SoundEventsString.push_back("Player 4 is Dominating!");
					break;
				case 7:
					SoundEvents.push_back(testSound[SoundKillingSpree5U]);
					SoundEventsString.push_back("Player 4 is God Like!");
					break;
				case 8:
					SoundEvents.push_back(testSound[SoundKillingSpree6U]);
					SoundEventsString.push_back("Player 4 is Legendary!");
					break;
				default:
					break;
				}
			}
			else if (playerID == PLAYER1){
				switch (Player3_KillSpree){
				case 3:
					SoundEventsString.push_back("Player 4 Killing Spree!");
					SoundEvents.push_back(testSound[SoundKillingSpreeY]);
					break;
				case 4:
					SoundEventsString.push_back("Player 4 Rampage!");
					SoundEvents.push_back(testSound[SoundKillingSpree2Y]);
					break;
				case 5:
					SoundEventsString.push_back("Player 4 is Unstoppable!");
					SoundEvents.push_back(testSound[SoundKillingSpree3Y]);
					break;
				case 6:
					SoundEventsString.push_back("Player 4 is Dominating!");
					SoundEvents.push_back(testSound[SoundKillingSpree4Y]);
					break;
				case 7:
					SoundEventsString.push_back("Player 4 is God Like!");
					SoundEvents.push_back(testSound[SoundKillingSpree5Y]);
					break;
				case 8:
					SoundEventsString.push_back("Player 4 is Legendary!");
					SoundEvents.push_back(testSound[SoundKillingSpree6Y]);
					break;
				default:
					break;
				}
			}
			else{
				switch (Player3_KillSpree){
				case 3:
					SoundEventsString.push_back("Player 4 Killing Spree!");
					SoundEvents.push_back(testSound[SoundKillingSpreeE]);
					break;
				case 4:
					SoundEventsString.push_back("Player 4 Rampage!");
					SoundEvents.push_back(testSound[SoundKillingSpree2E]);
					break;
				case 5:
					SoundEventsString.push_back("Player 4 is Unstoppable!");
					SoundEvents.push_back(testSound[SoundKillingSpree3E]);
					break;
				case 6:
					SoundEventsString.push_back("Player 4 is Dominating!");
					SoundEvents.push_back(testSound[SoundKillingSpree4E]);
					break;
				case 7:
					SoundEventsString.push_back("Player 4 is God Like!");
					SoundEvents.push_back(testSound[SoundKillingSpree5E]);
					break;
				case 8:
					SoundEventsString.push_back("Player 4 is Legendary!");
					SoundEvents.push_back(testSound[SoundKillingSpree6E]);
					break;
				default:
					break;
				}
			}
		}
		
		myGameMenu->setKills(0, Player0_KillCount);
		myGameMenu->setKills(1, Player1_KillCount);
		myGameMenu->setKills(2, Player2_KillCount);
		myGameMenu->setKills(3, Player3_KillCount);

		powerUp = parseOpts->getPPowerUp(recvVec, playerID);

		// TODO do something with power up status
		// check consts.h for int that corresponds to powerup
		if (parseOpts->getPPowerUp(recvVec, PLAYER0)){
			if (Player0_Powerup != parseOpts->getPPowerUp(recvVec, PLAYER0)){
				sound_3d_pick->setPosition(player0_sound_vec_lasterest);
				sound_3d_pick->Play3D(View);
				Player0_Powerup = parseOpts->getPPowerUp(recvVec, PLAYER0);
				powerUpAnimation(0);
			}
		}

		if (parseOpts->getPPowerUp(recvVec, PLAYER1)){
			if (Player1_Powerup != parseOpts->getPPowerUp(recvVec, PLAYER1)){
				sound_3d_pick->setPosition(player1_sound_vec_lasterest);
				sound_3d_pick->Play3D(View);
				Player1_Powerup = parseOpts->getPPowerUp(recvVec, PLAYER1);
				powerUpAnimation(1);
			}
		}

		if (parseOpts->getPPowerUp(recvVec, PLAYER2)){
			if (Player2_Powerup != parseOpts->getPPowerUp(recvVec, PLAYER2)){
				sound_3d_pick->setPosition(player2_sound_vec_lasterest);
				sound_3d_pick->Play3D(View);
				Player2_Powerup = parseOpts->getPPowerUp(recvVec, PLAYER2);
				powerUpAnimation(2);
			}
		}

		if (parseOpts->getPPowerUp(recvVec, PLAYER3)){
			if (Player3_Powerup != parseOpts->getPPowerUp(recvVec, PLAYER3)){
				sound_3d_pick->setPosition(player3_sound_vec_lasterest);
				sound_3d_pick->Play3D(View);
				Player3_Powerup = parseOpts->getPPowerUp(recvVec, PLAYER3);
				powerUpAnimation(3);
			}
		}

		//display players current power up
		myUI->setPowerUP(parseOpts->getPPowerUp(recvVec, playerID));

		// TODO bounces arrive
		if (parseOpts->getTramp(recvVec, PLAYER0)){
			sound_3d_tramp->setPosition(player0_sound_vec_lasterest);
			sound_3d_tramp->Play3D(View);
		}
		if (parseOpts->getTramp(recvVec, PLAYER1)){
			sound_3d_tramp->setPosition(player1_sound_vec_lasterest);
			sound_3d_tramp->Play3D(View);
		}
		if (parseOpts->getTramp(recvVec, PLAYER2)){
			sound_3d_tramp->setPosition(player2_sound_vec_lasterest);
			sound_3d_tramp->Play3D(View);
		}
		if (parseOpts->getTramp(recvVec, PLAYER3)){
			sound_3d_tramp->setPosition(player3_sound_vec_lasterest);
			sound_3d_tramp->Play3D(View);
		}
		// Teleporter sounds
		if (parseOpts->getTele(recvVec, PLAYER0))
		{
			sound_3d_tele->setPosition(player0_sound_vec_lasterest);
			sound_3d_tele->Play3D(View);
		}
		if (parseOpts->getTele(recvVec, PLAYER1))
		{
			sound_3d_tele->setPosition(player1_sound_vec_lasterest);
			sound_3d_tele->Play3D(View);
		}
		if (parseOpts->getTele(recvVec, PLAYER2))
		{
			sound_3d_tele->setPosition(player2_sound_vec_lasterest);
			sound_3d_tele->Play3D(View);
		}
		if (parseOpts->getTele(recvVec, PLAYER3))
		{
			sound_3d_tele->setPosition(player3_sound_vec_lasterest);
			sound_3d_tele->Play3D(View);
		}

		//cout << player_list[playerID]->getAABB().min[0] << " " << player_list[playerID]->getAABB().min[1] << " " << player_list[playerID]->getAABB().min[2] << " " << endl;

		tower_list[0]->setModelM((*recvVec)[TOWER_MAT_BEGIN + 0].second);
		tower_list[1]->setModelM((*recvVec)[TOWER_MAT_BEGIN + 1].second);
		tower_list[2]->setModelM((*recvVec)[TOWER_MAT_BEGIN + 2].second);
		tower_list[3]->setModelM((*recvVec)[TOWER_MAT_BEGIN + 3].second);
		tower_list[4]->setModelM((*recvVec)[TOWER_MAT_BEGIN + 4].second);
		tower_list[5]->setModelM((*recvVec)[TOWER_MAT_BEGIN + 5].second);

		elevator_list[0]->setModelM((*recvVec)[PLAT_MAT_BEGIN].second);
		elevator_list[1]->setModelM((*recvVec)[PLAT_MAT_BEGIN+1].second);
		elevator_list[2]->setModelM((*recvVec)[PLAT_MAT_BEGIN+2].second);
		elevator_list[3]->setModelM((*recvVec)[PLAT_MAT_BEGIN+3].second);
		elevator_list[4]->setModelM((*recvVec)[PLAT_MAT_BEGIN+4].second);


		// TODO make this happen based on remaining towers
		if (baseOpen)
		{
			for (uint i = 0; i < stationary_list.size(); i++)
			{
				if (strcmp(stationary_list[i]->getName().c_str(), "baset0") == 0)
				((Cube*)stationary_list[i])->setTransparency(0.5);
			}
		}

		for (int i = 0; i < 4; i++){
			if (i!=playerID)
				cam[i]->setCamM((*recvVec)[CAM_MAT_BEGIN + i].second);
		}
		
		//i++;

		if (p0f && (playerID != PLAYER0)){
			sound_3d_Throw->setPosition(player0_sound_vec_curr);
			sound_3d_Throw->Play3D(View);
		}
		if (p1f && (playerID != PLAYER1)){
			sound_3d_Throw->setPosition(player0_sound_vec_curr);
			sound_3d_Throw->Play3D(View);
		}
		if (p2f && (playerID != PLAYER2)){
			sound_3d_Throw->setPosition(player0_sound_vec_curr);
			sound_3d_Throw->Play3D(View);
		}
		if (p3f && (playerID != PLAYER3)){
			sound_3d_Throw->setPosition(player0_sound_vec_curr);
			sound_3d_Throw->Play3D(View);
		}

		std::fill_n(bVis, 6, true);
		int pUpState = parseOpts->getPUpState(recvVec);
		//std::cout << pUpState << std::endl;
		if (pUpState & 1)
			bVis[SPEEDUP] = false;
		if (pUpState & 1 << 1)
			bVis[DOUBLEDAMAGE] = false;
		if (pUpState & 1 << 2)
			bVis[HEALTHBOOST] = false;
		if (pUpState & 1 << 3)
			bVis[FASTERSHOOT] = false;
		if (pUpState & 1 << 4)
			bVis[FARTHERSHOOT] = false;

		//cout << bVis[FASTERSHOOT] << " " << bVis[FARTHERSHOOT] << (pUpState & 1 << 4) << endl;

		winner = parseOpts->getWinState(recvVec);
		if (playerReady)
		{
			//if (!winCountToggle)
				gameOver = (winner == 3) ? 0 : 1;
		}
		
		if (gameOver)
		{
			myClientState->setState(5);
			keyState = 0;
			playerReady = false;
			QueryPerformanceCounter(&time_track);
			double time = (double)time_track.QuadPart / (double)freq.QuadPart;
			player_list[playerID]->unsetAnimLoop(1, time);
		}
		//cout << (*recvVec)[PLATFORM_STATUS].first  <<  " " << playerReady << " " << gameOver << endl;
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
  //glutAttachMenu(GLUT_MIDDLE_BUTTON);

  int screen_width = glutGet(GLUT_WINDOW_WIDTH);
  int screen_height = glutGet(GLUT_WINDOW_HEIGHT);
  Window::width = screen_width;
  Window::height = screen_height;

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
  posTestSound->setMinDistance(10.0f);
  posTestSound->setMaxDistance(10000.0f);

  sound_3d_Throw = new Sound(mySoundSystem, "Sound/throw.mp3", true);
  sound_3d_Throw->setVolume(0.75);
  sound_3d_Throw->setPosition(pt);
  sound_3d_Throw->setVelocity(vt);
  sound_3d_Throw->setMinDistance(10.0f);
  sound_3d_Throw->setMaxDistance(10000.0f);  

  sound_3d_hit = new Sound(mySoundSystem, "Sound/blast.mp3", true);
  sound_3d_hit->setVolume(0.5);
  sound_3d_hit->setPosition(pt);
  sound_3d_hit->setVelocity(vt);
  sound_3d_hit->setMinDistance(5.0f);
  sound_3d_hit->setMaxDistance(10000.0f);

  sound_3d_light = new Sound(mySoundSystem, "Sound/blast3.mp3", true);
  sound_3d_light->setVolume(0.75);
  sound_3d_light->setPosition(pt);
  sound_3d_light->setVelocity(vt);
  sound_3d_light->setMinDistance(10.0f);
  sound_3d_light->setMaxDistance(10000.0f);

  sound_3d_death = new Sound(mySoundSystem, "Sound/death.mp3", true);
  sound_3d_death->setVolume(0.75);
  sound_3d_death->setPosition(pt);
  sound_3d_death->setVelocity(vt);
  sound_3d_death->setMinDistance(10.0f);
  sound_3d_death->setMaxDistance(10000.0f);

  sound_3d_death2 = new Sound(mySoundSystem, "Sound/blast2.mp3", true);
  sound_3d_death2->setVolume(0.5);
  sound_3d_death2->setPosition(pt);
  sound_3d_death2->setVelocity(vt);
  sound_3d_death2->setMinDistance(5.0f);
  sound_3d_death2->setMaxDistance(10000.0f);

  sound_3d_tramp = new Sound(mySoundSystem, "Sound/tramp.mp3", true);
  sound_3d_tramp->setVolume(0.75);
  sound_3d_tramp->setPosition(pt);
  sound_3d_tramp->setVelocity(vt);
  sound_3d_tramp->setMinDistance(10.0f);
  sound_3d_tramp->setMaxDistance(10000.0f);

  sound_3d_tele = new Sound(mySoundSystem, "Sound/fire.mp3", true);
  sound_3d_tele->setVolume(0.75);
  sound_3d_tele->setPosition(pt);
  sound_3d_tele->setVelocity(vt);
  sound_3d_tele->setMinDistance(10.0f);
  sound_3d_tele->setMaxDistance(10000.0f);
  
  sound_3d_pick = new Sound(mySoundSystem, "Sound/pickup.mp3", true);
  sound_3d_pick->setVolume(0.75);
  sound_3d_pick->setPosition(pt);
  sound_3d_pick->setVelocity(vt);
  sound_3d_pick->setMinDistance(10.0f);
  sound_3d_pick->setMaxDistance(10000.0f);

  posTestMusic = new Music(mySoundSystem, "Sound/prepunch1.ogg", true);
  posTestMusic->setLoopCount(-1);
  posTestMusic->setVolume(0.75);
  posTestMusic->setPosition(pt);
  posTestMusic->setVelocity(vt);
  posTestMusic->setMinDistance(5.0f);
  posTestMusic->setMaxDistance(10000.0f);

  sound_3d_tower_shoot = new Sound(mySoundSystem, "Sound/tower_shoot.mp3", true);
  sound_3d_tower_shoot->setVolume(0.5);
  sound_3d_tower_shoot->setPosition(pt);
  sound_3d_tower_shoot->setVelocity(vt);
  sound_3d_tower_shoot->setMinDistance(5.0f);
  sound_3d_tower_shoot->setMaxDistance(10000.0f);

  sound_3d_tower_explosion = new Sound(mySoundSystem, "Sound/tower_explosion.wav", true);
  sound_3d_tower_explosion->setVolume(0.75);
  sound_3d_tower_explosion->setPosition(pt);
  sound_3d_tower_explosion->setVelocity(vt);
  sound_3d_tower_explosion->setMinDistance(5.0f);
  sound_3d_tower_explosion->setMaxDistance(10000.0f);

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

	  //Loop check functions for music
	  PlayThunderSound(diff);
	  PlayBackgroundMusic(diff);
	  PlayAnnouncerEvents(diff);


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

void keyboard(unsigned char key, int, int){
	QueryPerformanceCounter(&time_track);
	double time = (double)time_track.QuadPart / (double)freq.QuadPart;
	
	//if (gameOver)
		//myClientState->setState(5);
	

	switch (myClientState->getState()){
	case 0:
		if (key == ' '){
			if (space_up){
				//testSound[SoundVegeta]->Play();
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
		//	cout << posTestSound->getVolume() << "," << posTestSound->getMinDistance() << "," << posTestSound->getMaxDistance() << endl;

		//	posTestSound->Play3D(View);
		//	cout << "Playing Sound!" << endl;
			SoundEvents.push_back(testSound[SoundDoubleKillY]);
			cout << "Adding a sound man!" << endl;
		}
		
		if (key == 'o'){
			//testSound[10]->Play();
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

				testSound[SoundJumpOgg]->Play();
			}
		}

		//Added for sound debugging
		if (key == 'f'){
			//testSound[SoundVegeta]->Play();
			myDeathScreen->setDeathClock(clock());
			myClientState->setState(3);
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

		if (key == 9)
		{
			kill_count = true;
		}

		if (key == 'p') //test for end screen
		{
			myClientState->setState(5);
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

		if (key == '1'){
			light->diffuse += vec3(0.1, 0.1, 0.1);
			cout << "diffuse: " << light->diffuse[0] << endl;
			cout << "ambient: " << light->ambient[0] << endl;
			cout << "specular: " << light->specular[0] << endl;
		}
		if (key == '2'){
			light->diffuse -= vec3(0.1, 0.1, 0.1);
			cout << "diffuse: " << light->diffuse[0] << endl;
			cout << "ambient: " << light->ambient[0] << endl;
			cout << "specular: " << light->specular[0] << endl;
		}
		if (key == '3'){
			light->ambient += vec3(0.1, 0.1, 0.1);
			cout << "diffuse: " << light->diffuse[0] << endl;
			cout << "ambient: " << light->ambient[0] << endl;
			cout << "specular: " << light->specular[0] << endl;
		}
		if (key == '4'){
			light->ambient -= vec3(0.1, 0.1, 0.1);
			cout << "diffuse: " << light->diffuse[0] << endl;
			cout << "ambient: " << light->ambient[0] << endl;
			cout << "specular: " << light->specular[0] << endl;
		}
		if (key == '5'){
			light->specular += vec3(0.1, 0.1, 0.1);
			cout << "diffuse: " << light->diffuse[0] << endl;
			cout << "ambient: " << light->ambient[0] << endl;
			cout << "specular: " << light->specular[0] << endl;
		}
		if (key == '6'){
			light->specular -= vec3(0.1, 0.1, 0.1);
			cout << "diffuse: " << light->diffuse[0] << endl;
			cout << "ambient: " << light->ambient[0] << endl;
			cout << "specular: " << light->specular[0] << endl;
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
			running = false;
			exit(0);
			myClientState->setState(1);
		}
		break;
	case 4:
		if (key == 27){
			myClientState->setState(0);
		}
		break;
	case 5:

		if (key == 27){
			//running = false;
			myUI->resetTowerKills();
			myClientState->setState(1);
			playerReady = true;
			winCountToggle = false;
		}
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
				//	testSound[SoundJumpOgg]->Play(FMOD_CHANNEL_FREE, 0, &channel);
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
		if (key == '9'){
			baseOpen = true;
		}

		if (key == 9)
		{
			kill_count = false;
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
	case 5:
		break;
	default:
		break;
	}
}
void mouseFunc(int button, int state, int x, int y)
{
	QueryPerformanceCounter(&time_track);
	double time = (double)time_track.QuadPart / (double)freq.QuadPart;
//	if (gameOver)
//		return;

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
				testSound[SoundMenuClick]->Play();
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
					
					//Player cam mats
					recvVec->push_back(std::make_pair("initRecvPos_c", mat4(0.0f)));
					recvVec->push_back(std::make_pair("initRecvPos_c", mat4(0.0f)));
					recvVec->push_back(std::make_pair("initRecvPos_c", mat4(0.0f)));
					recvVec->push_back(std::make_pair("initRecvPos_c", mat4(0.0f)));
					
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
						initializePlayerMark(playerID);
						myUI->teamColor(playerID);
						std::cout << "pid: " << playerID << std::endl;
						//system("pause");
					}
					catch (std::exception& e)
					{
						sprintf_s(buf, "%s", "Error connecting to server!");
						std::cerr << e.what() << std::endl;
					}

					for (int i = 0; i < 4; i++){
						cam[i] = new Camera();
						cam[i]->attach(player_list[i]);
						//cam->postTrans(glm::translate(vec3(0, 2.5, 6)));
						cam[i]->init(1.0, 1.5, 6, 1.0);
					}

					connected = true;
				}
				menuMusic->Stop();
			//	gameMusic->setFade(0.75, 0.005);
				gameMusic->Play();
				//gameThunder->Play();
				server_update(0);
			}
			else if (click == 2){
				testSound[SoundMenuClick]->Play();
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

					testSound[SoundSlap]->Play();
					///scene->basicAttack(playerID);

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
					testSound[SoundThrow]->Play();
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

				//	testSound[SoundPrePunch]->Play();
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
				testSound[SoundMenuClick]->Play();
				myClientState->setState(1);
			}
			if (click == 2){
				testSound[SoundMenuClick]->Play();
				myClientState->setState(0);
				gameMusic->Stop();
				//gameThunder->Stop();
				menuMusic->setFade(0.5, 0.005);
				menuMusic->Play();
			}
		}
		break;
	case 3:
		if (state == GLUT_DOWN){
			newX = (float)x / Window::width;
			newY = (float)y / Window::height;
			cout << "CLICK!" << newX << "," << newY << endl;
			int click = myDeathScreen->checkClick(newX, newY);
			if (click == 1){
				myClientState->setState(1);
			}
		}
		break;
	case 4:
		break;
	case 5:
		if (state == GLUT_DOWN){
			newX = (float)x / Window::width;
			newY = (float)y / Window::height;
			cout << "CLICK!" << newX << "," << newY << endl;
			int click = endScreen->checkClick(newX, newY);
			if (click == 1){
				//running = false;
				myClientState->setState(1);
				playerReady = true;
				winCountToggle = false;
				myUI->resetTowerKills();
			}
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
		int sound;
		sound = myMainMenu->checkHighlight(newX, newY);
		if (sound){
			if (!inMenuBox){
				testSound[SoundMenuHover]->Play();
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
			cam[playerID]->pushRot(cam_sp*dy);
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
				testSound[SoundMenuHover]->Play();
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
		int sound3;
		sound3 = myDeathScreen->checkHighlight(newX, newY);
		if (sound3){
			if (!inMenuBox){
				testSound[SoundMenuHover]->Play();
			}
			inMenuBox = true;
		}
		else{
			inMenuBox = false;
		}
		break;
	case 4:
		break;
	case 5:
		newX = (float)x / Window::width;
		newY = (float)y / Window::height;
		endScreen->checkHighlight(newX, newY);
		int sound5;
		sound5 = endScreen->checkHighlight(newX, newY);
		if (sound5){
			if (!inMenuBox){
				testSound[SoundMenuHover]->Play();
			}
			inMenuBox = true;
		}
		else{
			inMenuBox = false;
		}
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
			//	testSound[SoundJumpOgg1]->Play(FMOD_CHANNEL_FREE, 0, &channel);
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

	//Window::width = glutGet(GLUT_WINDOW_WIDTH);
	//Window::height = glutGet(GLUT_WINDOW_HEIGHT);

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

	//render buffer initialization
	glGenFramebuffers(1, &render_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, render_fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, render_tex->getTexID(), 0);
	GLuint depthBuf;
	glGenRenderbuffers(1, &depthBuf);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuf);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, Window::width, Window::height );
	// Bind the depth buffer to the FBO
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuf);
	// Set the target for the fragment shader outputs
	GLenum drawBufs[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, drawBufs);
	// Unbind the framebuffer, and revert to default framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	light[0].type=1;
	light[0].pos = vec4(0,200,0,1);
	light[0].specular = vec3(0.2,0.2,0.2);//0.1,0.1,0.1
	light[0].diffuse = vec3(1.1, 1.1, 1.1);//0.9, 0.9, 0.9
	light[0].ambient = vec3(0.45, 0.45, 0.45);//0.35, 0.35, 0.35
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
	myDeathScreen->setupSound(testSound[SoundCount]);
	settings = new Settings();
	endScreen = new End_Screen();
	logo = new Logo();

	screen_quad = new Quad();
	screen_quad->setShader(sdrCtl.getShader("screen_texture"));
	screen_quad->setTextureUnit(render_tex_id);

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

	lightning_generator.setDt(0.1f);//lightning generation per 0.1 seconds
	lightning_generator.setSize(400);//size of the map

	initializeMOM();

	LARGE_INTEGER ct;
	QueryPerformanceCounter(&ct);

	//ParticleAnimated* p_anim = new ParticleAnimated(*MOM.mother_of_p_anim);
	//p_anim->Init("img/sprite_sheets/light_003.png", "PNG");
	//p_anim->setShader(sdrCtl.getShader("billboard_anim"));
	//p_anim->setModelM(glm::translate(vec3(0, 7, 0)));
	//p_anim->setPosition(vec3(0.0f, 0.0f, 0.0f));
	//p_anim->setNumColumn(5);
	//p_anim->setNumRow(6);
	//p_anim->setValidFrame(0, 9);
	////p_anim->setReverse(true);
	//p_anim->setDuration(1);
	//p_anim->setFog(fog);
	//p_anim->Bind();
	//p_anim->setType(1);
	//p_anim->setWidth(2);
	//p_anim->setHeight(2);
	//p_anim->setDuration(1.0);
	//p_anim->setTransparency(1.0);
	////p_anim->setSampleCount(3, 3);
	////p_anim->setSampleDist(0.001, 0.005);
	//LARGE_INTEGER time_p_anim;
	//QueryPerformanceCounter(&time_p_anim);
	//p_anim->setStartTime(time_p_anim);
	//panim_list.push_back(p_anim);

	AnimController monkeyAnimController;
	monkeyAnimController.add(20 / 24.0, 5 / 24.0);//stand
	monkeyAnimController.add(0 / 24.0, 16 / 24.0,2);//walk
	monkeyAnimController.add(25 / 24.0, 10 / 24.0,2);//jump
	monkeyAnimController.add(40 / 24.0, 20 / 24.0,2);//attack
	monkeyAnimController.setDefault(0);//stand is the default animation
	AnimController gorillaAnimController;
	gorillaAnimController.add(0 / 24.0, 5 / 24.0);//stand
	gorillaAnimController.add(26 / 24.0, 24 / 24.0, 2);//walk
	gorillaAnimController.add(55 / 24.0, 25 / 24.0, 2);//jump
	gorillaAnimController.add(82 / 24.0, 17 / 24.0, 2);//attack
	gorillaAnimController.setDefault(0);//stand is the default animation
	AnimController chipmonkOculusAnimController;
	chipmonkOculusAnimController.add(0 / 24.0, 5 / 24.0);//stand
	chipmonkOculusAnimController.add(10 / 24.0, 20 / 24.0,2);//walk
	chipmonkOculusAnimController.add(35 / 24.0, 10 / 24.0);//jump
	chipmonkOculusAnimController.add(50 / 24.0, 15 / 24.0,2);//attack
	chipmonkOculusAnimController.setDefault(0);//stand is the default animation
	AnimController chipmonk2AnimController;
	chipmonk2AnimController.add(0 / 24.0, 5 / 24.0);//stand
	chipmonk2AnimController.add((float)(11 / 24.0), (float)(19 / 24.0), 1.2f);//walk
	chipmonk2AnimController.add(36 / 24.0, 9 / 24.0);//jump
	chipmonk2AnimController.add(52 / 24.0, 10 / 24.0,2);//attack
	chipmonk2AnimController.setDefault(0);//stand is the default animation

	Mesh* player0 = new Mesh();
	player0->LoadMesh("Model/2chipmunk_7_animated_6.dae");
	player0->setAnimController(chipmonk2AnimController);
	player0->setShader(sdrCtl.getShader("basic_model"));
	player0->setShadowTex(shadow_map_id);
	player0->setAdjustM(glm::translate(vec3(0.0, 0.95, 0.0))*glm::rotate(mat4(1.0), 180.0f, vec3(0, 1.0, 0))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0))*glm::scale(vec3(0.15, 0.15, 0.15)));
	player0->setShininess(30);
	player0->setFog(fog);
	player_list.push_back(player0);

	Mesh* player1 = new Mesh();
	player1->LoadMesh("Model/BlueGorilla_animation_9.dae");
	player1->setAnimController(gorillaAnimController);
	player1->setShader(sdrCtl.getShader("basic_model"));
	player1->setShadowTex(shadow_map_id);
	player1->setAdjustM(glm::translate(vec3(0.0, 1.05, 0.0))*glm::rotate(mat4(1.0), 180.0f, vec3(0, 1.0, 0))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0))*glm::scale(vec3(0.07, 0.07, 0.07)));
	player1->setShininess(30);
	player1->setFog(fog);
	player_list.push_back(player1);

	Mesh* player2 = new Mesh();
	player2->LoadMesh("Model/chipmunkOculus_animated_all3.dae");
	player2->setAnimController(chipmonkOculusAnimController);
	player2->setShader(sdrCtl.getShader("basic_model"));
	player2->setShadowTex(shadow_map_id);
	player2->setAdjustM(glm::translate(vec3(0.0, 1.05, 0.0))*glm::rotate(mat4(1.0), 180.0f, vec3(0, 1.0, 0))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0))*glm::scale(vec3(0.15, 0.15, 0.15)));
	player2->setShininess(30);
	player2->setFog(fog);
	player_list.push_back(player2);

	Mesh* player3 = new Mesh();
	player3->LoadMesh("Model/monky2014_delete2.dae");
	player3->setAnimController(monkeyAnimController);
	player3->setShader(sdrCtl.getShader("basic_model"));
	player3->setShadowTex(shadow_map_id);
	player3->setAdjustM(glm::translate(vec3(0.0, 1.35, 0.0))*glm::rotate(mat4(1.0), 180.0f, vec3(0, 1.0, 0))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0))*glm::scale(vec3(0.07, 0.07, 0.07)));
	player3->setShininess(30);
	player3->setFog(fog);
	player_list.push_back(player3);

	Mesh* tower0 = new Mesh();
	tower0->LoadMesh("Model/2Tower_6_bone.dae",false);
	tower0->setShader(sdrCtl.getShader("basic_model"));
	tower0->setShadowTex(shadow_map_id);
	tower0->setAdjustM(glm::translate(vec3(0.0, 1.0, 0.0))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0))*glm::scale(vec3(1.0, 1.0, 1.0)));
	tower0->setModelM(glm::translate(vec3(-30.0,0.0,-30.0)));
	tower0->setShininess(30);
	tower0->setFog(fog);
	tower_list.push_back(tower0);

	//tower mark effect
	ParticleAnimated* mark_tower0 = new ParticleAnimated(*(MOM.mother_of_orange_mark));
	mark_tower0->setFollow(tower0, vec3(0, 1.2, 0), 0.0f, &View);
	mark_tower0->setStartTime(ct);
	panim_list.push_back(mark_tower0);

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

	//tower mark effect
	ParticleAnimated* mark_tower1 = new ParticleAnimated(*(MOM.mother_of_orange_mark));
	mark_tower1->setFollow(tower1, vec3(0, 1.2, 0), 0.0f, &View);
	mark_tower1->setStartTime(ct);
	panim_list.push_back(mark_tower1);

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

	t4_ps_01 = new ParticleSystem2((float)1.0, (float)0.25, (float)0.25, (float)4.0, (float)0.5, (float)0.0, (float)360.0, (float)0.0, (float)360.0, (float)0.0);
	t4_ps_01->setShader(sdrCtl.getShader("pe_torus"));
	t4_ps_01->setType("Particle_System");
	t4_ps_01->setName("Particle_Test");
	t4_ps_01->setLoopInf(true);
	t4_ps_01->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG");
	t4_ps_01->setFog(fog);
	t4_ps_01->setBlastRadius(1.0f);// Blast radius
	t4_ps_01->setExplosionVelocity(0.5f);// Explosion velocity
	t4_ps_01->setExplosionDecay(10.0f);// Explosion decay
	t4_ps_01->setFragStartSize(12.0f);// Fragment start size
	t4_ps_01->setFragEndSize(1.0f);// Fragment end size
	t4_ps_01->setFragStartColor(vec3(0.0, 0.5, 1.0));// Fragment start color
	t4_ps_01->setFragEndColor(vec3(0.0, 0.125, 0.25));// Fragment end color
	t4_ps_01->setTime_Step(0.1f);
	t4_ps_01->setTime_Max(100.0);
	t4_ps_01->setTime_Min(0.0);
	t4_ps_01->setTime(0.0);
	//t4_ps_01->setEmitterPosition();// Emitter position
	t4_ps_01->setModelM(glm::translate(vec3(28.0, 6.5f, -30.0))*glm::rotate(mat4(1.0), 90.0f, vec3(0.0, 1.0, 0.0)));

	t4_ps_02 = new ParticleSystem2((float)1.0, (float)0.25, (float)0.25, (float)4.0, (float)0.5, (float)0.0, (float)360.0, (float)0.0, (float)360.0, (float)0.0);
	t4_ps_02->setShader(sdrCtl.getShader("pe_torus"));
	t4_ps_02->setType("Particle_System");
	t4_ps_02->setName("Particle_Test");
	t4_ps_02->setLoopInf(true);
	t4_ps_02->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG");
	t4_ps_02->setFog(fog);
	t4_ps_02->setBlastRadius(1.0f);// Blast radius
	t4_ps_02->setExplosionVelocity(0.5f);// Explosion velocity
	t4_ps_02->setExplosionDecay(10.0f);// Explosion decay
	t4_ps_02->setFragStartSize(12.0f);// Fragment start size
	t4_ps_02->setFragEndSize(1.0f);// Fragment end size
	t4_ps_02->setFragStartColor(vec3(0.0, 0.5, 1.0));// Fragment start color
	t4_ps_02->setFragEndColor(vec3(0.0, 0.125, 0.25));// Fragment end color
	t4_ps_02->setTime_Step(0.1f);
	t4_ps_02->setTime_Max(100.0);
	t4_ps_02->setTime_Min(0.0);
	t4_ps_02->setTime(33.0);
	//t4_ps_02->setEmitterPosition();// Emitter position
	t4_ps_02->setModelM(glm::translate(vec3(30.5, 6.5f, -28)));

	t4_ps_03 = new ParticleSystem2((float)1.0, (float)0.25, (float)0.25, (float)4.0, (float)0.5, (float)0.0, (float)360.0, (float)0.0, (float)360.0, (float)0.0);
	t4_ps_03->setShader(sdrCtl.getShader("pe_torus"));
	t4_ps_03->setType("Particle_System");
	t4_ps_03->setName("Particle_Test");
	t4_ps_03->setLoopInf(true);
	t4_ps_03->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG");
	t4_ps_03->setFog(fog);
	t4_ps_03->setBlastRadius(1.0f);// Blast radius
	t4_ps_03->setExplosionVelocity(0.5f);// Explosion velocity
	t4_ps_03->setExplosionDecay(10.0f);// Explosion decay
	t4_ps_03->setFragStartSize(12.0f);// Fragment start size
	t4_ps_03->setFragEndSize(1.0f);// Fragment end size
	t4_ps_03->setFragStartColor(vec3(0.0, 0.5, 1.0));// Fragment start color
	t4_ps_03->setFragEndColor(vec3(0.0, 0.125, 0.25));// Fragment end color
	t4_ps_03->setTime_Step(0.1f);
	t4_ps_03->setTime_Max(100.0);
	t4_ps_03->setTime_Min(0.0);
	t4_ps_03->setTime(66.0);
	//t4_ps_03->setEmitterPosition();// Emitter position
	t4_ps_03->setModelM(glm::translate(vec3(31.5, 6.5f, -31.5)));

	Mesh* tower2 = new Mesh();
	tower2->LoadMesh("Model/OctopusTower1_10_bone2.dae", false);
	tower2->setShader(sdrCtl.getShader("basic_model"));
	tower2->setShadowTex(shadow_map_id);
	tower2->setAdjustM(glm::translate(vec3(0.0, 3.7, 0.0))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0))*glm::scale(vec3(0.6, 0.6, 0.6)));
	tower2->setModelM(glm::translate(vec3(30.0, 2.5, 30.0)));
	tower2->setShininess(30);
	tower2->setFog(fog);
	tower_list.push_back(tower2);

	//tower mark effect
	ParticleAnimated* mark_tower2 = new ParticleAnimated(*(MOM.mother_of_blue_mark));
	mark_tower2->setFollow(tower2, vec3(0, 1.2, 0), 0.0f, &View);
	mark_tower2->setStartTime(ct);
	panim_list.push_back(mark_tower2);

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

	//tower mark effect
	ParticleAnimated* mark_tower3 = new ParticleAnimated(*(MOM.mother_of_blue_mark));
	mark_tower3->setFollow(tower3, vec3(0, 1.2, 0), 0.0f, &View);
	mark_tower3->setStartTime(ct);
	panim_list.push_back(mark_tower3);

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

	t5_ps_01 = new ParticleSystem(GL_POINTS);
	t5_ps_01->setShader(sdrCtl.getShader("halo"));
	t5_ps_01->setType("Particle_System");
	t5_ps_01->setName("Particle_Test");
	t5_ps_01->setK(1.0f);
	t5_ps_01->setColor(vec3(1.0, 1.0, 1.0));
	t5_ps_01->setShade(vec3(1.0, 1.0, 1.0));
	t5_ps_01->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG");
	t5_ps_01->setFog(fog);
	t5_ps_01->setTime_Step(0.25);
	t5_ps_01->setTime_Max(53.0);
	t5_ps_01->setTime_Min(5.0);
	t5_ps_01->setTime((float)5.0);
	t5_ps_01->setLoopInf(true);
	t5_ps_01->setModelM(glm::translate(vec3(-30.0f, 7.3f, 30.0f))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0)));

	t5_ps_02 = new ParticleSystem(GL_POINTS);
	t5_ps_02->setShader(sdrCtl.getShader("halo"));
	t5_ps_02->setType("Particle_System");
	t5_ps_02->setName("Particle_Test");
	t5_ps_02->setK(1.0f);
	t5_ps_02->setColor(vec3(1.0, 1.0, 1.0));
	t5_ps_02->setShade(vec3(1.0, 1.0, 1.0));
	t5_ps_02->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG");
	t5_ps_02->setFog(fog);
	t5_ps_02->setTime_Step(0.25);
	t5_ps_02->setTime_Max(53.0);
	t5_ps_02->setTime_Min(5.0);
	t5_ps_02->setTime((float)21.0);
	t5_ps_02->setLoopInf(true);
	t5_ps_02->setModelM(glm::translate(vec3(-30.0f, 7.3f, 30.0f))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0)));

	t5_ps_03 = new ParticleSystem(GL_POINTS);
	t5_ps_03->setShader(sdrCtl.getShader("halo"));
	t5_ps_03->setType("Particle_System");
	t5_ps_03->setName("Particle_Test");
	t5_ps_03->setK(1.0f);
	t5_ps_03->setColor(vec3(1.0, 1.0, 1.0));
	t5_ps_03->setShade(vec3(1.0, 1.0, 1.0));
	t5_ps_03->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG");
	t5_ps_03->setFog(fog);
	t5_ps_03->setTime_Step(0.25);
	t5_ps_03->setTime_Max(53.0);
	t5_ps_03->setTime_Min(5.0);
	t5_ps_03->setTime((float)37.0);
	t5_ps_03->setLoopInf(true);
	t5_ps_03->setModelM(glm::translate(vec3(-30.0f, 7.3f, 30.0f))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0)));

	//elevator 
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
	platform_01->postTrans(glm::translate(vec3(0, 5.0, 0)));
	//platform_01->setAABB(AABB(vec3(-10.0, -0.5, -10.0), vec3(10.0, 0.5, 10.0))); 
	platform_01->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_01->setShadowTex(shadow_map_id);
	platform_01->setType("Cube");
	platform_01->setName("Test Platform");
	platform_01->setAliveModelM(platform_01->getModelM());
	stationary_list.push_back(platform_01);
	elevator_list.push_back(platform_01);

	//island 
	Cube* platform_02 = new Cube(-20, 20, -0.5, 0.5, -20, 20);
	//platform_01->setSpeed(5); 
	platform_02->setKd(vec3(0.8, 0.0, 0.8));
	platform_02->setKa(vec3(0.0, 0.0, 0.3));
	platform_02->setKs(vec3(0.0, 0.0, 0.4));
	platform_02->setShininess(100);
	platform_02->setFog(fog);
	platform_02->setReflectFactor(vec2(0.2, 0.5));
	platform_02->setEta(0.5);
	platform_02->setCubeMapUnit(3);
	platform_02->setSpeed(5);
	platform_02->postTrans(glm::translate(vec3(30, 14, 0)));
	//platform_02->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_02->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_02->setShadowTex(shadow_map_id);
	platform_02->setType("Cube");
	platform_02->setName("Test Platform");
	platform_02->setAliveModelM(platform_02->getModelM());
	stationary_list.push_back(platform_02);

	//island 
	Cube* platform_03 = new Cube(-20, 20, -0.5, 0.5, -20, 20);
	//platform_01->setSpeed(5); 
	platform_03->setKd(vec3(0.8, 0.0, 0.8));
	platform_03->setKa(vec3(0.0, 0.0, 0.4));
	platform_03->setKs(vec3(0.0, 0.0, 0.4));
	platform_03->setShininess(100);
	platform_03->setFog(fog);
	platform_03->setReflectFactor(vec2(0.2, 0.5));
	platform_03->setEta(0.5);
	platform_03->setCubeMapUnit(3);
	platform_03->setSpeed(5);
	platform_03->postTrans(glm::translate(vec3(-30, 14, 0)));
	//platform_03->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_03->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_03->setShadowTex(shadow_map_id);
	platform_03->setType("Cube");
	platform_03->setName("Test Platform");
	platform_03->setAliveModelM(platform_03->getModelM());
	stationary_list.push_back(platform_03);

	//walkway 
	Cube* platform_04 = new Cube(-10.0, 10.0, -0.5, 0.5, -10, 42);
	//platform_01->setSpeed(5); 
	platform_04->setKd(vec3(0.8, 0.0, 0.8));
	platform_04->setKa(vec3(0.0, 0.0, 0.4));
	platform_04->setKs(vec3(0.0, 0.0, 0.4));
	platform_04->setShininess(100);
	platform_04->setFog(fog);
	platform_04->setReflectFactor(vec2(0.2, 0.5));
	platform_04->setEta(0.5);
	platform_04->setCubeMapUnit(3);
	platform_04->setSpeed(5);
	platform_04->postTrans(glm::translate(vec3(0.0, 14.0, 20.0)));
	platform_04->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_04->setShadowTex(shadow_map_id);
	platform_04->setType("Cube");
	platform_04->setName("Test Platform");
	platform_04->setAliveModelM(platform_04->getModelM());
	stationary_list.push_back(platform_04);

	//barricade on walkway 
	/*Cube* platform_05 = new Cube(-5, 5, -5, 5, -.5, .5);
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
	platform_05->postTrans(glm::translate(vec3(0.0, 18.0, 40.0)));
	//platform_05->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_05->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_05->setShadowTex(shadow_map_id);
	platform_05->setType("Cube");
	platform_05->setName("Test Platform");
	platform_05->setAliveModelM(platform_05->getModelM());
	stationary_list.push_back(platform_05);*/

	//walkway 
	Cube* platform_07 = new Cube(-10.0, 10.0, -0.5, 0.5, -42, 10);
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
	platform_07->postTrans(glm::translate(vec3(0.0, 14.0, -20.0)));
	//platform_07->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_07->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_07->setShadowTex(shadow_map_id);
	platform_07->setType("Cube");
	platform_07->setName("Test Platform");
	platform_07->setAliveModelM(platform_07->getModelM());
	stationary_list.push_back(platform_07);

	/*//barricade on walkway 
	Cube* platform_08 = new Cube(-5, 5, -5, 5, -.5, .5);
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
	platform_08->postTrans(glm::translate(vec3(0.0, 18.0, -40.0)));
	//platform_08->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_08->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_08->setShadowTex(shadow_map_id);
	platform_08->setType("Cube");
	platform_08->setName("Test Platform");
	platform_08->setAliveModelM(platform_08->getModelM());
	stationary_list.push_back(platform_08);*/

	//tower island
	Cube* platform_09 = new Cube(-10, 10, -0.5, 0.5, -10, 10);
	//platform_09->setSpeed(5); 
	platform_09->setKd(vec3(0.8, 0.8, 0.8));
	platform_09->setKa(vec3(0.3, 0.3, 0.0));
	platform_09->setKs(vec3(0.4, 0.4, 0.0));
	platform_09->setShininess(100);
	platform_09->setFog(fog);
	platform_09->setReflectFactor(vec2(0.2, 0.5));
	platform_09->setEta(0.5);
	platform_09->setCubeMapUnit(3);
	platform_09->setSpeed(5);
	platform_09->postTrans(glm::translate(vec3(60.0, 14.0, -80.0)));
	//platform_03->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_09->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_09->setShadowTex(shadow_map_id);
	platform_09->setType("Cube");
	platform_09->setName("Test Platform");
	platform_09->setAliveModelM(platform_09->getModelM());
	stationary_list.push_back(platform_09);

	//tower island
	Cube* platform_10 = new Cube(-10, 10, -0.5, 0.5, -10, 10);
	//platform_09->setSpeed(5); 
	platform_10->setKd(vec3(0.8, 0.8, 0.8));
	platform_10->setKa(vec3(0.3, 0.3, 0.0));
	platform_10->setKs(vec3(0.4, 0.4, 0.0));
	platform_10->setShininess(100);
	platform_10->setFog(fog);
	platform_10->setReflectFactor(vec2(0.2, 0.5));
	platform_10->setEta(0.5);
	platform_10->setCubeMapUnit(3);
	platform_10->setSpeed(5);
	platform_10->postTrans(glm::translate(vec3(-60.0, 14.0, -80.0)));
	//platform_03->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_10->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_10->setShadowTex(shadow_map_id);
	platform_10->setType("Cube");
	platform_10->setName("Test Platform");
	platform_10->setAliveModelM(platform_10->getModelM());
	stationary_list.push_back(platform_10);

	//tower island
	Cube* platform_10b = new Cube(-10, 10, -0.5, 0.5, -10, 10);
	//platform_09->setSpeed(5); 
	platform_10b->setKd(vec3(0.8, 0.8, 0.8));
	platform_10b->setKa(vec3(0.3, 0.3, 0.0));
	platform_10b->setKs(vec3(0.4, 0.4, 0.0));
	platform_10b->setShininess(100);
	platform_10b->setFog(fog);
	platform_10b->setReflectFactor(vec2(0.2, 0.5));
	platform_10b->setEta(0.5);
	platform_10b->setCubeMapUnit(3);
	platform_10b->setSpeed(5);
	platform_10b->postTrans(glm::translate(vec3(-60.0, 14.0, 80.0)));
	//platform_03->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_10b->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_10b->setShadowTex(shadow_map_id);
	platform_10b->setType("Cube");
	platform_10b->setName("Test Platform");
	platform_10b->setAliveModelM(platform_10->getModelM());
	stationary_list.push_back(platform_10b);

	//tower island
	Cube* platform_06 = new Cube(-10.0, 10.0, -0.5, 0.5, -10, 10);
	//platform_06->setSpeed(5); 
	platform_06->setKd(vec3(0.8, 0.8, 0.8));
	platform_06->setKa(vec3(0.3, 0.3, 0.0));
	platform_06->setKs(vec3(0.4, 0.3, 0.0));
	platform_06->setShininess(100);
	platform_06->setFog(fog);
	platform_06->setReflectFactor(vec2(0.2, 0.5));
	platform_06->setEta(0.5);
	platform_06->setCubeMapUnit(3);
	platform_06->setSpeed(5);
	platform_06->postTrans(glm::translate(vec3(60.0, 14.0, 80.0)));
	//platform_06->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_06->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_06->setShadowTex(shadow_map_id);
	platform_06->setType("Cube");
	platform_06->setName("Test Platform");
	platform_06->setAliveModelM(platform_06->getModelM());
	stationary_list.push_back(platform_06);

	//2nd level
	Cube* platform_11 = new Cube(-10.0, 10.0, -0.5, 0.5, -5, 5);
	//platform_06->setSpeed(5); 
	platform_11->setKd(vec3(0.8, 0.0, 0.8));
	platform_11->setKa(vec3(0.3, 0.0, 0.3));
	platform_11->setKs(vec3(0.4, 0.0, 0.4));
	platform_11->setShininess(100);
	platform_11->setFog(fog);
	platform_11->setReflectFactor(vec2(0.2, 0.5));
	platform_11->setEta(0.5);
	platform_11->setCubeMapUnit(3);
	platform_11->setSpeed(5);
	platform_11->postTrans(glm::translate(vec3(0, 50.0, 15.0)));
	//platform_06->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_11->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_11->setShadowTex(shadow_map_id);
	platform_11->setType("Cube");
	platform_11->setName("Test Platform");
	platform_11->setAliveModelM(platform_11->getModelM());
	stationary_list.push_back(platform_11);

	//2nd level
	Cube* platform_12 = new Cube(-10.0, 10.0, -0.5, 0.5, -5, 5);
	//platform_06->setSpeed(5); 
	platform_12->setKd(vec3(0.8, 0.0, 0.8));
	platform_12->setKa(vec3(0.3, 0.0, 0.3));
	platform_12->setKs(vec3(0.4, 0.0, 0.4));
	platform_12->setShininess(100);
	platform_12->setFog(fog);
	platform_12->setReflectFactor(vec2(0.2, 0.5));
	platform_12->setEta(0.5);
	platform_12->setCubeMapUnit(3);
	platform_12->setSpeed(5);
	platform_12->postTrans(glm::translate(vec3(0.0, 50.0, -15.0)));
	//platform_06->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_12->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_12->setShadowTex(shadow_map_id);
	platform_12->setType("Cube");
	platform_12->setName("Test Platform");
	platform_12->setAliveModelM(platform_12->getModelM());
	stationary_list.push_back(platform_12);

	//2nd level
	Cube* platform_13 = new Cube(-5.0, 5.0, -0.5, 0.5, -20, 20);
	//platform_06->setSpeed(5); 
	platform_13->setKd(vec3(0.8, 0.0, 0.8));
	platform_13->setKa(vec3(0.3, 0.0, 0.3));
	platform_13->setKs(vec3(0.4, 0.0, 0.4));
	platform_13->setShininess(100);
	platform_13->setFog(fog);
	platform_13->setReflectFactor(vec2(0.2, 0.5));
	platform_13->setEta(0.5);
	platform_13->setCubeMapUnit(3);
	platform_13->setSpeed(5);
	platform_13->postTrans(glm::translate(vec3(15.0, 50.0, 0.0)));
	//platform_06->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_13->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_13->setShadowTex(shadow_map_id);
	platform_13->setType("Cube");
	platform_13->setName("Test Platform");
	platform_13->setAliveModelM(platform_13->getModelM());
	stationary_list.push_back(platform_13);

	//2nd level
	Cube* platform_14 = new Cube(-5.0, 5.0, -0.5, 0.5, -20, 20);
	//platform_06->setSpeed(5); 
	platform_14->setKd(vec3(0.8, 0.0, 0.8));
	platform_14->setKa(vec3(0.3, 0.0, 0.3));
	platform_14->setKs(vec3(0.4, 0.0, 0.4));
	platform_14->setShininess(100);
	platform_14->setFog(fog);
	platform_14->setReflectFactor(vec2(0.2, 0.5));
	platform_14->setEta(0.5);
	platform_14->setCubeMapUnit(3);
	platform_14->setSpeed(5);
	platform_14->postTrans(glm::translate(vec3(-15, 50.0, 0.0)));
	//platform_06->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_14->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_14->setShadowTex(shadow_map_id);
	platform_14->setType("Cube");
	platform_14->setName("Test Platform");
	platform_14->setAliveModelM(platform_14->getModelM());
	stationary_list.push_back(platform_14);


	//Trampoline 
	Cube* tramp_01 = new Cube(-2.0, 2.0, -0.5, 0.5, -2.0, 2.0);
	tramp_01->setKd(vec3(0.0, 0.0, 0.0));
	tramp_01->setKa(vec3(0.0, 0.0, 0.0));
	tramp_01->setKs(vec3(0.0, 0.0, 0.0));
	tramp_01->setShininess(100);
	tramp_01->setFog(fog);
	tramp_01->setReflectFactor(vec2(0.2, 0.5));
	tramp_01->setEta(0.5);
	tramp_01->setCubeMapUnit(3);
	tramp_01->postTrans(glm::translate(vec3(20, 5.0, 45)));
	tramp_01->setShader(sdrCtl.getShader("basic_reflect_refract"));
	tramp_01->setShadowTex(shadow_map_id);
	tramp_01->setType("Trampoline");
	tramp_01->setName("Test Trampoline");
	stationary_list.push_back(tramp_01);

	//Trampoline effect
	ParticleAnimated* tramp_effect_01 = new ParticleAnimated(*(MOM.mother_of_tramp_effect));
	tramp_effect_01->setModelM(tramp_01->getModelM()*glm::translate(vec3(0, 1, 0)));
	tramp_effect_01->setStartTime(ct);
	panim_list.push_back(tramp_effect_01);

	//Trampoline 
	Cube* tramp_02 = new Cube(-2.0, 2.0, -0.5, 0.5, -2.0, 2.0);
	tramp_02->setKd(vec3(0.0, 0.0, 0.0));
	tramp_02->setKa(vec3(0.0, 0.0, 0.0));
	tramp_02->setKs(vec3(0.0, 0.0, 0.0));
	tramp_02->setShininess(100);
	tramp_02->setFog(fog);
	tramp_02->setReflectFactor(vec2(0.2, 0.5));
	tramp_02->setEta(0.5);
	tramp_02->setCubeMapUnit(3);
	tramp_02->postTrans(glm::translate(vec3(-20, 5.0, 45)));
	tramp_02->setShader(sdrCtl.getShader("basic_reflect_refract"));
	tramp_02->setShadowTex(shadow_map_id);
	tramp_02->setType("Trampoline");
	tramp_02->setName("Test Trampoline");
	stationary_list.push_back(tramp_02);

	//Trampoline effect
	ParticleAnimated* tramp_effect_02 = new ParticleAnimated(*(MOM.mother_of_tramp_effect));
	tramp_effect_02->setModelM(tramp_02->getModelM()*glm::translate(vec3(0, 1, 0)));
	tramp_effect_02->setStartTime(ct);
	panim_list.push_back(tramp_effect_02);

	//Trampoline 
	Cube* tramp_03 = new Cube(-2.0, 2.0, -0.5, 0.5, -2.0, 2.0);
	tramp_03->setKd(vec3(0.0, 0.0, 0.0));
	tramp_03->setKa(vec3(0.0, 0.0, 0.0));
	tramp_03->setKs(vec3(0.0, 0.0, 0.0));
	tramp_03->setShininess(100);
	tramp_03->setFog(fog);
	tramp_03->setReflectFactor(vec2(0.2, 0.5));
	tramp_03->setEta(0.5);
	tramp_03->setCubeMapUnit(3);
	tramp_03->postTrans(glm::translate(vec3(20, 5.0, -45)));
	tramp_03->setShader(sdrCtl.getShader("basic_reflect_refract"));
	tramp_03->setShadowTex(shadow_map_id);
	tramp_03->setType("Trampoline");
	tramp_03->setName("Test Trampoline");
	stationary_list.push_back(tramp_03);

	//Trampoline effect
	ParticleAnimated* tramp_effect_03 = new ParticleAnimated(*(MOM.mother_of_tramp_effect));
	tramp_effect_03->setModelM(tramp_03->getModelM()*glm::translate(vec3(0, 1, 0)));
	tramp_effect_03->setStartTime(ct);
	panim_list.push_back(tramp_effect_03);

	//Trampoline 
	Cube* tramp_04 = new Cube(-2.0, 2.0, -0.5, 0.5, -2.0, 2.0);
	tramp_04->setKd(vec3(0.0, 0.0, 0.0));
	tramp_04->setKa(vec3(0.0, 0.0, 0.0));
	tramp_04->setKs(vec3(0.0, 0.0, 0.0));
	tramp_04->setShininess(100);
	tramp_04->setFog(fog);
	tramp_04->setReflectFactor(vec2(0.2, 0.5));
	tramp_04->setEta(0.5);
	tramp_04->setCubeMapUnit(3);
	tramp_04->postTrans(glm::translate(vec3(-20, 5.0, -45)));
	tramp_04->setShader(sdrCtl.getShader("basic_reflect_refract"));
	tramp_04->setShadowTex(shadow_map_id);
	tramp_04->setType("Trampoline");
	tramp_04->setName("Test Trampoline");
	stationary_list.push_back(tramp_04);


	//Trampoline effect
	ParticleAnimated* tramp_effect_04 = new ParticleAnimated(*(MOM.mother_of_tramp_effect));
	tramp_effect_04->setModelM(tramp_04->getModelM()*glm::translate(vec3(0, 1, 0)));
	tramp_effect_04->setStartTime(ct);
	panim_list.push_back(tramp_effect_04);

	/*//Trampoline 
	Cube* tramp_05 = new Cube(-2.0, 2.0, -0.5, 0.5, -2.0, 2.0);
	tramp_05->setKd(vec3(0.0, 0.0, 0.0));
	tramp_05->setKa(vec3(0.0, 0.0, 0.0));
	tramp_05->setKs(vec3(0.0, 0.0, 0.0));
	tramp_05->setShininess(100);
	tramp_05->setFog(fog);
	tramp_05->setReflectFactor(vec2(0.2, 0.5));
	tramp_05->setEta(0.5);
	tramp_05->setCubeMapUnit(3);
	tramp_05->postTrans(glm::translate(vec3(-15, 6.0, 0)));
	tramp_05->setShader(sdrCtl.getShader("basic_reflect_refract"));
	tramp_05->setShadowTex(shadow_map_id);
	tramp_05->setType("Trampoline");
	tramp_05->setName("Test Trampoline");
	stationary_list.push_back(tramp_05);

	//Trampoline effect
	ParticleAnimated* tramp_effect_05 = new ParticleAnimated(*(MOM.mother_of_tramp_effect));
	tramp_effect_05->setModelM(tramp_05->getModelM()*glm::translate(vec3(0, 1, 0)));
	tramp_effect_05->setStartTime(ct);
	panim_list.push_back(tramp_effect_05);

	//Trampoline 
	Cube* tramp_06 = new Cube(-2.0, 2.0, -0.5, 0.5, -2.0, 2.0);
	tramp_06->setKd(vec3(0.0, 0.0, 0.0));
	tramp_06->setKa(vec3(0.0, 0.0, 0.0));
	tramp_06->setKs(vec3(0.0, 0.0, 0.0));
	tramp_06->setShininess(100);
	tramp_06->setFog(fog);
	tramp_06->setReflectFactor(vec2(0.2, 0.5));
	tramp_06->setEta(0.5);
	tramp_06->setCubeMapUnit(3);
	tramp_06->postTrans(glm::translate(vec3(15, 7.0, 0)));
	tramp_06->setShader(sdrCtl.getShader("basic_reflect_refract"));
	tramp_06->setShadowTex(shadow_map_id);
	tramp_06->setType("Trampoline");
	tramp_06->setName("Test Trampoline");
	stationary_list.push_back(tramp_06);

	//Trampoline effect
	ParticleAnimated* tramp_effect_06 = new ParticleAnimated(*(MOM.mother_of_tramp_effect));
	tramp_effect_06->setModelM(tramp_06->getModelM()*glm::translate(vec3(0, 1, 0)));
	tramp_effect_06->setStartTime(ct);
	panim_list.push_back(tramp_effect_06);*/


	Cube* tele_01 = new Cube(-2.0, 2.0, -0.5, 0.5, -2.0, 2.0);
	tele_01->setKd(vec3(1.0, .65, 0));
	tele_01->setKa(vec3(1.0, .65, 0));
	tele_01->setKs(vec3(1.0, .65, 0));
	tele_01->setShininess(100);
	tele_01->setFog(fog);
	tele_01->setReflectFactor(vec2(0.2, 0.5));
	tele_01->setEta(0.5);
	tele_01->setCubeMapUnit(3);
	tele_01->postTrans(glm::translate(vec3(80, 14.0, 80)));
	tele_01->setShader(sdrCtl.getShader("basic_reflect_refract"));
	tele_01->setShadowTex(shadow_map_id);
	tele_01->setType("Teleporter");
	tele_01->setName("Test Teleporter");
	stationary_list.push_back(tele_01);

	//Tele effect
	ParticleAnimated* tele_effect_01 = new ParticleAnimated(*(MOM.mother_of_portal_effect));
	tele_effect_01->setModelM(tele_01->getModelM()*glm::translate(vec3(0, 1, 0)));
	tele_effect_01->setStartTime(ct);
	panim_list.push_back(tele_effect_01);

	Cube* tele_02 = new Cube(-2.0, 2.0, -0.5, 0.5, -2.0, 2.0);
	tele_02->setKd(vec3(1.0, .65, 0));
	tele_02->setKa(vec3(1.0, .65, 0));
	tele_02->setKs(vec3(1.0, .65, 0));
	tele_02->setShininess(100);
	tele_02->setFog(fog);
	tele_02->setReflectFactor(vec2(0.2, 0.5));
	tele_02->setEta(0.5);
	tele_02->setCubeMapUnit(3);
	tele_02->postTrans(glm::translate(vec3(-80, 14.0, 80)));
	tele_02->setShader(sdrCtl.getShader("basic_reflect_refract"));
	tele_02->setShadowTex(shadow_map_id);
	tele_02->setType("Teleporter");
	tele_02->setName("Test Teleporter");
	stationary_list.push_back(tele_02);

	//Tele effect
	ParticleAnimated* tele_effect_02 = new ParticleAnimated(*(MOM.mother_of_portal_effect));
	tele_effect_02->setModelM(tele_02->getModelM()*glm::translate(vec3(0, 1, 0)));
	tele_effect_02->setStartTime(ct);
	panim_list.push_back(tele_effect_02);

	Cube* tele_03 = new Cube(-2.0, 2.0, -0.5, 0.5, -2.0, 2.0);
	tele_03->setKd(vec3(1.0, .65, 0));
	tele_03->setKa(vec3(1.0, .65, 0));
	tele_03->setKs(vec3(1.0, .65, 0));
	tele_03->setShininess(100);
	tele_03->setFog(fog);
	tele_03->setReflectFactor(vec2(0.2, 0.5));
	tele_03->setEta(0.5);
	tele_03->setCubeMapUnit(3);
	tele_03->postTrans(glm::translate(vec3(80, 14.0, -80)));
	tele_03->setShader(sdrCtl.getShader("basic_reflect_refract"));
	tele_03->setShadowTex(shadow_map_id);
	tele_03->setType("Teleporter");
	tele_03->setName("Test Teleporter");
	stationary_list.push_back(tele_03);

	//Tele effect
	ParticleAnimated* tele_effect_03 = new ParticleAnimated(*(MOM.mother_of_portal_effect));
	tele_effect_03->setModelM(tele_03->getModelM()*glm::translate(vec3(0, 1, 0)));
	tele_effect_03->setStartTime(ct);
	panim_list.push_back(tele_effect_03);

	Cube* tele_04 = new Cube(-2.0, 2.0, -0.5, 0.5, -2.0, 2.0);
	tele_04->setKd(vec3(1.0, .65, 0));
	tele_04->setKa(vec3(1.0, .65, 0));
	tele_04->setKs(vec3(1.0, .65, 0));
	tele_04->setShininess(100);
	tele_04->setFog(fog);
	tele_04->setReflectFactor(vec2(0.2, 0.5));
	tele_04->setEta(0.5);
	tele_04->setCubeMapUnit(3);
	tele_04->postTrans(glm::translate(vec3(-80, 14.0, -80)));
	tele_04->setShader(sdrCtl.getShader("basic_reflect_refract"));
	tele_04->setShadowTex(shadow_map_id);
	tele_04->setType("Teleporter");
	tele_04->setName("Test Teleporter");
	stationary_list.push_back(tele_04);

	//Tele effect
	ParticleAnimated* tele_effect_04 = new ParticleAnimated(*(MOM.mother_of_portal_effect));
	tele_effect_04->setModelM(tele_04->getModelM()*glm::translate(vec3(0, 1, 0)));
	tele_effect_04->setStartTime(ct);
	panim_list.push_back(tele_effect_04);

	Cube* ele_01 = new Cube(-5.0, 5.0, -0.5, 0.5, -5.0, 5.0);
	ele_01->setKd(vec3(1.0, 1.0, 1.0));
	ele_01->setKa(vec3(1.0, 1.0, 1.0));
	ele_01->setKs(vec3(1.0, 1.0, 1.0));
	ele_01->setShininess(100);
	ele_01->setFog(fog);
	ele_01->setReflectFactor(vec2(0.2, 0.5));
	ele_01->setEta(0.5);
	ele_01->setCubeMapUnit(3);
	ele_01->postTrans(glm::translate(vec3(12, 14.0, 38)));
	ele_01->setShader(sdrCtl.getShader("basic_reflect_refract"));
	ele_01->setShadowTex(shadow_map_id);
	ele_01->setType("Elevator");
	ele_01->setName("Test Elevator");
	stationary_list.push_back(ele_01);
	elevator_list.push_back(ele_01);

	Cube* ele_02 = new Cube(-5.0, 5.0, -0.5, 0.5, -5.0, 5.0);
	ele_02->setKd(vec3(1.0, 1.0, 1.0));
	ele_02->setKa(vec3(1.0, 1.0, 1.0));
	ele_02->setKs(vec3(1.0, 1.0, 1.0));
	ele_02->setShininess(100);
	ele_02->setFog(fog);
	ele_02->setReflectFactor(vec2(0.2, 0.5));
	ele_02->setEta(0.5);
	ele_02->setCubeMapUnit(3);
	ele_02->postTrans(glm::translate(vec3(12, 14.0, 38)));
	ele_02->setShader(sdrCtl.getShader("basic_reflect_refract"));
	ele_02->setShadowTex(shadow_map_id);
	ele_02->setType("Elevator");
	ele_02->setName("Test Elevator");
	stationary_list.push_back(ele_02);
	elevator_list.push_back(ele_02);

	Cube* ele_03 = new Cube(-5.0, 5.0, -0.5, 0.5, -5.0, 5.0);
	ele_03->setKd(vec3(1.0, 1.0, 1.0));
	ele_03->setKa(vec3(1.0, 1.0, 1.0));
	ele_03->setKs(vec3(1.0, 1.0, 1.0));
	ele_03->setShininess(100);
	ele_03->setFog(fog);
	ele_03->setReflectFactor(vec2(0.2, 0.5));
	ele_03->setEta(0.5);
	ele_03->setCubeMapUnit(3);
	ele_03->postTrans(glm::translate(vec3(12, 14.0, 38)));
	ele_03->setShader(sdrCtl.getShader("basic_reflect_refract"));
	ele_03->setShadowTex(shadow_map_id);
	ele_03->setType("Elevator");
	ele_03->setName("Test Elevator");
	stationary_list.push_back(ele_03);
	elevator_list.push_back(ele_03);

	Cube* ele_04 = new Cube(-5.0, 5.0, -0.5, 0.5, -5.0, 5.0);
	ele_04->setKd(vec3(1.0, 1.0, 1.0));
	ele_04->setKa(vec3(1.0, 1.0, 1.0));
	ele_04->setKs(vec3(1.0, 1.0, 1.0));
	ele_04->setShininess(100);
	ele_04->setFog(fog);
	ele_04->setReflectFactor(vec2(0.2, 0.5));
	ele_04->setEta(0.5);
	ele_04->setCubeMapUnit(3);
	ele_04->postTrans(glm::translate(vec3(12, 14.0, 38)));
	ele_04->setShader(sdrCtl.getShader("basic_reflect_refract"));
	ele_04->setShadowTex(shadow_map_id);
	ele_04->setType("Elevator");
	ele_04->setName("Test Elevator");
	stationary_list.push_back(ele_04);
	elevator_list.push_back(ele_04);
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

	m_billboardList.Init("img/boots.png", "PNG");
	m_billboardList.setShader(sdrCtl.getShader("billboard"));
	m_billboardList.AddBoard(vec3(-20.0f, 9.0f, 0.0f));//speed up
	m_billboardList.BindBoards();

	m_billboardList2.Init("img/dmgup.png", "PNG");
	m_billboardList2.setShader(sdrCtl.getShader("billboard"));
	m_billboardList2.AddBoard(vec3(20.0f, 9.0f, 0.0f));//dmg up
	m_billboardList2.BindBoards();

	m_billboardList3.Init("img/heart.png", "PNG");
	m_billboardList3.setShader(sdrCtl.getShader("billboard"));
	m_billboardList3.AddBoard(vec3(0.0f, 19.0f, -20.0f));//health up
	m_billboardList3.BindBoards();

	m_billboardList4.Init("img/projspd.png", "PNG");
	m_billboardList4.setShader(sdrCtl.getShader("billboard"));
	m_billboardList4.AddBoard(vec3(0.0f, 19.0f, 20.0f));//Shot Speed up
	m_billboardList4.BindBoards();

	m_billboardList5.Init("img/rngup.png", "PNG");
	m_billboardList5.setShader(sdrCtl.getShader("billboard"));
	m_billboardList5.AddBoard(vec3(0.0f, 10.0f, 0.0f));//Shot Rng up
	m_billboardList5.BindBoards();

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
	/*
	testSystem->setTime_Step(0.5);
	testSystem->setTime_Max(350.0);
	testSystem->setTime_Min(0.0);
	testSystem->setBlastRadius(20.0);
	testSystem->setExplosionVelocity(0.7);
	testSystem->setExplosionDecay(2.0);
	testSystem->setFragStartColor(vec3(1.0, 0.2, 0.2));
	testSystem->setFragEndColor(vec3(0.6, 0, 0));
	*/
	testSystem->setFog(fog);
	testSystem->setModelM(glm::translate(vec3(0.0f, 9.0f, 0.0f)));

	/*
	damagePart->setShader(sdrCtl.getShader("pe_system"));
	damagePart->setType("Particle_System");
	damagePart->setName("Particle_Test");
	damagePart->setLoopInf(false);
	damagePart->setLoopCount(1);
	damagePart->setTexture(GL_TEXTURE_2D, "img/smog.png", "PNG");
	damagePart->setFog(fog);
	*/



	//Floor
	Cube* platform_200 = new Cube(-35, 35, -0.5, 0.5, -35, 35);
	//platform_01->setSpeed(5); 
	platform_200->setKd(vec3(1, .65, 0));
	platform_200->setKa(vec3(1.0, .65, 0));
	platform_200->setKs(vec3(1.0, .65, 0));
	platform_200->setShininess(100);
	platform_200->setFog(fog);
	platform_200->setReflectFactor(vec2(0.1, 0.1));
	platform_200->setEta(0.5);
	platform_200->setCubeMapUnit(3);
	platform_200->setSpeed(5);
	platform_200->postTrans(glm::translate(vec3(ORIGINX0,
		ORIGINY0 + 5,
		ORIGINZ0)));
	//platform_200->setAABB(AABB(vec3(-20, -0.5, -20), vec3(20, 0.5, 20)));
	platform_200->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_200->setShadowTex(shadow_map_id);
	platform_200->setType("Cube");
	platform_200->setName("Test Platform");
	// don't draw for now so we can peek inside
	stationary_list.push_back(platform_200);

	//wall0
	Cube* platform_201 = new Cube(-0.5, 0.5, -15, 15, -PERIMETER_WALL_RADIUS, PERIMETER_WALL_RADIUS);
	//platform_01->setSpeed(5);
	platform_201->setKd(vec3(0.0, 0.6, 0.9));
	platform_201->setKa(vec3(0.0, 0.0, 0.3));
	platform_201->setKs(vec3(0.0, 0.0, 0.4));
	platform_201->setShininess(100);
	platform_201->setFog(fog);
	platform_201->setReflectFactor(vec2(0.1, 0.1));
	platform_201->setEta(0.5);
	platform_201->setCubeMapUnit(3);
	platform_201->setSpeed(5);
	platform_201->postTrans(glm::translate(vec3(ORIGINX0 + PERIMETER_WALL_RADIUS,
		ORIGINY0 + PERIMETER_WALL_HEIGHT,
		ORIGINZ0)));
	platform_201->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_201->setShadowTex(shadow_map_id);
	//platform_201->setAABB(AABB(vec3(-0.5, -15, -5.0), vec3(1.5, 0.5, 5.0)));
	platform_201->setType("Cube");
	platform_201->setName("baset0");
	stationary_list.push_back(platform_201);

	//wall1
	Cube* platform_202 = new Cube(-0.5, 0.5, -15, 15, -PERIMETER_WALL_RADIUS, PERIMETER_WALL_RADIUS);
	//platform_01->setSpeed(5); 
	platform_202->setKd(vec3(0.0, 0.6, 0.9));
	platform_202->setKa(vec3(0.0, 0.0, 0.3));
	platform_202->setKs(vec3(0.0, 0.0, 0.4));
	platform_202->setShininess(100);
	platform_202->setFog(fog);
	platform_202->setReflectFactor(vec2(0.1, 0.1));
	platform_202->setEta(0.5);
	platform_202->setCubeMapUnit(3);
	platform_202->setSpeed(5);
	platform_202->postTrans(glm::translate(vec3(ORIGINX0 - PERIMETER_WALL_RADIUS,
		ORIGINY0 + PERIMETER_WALL_HEIGHT,
		ORIGINZ0)));
	//platform_202->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_202->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_202->setShadowTex(shadow_map_id);
	platform_202->setType("Cube");
	platform_202->setName("baset0");
	stationary_list.push_back(platform_202);

	//wall2
	Cube* platform_203 = new Cube(-PERIMETER_WALL_RADIUS, PERIMETER_WALL_RADIUS, -15, 15, -0.5, 0.5);
	//platform_01->setSpeed(5); 
	platform_203->setKd(vec3(0.0, 0.6, 0.9));
	platform_203->setKa(vec3(0.0, 0.0, 0.3));
	platform_203->setKs(vec3(0.0, 0.0, 0.4));
	platform_203->setShininess(100);
	platform_203->setFog(fog);
	platform_203->setReflectFactor(vec2(0.1, 0.1));
	platform_203->setEta(0.5);
	platform_203->setCubeMapUnit(3);
	platform_203->setSpeed(5);
	platform_203->postTrans(glm::translate(vec3(ORIGINX0,
		ORIGINY0 + PERIMETER_WALL_HEIGHT,
		ORIGINZ0 + PERIMETER_WALL_RADIUS)));
	//platform_203->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_203->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_203->setShadowTex(shadow_map_id);
	platform_203->setType("Cube");
	platform_203->setName("baset0");
	stationary_list.push_back(platform_203);

	//wall3
	Cube* platform_204 = new Cube(-PERIMETER_WALL_RADIUS, PERIMETER_WALL_RADIUS, -15, 15, -0.5, 0.5);
	//platform_01->setSpeed(5); 
	platform_204->setKd(vec3(0.0, 0.6, 0.9));
	platform_204->setKa(vec3(0.0, 0.0, 0.3));
	platform_204->setKs(vec3(0.0, 0.0, 0.4));
	platform_204->setShininess(100);
	platform_204->setFog(fog);
	platform_204->setReflectFactor(vec2(0.1, 0.1));
	platform_204->setEta(0.5);
	platform_204->setCubeMapUnit(3);
	platform_204->setSpeed(5);
	platform_204->postTrans(glm::translate(vec3(ORIGINX0,
		ORIGINY0 + PERIMETER_WALL_HEIGHT,
		ORIGINZ0 - PERIMETER_WALL_RADIUS)));
	//platform_204->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_204->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_204->setShadowTex(shadow_map_id);
	platform_204->setType("Cube");
	platform_204->setName("baset0");
	stationary_list.push_back(platform_204);

	// inside middle
	Cube* platform_205 = new Cube(-2, 2, -0.5, 0.5, -2, 2);
	//platform_01->setSpeed(5); 
	platform_205->setKd(vec3(0.0, 0.6, 0.9));
	platform_205->setKa(vec3(0.0, 0.0, 0.3));
	platform_205->setKs(vec3(0.0, 0.0, 0.4));
	platform_205->setShininess(100);
	platform_205->setFog(fog);
	platform_205->setReflectFactor(vec2(0.1, 0.1));
	platform_205->setEta(0.5);
	platform_205->setCubeMapUnit(3);
	platform_205->setSpeed(5);
	platform_205->postTrans(glm::translate(vec3(ORIGINX0,
		ORIGINY0 + CENTER_TOWERPLAT_HEIGHT,
		ORIGINZ0)));
	//platform_205->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_205->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_205->setShadowTex(shadow_map_id);
	platform_205->setType("Cube");
	platform_205->setName("Test Platform");
	stationary_list.push_back(platform_205);

	// tower in the middle
	Mesh* tower100 = new Mesh();
	tower100->LoadMesh("Model/OctopusTower1_10_bone2.dae", false);
	tower100->setShader(sdrCtl.getShader("basic_model"));
	tower100->setShadowTex(shadow_map_id);
	tower100->setAdjustM(glm::translate(vec3(0.0, 2.9, 0.0))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0))*glm::scale(vec3(0.6, 0.6, 0.6)));
	tower100->setModelM(glm::translate(vec3(ORIGINX0,
		ORIGINY0 + CENTER_TOWERPLAT_HEIGHT,
		ORIGINZ0)));
	tower100->setShininess(30);
	tower100->setFog(fog);
	tower_list.push_back(tower100);

	//force field effect
	force_field[0] = new ParticleAnimated(*(MOM.mother_of_force_field));
	force_field[0]->setFollow(tower100, vec3(0, 1.0, 0), 1, &View);
	force_field[0]->setStartTime(ct);

	//diag plat 0
	Cube* platform_206 = new Cube(-5, 5, -0.5, 0.5, -5, 5);
	//platform_01->setSpeed(5); 
	platform_206->setKd(vec3(0.0, 0.6, 0.9));
	platform_206->setKa(vec3(0.0, 0.0, 0.3));
	platform_206->setKs(vec3(0.0, 0.0, 0.4));
	platform_206->setShininess(100);
	platform_206->setFog(fog);
	platform_206->setReflectFactor(vec2(0.1, 0.1));
	platform_206->setEta(0.5);
	platform_206->setCubeMapUnit(3);
	platform_206->setSpeed(5);
	platform_206->postTrans(glm::translate(vec3(ORIGINX0 + CENTER_PLAT_SPACING,
		ORIGINY0 + CENTER_PLAT_HEIGHT,
		ORIGINZ0 + CENTER_PLAT_SPACING)));
	//platform_206->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_206->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_206->setShadowTex(shadow_map_id);
	platform_206->setType("Cube");
	platform_206->setName("Test Platform");
	stationary_list.push_back(platform_206);

	//diag plat 1
	Cube* platform_207 = new Cube(-5, 5, -0.5, 0.5, -5, 5);
	//platform_01->setSpeed(5); 
	platform_207->setKd(vec3(0.0, 0.6, 0.9));
	platform_207->setKa(vec3(0.0, 0.0, 0.3));
	platform_207->setKs(vec3(0.0, 0.0, 0.4));
	platform_207->setShininess(100);
	platform_207->setFog(fog);
	platform_207->setReflectFactor(vec2(0.1, 0.1));
	platform_207->setEta(0.5);
	platform_207->setCubeMapUnit(3);
	platform_207->setSpeed(5);
	platform_207->postTrans(glm::translate(vec3(ORIGINX0 - CENTER_PLAT_SPACING,
		ORIGINY0 + CENTER_PLAT_HEIGHT,
		ORIGINZ0 - CENTER_PLAT_SPACING)));
	//platform_207->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_207->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_207->setShadowTex(shadow_map_id);
	platform_207->setType("Cube");
	platform_207->setName("Test Platform");
	stationary_list.push_back(platform_207);

	//diag plat 2
	Cube* platform_208 = new Cube(-5, 5, -0.5, 0.5, -5, 5);
	//platform_01->setSpeed(5); 
	platform_208->setKd(vec3(0.0, 0.6, 0.9));
	platform_208->setKa(vec3(0.0, 0.0, 0.3));
	platform_208->setKs(vec3(0.0, 0.0, 0.4));
	platform_208->setShininess(100);
	platform_208->setFog(fog);
	platform_208->setReflectFactor(vec2(0.1, 0.1));
	platform_208->setEta(0.5);
	platform_208->setCubeMapUnit(3);
	platform_208->setSpeed(5);
	platform_208->postTrans(glm::translate(vec3(ORIGINX0 + CENTER_PLAT_SPACING,
		ORIGINY0 + CENTER_PLAT_HEIGHT,
		ORIGINZ0 - CENTER_PLAT_SPACING)));
	//platform_208->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_208->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_208->setShadowTex(shadow_map_id);
	platform_208->setType("Cube");
	platform_208->setName("Test Platform");
	stationary_list.push_back(platform_208);

	//diag plat 3
	Cube* platform_209 = new Cube(-5, 5, -0.5, 0.5, -5, 5);
	//platform_01->setSpeed(5); 
	platform_209->setKd(vec3(0.0, 0.6, 0.9));
	platform_209->setKa(vec3(0.0, 0.0, 0.3));
	platform_209->setKs(vec3(0.0, 0.0, 0.4));
	platform_209->setShininess(100);
	platform_209->setFog(fog);
	platform_209->setReflectFactor(vec2(0.1, 0.1));
	platform_209->setEta(0.5);
	platform_209->setCubeMapUnit(3);
	platform_209->setSpeed(5);
	platform_209->postTrans(glm::translate(vec3(ORIGINX0 - CENTER_PLAT_SPACING,
		ORIGINY0 + CENTER_PLAT_HEIGHT,
		ORIGINZ0 + CENTER_PLAT_SPACING)));
	//platform_209->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_209->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_209->setShadowTex(shadow_map_id);
	platform_209->setType("Cube");
	platform_209->setName("Test Platform");
	stationary_list.push_back(platform_209);

	//stairs0 top
	Cube* platform_210 = new Cube(-20, 20, -1.5, 1.5, -5, 5);
	//platform_01->setSpeed(5); 
	platform_210->setKd(vec3(0.0, 0.6, 0.9));
	platform_210->setKa(vec3(0.0, 0.0, 0.3));
	platform_210->setKs(vec3(0.0, 0.0, 0.4));
	platform_210->setShininess(100);
	platform_210->setFog(fog);
	platform_210->setReflectFactor(vec2(0.1, 0.1));
	platform_210->setEta(0.5);
	platform_210->setCubeMapUnit(3);
	platform_210->setSpeed(5);
	platform_210->postTrans(glm::translate(vec3(ORIGINX0,
		ORIGINY0 + 17.5,
		ORIGINZ0 - 45)));
	//platform_210->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_210->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_210->setShadowTex(shadow_map_id);
	platform_210->setType("Cube");
	platform_210->setName("Test Platform");
	stationary_list.push_back(platform_210);

	//stairs1
	Cube* platform_211 = new Cube(-20, 20, -1.5, 1.5, -5, 5);
	//platform_01->setSpeed(5); 
	platform_211->setKd(vec3(0.0, 0.6, 0.9));
	platform_211->setKa(vec3(0.0, 0.0, 0.3));
	platform_211->setKs(vec3(0.0, 0.0, 0.4));
	platform_211->setShininess(100);
	platform_211->setFog(fog);
	platform_211->setReflectFactor(vec2(0.1, 0.1));
	platform_211->setEta(0.5);
	platform_211->setCubeMapUnit(3);
	platform_211->setSpeed(5);
	platform_211->postTrans(glm::translate(vec3(ORIGINX0,
		ORIGINY0 + 14,
		ORIGINZ0 - 55)));
	//platform_211->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_211->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_211->setShadowTex(shadow_map_id);
	platform_211->setType("Cube");
	platform_211->setName("Test Platform");
	stationary_list.push_back(platform_211);

	//stairs2
	Cube* platform_212 = new Cube(-20, 20, -1.5, 1.5, -5, 5);
	//platform_01->setSpeed(5); 
	platform_212->setKd(vec3(0.0, 0.6, 0.9));
	platform_212->setKa(vec3(0.0, 0.0, 0.3));
	platform_212->setKs(vec3(0.0, 0.0, 0.4));
	platform_212->setShininess(100);
	platform_212->setFog(fog);
	platform_212->setReflectFactor(vec2(0.1, 0.1));
	platform_212->setEta(0.5);
	platform_212->setCubeMapUnit(3);
	platform_212->setSpeed(5);
	platform_212->postTrans(glm::translate(vec3(ORIGINX0,
		ORIGINY0 + 10.5,
		ORIGINZ0 - 65)));
	//platform_212->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_212->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_212->setShadowTex(shadow_map_id);
	platform_212->setType("Cube");
	platform_212->setName("Test Platform");
	stationary_list.push_back(platform_212);

	//stairs3
	Cube* platform_213 = new Cube(-20, 20, -1.5, 1.5, -5, 5);
	//platform_01->setSpeed(5); 
	platform_213->setKd(vec3(0.0, 0.6, 0.9));
	platform_213->setKa(vec3(0.0, 0.0, 0.3));
	platform_213->setKs(vec3(0.0, 0.0, 0.4));
	platform_213->setShininess(100);
	platform_213->setFog(fog);
	platform_213->setReflectFactor(vec2(0.1, 0.1));
	platform_213->setEta(0.5);
	platform_213->setCubeMapUnit(3);
	platform_213->setSpeed(5);
	platform_213->postTrans(glm::translate(vec3(ORIGINX0,
		ORIGINY0 + 7,
		ORIGINZ0 - 75)));
	//platform_213->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0)));
	platform_213->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_213->setShadowTex(shadow_map_id);
	platform_213->setType("Cube");
	platform_213->setName("Test Platform");
	stationary_list.push_back(platform_213);




	//rampart0
	Cube* platform_214 = new Cube(-PERIMETER_WALL_RADIUS, PERIMETER_WALL_RADIUS, -0.5, 0.5, -3, 3);
	//platform_01->setSpeed(5); 
	platform_214->setKd(vec3(0.0, 0.6, 0.9));
	platform_214->setKa(vec3(0.0, 0.0, 0.3));
	platform_214->setKs(vec3(0.0, 0.0, 0.4));
	platform_214->setShininess(100);
	platform_214->setFog(fog);
	platform_214->setReflectFactor(vec2(0.1, 0.1));
	platform_214->setEta(0.5);
	platform_214->setCubeMapUnit(3);
	platform_214->setSpeed(5);
	platform_214->postTrans(glm::translate(vec3(ORIGINX0,
		ORIGINY0 + 20,
		ORIGINZ0 - PERIMETER_WALL_RADIUS - 2)));
	//platform_214->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_214->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_214->setShadowTex(shadow_map_id);
	platform_214->setType("Cube");
	platform_214->setName("Test Platform");
	stationary_list.push_back(platform_214);

	//rampart1
	Cube* platform_215 = new Cube(-PERIMETER_WALL_RADIUS, PERIMETER_WALL_RADIUS, -0.5, 0.5, -3, 3);
	//platform_01->setSpeed(5); 
	platform_215->setKd(vec3(0.0, 0.6, 0.9));
	platform_215->setKa(vec3(0.0, 0.0, 0.3));
	platform_215->setKs(vec3(0.0, 0.0, 0.4));
	platform_215->setShininess(100);
	platform_215->setFog(fog);
	platform_215->setReflectFactor(vec2(0.1, 0.1));
	platform_215->setEta(0.5);
	platform_215->setCubeMapUnit(3);
	platform_215->setSpeed(5);
	platform_215->postTrans(glm::translate(vec3(ORIGINX0,
		ORIGINY0 + 20,
		ORIGINZ0 + PERIMETER_WALL_RADIUS + 2)));
	//platform_215->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_215->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_215->setShadowTex(shadow_map_id);
	platform_215->setType("Cube");
	platform_215->setName("Test Platform");
	stationary_list.push_back(platform_215);

	//rampart2
	Cube* platform_216 = new Cube(-3, 3, -0.5, 0.5, -PERIMETER_WALL_RADIUS, PERIMETER_WALL_RADIUS);
	//platform_01->setSpeed(5); 
	platform_216->setKd(vec3(0.0, 0.6, 0.9));
	platform_216->setKa(vec3(0.0, 0.0, 0.3));
	platform_216->setKs(vec3(0.0, 0.0, 0.4));
	platform_216->setShininess(100);
	platform_216->setFog(fog);
	platform_216->setReflectFactor(vec2(0.1, 0.1));
	platform_216->setEta(0.5);
	platform_216->setCubeMapUnit(3);
	platform_216->setSpeed(5);
	platform_216->postTrans(glm::translate(vec3(ORIGINX0 + PERIMETER_WALL_RADIUS + 2,
		ORIGINY0 + 20,
		ORIGINZ0)));
	//platform_216->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_216->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_216->setShadowTex(shadow_map_id);
	platform_216->setType("Cube");
	platform_216->setName("Test Platform");
	stationary_list.push_back(platform_216);

	//rampart3
	Cube* platform_217 = new Cube(-3, 3, -0.5, 0.5, -PERIMETER_WALL_RADIUS, PERIMETER_WALL_RADIUS);
	//platform_01->setSpeed(5); 
	platform_217->setKd(vec3(0.0, 0.6, 0.9));
	platform_217->setKa(vec3(0.0, 0.0, 0.3));
	platform_217->setKs(vec3(0.0, 0.0, 0.4));
	platform_217->setShininess(100);
	platform_217->setFog(fog);
	platform_217->setReflectFactor(vec2(0.1, 0.1));
	platform_217->setEta(0.5);
	platform_217->setCubeMapUnit(3);
	platform_217->setSpeed(5);
	platform_217->postTrans(glm::translate(vec3(ORIGINX0 - PERIMETER_WALL_RADIUS - 2,
		ORIGINY0 + 20,
		ORIGINZ0)));
	//platform_217->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_217->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_217->setShadowTex(shadow_map_id);
	platform_217->setType("Cube");
	platform_217->setName("Test Platform");
	stationary_list.push_back(platform_217);







	//Floor
	Cube* platform_300 = new Cube(-35, 35, -0.5, 0.5, -35, 35);
	//platform_01->setSpeed(5); 
	platform_300->setKd(vec3(1, 0.65, 0));
	platform_300->setKa(vec3(1, 0.65, 0));
	platform_300->setKs(vec3(1, 0.65, 0));
	platform_300->setShininess(100);
	platform_300->setFog(fog);
	platform_300->setReflectFactor(vec2(0.1, 0.1));
	platform_300->setEta(0.5);
	platform_300->setCubeMapUnit(3);
	platform_300->setSpeed(5);
	platform_300->postTrans(glm::translate(vec3(ORIGINX1,
		ORIGINY1 + 5,
		ORIGINZ1)));
	//platform_300->setAABB(AABB(vec3(-20, -0.5, -20), vec3(20, 0.5, 20)));
	platform_300->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_300->setShadowTex(shadow_map_id);
	platform_300->setType("Cube");
	platform_300->setName("Test Platform");
	// don't draw for now so we can peek inside
	stationary_list.push_back(platform_300);

	//wall0
	Cube* platform_301 = new Cube(-0.5, 0.5, -15, 15, -PERIMETER_WALL_RADIUS, PERIMETER_WALL_RADIUS);
	//platform_01->setSpeed(5);
	platform_301->setKd(vec3(0.0, 0.5, 0.0));
	platform_301->setKa(vec3(0.0, 0.0, 0.3));
	platform_301->setKs(vec3(0.0, 0.0, 0.4));
	platform_301->setShininess(100);
	platform_301->setFog(fog);
	platform_301->setReflectFactor(vec2(0.1, 0.1));
	platform_301->setEta(0.5);
	platform_301->setCubeMapUnit(3);
	platform_301->setSpeed(5);
	platform_301->postTrans(glm::translate(vec3(ORIGINX1 + PERIMETER_WALL_RADIUS,
		ORIGINY1 + PERIMETER_WALL_HEIGHT,
		ORIGINZ1)));
	platform_301->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_301->setShadowTex(shadow_map_id);
	//platform_301->setAABB(AABB(vec3(-0.5, -15, -5.0), vec3(1.5, 0.5, 5.0)));
	platform_301->setType("Cube");
	platform_301->setName("baset1");
	stationary_list.push_back(platform_301);

	//wall1
	Cube* platform_302 = new Cube(-0.5, 0.5, -15, 15, -PERIMETER_WALL_RADIUS, PERIMETER_WALL_RADIUS);
	//platform_01->setSpeed(5); 
	platform_302->setKd(vec3(0.0, 0.5, 0.0));
	platform_302->setKa(vec3(0.0, 0.0, 0.3));
	platform_302->setKs(vec3(0.0, 0.0, 0.4));
	platform_302->setShininess(100);
	platform_302->setFog(fog);
	platform_302->setReflectFactor(vec2(0.1, 0.1));
	platform_302->setEta(0.5);
	platform_302->setCubeMapUnit(3);
	platform_302->setSpeed(5);
	platform_302->postTrans(glm::translate(vec3(ORIGINX1 - PERIMETER_WALL_RADIUS,
		ORIGINY1 + PERIMETER_WALL_HEIGHT,
		ORIGINZ1)));
	//platform_302->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_302->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_302->setShadowTex(shadow_map_id);
	platform_302->setType("Cube");
	platform_302->setName("baset1");
	stationary_list.push_back(platform_302);

	//wall2
	Cube* platform_303 = new Cube(-PERIMETER_WALL_RADIUS, PERIMETER_WALL_RADIUS, -15, 15, -0.5, 0.5);
	//platform_01->setSpeed(5); 
	platform_303->setKd(vec3(0.0, 0.5, 0.0));
	platform_303->setKa(vec3(0.0, 0.0, 0.3));
	platform_303->setKs(vec3(0.0, 0.0, 0.4));
	platform_303->setShininess(100);
	platform_303->setFog(fog);
	platform_303->setReflectFactor(vec2(0.1, 0.1));
	platform_303->setEta(0.5);
	platform_303->setCubeMapUnit(3);
	platform_303->setSpeed(5);
	platform_303->postTrans(glm::translate(vec3(ORIGINX1,
		ORIGINY1 + PERIMETER_WALL_HEIGHT,
		ORIGINZ1 + PERIMETER_WALL_RADIUS)));
	//platform_303->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_303->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_303->setShadowTex(shadow_map_id);
	platform_303->setType("Cube");
	platform_303->setName("baset1");
	stationary_list.push_back(platform_303);

	//wall3
	Cube* platform_304 = new Cube(-PERIMETER_WALL_RADIUS, PERIMETER_WALL_RADIUS, -15, 15, -0.5, 0.5);
	//platform_01->setSpeed(5); 
	platform_304->setKd(vec3(0.0, 0.5, 0.0));
	platform_304->setKa(vec3(0.0, 0.0, 0.3));
	platform_304->setKs(vec3(0.0, 0.0, 0.4));
	platform_304->setShininess(100);
	platform_304->setFog(fog);
	platform_304->setReflectFactor(vec2(0.1, 0.1));
	platform_304->setEta(0.5);
	platform_304->setCubeMapUnit(3);
	platform_304->setSpeed(5);
	platform_304->postTrans(glm::translate(vec3(ORIGINX1,
		ORIGINY1 + PERIMETER_WALL_HEIGHT,
		ORIGINZ1 - PERIMETER_WALL_RADIUS)));
	//platform_304->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_304->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_304->setShadowTex(shadow_map_id);
	platform_304->setType("Cube");
	platform_304->setName("baset1");
	stationary_list.push_back(platform_304);

	// inside middle
	Cube* platform_305 = new Cube(-2, 2, -0.5, 0.5, -2, 2);
	//platform_01->setSpeed(5); 
	platform_305->setKd(vec3(0.0, 0.5, 0.0));
	platform_305->setKa(vec3(0.0, 0.0, 0.3));
	platform_305->setKs(vec3(0.0, 0.0, 0.4));
	platform_305->setShininess(100);
	platform_305->setFog(fog);
	platform_305->setReflectFactor(vec2(0.1, 0.1));
	platform_305->setEta(0.5);
	platform_305->setCubeMapUnit(3);
	platform_305->setSpeed(5);
	platform_305->postTrans(glm::translate(vec3(ORIGINX1,
		ORIGINY1 + CENTER_TOWERPLAT_HEIGHT,
		ORIGINZ1)));
	//platform_305->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_305->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_305->setShadowTex(shadow_map_id);
	platform_305->setType("Cube");
	platform_305->setName("Test Platform");
	stationary_list.push_back(platform_305);

	// tower in the middle
	Mesh* tower200 = new Mesh();
	tower200->LoadMesh("Model/2Tower_6_bone.dae", false);
	tower200->setShader(sdrCtl.getShader("basic_model"));
	tower200->setShadowTex(shadow_map_id);
	tower200->setAdjustM(glm::translate(vec3(0.0, 2.9, 0.0))*glm::rotate(mat4(1.0), 90.0f, vec3(-1.0, 0, 0))*glm::scale(vec3(0.6, 0.6, 0.6)));
	tower200->setModelM(glm::translate(vec3(ORIGINX1,
		ORIGINY1 + CENTER_TOWERPLAT_HEIGHT,
		ORIGINZ1)));
	tower200->setShininess(30);
	tower200->setFog(fog);
	tower_list.push_back(tower200);

	//force field effect
	force_field[1] = new ParticleAnimated(*(MOM.mother_of_force_field));
	force_field[1]->setFollow(tower200, vec3(0, 2.3, 0), 1, &View);
	force_field[1]->setStartTime(ct);



	//diag plat 0
	Cube* platform_306 = new Cube(-5, 5, -0.5, 0.5, -5, 5);
	//platform_01->setSpeed(5); 
	platform_306->setKd(vec3(0.0, 0.5, 0.0));
	platform_306->setKa(vec3(0.0, 0.0, 0.3));
	platform_306->setKs(vec3(0.0, 0.0, 0.4));
	platform_306->setShininess(100);
	platform_306->setFog(fog);
	platform_306->setReflectFactor(vec2(0.1, 0.1));
	platform_306->setEta(0.5);
	platform_306->setCubeMapUnit(3);
	platform_306->setSpeed(5);
	platform_306->postTrans(glm::translate(vec3(ORIGINX1 + CENTER_PLAT_SPACING,
		ORIGINY1 + CENTER_PLAT_HEIGHT,
		ORIGINZ1 + CENTER_PLAT_SPACING)));
	//platform_306->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_306->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_306->setShadowTex(shadow_map_id);
	platform_306->setType("Cube");
	platform_306->setName("Test Platform");
	stationary_list.push_back(platform_306);

	//diag plat 1
	Cube* platform_307 = new Cube(-5, 5, -0.5, 0.5, -5, 5);
	//platform_01->setSpeed(5); 
	platform_307->setKd(vec3(0.0, 0.5, 0.0));
	platform_307->setKa(vec3(0.0, 0.0, 0.3));
	platform_307->setKs(vec3(0.0, 0.0, 0.4));
	platform_307->setShininess(100);
	platform_307->setFog(fog);
	platform_307->setReflectFactor(vec2(0.1, 0.1));
	platform_307->setEta(0.5);
	platform_307->setCubeMapUnit(3);
	platform_307->setSpeed(5);
	platform_307->postTrans(glm::translate(vec3(ORIGINX1 - CENTER_PLAT_SPACING,
		ORIGINY1 + CENTER_PLAT_HEIGHT,
		ORIGINZ1 - CENTER_PLAT_SPACING)));
	//platform_307->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_307->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_307->setShadowTex(shadow_map_id);
	platform_307->setType("Cube");
	platform_307->setName("Test Platform");
	stationary_list.push_back(platform_307);

	//diag plat 2
	Cube* platform_308 = new Cube(-5, 5, -0.5, 0.5, -5, 5);
	//platform_01->setSpeed(5); 
	platform_308->setKd(vec3(0.0, 0.5, 0.0));
	platform_308->setKa(vec3(0.0, 0.0, 0.3));
	platform_308->setKs(vec3(0.0, 0.0, 0.4));
	platform_308->setShininess(100);
	platform_308->setFog(fog);
	platform_308->setReflectFactor(vec2(0.1, 0.1));
	platform_308->setEta(0.5);
	platform_308->setCubeMapUnit(3);
	platform_308->setSpeed(5);
	platform_308->postTrans(glm::translate(vec3(ORIGINX1 + CENTER_PLAT_SPACING,
		ORIGINY1 + CENTER_PLAT_HEIGHT,
		ORIGINZ1 - CENTER_PLAT_SPACING)));
	//platform_308->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_308->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_308->setShadowTex(shadow_map_id);
	platform_308->setType("Cube");
	platform_308->setName("Test Platform");
	stationary_list.push_back(platform_308);

	//diag plat 3
	Cube* platform_309 = new Cube(-5, 5, -0.5, 0.5, -5, 5);
	//platform_01->setSpeed(5); 
	platform_309->setKd(vec3(0.0, 0.5, 0.0));
	platform_309->setKa(vec3(0.0, 0.0, 0.3));
	platform_309->setKs(vec3(0.0, 0.0, 0.4));
	platform_309->setShininess(100);
	platform_309->setFog(fog);
	platform_309->setReflectFactor(vec2(0.1, 0.1));
	platform_309->setEta(0.5);
	platform_309->setCubeMapUnit(3);
	platform_309->setSpeed(5);
	platform_309->postTrans(glm::translate(vec3(ORIGINX1 - CENTER_PLAT_SPACING,
		ORIGINY1 + CENTER_PLAT_HEIGHT,
		ORIGINZ1 + CENTER_PLAT_SPACING)));
	//platform_309->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_309->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_309->setShadowTex(shadow_map_id);
	platform_309->setType("Cube");
	platform_309->setName("Test Platform");
	stationary_list.push_back(platform_309);

	//stairs0 top
	Cube* platform_310 = new Cube(-20, 20, -1.5, 1.5, -5, 5);
	//platform_01->setSpeed(5); 
	platform_310->setKd(vec3(0.0, 0.5, 0.0));
	platform_310->setKa(vec3(0.0, 0.0, 0.3));
	platform_310->setKs(vec3(0.0, 0.0, 0.4));
	platform_310->setShininess(100);
	platform_310->setFog(fog);
	platform_310->setReflectFactor(vec2(0.1, 0.1));
	platform_310->setEta(0.5);
	platform_310->setCubeMapUnit(3);
	platform_310->setSpeed(5);
	platform_310->postTrans(glm::translate(vec3(ORIGINX1,
		ORIGINY1 + 17.5,
		ORIGINZ1 + 45)));
	//platform_310->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_310->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_310->setShadowTex(shadow_map_id);
	platform_310->setType("Cube");
	platform_310->setName("Test Platform");
	stationary_list.push_back(platform_310);

	//stairs1
	Cube* platform_311 = new Cube(-20, 20, -1.5, 1.5, -5, 5);
	//platform_01->setSpeed(5); 
	platform_311->setKd(vec3(0.0, 0.5, 0.0));
	platform_311->setKa(vec3(0.0, 0.0, 0.3));
	platform_311->setKs(vec3(0.0, 0.0, 0.4));
	platform_311->setShininess(100);
	platform_311->setFog(fog);
	platform_311->setReflectFactor(vec2(0.1, 0.1));
	platform_311->setEta(0.5);
	platform_311->setCubeMapUnit(3);
	platform_311->setSpeed(5);
	platform_311->postTrans(glm::translate(vec3(ORIGINX1,
		ORIGINY1 + 14,
		ORIGINZ1 + 55)));
	//platform_311->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_311->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_311->setShadowTex(shadow_map_id);
	platform_311->setType("Cube");
	platform_311->setName("Test Platform");
	stationary_list.push_back(platform_311);

	//stairs2
	Cube* platform_312 = new Cube(-20, 20, -1.5, 1.5, -5, 5);
	//platform_01->setSpeed(5); 
	platform_312->setKd(vec3(0.0, 0.5, 0.0));
	platform_312->setKa(vec3(0.0, 0.0, 0.3));
	platform_312->setKs(vec3(0.0, 0.0, 0.4));
	platform_312->setShininess(100);
	platform_312->setFog(fog);
	platform_312->setReflectFactor(vec2(0.1, 0.1));
	platform_312->setEta(0.5);
	platform_312->setCubeMapUnit(3);
	platform_312->setSpeed(5);
	platform_312->postTrans(glm::translate(vec3(ORIGINX1,
		ORIGINY1 + 10.5,
		ORIGINZ1 + 65)));
	//platform_312->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_312->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_312->setShadowTex(shadow_map_id);
	platform_312->setType("Cube");
	platform_312->setName("Test Platform");
	stationary_list.push_back(platform_312);

	//stairs3
	Cube* platform_313 = new Cube(-20, 20, -1.5, 1.5, -5, 5);
	//platform_01->setSpeed(5); 
	platform_313->setKd(vec3(0.0, 0.5, 0.0));
	platform_313->setKa(vec3(0.0, 0.0, 0.3));
	platform_313->setKs(vec3(0.0, 0.0, 0.4));
	platform_313->setShininess(100);
	platform_313->setFog(fog);
	platform_313->setReflectFactor(vec2(0.1, 0.1));
	platform_313->setEta(0.5);
	platform_313->setCubeMapUnit(3);
	platform_313->setSpeed(5);
	platform_313->postTrans(glm::translate(vec3(ORIGINX1,
		ORIGINY1 + 7,
		ORIGINZ1 + 75)));
	//platform_313->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0)));
	platform_313->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_313->setShadowTex(shadow_map_id);
	platform_313->setType("Cube");
	platform_313->setName("Test Platform");
	stationary_list.push_back(platform_313);


	//rampart0
	Cube* platform_314 = new Cube(-PERIMETER_WALL_RADIUS, PERIMETER_WALL_RADIUS, -0.5, 0.5, -3, 3);
	//platform_01->setSpeed(5); 
	platform_314->setKd(vec3(0.0, 0.5, 0.0));
	platform_314->setKa(vec3(0.0, 0.0, 0.3));
	platform_314->setKs(vec3(0.0, 0.0, 0.4));
	platform_314->setShininess(100);
	platform_314->setFog(fog);
	platform_314->setReflectFactor(vec2(0.1, 0.1));
	platform_314->setEta(0.5);
	platform_314->setCubeMapUnit(3);
	platform_314->setSpeed(5);
	platform_314->postTrans(glm::translate(vec3(ORIGINX1,
		ORIGINY1 + 20,
		ORIGINZ1 - PERIMETER_WALL_RADIUS - 2)));
	//platform_314->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_314->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_314->setShadowTex(shadow_map_id);
	platform_314->setType("Cube");
	platform_314->setName("Test Platform");
	stationary_list.push_back(platform_314);

	//rampart1
	Cube* platform_315 = new Cube(-PERIMETER_WALL_RADIUS, PERIMETER_WALL_RADIUS, -0.5, 0.5, -3, 3);
	//platform_01->setSpeed(5); 
	platform_315->setKd(vec3(0.0, 0.5, 0.0));
	platform_315->setKa(vec3(0.0, 0.0, 0.3));
	platform_315->setKs(vec3(0.0, 0.0, 0.4));
	platform_315->setShininess(100);
	platform_315->setFog(fog);
	platform_315->setReflectFactor(vec2(0.1, 0.1));
	platform_315->setEta(0.5);
	platform_315->setCubeMapUnit(3);
	platform_315->setSpeed(5);
	platform_315->postTrans(glm::translate(vec3(ORIGINX1,
		ORIGINY1 + 20,
		ORIGINZ1 + PERIMETER_WALL_RADIUS + 2)));
	//platform_315->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_315->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_315->setShadowTex(shadow_map_id);
	platform_315->setType("Cube");
	platform_315->setName("Test Platform");
	stationary_list.push_back(platform_315);

	//rampart2
	Cube* platform_316 = new Cube(-3, 3, -0.5, 0.5, -PERIMETER_WALL_RADIUS, PERIMETER_WALL_RADIUS);
	//platform_01->setSpeed(5); 
	platform_316->setKd(vec3(0.0, 0.5, 0.0));
	platform_316->setKa(vec3(0.0, 0.0, 0.3));
	platform_316->setKs(vec3(0.0, 0.0, 0.4));
	platform_316->setShininess(100);
	platform_316->setFog(fog);
	platform_316->setReflectFactor(vec2(0.1, 0.1));
	platform_316->setEta(0.5);
	platform_316->setCubeMapUnit(3);
	platform_316->setSpeed(5);
	platform_316->postTrans(glm::translate(vec3(ORIGINX1 + PERIMETER_WALL_RADIUS + 2,
		ORIGINY1 + 20,
		ORIGINZ1)));
	//platform_316->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_316->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_316->setShadowTex(shadow_map_id);
	platform_316->setType("Cube");
	platform_316->setName("Test Platform");
	stationary_list.push_back(platform_316);

	//rampart3
	Cube* platform_317 = new Cube(-3, 3, -0.5, 0.5, -PERIMETER_WALL_RADIUS, PERIMETER_WALL_RADIUS);
	//platform_01->setSpeed(5); 
	platform_317->setKd(vec3(0.0, 0.5, 0.0));
	platform_317->setKa(vec3(0.0, 0.0, 0.3));
	platform_317->setKs(vec3(0.0, 0.0, 0.4));
	platform_317->setShininess(100);
	platform_317->setFog(fog);
	platform_317->setReflectFactor(vec2(0.1, 0.1));
	platform_317->setEta(0.5);
	platform_317->setCubeMapUnit(3);
	platform_317->setSpeed(5);
	platform_317->postTrans(glm::translate(vec3(ORIGINX1 - PERIMETER_WALL_RADIUS - 2,
		ORIGINY1 + 20,
		ORIGINZ1)));
	//platform_317->setAABB(AABB(vec3(-1.5, -0.5, -5.0), vec3(1.5, 0.5, 5.0))); 
	platform_317->setShader(sdrCtl.getShader("basic_reflect_refract"));
	platform_317->setShadowTex(shadow_map_id);
	platform_317->setType("Cube");
	platform_317->setName("Test Platform");
	stationary_list.push_back(platform_317);



	for (uint i = 0; i < stationary_list.size(); i++)
	{
		stationary_list[i]->setAliveModelM(stationary_list[i]->getModelM());
	}







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
	menuMusic->setVolume(0.5);
	menuMusic->Play();

	gameMusic = new Music(mySoundSystem, "Music/background_music.mp3", false);
	gameMusic->setLoopCount(-1);
	gameMusic->setVolume(0.9);

	gameThunder = new Music(mySoundSystem, "Sound/thunder.wav", false);
	gameThunder->setLoopCount(-1);
	gameThunder->setVolume(0.2);

	gameThunder2 = new Sound(mySoundSystem, "Sound/thunder.wav", false);
	//gameThunder2->setLoopCount(-1);
	gameThunder2->setVolume(0.2);
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
		if (i == SoundThrow || i == SoundSlap){
			testSound[i]->setVolume(0.75);
			testSound[i]->setVolume(0.75);
		}
		else if (i == SoundJumpWav || i == SoundJumpOgg){
			testSound[i]->setVolume(0.25);
		}
		else if (i == SoundCount){
			testSound[i]->setVolume(0.15);
		}
		else{
			testSound[i]->setVolume(0.5);
		}
		sound_list.push_back(testSound[i]);
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
	shadow->Bind(GL_TEXTURE0 + shadow_map_id);

	render_tex = new Texture(GL_TEXTURE_2D);
	render_tex->LoadRenderTexture(Window::width, Window::height);
	render_tex->Bind(GL_TEXTURE0 + render_tex_id);
	
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

void initializeMOM(){
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

	MOM.mother_of_p_anim = new ParticleAnimated();
	MOM.mother_of_p_anim->Init("img/sprite_sheets/effect_002.png", "PNG");
	MOM.mother_of_p_anim->setShader(sdrCtl.getShader("billboard_anim"));
	MOM.mother_of_p_anim->setPosition(vec3(0.0f, 0.0f, 0.0f));
	MOM.mother_of_p_anim->setWidth(2.0f);
	MOM.mother_of_p_anim->setHeight(2.0f);
	MOM.mother_of_p_anim->setNumColumn(5);
	MOM.mother_of_p_anim->setNumRow(4);
	MOM.mother_of_p_anim->setValidFrame(0, 19);
	MOM.mother_of_p_anim->setDuration(1);
	MOM.mother_of_p_anim->setFog(fog);
	MOM.mother_of_p_anim->Bind();

	MOM.mother_of_lightning = new ParticleAnimated();
	MOM.mother_of_lightning->Init("img/sprite_sheets/lightning.png", "PNG");
	MOM.mother_of_lightning->setShader(sdrCtl.getShader("billboard_anim"));
	MOM.mother_of_lightning->setPosition(vec3(0.0f, 0.0f, 0.0f));
	MOM.mother_of_lightning->setWidth(2.0f);
	MOM.mother_of_lightning->setHeight(2.0f);
	MOM.mother_of_lightning->setNumColumn(10);
	MOM.mother_of_lightning->setNumRow(1);
	MOM.mother_of_lightning->setValidFrame(0, 9);
	MOM.mother_of_lightning->setDuration(1);
	MOM.mother_of_lightning->setType(0);
	MOM.mother_of_lightning->setFog(fog);
	MOM.mother_of_lightning->Bind();

	MOM.mother_of_tower_shoot_1 = new ParticleAnimated();
	MOM.mother_of_tower_shoot_1->Init("img/sprite_sheets/light_003.png", "PNG");
	MOM.mother_of_tower_shoot_1->setShader(sdrCtl.getShader("billboard_anim"));
	MOM.mother_of_tower_shoot_1->setPosition(vec3(0.0f, 0.0f, 0.0f));
	MOM.mother_of_tower_shoot_1->setWidth(4.0f);
	MOM.mother_of_tower_shoot_1->setHeight(4.0f);
	MOM.mother_of_tower_shoot_1->setNumColumn(5);
	MOM.mother_of_tower_shoot_1->setNumRow(6);
	MOM.mother_of_tower_shoot_1->setValidFrame(0, 29);
	MOM.mother_of_tower_shoot_1->setDuration(0.75);
	MOM.mother_of_tower_shoot_1->setType(1);
	MOM.mother_of_tower_shoot_1->setSampleCount(3, 3);
	MOM.mother_of_tower_shoot_1->setSampleDist(0.002f, 0.002f);
	MOM.mother_of_tower_shoot_1->setTransparency(1.0);
	MOM.mother_of_tower_shoot_1->setBlurStrength(1.0);
	MOM.mother_of_tower_shoot_1->setFog(fog);
	MOM.mother_of_tower_shoot_1->Bind();

	MOM.mother_of_tower_damage_1 = new ParticleAnimated();
	MOM.mother_of_tower_damage_1->Init("img/sprite_sheets/fire_003.png", "PNG");
	MOM.mother_of_tower_damage_1->setShader(sdrCtl.getShader("billboard_anim"));
	MOM.mother_of_tower_damage_1->setPosition(vec3(0.0f, 0.0f, 0.0f));
	MOM.mother_of_tower_damage_1->setWidth(4.0f);
	MOM.mother_of_tower_damage_1->setHeight(4.0f);
	MOM.mother_of_tower_damage_1->setNumColumn(5);
	MOM.mother_of_tower_damage_1->setNumRow(8);
	MOM.mother_of_tower_damage_1->setValidFrame(20, 39);
	MOM.mother_of_tower_damage_1->setDuration(1);
	MOM.mother_of_tower_damage_1->setType(0);
	MOM.mother_of_tower_damage_1->setSampleCount(3, 3);
	MOM.mother_of_tower_damage_1->setSampleDist(0.002f, 0.002f);
	MOM.mother_of_tower_damage_1->setTransparency(0.9f);
	MOM.mother_of_tower_damage_1->setBlurStrength(1.0);
	MOM.mother_of_tower_damage_1->setFog(fog);
	MOM.mother_of_tower_damage_1->Bind();

	MOM.mother_of_tower_explosion_1 = new ParticleAnimated();
	MOM.mother_of_tower_explosion_1->Init("img/sprite_sheets/light_004.png", "PNG");
	MOM.mother_of_tower_explosion_1->setShader(sdrCtl.getShader("billboard_anim"));
	MOM.mother_of_tower_explosion_1->setPosition(vec3(0.0f, 0.0f, 0.0f));
	MOM.mother_of_tower_explosion_1->setWidth(14.0f);
	MOM.mother_of_tower_explosion_1->setHeight(14.0f);
	MOM.mother_of_tower_explosion_1->setNumColumn(5);
	MOM.mother_of_tower_explosion_1->setNumRow(5);
	MOM.mother_of_tower_explosion_1->setValidFrame(0, 24);
	MOM.mother_of_tower_explosion_1->setDuration(0.8);
	MOM.mother_of_tower_explosion_1->setType(0);
	MOM.mother_of_tower_explosion_1->setSampleCount(3, 3);
	MOM.mother_of_tower_explosion_1->setSampleDist(0.002f, 0.002f);
	MOM.mother_of_tower_explosion_1->setTransparency(0.9f);
	MOM.mother_of_tower_explosion_1->setBlurStrength(0.3f);
	MOM.mother_of_tower_explosion_1->setFog(fog);
	MOM.mother_of_tower_explosion_1->Bind();

	MOM.mother_of_health_potion = new ParticleAnimated();
	MOM.mother_of_health_potion->Init("img/sprite_sheets/heal_003.png", "PNG");
	MOM.mother_of_health_potion->setShader(sdrCtl.getShader("billboard_anim"));
	MOM.mother_of_health_potion->setPosition(vec3(0.0f, 0.0f, 0.0f));
	MOM.mother_of_health_potion->setWidth(4.0f);
	MOM.mother_of_health_potion->setHeight(4.0f);
	MOM.mother_of_health_potion->setNumColumn(5);
	MOM.mother_of_health_potion->setNumRow(4);
	MOM.mother_of_health_potion->setValidFrame(0, 19);
	MOM.mother_of_health_potion->setDuration(0.5);
	MOM.mother_of_health_potion->setType(0);
	//MOM.mother_of_health_potion->setSampleCount(3, 3);
	//MOM.mother_of_health_potion->setSampleDist(0.002, 0.002);
	MOM.mother_of_health_potion->setTransparency(1.0);
	//MOM.mother_of_health_potion->setBlurStrength(0.3);
	MOM.mother_of_health_potion->setFog(fog);
	MOM.mother_of_health_potion->Bind();

	MOM.mother_of_red_arrow = new ParticleAnimated();
	MOM.mother_of_red_arrow->Init("img/enemySign.png", "PNG");
	MOM.mother_of_red_arrow->setShader(sdrCtl.getShader("billboard_anim"));
	MOM.mother_of_red_arrow->setPosition(vec3(0.0f, 0.0f, 0.0f));
	MOM.mother_of_red_arrow->setWidth(2.0f);
	MOM.mother_of_red_arrow->setHeight(2.0f);
	MOM.mother_of_red_arrow->setNumColumn(1);
	MOM.mother_of_red_arrow->setNumRow(1);
	MOM.mother_of_red_arrow->setValidFrame(0, 0);
	MOM.mother_of_red_arrow->setDuration(1.0);
	MOM.mother_of_red_arrow->setType(1);
	//MOM.mother_of_red_arrow->setSampleCount(5, 5);
	//MOM.mother_of_red_arrow->setSampleDist(0.005, 0.005);
	MOM.mother_of_red_arrow->setTransparency(0.9f);
	//MOM.mother_of_red_arrow->setBlurStrength(1.0);
	MOM.mother_of_red_arrow->setFog(emptyFog);
	MOM.mother_of_red_arrow->Bind();

	MOM.mother_of_green_arrow = new ParticleAnimated();
	MOM.mother_of_green_arrow->Init("img/friendSign.png", "PNG");
	MOM.mother_of_green_arrow->setShader(sdrCtl.getShader("billboard_anim"));
	MOM.mother_of_green_arrow->setPosition(vec3(0.0f, 0.0f, 0.0f));
	MOM.mother_of_green_arrow->setWidth(2.0f);
	MOM.mother_of_green_arrow->setHeight(2.0f);
	MOM.mother_of_green_arrow->setNumColumn(1);
	MOM.mother_of_green_arrow->setNumRow(1);
	MOM.mother_of_green_arrow->setValidFrame(0, 0);
	MOM.mother_of_green_arrow->setDuration(1.0);
	MOM.mother_of_green_arrow->setType(1);
	//MOM.mother_of_green_arrow->setSampleCount(5, 5);
	//MOM.mother_of_green_arrow->setSampleDist(0.005, 0.005);
	MOM.mother_of_green_arrow->setTransparency(0.9f);
	//MOM.mother_of_green_arrow->setBlurStrength(1.0);
	MOM.mother_of_green_arrow->setFog(emptyFog);
	MOM.mother_of_green_arrow->Bind();

	MOM.mother_of_tramp_effect = new ParticleAnimated();
	MOM.mother_of_tramp_effect->Init("img/sprite_sheets/wind_003.png", "PNG");
	MOM.mother_of_tramp_effect->setShader(sdrCtl.getShader("billboard_anim"));
	MOM.mother_of_tramp_effect->setPosition(vec3(0.0f, 1.3f, 0.0f));
	MOM.mother_of_tramp_effect->setWidth(4.0f);
	MOM.mother_of_tramp_effect->setHeight(4.0f);
	MOM.mother_of_tramp_effect->setNumColumn(5);
	MOM.mother_of_tramp_effect->setNumRow(6);
	MOM.mother_of_tramp_effect->setValidFrame(0, 29);
	MOM.mother_of_tramp_effect->setDuration(1.0);
	MOM.mother_of_tramp_effect->setType(1);
	MOM.mother_of_tramp_effect->setSampleCount(3, 3);
	MOM.mother_of_tramp_effect->setSampleDist(0.001f, 0.001f);
	MOM.mother_of_tramp_effect->setTransparency(0.9f);
	MOM.mother_of_tramp_effect->setBlurStrength(0.3f);
	MOM.mother_of_tramp_effect->setFog(fog);
	MOM.mother_of_tramp_effect->Bind();

	MOM.mother_of_portal_effect = new ParticleAnimated();
	MOM.mother_of_portal_effect->Init("img/sprite_sheets/darkness_001.png", "PNG");
	MOM.mother_of_portal_effect->setShader(sdrCtl.getShader("billboard_anim"));
	MOM.mother_of_portal_effect->setPosition(vec3(0.0f, 1.3f, 0.0f));
	MOM.mother_of_portal_effect->setWidth(4.0f);
	MOM.mother_of_portal_effect->setHeight(4.0f);
	MOM.mother_of_portal_effect->setNumColumn(5);
	MOM.mother_of_portal_effect->setNumRow(6);
	MOM.mother_of_portal_effect->setValidFrame(0, 29);
	MOM.mother_of_portal_effect->setDuration(1.0);
	MOM.mother_of_portal_effect->setType(1);
	MOM.mother_of_portal_effect->setSampleCount(3, 3);
	MOM.mother_of_portal_effect->setSampleDist(0.001f, 0.001f);
	MOM.mother_of_portal_effect->setTransparency(0.8f);
	MOM.mother_of_portal_effect->setBlurStrength(0.5);
	MOM.mother_of_portal_effect->setFog(fog);
	MOM.mother_of_portal_effect->Bind();

	MOM.mother_of_orange_mark = new ParticleAnimated();
	MOM.mother_of_orange_mark->Init("img/sprite_sheets/cast_006.png", "PNG");
	MOM.mother_of_orange_mark->setShader(sdrCtl.getShader("billboard_anim"));
	MOM.mother_of_orange_mark->setPosition(vec3(0.0f, 5.3f, 0.0f));
	MOM.mother_of_orange_mark->setWidth(4.0f);
	MOM.mother_of_orange_mark->setHeight(4.0f);
	MOM.mother_of_orange_mark->setNumColumn(5);
	MOM.mother_of_orange_mark->setNumRow(4);
	MOM.mother_of_orange_mark->setValidFrame(0, 19);
	MOM.mother_of_orange_mark->setDuration(1.0);
	MOM.mother_of_orange_mark->setType(1);
	MOM.mother_of_orange_mark->setSampleCount(3, 3);
	MOM.mother_of_orange_mark->setSampleDist(0.001f, 0.001f);
	MOM.mother_of_orange_mark->setTransparency(0.8f);
	MOM.mother_of_orange_mark->setBlurStrength(0.5);
	MOM.mother_of_orange_mark->setFog(emptyFog);
	MOM.mother_of_orange_mark->Bind();

	MOM.mother_of_blue_mark = new ParticleAnimated();
	MOM.mother_of_blue_mark->Init("img/sprite_sheets/cast_004.png", "PNG");
	MOM.mother_of_blue_mark->setShader(sdrCtl.getShader("billboard_anim"));
	MOM.mother_of_blue_mark->setPosition(vec3(0.0f, 5.3f, 0.0f));
	MOM.mother_of_blue_mark->setWidth(4.0f);
	MOM.mother_of_blue_mark->setHeight(4.0f);
	MOM.mother_of_blue_mark->setNumColumn(5);
	MOM.mother_of_blue_mark->setNumRow(4);
	MOM.mother_of_blue_mark->setValidFrame(0, 19);
	MOM.mother_of_blue_mark->setDuration(1.0);
	MOM.mother_of_blue_mark->setType(1);
	MOM.mother_of_blue_mark->setSampleCount(3, 3);
	MOM.mother_of_blue_mark->setSampleDist(0.001f, 0.001f);
	MOM.mother_of_blue_mark->setTransparency(0.8f);
	MOM.mother_of_blue_mark->setBlurStrength(0.5);
	MOM.mother_of_blue_mark->setFog(emptyFog);
	MOM.mother_of_blue_mark->Bind();

	MOM.mother_of_force_field = new ParticleAnimated();
	MOM.mother_of_force_field->Init("img/sprite_sheets/magic_007.png", "PNG");
	MOM.mother_of_force_field->setShader(sdrCtl.getShader("billboard_anim"));
	MOM.mother_of_force_field->setPosition(vec3(0.0f, 1.3f, 0.0f));
	MOM.mother_of_force_field->setWidth(8.0f);
	MOM.mother_of_force_field->setHeight(8.0f);
	MOM.mother_of_force_field->setNumColumn(5);
	MOM.mother_of_force_field->setNumRow(4);
	MOM.mother_of_force_field->setValidFrame(0, 19);
	MOM.mother_of_force_field->setDuration(1.0);
	MOM.mother_of_force_field->setType(1);
	MOM.mother_of_force_field->setSampleCount(3, 3);
	MOM.mother_of_force_field->setSampleDist(0.001f, 0.001f);
	MOM.mother_of_force_field->setTransparency(0.8f);
	MOM.mother_of_force_field->setBlurStrength(0.5);
	MOM.mother_of_force_field->setFog(fog);
	MOM.mother_of_force_field->Bind();
}

void initializePlayerMark(int main_player_ID){
	LARGE_INTEGER ct;
	QueryPerformanceCounter(&ct);
	float up = 3.0;
	if (main_player_ID % 2){
		for (uint i = 0; i < player_list.size(); i++){
			if (i == main_player_ID)
				continue;
			if (i % 2){
				ParticleAnimated* playerMark = new ParticleAnimated(*(MOM.mother_of_green_arrow));
				playerMark->setFollow(player_list[i], vec3(0, up, 0), 0.0f, &View);
				playerMark->setStartTime(ct);
				panim_list.push_back(playerMark);
			}
			else{
				ParticleAnimated* playerMark = new ParticleAnimated(*(MOM.mother_of_red_arrow));
				playerMark->setFollow(player_list[i], vec3(0, up, 0), 0.0f, &View);
				playerMark->setStartTime(ct);
				panim_list.push_back(playerMark);
			}
		}
	}
	else{
		for (uint i = 0; i < player_list.size(); i++){
			if (i == main_player_ID)
				continue;
			if (i % 2){
				ParticleAnimated* playerMark = new ParticleAnimated(*(MOM.mother_of_red_arrow));
				playerMark->setFollow(player_list[i], vec3(0, up, 0), 0.0f, &View);
				playerMark->setStartTime(ct);
				panim_list.push_back(playerMark);
			}
			else{
				ParticleAnimated* playerMark = new ParticleAnimated(*(MOM.mother_of_green_arrow));
				playerMark->setFollow(player_list[i], vec3(0, up, 0), 0.0f, &View);
				playerMark->setStartTime(ct);
				panim_list.push_back(playerMark);
			}
		}
	}
}
