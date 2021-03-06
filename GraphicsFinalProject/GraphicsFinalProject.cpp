//SURSA:  lighthouse3D:  http://www.lighthouse3d.com/tutorials/glut-tutorial/keyboard-example-moving-around-the-world/
#include "stdafx.h"

#include<GL/freeglut.h>
#include "SOIL.h"
#include<math.h>
#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>

#include "House.h"
// angle of rotation for the camera direction
float angle = 3.6;
// actual vector representing the camera's direction
float lx = -0.442521f, lz = 0.896758f, ly = 0.0f;

// XYZ position of the camera
float x = -18.754734f, z = -98.146317f, y = 1.0f;

const  GLfloat PI = 3.1415;

using namespace House;


//vectors used for lighting
GLfloat specularMaterial[] = { 1,1,1,1 };
GLfloat emissionMaterial[] = { 0,0,0,1 };
GLfloat lightPosition[] = { 0, 0, 0, 1 };
GLfloat lightAmbient[] = { 0.2,0.2,0.2,1 };
GLfloat lightDiffuse[] = { 0,0,0,1 };
GLfloat lightSpecular[] = { 0,0,0,1 };

GLfloat angleForLight = PI/2;
GLfloat diffuseAndSpecLightCoeff = 0.47;
GLfloat daySpeed = 0.01;

GLfloat skyColorRed = 0.139216;
GLfloat skyColorGreen = 0.158824;
GLfloat skyColorBlue = 0.306471;

GLfloat AddSkyColorRed = 0.0;
GLfloat AddSkyColorGreen = 0.0;
GLfloat AddSkyColorBlue = 0.0;

enum {
	X, Y, Z, W
};
enum {
	A, B, C, D
};


GLfloat roadPoints[4][4][3] = {
	{ { -29.6, 0.0, 52.0 },{ -24.6, 0.0, 52.0 },{ -19.6, 0.0, 52.0 },{ -14.6,  0.0, 52.0 } },
{ { 77.6,  0.0, -50.0 },{ 83.6,  0.0, -50.0 },{ 88.6,  0.0, -50.0 },{ 93.6,  0.0, -50.0 } },
{ { -101.0,  0.0, 0.6 },{ -96.0,  0.0, 0.6 },{ -91.0,  0.0, 0.6 },{ -86.0,  0.0, 0.6 } },
{ { -24.0,  0.0, -100.0 },{ -19.0,  0.0, -100.0 },{ -14.0,  0.0, -100.0 },{ -9.0,  0.0, -100.0 } }
};

GLfloat houseArea[3][3][3] = {
	{ { -29.6, 0.0, 52.0 },{ -22.6, 0.0, 52.0 },{ -14.6, 0.0, 52.0 } },
{ { -45.5, 0.0, 76.0 },{ -14.6, 0.0, 76.0 },{ 26.3, 0.0, 76.0 } },
{ { -29.6, 0.0, 100.0 },{ -22.6, 0.0, 100.0 },{ -14.6, 0.0, 100.0 } }
};

GLfloat hillPoints[4][4][3] = {

	{ { -80, 0.0, 8.0 },{ -65, 0.0, 8.0 },{ -50, 0.0, 8.0 },{ -35,  0.0, 8.0 } },
{ { -90,  0.0, 16.0 },{ -55,  -5.5, 16.0 },{ -50, 27.0, 16.0 },{ -5,  0.0, 16.0 } },
{ { -100,  0.0, 24.0 },{ -75,  15.0, 24.0 },{ -40,  -6.0, 24.0 },{ -25,  0.0, 24.0 } },
{ { -80,  0.0, 32.0 },{ -65,  0.0, 32.0 },{ -50, 0.0, 32.0 },{ -35,  0.0, 32.0 } }
};

GLfloat hill2Points[4][4][3] = {

	{ { 30, 0.0, 20.0 },{ 45, 0.0, 10.0 },{ 60, 0.0, 30.0 },{ 75,  0.0, 20.0 } },
{ { 20,  0.0, 35.0 },{ 25,  -4.5, 40.0 },{ 60, 55.0, 35.0 },{ 175,  0.0, 25.0 } },
{ { 10,  0.0, 50.0 },{ 50,  -0.5, 55.0 },{ 65,  40.0, 60.0 },{ 125,  0.0, 35.0 } },
{ { 30,  0.0, 65.0 },{ 45,  0.0, 45.0 },{ 60, 0.0, 55.0 },{ 75,  0.0, 65.0 } }
};

GLfloat hill3Points[4][4][3] = {

	{ { -50, 0, 66 },{ -60, 0, 66 },{ -70, 0, 66 },{ -70, 0, 66 } },
{ { -55, 0, 46 },{ -55, 20, 70 },{ -70, -0.2, 76 },{ -70, 0, 76 } },
{ { -55, 0, 86 },{ -50, 0, 86 },{ -75, 35, 90 },{ -70, 0, 86 } },
{ { -50, 0, 96 },{ -60, 0, 96 },{ -70, 0, 96 },{ -70, 0, 90 } }
};

GLfloat hill4Points[4][4][3] = {

	{ { 70, 0, 66 },{ 80, 0, 66 },{ 90, 0, 66 },{ 90, 0, 66 } },
{ { 75, 0, 46 },{ 75, 20, 70 },{ 90, -0.2, 76 },{ 90, 0, 76 } },
{ { 75, 0, 86 },{ 70, 0, 86 },{ 95, 35, 90 },{ 90, 0, 86 } },
{ { 70, 0, 96 },{ 80, 0, 96 },{ 90, 0, 96 },{ 90, 0, 90 } }
};

GLfloat texturePointsRoad[2][2][2] = { { { 0.0, 0.0 },{ 0.0, 5.0 } },
{ { 60.0, 0.0 },{ 60.0, 5.0 } } };

GLfloat texturePointsHouse[2][2][2] = { { { 0.0, 0.0 },{ 0.0, 10.0 } },
{ { 10.0, 0.0 },{ 10.0, 10.0 } } };

GLfloat texturePointsHill[2][2][2] = { { { 0.0, 0.0 },{ 0.0, 10.0 } },
{ { 10.0, 0.0 },{ 10.0, 10.0 } } };


GLfloat floorShadow[4][4];
GLfloat floorPlane[4];

//game logic area
bool gameStarted = false;
bool gameWon = false;
float ravenSpeed = 0.1;

//textures zone
const char* roadImagePath = "";
GLuint roadImageTexID = 0;
GLuint grassTextureID = 0;
GLuint ravenTextureID = 0;
GLuint houseAreaTextureID = 0;
GLuint hillImageTexID = 0;
GLuint hill2ImageTexID = 0;
GLuint hill3ImageTexID = 0;
GLuint hill4ImageTexID = 0;

//fog zone
bool fogActive = false;
GLfloat fogColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };

//other objects
GLuint houseDisplayList = 0, cratesDisplayList = 0, lampPostDisplayList = 0, fenceDisplayList[4], cratesDisplayList2 = 0;
GLuint grassRandom1, grassRandom2, grassRandom3;

//experimental area
GLfloat testAngle = 0.0f;
GLfloat testRotation = 0.0f;
GLfloat testLight[] = { -6, 4.55, -50, 1.0 };
GLfloat testAmbient[] = { 0.2, 0.2, 0.2, 1 };
GLfloat testDiffuse[] = { 0.3,0.3,0.3,1 };
GLfloat testSpecular[] = { 0.3,0.3,0.3,1 };
GLfloat emissionTest[] = { 0.8, 0.8, 0.8, 1 };
float move_y = 0.0;
float alpha = 0.1;

//////////////////////

//GLUquadricObj *qobj;
GLfloat planeMatrix[4][3] = {
	{ -100.0f, 0.0f, -100.0f },
{ -100.0f, 0.0f, 100.0f },
{ 100.0f, 0.0f, 100.0f },
{ 100.0f, 0.0f, -100.0f }
};

unsigned char text[255] = "PRESS ENTER TO START";

GLuint shadowTextureID = 0;

GLuint loadBMP_soil(const char * imagepath)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);	// Set texture wrapping to GL_REPEAT
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	int width, height;
	unsigned char* image = SOIL_load_image(imagepath, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	return texture;
}

//global ratio
float ratio = 0.0;
void changeSize(int w, int h)
{
	glClearColor(skyColorRed, skyColorGreen, skyColorBlue, 0.0);
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void dayNightCycle()
{
	GLfloat xLight = 100 * cos(angleForLight);
	GLfloat yLight = 100 * sin(angleForLight);
	lightPosition[0] = xLight;
	lightPosition[1] = yLight;

	if(!fogActive)
		glClearColor(skyColorRed + AddSkyColorRed, skyColorGreen + AddSkyColorGreen, skyColorBlue + AddSkyColorBlue, 0.0);
	else
	{
		fogColor[0] = 0.2 + AddSkyColorBlue * 2;
		fogColor[1] = 0.2 + AddSkyColorBlue * 2;
		fogColor[2] = 0.2 + AddSkyColorBlue * 2;
		glClearColor(fogColor[0], fogColor[1], fogColor[2], 0.0);
		glFogfv(GL_FOG_COLOR, fogColor);
	}
	



	for (int i = 0; i < 3; i++)
	{
		lightDiffuse[i] = diffuseAndSpecLightCoeff;
		lightAmbient[i] = diffuseAndSpecLightCoeff;
	}

	if (angleForLight < PI)
	{
		glEnable(GL_LIGHT0);
		angleForLight += daySpeed;
		emissionTest[0] = 0.1;
		emissionTest[1] = 0.1;
		emissionTest[2] = 0.1;
		glDisable(GL_LIGHT1);
	}
	else if (angleForLight < PI * 2)
	{
		angleForLight += daySpeed;
		glDisable(GL_LIGHT0);
		emissionTest[0] = 0.8;
		emissionTest[1] = 0.8;
		emissionTest[2] = 0.8;
		glEnable(GL_LIGHT1);

	}
	else
	{
		angleForLight = 0.0f;
	}

	if (angleForLight < PI / 2)
	{
		diffuseAndSpecLightCoeff += (daySpeed / 10) * 3;
		AddSkyColorRed = angleForLight / (PI / 2 * 5);
		AddSkyColorGreen = angleForLight / (PI / 2 * 3);
		AddSkyColorBlue = angleForLight / (PI / 2 * 5);
	}
	else if (angleForLight < PI)
	{
		diffuseAndSpecLightCoeff -= (daySpeed / 10) * 3;
		AddSkyColorRed = (PI-angleForLight) / (PI / 2 * 5);
		AddSkyColorGreen = (PI-angleForLight) / (PI / 2 * 3);
		AddSkyColorBlue = (PI-angleForLight) / (PI / 2 * 5);
	}
	else
	{
		diffuseAndSpecLightCoeff = 0.0f;
		AddSkyColorRed = 0.0f;
		AddSkyColorGreen = 0.0f;
		AddSkyColorBlue = 0.0f;
	}
		
	
}


void noneSpecialFunc(int key, int xx, int yy)
{

}

void noneKeyboardFunc(unsigned char key, int xx, int yy)
{
	switch (key)
	{
	case 'f':
		if (!gameStarted)
			fogActive = !fogActive;
		if (fogActive)
			glEnable(GL_FOG);
		else
			glDisable(GL_FOG);
		break;
	case 13:
		gameStarted = true;
		break;
	}
}

void lastKeyboardFunc(unsigned char key, int xx, int yy)
{
	switch (key) {
	case 13:
		exit(0);
	}
}

void processNormalKeys(unsigned char key, int xx, int yy)
{
	float fraction = 1.1f;

	switch (key) {
	case 'a':
		
		angle -= 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case 'd':
		angle += 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;

	case 'w':
		x += lx * fraction;
		z += lz * fraction;
		break;
	case 's':
		x -= lx * fraction;
		z -= lz * fraction;
		break;
	case 'f':
		if(!gameStarted)
			fogActive = !fogActive;
		if (fogActive)
			glEnable(GL_FOG);
		else
			glDisable(GL_FOG);
		break;
	case 13:
		gameStarted = true;
		break;
	}
	if (key == 27)
		exit(0);
}

void processSpecialKeys(int key, int xx, int yy)
{
	switch (key)
	{
	case GLUT_KEY_UP:
	{
		y += 0.05;
		break;
	}
	case GLUT_KEY_DOWN:
	{
		y -= 0.05;
		break;
	}

	}
}

/* Create a single component texture map */
GLfloat *
make_texture(int maxs, int maxt)
{
	int s, t;
	static GLfloat *texture;

	texture = (GLfloat *)malloc(maxs * maxt * sizeof(GLfloat));
	for (t = 0; t < maxt; t++) {
		for (s = 0; s < maxs; s++) {
			texture[s + maxs * t] = ((s >> 4) & 0x1) ^ ((t >> 4) & 0x1);
		}
	}
	return texture;
}

/* create a matrix that will project the desired shadow */
void
shadowmatrix(GLfloat shadowMat[4][4],
	GLfloat groundplane[4],
	GLfloat lightpos[4])
{
	GLfloat dot;

	/* find dot product between light position vector and ground plane normal */
	dot = groundplane[X] * lightpos[X] +
		groundplane[Y] * lightpos[Y] +
		groundplane[Z] * lightpos[Z] +
		groundplane[W] * lightpos[W];

	shadowMat[0][0] = dot - lightpos[X] * groundplane[X];
	shadowMat[1][0] = 0.f - lightpos[X] * groundplane[Y];
	shadowMat[2][0] = 0.f - lightpos[X] * groundplane[Z];
	shadowMat[3][0] = 0.f - lightpos[X] * groundplane[W];

	shadowMat[X][1] = 0.f - lightpos[Y] * groundplane[X];
	shadowMat[1][1] = dot - lightpos[Y] * groundplane[Y];
	shadowMat[2][1] = 0.f - lightpos[Y] * groundplane[Z];
	shadowMat[3][1] = 0.f - lightpos[Y] * groundplane[W];

	shadowMat[X][2] = 0.f - lightpos[Z] * groundplane[X];
	shadowMat[1][2] = 0.f - lightpos[Z] * groundplane[Y];
	shadowMat[2][2] = dot - lightpos[Z] * groundplane[Z];
	shadowMat[3][2] = 0.f - lightpos[Z] * groundplane[W];

	shadowMat[X][3] = 0.f - lightpos[W] * groundplane[X];
	shadowMat[1][3] = 0.f - lightpos[W] * groundplane[Y];
	shadowMat[2][3] = 0.f - lightpos[W] * groundplane[Z];
	shadowMat[3][3] = dot - lightpos[W] * groundplane[W];

}

/* find the plane equation given 3 points */
void
findplane(GLfloat plane[4],
	GLfloat v0[3], GLfloat v1[3], GLfloat v2[3])
{
	GLfloat vec0[3], vec1[3];

	/* need 2 vectors to find cross product */
	vec0[X] = v1[X] - v0[X];
	vec0[Y] = v1[Y] - v0[Y];
	vec0[Z] = v1[Z] - v0[Z];

	vec1[X] = v2[X] - v0[X];
	vec1[Y] = v2[Y] - v0[Y];
	vec1[Z] = v2[Z] - v0[Z];

	/* find cross product to get A, B, and C of plane equation */
	plane[A] = vec0[Y] * vec1[Z] - vec0[Z] * vec1[Y];
	plane[B] = -(vec0[X] * vec1[Z] - vec0[Z] * vec1[X]);
	plane[C] = vec0[X] * vec1[Y] - vec0[Y] * vec1[X];

	plane[D] = -(plane[A] * v0[X] + plane[B] * v0[Y] + plane[C] * v0[Z]);
}

void updateGame(int value)
{
	
	dayNightCycle();
	testAngle += 1.0f;

	//may be unefficient
	/*if (!gameStarted)
	{
		glutKeyboardFunc(noneKeyboardFunc);
		glutSpecialFunc(noneSpecialFunc);
	}
	else
	{
		glutKeyboardFunc(processNormalKeys);
		glutSpecialFunc(processSpecialKeys);
	}*/

	if (gameStarted)
	{
		x += lx * ravenSpeed;
		z += lz * ravenSpeed;
	}

	if (move_y > 10 || move_y < 0)
		alpha = -alpha;

	move_y += alpha;

	testRotation += 0.5;

	if (x < -17.5 && x > -19.5 && z > 56 && z < 59)
	{
		strcpy_s((char*)text, 37, "YOU WON! \n PRESS ENTER TO EXIT");
		glutKeyboardFunc(lastKeyboardFunc);
		gameWon = true;
		ravenSpeed = 0.0;
	}

	glutPostRedisplay();
	glutTimerFunc(17, updateGame, 1);
}


void showStatistics()
{
	
	glLineWidth(2);
	glColor3f(0.0, 0.0, 0.0);
	//draw 2d things on screen
	//like the game hud
	glBegin(GL_LINES);
	glVertex2f(-10.0, 8.0);
	glVertex2f(10.0, 8.0);
	glEnd();

	std::string textString;
	glRasterPos2f(-9.0, 8.1);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"z = ");
	glRasterPos2f(-8.0, 8.1);
	textString = std::to_string(z);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char*)textString.c_str());

	glRasterPos2f(-9.0, 8.8);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"y = ");
	glRasterPos2f(-8.0, 8.8);
	textString = std::to_string(y);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char*)textString.c_str());

	glRasterPos2f(-9.0, 9.5);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"x = ");
	glRasterPos2f(-8.0, 9.5);
	textString = std::to_string(x);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char*)textString.c_str());

	glRasterPos2f(-5.0, 8.1);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"lz = ");
	glRasterPos2f(-4.0, 8.1);
	textString = std::to_string(lz);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char*)textString.c_str());

	glRasterPos2f(-5.0, 8.8);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"ly = ");
	glRasterPos2f(-4.0, 8.8);
	textString = std::to_string(ly);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char*)textString.c_str());

	glRasterPos2f(-5.0, 9.5);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"lx = ");
	glRasterPos2f(-4.0, 9.5);
	textString = std::to_string(lx);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char*)textString.c_str());

	glRasterPos2f(-1.0, 9.5);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"angle = ");
	glRasterPos2f(1.0, 9.5);
	textString = std::to_string(angle);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char*)textString.c_str());
}

void drawGrass(GLfloat move_x, GLfloat move_z)
{
	//Draw grass
	glEnable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslated(move_x, 0, move_z);
	glBindTexture(GL_TEXTURE_2D, grassTexture);
	for (int i = 0; i < 3; i++)
	{
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0); glVertex3f(grass[i][0].x, grass[i][0].y, grass[i][0].z);
		glTexCoord2f(1.0, 1.0); glVertex3f(grass[i][1].x, grass[i][1].y, grass[i][1].z);
		glTexCoord2f(1.0, 0.0); glVertex3f(grass[i][2].x, grass[i][2].y, grass[i][2].z);
		glTexCoord2f(0.0, 0.0); glVertex3f(grass[i][3].x, grass[i][3].y, grass[i][3].z);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

GLuint grassRandom()
{
	GLuint index = glGenLists(1);
	glNewList(index, GL_COMPILE);
	srand(time(NULL));
	for (float i = 0; i < 20; i += 0.6)
	{

		int r2 = rand() % 10 + 1;
		std::cout << r2;
		drawGrass(-11 + r2, -93 + i);
	}

	glEndList();
	return index;
}

void renderScene(void) {

	//generate a new shadow matrix
	findplane(floorPlane, planeMatrix[0], planeMatrix[1], planeMatrix[2]);
	shadowmatrix(floorShadow, floorPlane, lightPosition);


	// Clear Color and Depth Buffers

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION); // Tell opengl that we are doing project matrix work
	glLoadIdentity(); // Clear the matrix
	glOrtho(-10.0, 10.0, -10.0, 10.0, 0.0, 30.0); // Setup an Ortho view
	glMatrixMode(GL_MODELVIEW); // Tell opengl that we are doing model matrix work. (drawing)
	glLoadIdentity(); // Clear the model matrix

	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);
	//HUD drawing

	if (!gameStarted)
	{
		glRasterPos2f(-3.0, 1.0);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, text);
	}
	
	if (gameWon)
	{
		glRasterPos2f(-3.0, 1.0);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, text);
	}


	showStatistics();



	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(x, y, z,
		x + lx, y, z + lz,
		0.0f, 1.0f, 0.0f);

	//light initialization
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

	//material initialization
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissionMaterial);


	// Draw ground
	//glColor3f(0.137255f, 0.556863f, 0.137255f);
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, grassTextureID);

	for (int i = -100; i < 100; i+= 10)
	{
		for (int j = -100; j < 100; j+= 10)
		{
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0); glVertex3f(i, 0, j);
			glTexCoord2f(0, 4); glVertex3f(i, 0, j + 10);
			glTexCoord2f(4, 0); glVertex3f(i + 10, 0, j + 10);
			glTexCoord2f(4, 4); glVertex3f(i + 10, 0, j);
			glEnd();
		}

	}
	glDisable(GL_TEXTURE_2D);

	//Draw road
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslated(0.0, 0.02, 0.0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, roadImageTexID);
	//glBindTexture(GL_TEXTURE_2D, houseAreaTextureID);
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4, 0.0, 1.0, 12, 4, &roadPoints[0][0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 2, 2, 0, 1, 4, 2, &texturePointsRoad[0][0][0]);
	glMapGrid2f(100, 0.0, 1.0, 100, 0.0, 1.0);
	glEvalMesh2(GL_FILL, 0, 100, 0, 100);

	//draw house area
	glBindTexture(GL_TEXTURE_2D, houseAreaTextureID);
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &houseArea[0][0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 2, 2, 0, 1, 4, 2, &texturePointsHouse[0][0][0]);
	glMapGrid2f(100, 0.0, 1.0, 100, 0.0, 1.0);
	glEvalMesh2(GL_FILL, 0, 100, 0, 100);
	glPopMatrix();
	
	glDisable(GL_TEXTURE_2D);
	
	if (!fogActive)
	{
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		glColor4f(0.f, 0.f, 0.f, 0.45f);
		glPushMatrix();
		glMultMatrixf((GLfloat *)floorShadow);
		glCallList(houseDisplayList);
		glCallList(cratesDisplayList);
		glCallList(cratesDisplayList2);
		glCallList(lampPostDisplayList);
		for(int i = 0; i < 4; i++)
			glCallList(fenceDisplayList[i]);
		glCallList(lampPostDisplayList);
		glPopMatrix();
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
	}

	glEnable(GL_TEXTURE_2D);
	glColor4f(1.f, 1.f, 1.f, 1.f);
	glCallList(houseDisplayList);
	glCallList(cratesDisplayList);
	glCallList(cratesDisplayList2);
	for (int i = 0; i < 4; i++)
		glCallList(fenceDisplayList[i]);
	glCallList(lampPostDisplayList);

	
	glDisable(GL_TEXTURE_2D);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissionTest);
	//Draw streetPost Sphere
	House::qobj = gluNewQuadric();
	// gluQuadricCallback(qobj, GLU_ERROR, errorCallback);
	gluQuadricDrawStyle(House::qobj, GLU_FILL);
	gluQuadricNormals(House::qobj, GLU_SMOOTH);
	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslated(-30 + 0.5, 4.3, 56 + 0.5);
	gluSphere(House::qobj, 0.5, 100, 100);
	glPopMatrix();
	gluDeleteQuadric(House::qobj);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissionMaterial);

	//Draw Beacon
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(-18.5, move_y + 1, 60);
	glRotated(testRotation, 0, 1, 0);
	glutWireOctahedron();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslated(-18.5, move_y + 1, 60);
	glRotated(testRotation, 0, 1, 0);
	glutSolidOctahedron();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-19.5, 0.1, 59);
	glColor4f(1, 1, 0, 0.45);
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.0, 1.0); glVertex3f(beaconSquare[1][0].x, beaconSquare[1][0].y, beaconSquare[1][0].z);
	glTexCoord2f(1.0, 1.0); glVertex3f(beaconSquare[1][1].x, beaconSquare[1][1].y, beaconSquare[1][1].z);
	glTexCoord2f(1.0, 0.0); glVertex3f(beaconSquare[1][2].x, beaconSquare[1][2].y, beaconSquare[1][2].z);
	glTexCoord2f(0.0, 0.0); glVertex3f(beaconSquare[1][3].x, beaconSquare[1][3].y, beaconSquare[1][3].z);
	glEnd();
	glPopMatrix();


	//Mihaela zone
	//there should be hills
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glColor4f(1, 1, 1, 1);
	glTranslated(-60, 0, -30);
	glRotated(90, 0, 1, 0);
	for (int i = 0; i < 4; i++)
	{

		glTranslated(-15, 0, -5);
		glBindTexture(GL_TEXTURE_2D, hillImageTexID);
		glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4, 0.0, 1.0, 12, 4, &hill4Points[0][0][0]);
		glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 2, 2, 0, 1, 4, 2, &texturePointsHill[0][0][0]);
		glMapGrid2f(100, 0.0, 1.0, 100, 0.0, 1.0);
		glEvalMesh2(GL_FILL, 0, 100, 0, 100);
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//drawGrass(-11, -93);
	glPushMatrix();
	glCallList(grassRandom1);
	glTranslated(-10, 0, 30);
	glCallList(grassRandom3);
	//glTranslated(0, 0, 0);
	//glCallList(grassRandom2);

	glPopMatrix();
	

	//draw player
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslated(x, y, z);
	glRotated(-angle*(180/PI), 0, 1, 0);
	//glRotated(testAngle, 0, 1, 0);
	glTranslated(0, -0.2f, -0.4f);
	//glMultMatrixf((GLfloat *)floorShadow);
	//glutSolidCube(0.2f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ravenTextureID);

	glRotated(10, 1, 0, 0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-0.1,0.07, -0.1);
	glTexCoord2f(0, 1); glVertex3f(-0.1,0.07, 0.1);
	glTexCoord2f(1, 1); glVertex3f(0.1,0.07, 0.1);
	glTexCoord2f(1, 0); glVertex3f(0.1,0.07, -0.1);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	glutSwapBuffers();
}



void init()
{
	

	// OpenGL init
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);

	//for lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	//for bezier
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_TEXTURE_COORD_2);

	//for testing purposes
	//todo: create and use normals table
	glEnable(GL_AUTO_NORMAL);

	//for texture
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	//for shadow
	//nothing needed here for now

	//post lamp
	//test light
	//street pole light
	glLightfv(GL_LIGHT1, GL_POSITION, testLight);
	glLightfv(GL_LIGHT1, GL_AMBIENT, testAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, testDiffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, testSpecular);
	//glEnable(GL_LIGHT1);

	//blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	//for fog
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, 0.15f);
	glHint(GL_FOG_HINT, GL_DONT_CARE);
	glFogf(GL_FOG_START, 10.0f);
	glFogf(GL_FOG_END, 30.0f);
	//glEnable(GL_FOG);

}

int main(int argc, char **argv) {

	// init GLUT and create window

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_STENCIL | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Lighthouse3D - GLUT Tutorial");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	//glutIdleFunc(renderScene);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	init();
	glutTimerFunc(17, updateGame, 1);

	House::initCoordinates();

	roadImageTexID = loadBMP_soil("Textures/Road1.jpg");
	houseAreaTextureID = loadBMP_soil("Textures/HouseArea1.jpg");
	grassTextureID = loadBMP_soil("Textures/Grass1.png");
	ravenTextureID = loadBMP_soil("Textures/Raven1.png");
	
	House::wallTexture = loadBMP_soil("Textures/Wall4.jpg");
	House::roofTexture = loadBMP_soil("Textures/Roof2.jpg");
	House::creteTexture = loadBMP_soil("Textures/Crete1.jpg");
	House::fenceTexture = loadBMP_soil("Textures/Fence6.jpg");
	House::doorTexture = loadBMP_soil("Textures/Door1.jpg");
	House::window1Texture = loadBMP_soil("Textures/Window2.jpg");
	House::window2Texture = loadBMP_soil("Textures/Window9.jpg");
	House::window3Texture = loadBMP_soil("Textures/Window3.jpg");
	House::grassTexture = loadBMP_soil("Textures/Grass2.png");
	hillImageTexID = loadBMP_soil("Textures/Hill2.jpg");

	houseDisplayList = House::createHouse(-21, 72);
	cratesDisplayList = House::createCrates(-27, 70);
	cratesDisplayList2 = House::createCrates(-30, 80);
	fenceDisplayList[0] = House::createFence(-13, 53, 150);
	fenceDisplayList[1] = House::createFence(-9, 56, 150);
	fenceDisplayList[2] = House::createFence(-5, 59, 150);
	fenceDisplayList[3] = House::createFence(-1, 62, 150);

	grassRandom1 = grassRandom();
	grassRandom2 = grassRandom();
	grassRandom3 = grassRandom();

	lampPostDisplayList = House::createPole(-30, 56);
	
	glutMainLoop();

	return 1;
}