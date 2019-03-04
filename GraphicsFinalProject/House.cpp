#include "stdafx.h"
#include "House.h"



House::Point House::roofHouse[20][4];
House::Point House::roofHousePart[4][4];
House::Point House::wallHouse[7][4];
House::Point House::door[4];
House::Point House::window[5][4];
House::Point House::crete[7][4];
House::Point House::fence[7][4];
House::Point House::streetPostBottom[7][4];
House::Point House::beaconSquare[2][4];
House::Point House::streetPostPillar[7][4];
House::Point House::grass[3][4];
GLuint House::wallTexture, House::roofTexture, House::creteTexture, House::fenceTexture;
GLuint House::doorTexture, House::window1Texture, House::window2Texture, House::window3Texture, House::grassTexture;
GLUquadricObj * House::qobj;

GLuint House::createCrates(GLfloat move_x, GLfloat move_z)
{

	GLuint index = glGenLists(1);
	glNewList(index, GL_COMPILE);
	// Draw crete
	//glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslated(move_x, 0, move_z+15);
	glBindTexture(GL_TEXTURE_2D, creteTexture);
	for (int i = 0; i < 7; i++)
	{
		glBegin(GL_QUADS);
		glTexCoord2f(1.0, 1.0); glVertex3f(crete[i][0].x, crete[i][0].y, crete[i][0].z);
		glTexCoord2f(1.0, 0.0); glVertex3f(crete[i][1].x, crete[i][1].y, crete[i][1].z);
		glTexCoord2f(0.0, 0.0); glVertex3f(crete[i][2].x, crete[i][2].y, crete[i][2].z);
		glTexCoord2f(0.0, 1.0); glVertex3f(crete[i][3].x, crete[i][3].y, crete[i][3].z);
		glEnd();
	}
	glPopMatrix();

	//glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, creteTexture);
	glPushMatrix();
	glTranslated(move_x + 2.6, 0, move_z+15);
	for (int i = 0; i < 7; i++)
	{
		glBegin(GL_QUADS);
		glTexCoord2f(1.0, 1.0); glVertex3f(crete[i][0].x, crete[i][0].y, crete[i][0].z);
		glTexCoord2f(1.0, 0.0); glVertex3f(crete[i][1].x, crete[i][1].y, crete[i][1].z);
		glTexCoord2f(0.0, 0.0); glVertex3f(crete[i][2].x, crete[i][2].y, crete[i][2].z);
		glTexCoord2f(0.0, 1.0); glVertex3f(crete[i][3].x, crete[i][3].y, crete[i][3].z);
		glEnd();
	}
	glPopMatrix();

	//glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, creteTexture);
	glPushMatrix();
	glTranslated(move_x + 1.2, 2, move_z+15);
	for (int i = 0; i < 7; i++)
	{
		glBegin(GL_QUADS);
		glTexCoord2f(1.0, 1.0); glVertex3f(crete[i][0].x, crete[i][0].y, crete[i][0].z);
		glTexCoord2f(1.0, 0.0); glVertex3f(crete[i][1].x, crete[i][1].y, crete[i][1].z);
		glTexCoord2f(0.0, 0.0); glVertex3f(crete[i][2].x, crete[i][2].y, crete[i][2].z);
		glTexCoord2f(0.0, 1.0); glVertex3f(crete[i][3].x, crete[i][3].y, crete[i][3].z);
		glEnd();
	}
	glPopMatrix();

	//glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, creteTexture);
	glPushMatrix();
	glTranslated(move_x + 1.0, 0.0, move_z + 13);
	glRotated(-15, 1, 0, 0);
	for (int i = 0; i < 7; i++)
	{
		glBegin(GL_QUADS);
		glTexCoord2f(1.0, 1.0); glVertex3f(crete[i][0].x, crete[i][0].y, crete[i][0].z);
		glTexCoord2f(1.0, 0.0); glVertex3f(crete[i][1].x, crete[i][1].y, crete[i][1].z);
		glTexCoord2f(0.0, 0.0); glVertex3f(crete[i][2].x, crete[i][2].y, crete[i][2].z);
		glTexCoord2f(0.0, 1.0); glVertex3f(crete[i][3].x, crete[i][3].y, crete[i][3].z);
		glEnd();
	}
	glPopMatrix();

	//glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, creteTexture);
	glPushMatrix();
	glTranslated(move_x + 1.0, 0.0, move_z + 17.3);
	for (int i = 0; i < 7; i++)
	{
		glBegin(GL_QUADS);
		glTexCoord2f(1.0, 1.0); glVertex3f(crete[i][0].x, crete[i][0].y, crete[i][0].z);
		glTexCoord2f(1.0, 0.0); glVertex3f(crete[i][1].x, crete[i][1].y, crete[i][1].z);
		glTexCoord2f(0.0, 0.0); glVertex3f(crete[i][2].x, crete[i][2].y, crete[i][2].z);
		glTexCoord2f(0.0, 1.0); glVertex3f(crete[i][3].x, crete[i][3].y, crete[i][3].z);
		glEnd();
	}

	glPopMatrix();

	glEndList();

	return index;
}

GLuint House::createFence(GLfloat move_x, GLfloat move_y, GLuint rotation)
{
	GLuint index;
	index = glGenLists(1);
	glNewList(index, GL_COMPILE);
	
	//Draw fence
	//glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslated(move_x, 0, move_y);
	glRotated(rotation, 0, 1, 0);
	glTranslated(-2.5f, 0, -0.1f);
	glBindTexture(GL_TEXTURE_2D, fenceTexture);
	for (int i = 0; i < 7; i++)
	{
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0); glVertex3f(fence[i][0].x, fence[i][0].y, fence[i][0].z);
		glTexCoord2f(1.0, 1.0); glVertex3f(fence[i][1].x, fence[i][1].y, fence[i][1].z);
		glTexCoord2f(1.0, 0.0); glVertex3f(fence[i][2].x, fence[i][2].y, fence[i][2].z);
		glTexCoord2f(0.0, 0.0); glVertex3f(fence[i][3].x, fence[i][3].y, fence[i][3].z);
		glEnd();
	}

	glPopMatrix();

	glEndList();

	return index;
}

GLuint House::createPole(GLfloat move_x, GLfloat move_z)
{
	GLuint index = glGenLists(1);
	glNewList(index, GL_COMPILE);

	//Draw streetPortBottom
	//glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslated(move_x, 0, move_z);
	glBindTexture(GL_TEXTURE_2D, wallTexture);
	for (int i = 0; i < 7; i++)
	{
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0); glVertex3f(streetPostBottom[i][0].x, streetPostBottom[i][0].y, streetPostBottom[i][0].z);
		glTexCoord2f(1.0, 1.0); glVertex3f(streetPostBottom[i][1].x, streetPostBottom[i][1].y, streetPostBottom[i][1].z);
		glTexCoord2f(1.0, 0.0); glVertex3f(streetPostBottom[i][2].x, streetPostBottom[i][2].y, streetPostBottom[i][2].z);
		glTexCoord2f(0.0, 0.0); glVertex3f(streetPostBottom[i][3].x, streetPostBottom[i][3].y, streetPostBottom[i][3].z);
		glEnd();
	}
	glPopMatrix();

	//Draw streetPostPillar
	//glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslated(move_x, 0, move_z);
	glBindTexture(GL_TEXTURE_2D, fenceTexture);
	for (int i = 0; i < 7; i++)
	{
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0); glVertex3f(streetPostPillar[i][0].x, streetPostPillar[i][0].y, streetPostPillar[i][0].z);
		glTexCoord2f(1.0, 1.0); glVertex3f(streetPostPillar[i][1].x, streetPostPillar[i][1].y, streetPostPillar[i][1].z);
		glTexCoord2f(1.0, 0.0); glVertex3f(streetPostPillar[i][2].x, streetPostPillar[i][2].y, streetPostPillar[i][2].z);
		glTexCoord2f(0.0, 0.0); glVertex3f(streetPostPillar[i][3].x, streetPostPillar[i][3].y, streetPostPillar[i][3].z);
		glEnd();
	}
	glPopMatrix();

	glEndList();

	return index;




}

//not used
void House::drawPoleSphere(GLfloat move_x, GLfloat move_z)
{
	
}

GLuint House::createHouse(GLfloat move_x, GLfloat move_z)
{
	GLuint index = glGenLists(1);
	glNewList(index, GL_COMPILE);

	glPushMatrix();
	glTranslated(move_x, 0, move_z);
	//Draw house
	//glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, wallTexture);
	for (int i = 0; i < 7; i++)
	{
		glBegin(GL_QUADS);
		glTexCoord2f(3.0, 3.0); glVertex3f(wallHouse[i][0].x, wallHouse[i][0].y, wallHouse[i][0].z);
		glTexCoord2f(3.0, 0.0); glVertex3f(wallHouse[i][1].x, wallHouse[i][1].y, wallHouse[i][1].z);
		glTexCoord2f(0.0, 0.0); glVertex3f(wallHouse[i][2].x, wallHouse[i][2].y, wallHouse[i][2].z);
		glTexCoord2f(0.0, 3.0); glVertex3f(wallHouse[i][3].x, wallHouse[i][3].y, wallHouse[i][3].z);
		glEnd();
	}

	//glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, wallTexture);

	for (int i = 0; i < 4; i++)
	{
		glBegin(GL_TRIANGLES);
		glTexCoord2f(0.0, 0.0); glVertex3f(roofHousePart[i][0].x, roofHousePart[i][0].y, roofHousePart[i][0].z);
		glTexCoord2f(0.5, 3.0); glVertex3f(roofHousePart[i][1].x, roofHousePart[i][1].y, roofHousePart[i][1].z);
		glTexCoord2f(3.0, 0.0); glVertex3f(roofHousePart[i][2].x, roofHousePart[i][2].y, roofHousePart[i][2].z);
		glEnd();
	}

	//glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, roofTexture);

	for (int i = 0; i < 20; i++)
	{
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 4.0); glVertex3f(roofHouse[i][0].x, roofHouse[i][0].y, roofHouse[i][0].z);
		glTexCoord2f(4.0, 4.0); glVertex3f(roofHouse[i][1].x, roofHouse[i][1].y, roofHouse[i][1].z);
		glTexCoord2f(4.0, 0.0); glVertex3f(roofHouse[i][2].x, roofHouse[i][2].y, roofHouse[i][2].z);
		glTexCoord2f(0.0, 0.0); glVertex3f(roofHouse[i][3].x, roofHouse[i][3].y, roofHouse[i][3].z);
		glEnd();
	}

	//Draw Door
	//glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, doorTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex3f(door[0].x, door[0].y, door[0].z);
	glTexCoord2f(1.0, 1.0); glVertex3f(door[1].x, door[1].y, door[1].z);
	glTexCoord2f(1.0, 0.0); glVertex3f(door[2].x, door[2].y, door[2].z);
	glTexCoord2f(0.0, 0.0); glVertex3f(door[3].x, door[3].y, door[3].z);
	glEnd();

	//Window 1
	//glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, window1Texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex3f(window[1][0].x, window[1][0].y, window[1][0].z);
	glTexCoord2f(1.0, 1.0); glVertex3f(window[1][1].x, window[1][1].y, window[1][1].z);
	glTexCoord2f(1.0, 0.0); glVertex3f(window[1][2].x, window[1][2].y, window[1][2].z);
	glTexCoord2f(0.0, 0.0); glVertex3f(window[1][3].x, window[1][3].y, window[1][3].z);
	glEnd();

	//Window 2
	//glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, window2Texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex3f(window[2][0].x, window[2][0].y, window[2][0].z);
	glTexCoord2f(1.0, 1.0); glVertex3f(window[2][1].x, window[2][1].y, window[2][1].z);
	glTexCoord2f(1.0, 0.0); glVertex3f(window[2][2].x, window[2][2].y, window[2][2].z);
	glTexCoord2f(0.0, 0.0); glVertex3f(window[2][3].x, window[2][3].y, window[2][3].z);
	glEnd();

	//Window 3 & 4
	//glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, window3Texture);
	for (int i = 3; i < 5; i++)
	{
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0); glVertex3f(window[i][0].x, window[i][0].y, window[i][0].z);
		glTexCoord2f(1.0, 1.0); glVertex3f(window[i][1].x, window[i][1].y, window[i][1].z);
		glTexCoord2f(1.0, 0.0); glVertex3f(window[i][2].x, window[i][2].y, window[i][2].z);
		glTexCoord2f(0.0, 0.0); glVertex3f(window[i][3].x, window[i][3].y, window[i][3].z);
		glEnd();
	}
	glPopMatrix();

	glEndList();

	return index;
}

void House::initCoordinates()
{
	//point data
	wallHouse[1][0] = { 0.0f, 0.0f, 0.0f }; wallHouse[1][1] = { 0.0f, 5.0f, 0.0f }; wallHouse[1][2] = { 5.0f, 5.0f, 0.0f }; wallHouse[1][3] = { 5.0f, 0.0f, 0.0f };
	wallHouse[2][0] = { 5.0f, 0.0f, 0.0f }; wallHouse[2][1] = { 5.0f, 5.0f, 0.0f }; wallHouse[2][2] = { 5.0f, 5.0f, 5.0f }; wallHouse[2][3] = { 5.0f, 0.0f, 5.0f };
	wallHouse[3][0] = { 5.0f, 0.0f, 5.0f }; wallHouse[3][1] = { 5.0f, 5.0f, 5.0f }; wallHouse[3][2] = { 20.0f, 5.0f, 5.0f }; wallHouse[3][3] = { 20.0f, 0.0f, 5.0f };
	wallHouse[4][0] = { 20.0f, 0.0f, 5.0f }; wallHouse[4][1] = { 20.0f, 5.0f, 5.0f }; wallHouse[4][2] = { 20.0f, 5.0f, 15.0f }; wallHouse[4][3] = { 20.0f, 0.0f, 15.0f };
	wallHouse[5][0] = { 20.0f, 0.0f, 15.0f }; wallHouse[5][1] = { 20.0f, 5.0f, 15.0f }; wallHouse[5][2] = { 0.0f, 5.0f, 15.0f }; wallHouse[5][3] = { 0.0f, 0.0f, 15.0f };
	wallHouse[6][0] = { 0.0f, 0.0f, 15.0f }; wallHouse[6][1] = { 0.0f, 5.0f, 15.0f }; wallHouse[6][2] = { 0.0f, 5.0f, 0.0f }; wallHouse[6][3] = { 0.0f, 0.0f, 0.0f };

	roofHousePart[1][0] = { 0.0f, 5.0f, 0.0f }; roofHousePart[1][1] = { 2.5f, 10.0f, 0.0f }; roofHousePart[1][2] = { 5.0f, 5.0f, 0.0f };
	roofHousePart[2][0] = { 0.0f, 5.0f, 15.0f }; roofHousePart[2][1] = { 2.5f, 10.0f, 15.0f }; roofHousePart[2][2] = { 5.0f, 5.0f, 15.0 };
	roofHousePart[3][0] = { 20.0f, 5.0f, 5.0f }; roofHousePart[3][1] = { 20.0f, 10.0f, 10.f }; roofHousePart[3][2] = { 20.0f, 5.0f, 15.0f };

	roofHouse[1][0] = { -1.0f, 3.0f, -0.9f }; roofHouse[1][1] = { 2.5f, 10.0f, -0.9f }; roofHouse[1][2] = { 2.5f, 10.0f, 15.9f }; roofHouse[1][3] = { -1.0f, 3.0f, 15.9f };
	roofHouse[2][0] = { -1.5f, 3.0f, -0.9f }; roofHouse[2][1] = { -1.5f, 3.0f, 15.9f }; roofHouse[2][2] = { 2.5f, 12.0f, 15.9f }; roofHouse[2][3] = { 2.5f, 12.0f, -0.9f };
	roofHouse[3][0] = { 6.0f, 3.0f, -0.9f }; roofHouse[3][1] = { 2.5f, 10.0f, -0.9f }; roofHouse[3][2] = { 2.5f, 10.0f, 15.9f }; roofHouse[3][3] = { 6.0f, 3.0f, 15.9f };
	roofHouse[4][0] = { 6.5f, 3.0f, -0.9f }; roofHouse[4][1] = { 6.5f, 3.0f, 15.9f }; roofHouse[4][2] = { 2.5f, 12.0f, 15.9f }; roofHouse[4][3] = { 2.5f, 12.0f, -0.9f };
	roofHouse[5][0] = { 20.5f, 3.0f, 3.0f }; roofHouse[5][1] = { 6.5f, 3.0f, 3.0f }; roofHouse[5][2] = { 2.5f, 10.0f, 10.0f }; roofHouse[5][3] = { 20.5f, 10.0f, 10.0f };
	roofHouse[6][0] = { 20.5f, 3.0f, 17.0f }; roofHouse[6][1] = { 6.5f, 3.0f, 17.0f }; roofHouse[6][2] = { 2.5f, 10.0f, 10.0f }; roofHouse[6][3] = { 20.5f, 10.0f, 10.0f };
	roofHouse[7][0] = { 20.5f, 3.0f, 2.0f }; roofHouse[7][1] = { 6.5f, 3.0f, 2.0f }; roofHouse[7][2] = { 2.5f, 12.0f, 10.0f }; roofHouse[7][3] = { 20.5f, 12.0f, 10.0f };
	roofHouse[8][0] = { 20.5f, 3.0f, 18.0f }; roofHouse[8][1] = { 6.5f, 3.0f, 18.0f }; roofHouse[8][2] = { 2.5f, 12.0f, 10.0f }; roofHouse[8][3] = { 20.5f, 12.0f, 10.0f };
	roofHouse[9][0] = { -1.0f, 3.0f, -0.9f }; roofHouse[9][1] = { -1.5f, 3.0f, -0.9f }; roofHouse[9][2] = { 2.5f, 12.0f, -0.9f }; roofHouse[9][3] = { 2.5f, 10.0f, -0.9f };
	roofHouse[10][0] = { -1.0f, 3.0f, 15.9f }; roofHouse[10][1] = { -1.5f, 3.0f, 15.9f }; roofHouse[10][2] = { 2.5f, 12.0f, 15.9f }; roofHouse[10][3] = { 2.5f, 10.0f, 15.9f };
	roofHouse[11][0] = { 6.0f, 3.0f, -0.9f }; roofHouse[11][1] = { 6.5f, 3.0f, -0.9f }; roofHouse[11][2] = { 2.5f, 12.0f, -0.9f }; roofHouse[11][3] = { 2.5f, 10.0f, -0.9f };
	roofHouse[12][0] = { 6.0f, 3.0f, 15.9f }; roofHouse[12][1] = { 6.5f, 3.0f, 15.9f }; roofHouse[12][2] = { 2.5f, 12.0f, 15.9f }; roofHouse[12][3] = { 2.5f, 10.0f, 15.9f };
	roofHouse[13][0] = { 20.5f, 3.0f, 3.0f }; roofHouse[13][1] = { 20.5f, 3.0f, 2.0f }; roofHouse[13][2] = { 20.5f, 12.0f, 10.0f }; roofHouse[13][3] = { 20.5f, 10.0f, 10.0f };
	roofHouse[14][0] = { 20.5f, 3.0f, 17.0f }; roofHouse[14][1] = { 20.5f, 3.0f, 18.0f }; roofHouse[14][2] = { 20.5f, 12.0f, 10.0f }; roofHouse[14][3] = { 20.5f, 10.0f, 10.0f };
	roofHouse[15][0] = { 6.5f, 3.0f, 17.0f }; roofHouse[15][1] = { 6.5f, 3.0f, 18.0f }; roofHouse[15][2] = { 2.5f, 12.0f, 10.0f }; roofHouse[15][3] = { 2.5f, 10.0f, 10.0f };
	roofHouse[16][0] = { -1.0f, 3.0f, -0.9f }; roofHouse[16][1] = { -1.5f, 3.0f, -0.9f }; roofHouse[16][2] = { -1.5f, 3.0f, 15.9f }; roofHouse[16][3] = { -1.0f, 3.0f, 15.9f };
	roofHouse[17][0] = { 6.0f, 3.0f, -0.9f }; roofHouse[17][1] = { 6.5f, 3.0f, -0.9f }; roofHouse[17][2] = { 6.5f, 3.0f, 15.9f }; roofHouse[17][3] = { 6.0f, 3.0f, 15.9f };
	roofHouse[18][0] = { 20.5f, 3.0f, 2.0f }; roofHouse[18][1] = { 6.5f, 3.0f, 2.0f }; roofHouse[18][2] = { 6.5f, 3.0f, 3.0f }; roofHouse[18][3] = { 20.5f, 3.0f, 3.0f };
	roofHouse[19][0] = { 20.5f, 3.0f, 18.0f }; roofHouse[19][1] = { 6.5f, 3.0f, 18.0f }; roofHouse[19][2] = { 6.5f, 3.0f, 17.0f }; roofHouse[19][3] = { 20.5f, 3.0f, 17.0f };

	door[0] = { 1.5f, 0.0f, -0.05f }; door[1] = { 3.5f, 0.0f, -0.05f }; door[2] = { 3.5f, 4.0f, -0.05f }; door[3] = { 1.5f, 4.0f, -0.05f };

	window[1][0] = { 7.0f, 1.0f, 4.98f }; window[1][1] = { 10.0f, 1.0f, 4.98f }; window[1][2] = { 10.0f, 4.0f, 4.98f }; window[1][3] = { 7.0f, 4.0f, 4.98f };
	window[2][0] = { 15.0f, 1.0f, 4.98f }; window[2][1] = { 18.0f, 1.0f, 4.98f }; window[2][2] = { 18.0f, 4.0f, 4.98f }; window[2][3] = { 15.0f, 4.0f, 4.98f };

	window[3][0] = { -0.02f, 1.0f, 2.5f }; window[3][1] = { -0.02f, 1.0f, 5.5f }; window[3][2] = { -0.02f, 4.0f, 5.5f }; window[3][3] = { -0.02f, 4.0f, 2.5f };
	window[4][0] = { -0.02f, 1.0f, 9.5f }; window[4][1] = { -0.02f, 1.0f, 12.5f }; window[4][2] = { -0.02f, 4.0f, 12.5f }; window[4][3] = { -0.02f, 4.0f, 9.5f };

	crete[1][0] = { 0.0f, 0.0f, 0.0f }; crete[1][1] = { 2.0f, 0.0f, 0.0f }; crete[1][2] = { 2.0f, 2.0f, 0.0f }; crete[1][3] = { 0.0f, 2.0f, 0.0f };
	crete[2][0] = { 2.0f, 0.0f, 0.0f }; crete[2][1] = { 2.0f, 0.0f, 2.0f }; crete[2][2] = { 2.0f, 2.0f, 2.0f }; crete[2][3] = { 2.0f, 2.0f, 0.0f };
	crete[3][0] = { 2.0f, 0.0f, 2.0f }; crete[3][1] = { 0.0f, 0.0f, 2.0f }; crete[3][2] = { 0.0f, 2.0f, 2.0f }; crete[3][3] = { 2.0f, 2.0f, 2.0f };
	crete[4][0] = { 0.0f, 0.0f, 2.0f }; crete[4][1] = { 0.0f, 0.0f, 0.0f }; crete[4][2] = { 0.0f, 2.0f, 0.0f }; crete[4][3] = { 0.0f, 2.0f, 2.0f };
	crete[5][0] = { 0.0f, 2.0f, 0.0f }; crete[5][1] = { 2.0f, 2.0f, 0.0f }; crete[5][2] = { 2.0f, 2.0f, 2.0f }; crete[5][3] = { 0.0f, 2.0f, 2.0f };
	crete[6][0] = { 0.0f, 0.0f, 0.0f }; crete[6][1] = { 2.0f, 0.0f, 0.0f }; crete[6][2] = { 2.0f, 0.0f, 2.0f }; crete[6][3] = { 0.0f, 0.0f, 2.0f };

	fence[1][0] = { 0.0f, 0.0f, 0.0f }; fence[1][1] = { 5.0f, 0.0f, 0.0f }; fence[1][2] = { 5.0f, 3.0f, 0.0f }; fence[1][3] = { 0.0f, 3.0f, 0.0f };
	fence[2][0] = { 0.0f, 0.0f, 0.0f }; fence[2][1] = { 0.0f, 0.0f, 0.2f }; fence[2][2] = { 0.0f, 3.0f, 0.2f }; fence[2][3] = { 0.0f, 3.0f, 0.0f };
	fence[3][0] = { 5.0f, 0.0f, 0.0f }; fence[3][1] = { 5.0f, 0.0f, 0.2f }; fence[3][2] = { 5.0f, 3.0f, 0.2f }; fence[3][3] = { 5.0f, 3.0f, 0.0f };
	fence[4][0] = { 0.0f, 0.0f, 0.0f }; fence[4][1] = { 5.0f, 0.0f, 0.0f }; fence[4][2] = { 5.0f, 0.0f, 0.2f }; fence[4][3] = { 0.0f, 0.0f, 0.2f };
	fence[5][0] = { 0.0f, 2.0f, 0.0f }; fence[5][1] = { 5.0f, 3.0f, 0.0f }; fence[5][2] = { 5.0f, 3.0f, 0.2f }; fence[5][3] = { 0.0f, 3.0f, 0.2f };
	fence[6][0] = { 0.0f, 0.0f, 0.2f }; fence[6][1] = { 5.0f, 0.0f, 0.2f }; fence[6][2] = { 5.0f, 3.0f, 0.2f }; fence[6][3] = { 0.0f, 3.0f, 0.2f };

	streetPostBottom[1][0] = { 0.0f, 0.0f, 0.0f }; streetPostBottom[1][1] = { 1.0f, 0.0f, 0.0f }; streetPostBottom[1][2] = { 1.0f, 1.0f, 0.0f }; streetPostBottom[1][3] = { 0.0f, 1.0f, 0.0f };
	streetPostBottom[2][0] = { 1.0f, 0.0f, 0.0f }; streetPostBottom[2][1] = { 1.0f, 0.0f, 1.0f }; streetPostBottom[2][2] = { 1.0f, 1.0f, 1.0f }; streetPostBottom[2][3] = { 1.0f, 1.0f, 0.0f };
	streetPostBottom[3][0] = { 1.0f, 0.0f, 1.0f }; streetPostBottom[3][1] = { 0.0f, 0.0f, 1.0f }; streetPostBottom[3][2] = { 0.0f, 1.0f, 1.0f }; streetPostBottom[3][3] = { 1.0f, 1.0f, 1.0f };
	streetPostBottom[4][0] = { 0.0f, 0.0f, 1.0f }; streetPostBottom[4][1] = { 0.0f, 0.0f, 0.0f }; streetPostBottom[4][2] = { 0.0f, 1.0f, 0.0f }; streetPostBottom[4][3] = { 0.0f, 1.0f, 1.0f };
	streetPostBottom[5][0] = { 0.0f, 1.0f, 0.0f }; streetPostBottom[5][1] = { 1.0f, 1.0f, 0.0f }; streetPostBottom[5][2] = { 1.0f, 1.0f, 1.0f }; streetPostBottom[5][3] = { 0.0f, 1.0f, 1.0f };
	streetPostBottom[6][0] = { 0.0f, 0.0f, 0.0f }; streetPostBottom[6][1] = { 1.0f, 0.0f, 0.0f }; streetPostBottom[6][2] = { 1.0f, 0.0f, 1.0f }; streetPostBottom[6][3] = { 0.0f, 0.0f, 1.0f };

	streetPostPillar[1][0] = { 0.3f, 1.0f, 0.3f }; streetPostPillar[1][1] = { 0.7f, 1.0f, 0.3f }; streetPostPillar[1][2] = { 0.7f, 1.0f, 0.7f }; streetPostPillar[1][3] = { 0.3f, 1.0f, 0.7f };
	streetPostPillar[2][0] = { 0.3f, 1.0f, 0.3f }; streetPostPillar[2][1] = { 0.7f, 1.0f, 0.3f }; streetPostPillar[2][2] = { 0.7f, 4.0f, 0.3f }; streetPostPillar[2][3] = { 0.3f, 4.0f, 0.3f };
	streetPostPillar[3][0] = { 0.3f, 1.0f, 0.7f }; streetPostPillar[3][1] = { 0.7f, 1.0f, 0.7f }; streetPostPillar[3][2] = { 0.7f, 4.0f, 0.7f }; streetPostPillar[3][3] = { 0.3f, 4.0f, 0.7f };
	streetPostPillar[4][0] = { 0.3f, 1.0f, 0.3f }; streetPostPillar[4][1] = { 0.3f, 1.0f, 0.7f }; streetPostPillar[4][2] = { 0.3f, 4.0f, 0.7f }; streetPostPillar[4][3] = { 0.3f, 4.0f, 0.3f };
	streetPostPillar[5][0] = { 0.7f, 1.0f, 0.3f }; streetPostPillar[5][1] = { 0.7f, 1.0f, 0.7f }; streetPostPillar[5][2] = { 0.7f, 4.0f, 0.7f }; streetPostPillar[5][3] = { 0.7f, 4.0f, 0.3f };
	streetPostPillar[6][0] = { 0.3f, 4.0f, 0.3f }; streetPostPillar[6][1] = { 0.7f, 4.0f, 0.3f }; streetPostPillar[6][2] = { 0.7f, 4.0f, 0.7f }; streetPostPillar[6][3] = { 0.3f, 4.0f, 0.7f };

	beaconSquare[1][0] = { 0.0f, 0.01f, 0.0f }; beaconSquare[1][1] = { 2.0f, 0.01f, 0.0f }; beaconSquare[1][2] = { 2.0f, 0.01f, 2.0f }; beaconSquare[1][3] = { 0.0f, 0.01f, 2.0f };

	grass[1][0] = { 0.0f, 0.0f, 0.0f }; grass[1][1] = { 0.5f, 0.0f, 0.5f }; grass[1][2] = { 0.5f, 0.5f, 0.5f }; grass[1][3] = { 0.0f, 0.5f, 0.0f };
	grass[2][0] = { 0.0f, 0.0f, 0.5f }; grass[2][1] = { 0.5f, 0.0f, 0.0f }; grass[2][2] = { 0.5f, 0.5f, 0.0f }; grass[2][3] = { 0.0f, 0.5f, 0.5f };
}
