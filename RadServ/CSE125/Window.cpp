#define _USE_MATH_DEFINES
#include <string>
#include <iostream>
#include <time.h>
#include <boost/asio.hpp>
#include "Server.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Window.h"
#include <time.h>
#include "Object.h"
#include "VAO.h"
#include "glslprogram.h"
#include "Cube.h"
#include "ShaderController.h"
#include "Ground.h"
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
#include <AL/al.h>
#include <AL/alc.h>
#include <sys/types.h>
#include <sys/stat.h>
using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::mat3;
using glm::quat;
using namespace std;
Ground* ground;
float cam_sp = 0.01;
string configBuf;
int counter = 0;
std::vector <pair<string, mat4>>* sendVec = new vector<pair<string, mat4>>;
std::vector <pair<string, mat4>>* recvVec = new vector<pair<string, mat4>>;
Scene* scene;
boost::asio::io_service io_service;
tcp_server* server;
int cam_rot = 0;
int playerID = -1;
int numOfVecs = 4;
int keyState = 0;
bool player1shoot, player2shoot, player3shoot, player4shoot;

void handle_mouse_state(int pid, int mouseState){
	if (mouseState & 1){
		scene->basicAttack(pid);
	}
	else if (mouseState & 1 << 1){
		std::cout << "projectile attack from client" << std::endl;
		if (pid == 0)
			player1shoot = true;
		else if (pid == 1)
			player2shoot = true;
		else if (pid == 2)
			player3shoot = true;
		else if (pid == 3)
			player4shoot = true;
		//std::cout << player1shoot << player2shoot << player3shoot << player4shoot << std::endl;
		scene->projectileAttack(pid, &(*recvVec)[playerID * 4 + 2].second);
	}
}
void handle_key_state(int pid, int keyState){
	if (keyState & 1){ //'a'
		//cout << "move left" << endl;
		scene->setHMove(pid, -1);
	}
	else{
		scene->cancelHMove(pid, -1);
	}
	if (keyState & 1 << 1){ //'d'
		//cout << "move right" << endl;
		scene->setHMove(pid, 1);
	}
	else{
		scene->cancelHMove(pid, 1);
	}
	if (keyState & 1 << 2){ //'w'
		//cout << "move up" << endl;
		scene->setVMove(pid, 1);
	}
	else{
		scene->cancelVMove(pid, 1);
	}
	if (keyState & 1 << 3){ //'s'
		//cout << "move down" << endl;
		scene->setVMove(pid, -1);
	}
	else{
		scene->cancelVMove(pid, -1);
	}
	if (keyState & 1 << 4){ //' '
		//cout << "jump" << endl;
		scene->jump(pid);
	}
}
void handle_cam_rot(int pid, float cam_rot){
	scene->pushRot(pid, -cam_sp*cam_rot);
	cam_rot = 0; // possibly a problem
}
void handle_cam_mat(int pid, mat4 camM)
{
	scene->setCamM(pid, camM);
}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // open an OpenGL context with double buffering, RGB colors, and depth buffering
	glutInitWindowSize(10, 10); // set initial window size
	glutCreateWindow("CSE 125 - Group 4 (RadioactiveChipmunks)");
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "Error initializing GLEW: %s\n",
			glewGetErrorString(err));
		system("pause");
	}
	scene = new Scene();
	scene->setGravity(vec3(0, -9.8, 0));

	sendVec->push_back(std::make_pair("", mat4(0.0f)));
	sendVec->push_back(std::make_pair("", mat4(0.0f)));
	sendVec->push_back(std::make_pair("", mat4(0.0f)));
	sendVec->push_back(std::make_pair("", mat4(0.0f)));

	recvVec->push_back(std::make_pair("", mat4(0.0f)));
	recvVec->push_back(std::make_pair("", mat4(0.0f)));
	recvVec->push_back(std::make_pair("", mat4(0.0f)));
	recvVec->push_back(std::make_pair("", mat4(0.0f)));

	recvVec->push_back(std::make_pair("", mat4(0.0f)));
	recvVec->push_back(std::make_pair("", mat4(0.0f)));
	recvVec->push_back(std::make_pair("", mat4(0.0f)));
	recvVec->push_back(std::make_pair("", mat4(0.0f)));

	recvVec->push_back(std::make_pair("", mat4(0.0f)));
	recvVec->push_back(std::make_pair("", mat4(0.0f)));
	recvVec->push_back(std::make_pair("", mat4(0.0f)));
	recvVec->push_back(std::make_pair("", mat4(0.0f)));

	recvVec->push_back(std::make_pair("", mat4(0.0f)));
	recvVec->push_back(std::make_pair("", mat4(0.0f)));
	recvVec->push_back(std::make_pair("", mat4(0.0f)));
	recvVec->push_back(std::make_pair("", mat4(0.0f)));

	try
	{
		tcp::resolver resolver(io_service);
		tcp::resolver::query query(tcp::v4(), "localhost", "13"); // does nothing for the moment
		tcp::resolver::iterator itr = resolver.resolve(query);
		tcp::endpoint endpoint = *itr;
		server = new tcp_server(io_service, endpoint);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	LARGE_INTEGER freq, last, current;
	double diff;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&last);
	string p0, p1, p2, p3;

	while (true){
		QueryPerformanceCounter(&current);
		diff = (double)(current.QuadPart - last.QuadPart) / (double)freq.QuadPart;
		last = current;
		recvVec = server->getState();
		io_service.poll();
		//std::cout << "recvVec key string:" << recvVec->front().first << std::endl; 
		player1shoot = false;
		player2shoot = false;
		player3shoot = false;
		player4shoot = false;
		if (!strcmp((*recvVec)[0].first.c_str(), ""))
		{
			playerID = atoi((*recvVec)[0].first.c_str());
			handle_key_state(playerID, (int)(*recvVec)[playerID * 4].second[0][0]);
			handle_mouse_state(playerID, (int)(*recvVec)[playerID * 4 + 1].second[0][0]);
			handle_cam_mat(playerID, (*recvVec)[playerID * 4 + 2].second);
			handle_cam_rot(playerID, (int)(*recvVec)[playerID * 4 + 3].second[0][0]);
		}
		// VECTOR INDICES NEED UPDATE FOR MOUSE
		if (!strcmp((*recvVec)[numOfVecs - 1].first.c_str(), ""))
		{
			playerID = atoi((*recvVec)[numOfVecs - 1].first.c_str());
			handle_key_state(playerID, (int)(*recvVec)[playerID * 4].second[0][0]);
			handle_mouse_state(playerID, (int)(*recvVec)[playerID * 4 + 1].second[0][0]);
			handle_cam_mat(playerID, (*recvVec)[playerID * 4 + 2].second);
			handle_cam_rot(playerID, (int)(*recvVec)[playerID * 4 + 3].second[0][0]);
		}
		if (!strcmp((*recvVec)[numOfVecs * 2 - 1].first.c_str(), ""))
		{
			playerID = atoi((*recvVec)[numOfVecs * 2 - 1].first.c_str());
			handle_key_state(playerID, (int)(*recvVec)[playerID * 4].second[0][0]);
			handle_mouse_state(playerID, (int)(*recvVec)[playerID * 4 + 1].second[0][0]);
			handle_cam_mat(playerID, (*recvVec)[playerID * 4 + 2].second);
			handle_cam_rot(playerID, (int)(*recvVec)[playerID * 4 + 3].second[0][0]);
		}
		if (!strcmp((*recvVec)[numOfVecs * 3 - 1].first.c_str(), ""))
		{
			playerID = atoi((*recvVec)[numOfVecs * 3 - 1].first.c_str());
			handle_key_state(playerID, (int)(*recvVec)[playerID * 4].second[0][0]);
			handle_mouse_state(playerID, (int)(*recvVec)[playerID * 4 + 1].second[0][0]);
			handle_cam_mat(playerID, (*recvVec)[playerID * 4 + 2].second);
			handle_cam_rot(playerID, (int)(*recvVec)[playerID * 4 + 3].second[0][0]);
		}
		scene->simulate(diff, 1.0 / 100);
		boost::array<mat4, 4> m;
		m[0] = scene->getPlayerMats()[0];
		m[1] = scene->getPlayerMats()[1];
		m[2] = scene->getPlayerMats()[2];
		m[3] = scene->getPlayerMats()[3];
		// Print out matrix contents
		/*
		cout << (m[0])[0][0] << (m[0])[0][1] << (m[0])[0][2] << (m[0])[0][3] << endl;
		cout << (m[0])[1][0] << (m[0])[1][1] << (m[0])[1][2] << (m[0])[1][3] << endl;
		cout << (m[0])[2][0] << (m[0])[2][1] << (m[0])[2][2] << (m[0])[2][3] << endl;
		cout << (m[0])[3][0] << (m[0])[3][1] << (m[0])[3][2] << (m[0])[3][3] << endl;
		*/
		if (player1shoot == true)
			p0 = "0s";
		else
			p0 = "0S";
		if (player2shoot == true)
			p1 = "1s";
		else
			p1 = "1S";
		if (player3shoot == true)
			p3 = "2s";
		else
			p2 = "2S";
		if (player4shoot == true)
			p3 = "3s";
		else
			p3 = "3S";

		(*sendVec)[0] = std::make_pair(p0.c_str(), m[0]);
		(*sendVec)[1] = std::make_pair(p1.c_str(), m[1]);
		(*sendVec)[2] = std::make_pair(p2.c_str(), m[2]);
		(*sendVec)[3] = std::make_pair(p3.c_str(), m[3]);
		//std::cout << "pair 0: " << ((*sendVec)[0].first.c_str()) << std::endl;
		//std::cout << "pair 1: " << ((*sendVec)[1].first.c_str()) << std::endl;
		//std::cout << "pair 2: " << ((*sendVec)[2].first.c_str()) << std::endl;
		//std::cout << "pair 3: " << ((*sendVec)[3].first.c_str()) << std::endl;
		server->send(*sendVec);
		io_service.poll();
	}
	return 0;
}