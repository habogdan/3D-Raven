#pragma once
#include <GL/freeglut.h>

namespace House
{

	typedef struct Point
	{
		float x, y, z;
	} point;


	extern Point roofHouse[20][4];
	extern Point roofHousePart[4][4];
	extern Point wallHouse[7][4];
	extern Point door[4];
	extern Point window[5][4];
	extern Point crete[7][4];
	extern Point fence[7][4];
	extern Point streetPostBottom[7][4];
	extern Point streetPostPillar[7][4];
	extern Point beaconSquare[2][4];
	extern Point grass[3][4];
	extern GLuint wallTexture, roofTexture, creteTexture, fenceTexture, doorTexture, window1Texture, window2Texture, window3Texture, grassTexture;
	extern GLUquadricObj *qobj;

	GLuint createCrates(GLfloat move_x, GLfloat move_z);

	GLuint createFence(GLfloat move_x, GLfloat move_y, GLuint rotation);

	GLuint createPole(GLfloat move_x, GLfloat move_y);

	void drawPoleSphere(GLfloat move_x, GLfloat move_y);

	GLuint createHouse(GLfloat move_x, GLfloat move_z);
	void initCoordinates();

}