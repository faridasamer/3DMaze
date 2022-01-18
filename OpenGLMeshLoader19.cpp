#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <iostream>
#include <Windows.h>
#include <ctime>
#include "TextureBuilder.h"
#include "Model_3DS.h"
#include "GLTexture.h"
#include <glut.h>
#define DEG2RAD(a) (a * 0.0174532925)

using namespace std;

float points = 0;
int coins = 0;
bool level2 = false;

int WIDTH = 1280;
int HEIGHT = 720;

int charx = -3;
int charz = 9;
int chary = 1;

float charAngle = 5;


int obs1_x;
int obs1_y;
int obs1_z;
int obs1_x2;
int obs1_y2;
int obs1_z2;
int obs1_x3;
int obs1_y3;
int obs1_z3;

int obs2_x;
int obs2_y;
int obs2_z;
int obs2_x2;
int obs2_y2;
int obs2_z2;
int obs2_x3;
int obs2_y3;
int obs2_z3;

int obs3_x;
int obs3_y;
int obs3_z;
int obs3_x2;
int obs3_y2;
int obs3_z2;

int obs4_x;
int obs4_y;
int obs4_z;
int obs4_x2;
int obs4_y2;
int obs4_z2;

int coin_x1;
int coin_z1;
bool coin1 = false;

int coin_x2;
int coin_z2;
bool coin2 = false;

int coin_x3;
int coin_z3;
bool coin3 = false;

int coin_x4;
int coin_z4;
bool coin4 = false;

int coin_x5;
int coin_z5;
bool coin5 = false;

int coin_x6;
int coin_z6;
bool coin6 = true;

int coin_x7;
int coin_z7;
bool coin7 = true;

int coin_x8;
int coin_z8;
bool coin8 = true;

int coin_x9;
int coin_z9;
bool coin9 = true;


int randCoin1;
int randCoin2;
int randCoin3;
int randCoin4;
int randCoin5;


int randCoin6;
int randCoin7;
int randCoin8;
int randCoin9;

int randObs1;
bool obs1 = false;
int randObs2;
bool obs2 = false;
int randObs3;
bool obs3 = false;
int randObs4;
bool obs4 = false;
int randObs5;
bool obs5 = false;
int randObs6;
bool obs6 = false;

int randObs7;
bool obs7 = false;
int randObs8;
bool obs8 = false;
int randObs9;
bool obs9 = false;
int randObs10;
bool obs10 = false;

float light1x = 0;
float light1y = 0;
float light1z = 0;

float rotAngle = 0;
bool init;
bool third;
bool first;
GLuint sky;
GLuint skyDay;
GLuint earth;
GLuint galaxy;
GLuint cactus;
GLuint sandObs;
GLuint gold;

// 3D Projection Options
GLdouble fovy = 45.0;
GLdouble aspectRatio = (GLdouble)WIDTH / (GLdouble)HEIGHT;
GLdouble zNear = 0.1;
GLdouble zFar = 100;
class Vector3f {
public:
	float x, y, z;

	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f operator+(Vector3f& v) {
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}

	Vector3f operator-(Vector3f& v) {
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}

	Vector3f operator*(float n) {
		return Vector3f(x * n, y * n, z * n);
	}

	Vector3f operator/(float n) {
		return Vector3f(x / n, y / n, z / n);
	}

	Vector3f unit() {
		return *this / sqrt(x * x + y * y + z * z);
	}

	Vector3f cross(Vector3f v) {
		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};
class Camera {
public:
	Vector3f eye, center, up;

	Camera(float eyeX = 20, float eyeY = 5, float eyeZ = 20, float centerX = 0, float centerY = 1, float centerZ = 0, float upX = 0, float upY = 1, float upZ = 0) {
		eye = Vector3f(eyeX, eyeY, eyeZ);
		center = Vector3f(centerX, centerY, centerZ);
		up = Vector3f(upX, upY, upZ);
	}

	void moveX(float d) {
		Vector3f right = up.cross(center - eye).unit();
		eye = eye + right * d;
		center = center + right * d;
	}

	void moveY(float d) {
		eye = eye + up.unit() * d;
		center = center + up.unit() * d;
	}

	void moveZ(float d) {
		Vector3f view = (center - eye).unit();
		eye = eye + view * d;
		center = center + view * d;
	}

	void rotateX(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
		up = view.cross(right);
		center = eye + view;
	}

	void rotateY(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
		right = view.cross(up);
		center = eye + view;
	}

	void look() {
		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z
		);
	}
};
class Vector
{
public:
	GLdouble x, y, z;
	Vector() {}
	Vector(GLdouble _x, GLdouble _y, GLdouble _z) : x(_x), y(_y), z(_z) {}
	//================================================================================================//
	// Operator Overloading; In C++ you can override the behavior of operators for you class objects. //
	// Here we are overloading the += operator to add a given value to all vector coordinates.        //
	//================================================================================================//
	void operator +=(float value)
	{
		x += value;
		y += value;
		z += value;
	}
};

Vector Eye(0, 10, 20);
Vector At(0, 0, 0);
Vector Up(0, 1, 0);


int cameraZoom = 0;

// Model Variables
Model_3DS model_house;
Model_3DS model_tree;
Model_3DS character;

// Textures
GLTexture tex_moon;
GLTexture tex_sand;

//=======================================================================
// Lighting Configuration Function
//=======================================================================

Camera camera;

void InitLightSource()
{
	// Enable Lighting for this OpenGL Program
	glEnable(GL_LIGHTING);

	// Enable Light Source number 0
	// OpengL has 8 light sources
	glEnable(GL_LIGHT0);

	// Define Light source 0 ambient light
	GLfloat ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	// Define Light source 0 diffuse light
	GLfloat diffuse[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	// Define Light source 0 Specular light
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	// Finally, define light source 0 position in World Space
	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}
void lightOne()
{
	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT1);

	GLfloat ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);

	GLfloat diffuse[] = { light1x, light1y, light1z, 1.0f };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);

	GLfloat specular[] = { light1x, light1y, light1z, 1.0f };
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);

	GLfloat light_position[] = { charx, chary, charz, 1.0f };
	glLightfv(GL_LIGHT1, GL_POSITION, light_position);

}
void lightTwo()
{
	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT2);

	GLfloat ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);

	GLfloat diffuse[] = { 0, 5, 0, 1.0f };
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);

	GLfloat specular[] = { 0, 5, 0, 1.0f };
	glLightfv(GL_LIGHT2, GL_SPECULAR, specular);


	GLfloat light_position[] = { -3, 1, 9, 1.0f };
	glLightfv(GL_LIGHT2, GL_POSITION, light_position);

}

void lightThree()
{
	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT3);

	GLfloat ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	glLightfv(GL_LIGHT3, GL_AMBIENT, ambient);

	GLfloat diffuse[] = { 0, 0, 5, 1.0f };
	glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse);

	GLfloat specular[] = { 0, 0, 5, 1.0f };
	glLightfv(GL_LIGHT3, GL_SPECULAR, specular);


	GLfloat light_position[] = { -6, 1, -8, 1.0f };
	glLightfv(GL_LIGHT3, GL_POSITION, light_position);

}

//=======================================================================
// Material Configuration Function
//======================================================================
void InitMaterial()
{
	// Enable Material Tracking
	glEnable(GL_COLOR_MATERIAL);

	// Sich will be assigneet Material Properties whd by glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Set Material's Specular Color
	// Will be applied to all objects
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	// Set Material's Shine value (0->128)
	GLfloat shininess[] = { 96.0f };
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

//=======================================================================
// OpengGL Configuration Function
//=======================================================================
void myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(fovy, aspectRatio, zNear, zFar);
	//*******************************************************************************************//
	// fovy:			Angle between the bottom and top of the projectors, in degrees.			 //
	// aspectRatio:		Ratio of width to height of the clipping plane.							 //
	// zNear and zFar:	Specify the front and back clipping planes distances from camera.		 //
	//*******************************************************************************************//

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
	//*******************************************************************************************//
	// EYE (ex, ey, ez): defines the location of the camera.									 //
	// AT (ax, ay, az):	 denotes the direction where the camera is aiming at.					 //
	// UP (ux, uy, uz):  denotes the upward orientation of the camera.							 //
	//*******************************************************************************************//

	InitLightSource();

	InitMaterial();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);
}

void ground() {
	glColor3f(0, 0, 0);
	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex3f(-7, 1, 10);
	glVertex3f(-7, 1, -10);
	glVertex3f(8, 1, -10);
	glVertex3f(8, 1, 10);
}
void RenderGround()
{
	glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit
	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	if (level2) {
		glBindTexture(GL_TEXTURE_2D, tex_moon.texture[0]);
	}
	else {
		glBindTexture(GL_TEXTURE_2D, tex_sand.texture[0]);
	}


	glPushMatrix();
	glTranslated(0, 100, 45);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-4, 1, 10);
	glTexCoord2f(1, 0);
	glVertex3f(8, 1, 9);
	glTexCoord2f(1, 1);
	glVertex3f(8, 1, -9);
	glTexCoord2f(0, 1);
	glVertex3f(-7, 1, -10);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}

void firstObstacle() {
	glPushMatrix();
	glTranslatef(obs1_x, 1, obs1_z);
	glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
	glEnable(GL_TEXTURE_GEN_T);
	glBindTexture(GL_TEXTURE_2D, earth);
	glutSolidSphere(0.5, 20, 20);
	glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
	glDisable(GL_TEXTURE_GEN_T);
	glColor3f(1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(obs1_x2, 1, obs1_z2);
	glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
	glEnable(GL_TEXTURE_GEN_T);
	glBindTexture(GL_TEXTURE_2D, earth);
	glutSolidSphere(0.5, 20, 20);
	glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
	glDisable(GL_TEXTURE_GEN_T);
	glColor3f(1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(obs1_x3, 1, obs1_z3);
	glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
	glEnable(GL_TEXTURE_GEN_T);
	glBindTexture(GL_TEXTURE_2D, earth);
	glutSolidSphere(0.5, 20, 20);
	glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
	glDisable(GL_TEXTURE_GEN_T);
	glColor3f(1, 1, 1);
	glPopMatrix();
}

void secondObstacle() {
	glPushMatrix();
	//glColor3f(1, 0, 0);
	glTranslatef(obs2_x, 1, obs2_z);
	glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
	glEnable(GL_TEXTURE_GEN_T);
	glBindTexture(GL_TEXTURE_2D, galaxy);
	glutSolidCube(0.5);
	glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
	glDisable(GL_TEXTURE_GEN_T);
	glColor3f(1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	//glColor3f(0, 1, 0);
	glTranslatef(obs2_x2, 1, obs2_z2);
	glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
	glEnable(GL_TEXTURE_GEN_T);
	glBindTexture(GL_TEXTURE_2D, galaxy);
	glutSolidCube(0.5);
	glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
	glDisable(GL_TEXTURE_GEN_T);
	glColor3f(1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	//glColor3f(0, 0, 1);
	glTranslatef(obs2_x3, 1, obs2_z3);
	glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
	glEnable(GL_TEXTURE_GEN_T);
	glBindTexture(GL_TEXTURE_2D, galaxy);
	glutSolidCube(0.5);
	glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
	glDisable(GL_TEXTURE_GEN_T);
	glColor3f(1, 1, 1);
	glPopMatrix();
}
void thirdObstacle() {
	glPushMatrix();
	//glColor3f(0.37, 0.184, 0.039);
	glTranslatef(obs3_x, 1, obs3_z);
	glScalef(0.5, 0.5, 0.5);
	glRotatef(0, 1, 0, 90);
	glEnable(GL_TEXTURE_GEN_S); 
	glEnable(GL_TEXTURE_GEN_T);
	glBindTexture(GL_TEXTURE_2D, sandObs);
	glutSolidTetrahedron();
	glDisable(GL_TEXTURE_GEN_S); 
	glDisable(GL_TEXTURE_GEN_T);
	glColor3f(1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	//glColor3f(0.37, 0.184, 0.039);
	glTranslatef(obs3_x2, 1, obs3_z2);
	glScalef(0.5, 0.5, 0.5);
	glRotatef(0, 1, 0, 90);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glBindTexture(GL_TEXTURE_2D, sandObs);
	glutSolidTetrahedron();
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glColor3f(1, 1, 1);
	glPopMatrix();
}

void fourthObstacle() {
	glPushMatrix();
	//glColor3f(0.37, 0.184, 0.039);
	glRotatef(0, 0, 1, 90);
	glTranslatef(obs4_x, 1, obs4_z);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glBindTexture(GL_TEXTURE_2D, cactus);
	glutSolidCone(0.5, 0.5, 10, 10);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glColor3f(1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	//glColor3f(0.37, 0.184, 0.039);
	glRotatef(0, 0, 1, 90);
	glTranslatef(obs4_x2, 1, obs4_z2); glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glBindTexture(GL_TEXTURE_2D, cactus);
	glutSolidCone(0.5, 0.5, 10, 10);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glColor3f(1, 1, 1);
	glPopMatrix();
}

void coin(int coin_x, int coin_z) {
	glPushMatrix();
	//glColor3f(1, 0.84, 0);
	glTranslated(coin_x, 1, coin_z);
	glRotated(rotAngle, 0, 1, 0);
	glEnable(GL_TEXTURE_GEN_T);
	glBindTexture(GL_TEXTURE_2D, gold);
	glutSolidTorus(0.1, 0.2, 10, 10);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glColor3f(1, 1, 1);
	glPopMatrix();
}

void genRand() {
	srand(time(NULL));
	randObs1 = rand() % 2;
	randObs2 = rand() % 2;
	randObs3 = rand() % 2;
	randObs4 = rand() % 2;
	randObs5 = rand() % 2;
	randObs6 = rand() % 2;

	if (randObs1 == 1) {
		obs1_x = -3;
		obs1_z = 8;
		obs1 = true;
	}
	else {
		obs1_x = -3;
		obs1_z = 7;
	}

	if (randObs2 == 1) {
		obs1_x2 = 1;
		obs1_z2 = 5;
		obs2 = true;
	}
	else {
		obs1_x2 = 6;
		obs1_z2 = 3;
	}

	if (randObs3 == 1) {
		obs1_x3 = 8;
		obs1_z3 = -3;
		obs3 = true;
	}
	else {
		obs1_x3 = 4;
		obs1_z3 = -1;
	}

	if (randObs4 == 1) {
		obs2_x = 2;
		obs2_z = 3;
		obs4 = true;
	}
	else {
		obs2_x = -1;
		obs2_z = -4;
	}

	if (randObs5 == 1) {
		obs2_x2 = -4;
		obs2_z2 = -4;
		obs5 = true;
	}
	else {
		obs2_x2 = 2;
		obs2_z2 = 8;
	}
	if (randObs6 == 1) {
		obs2_x3 = 2;
		obs2_z3 = 3;
		obs6 = true;
	}
	else {
		obs2_x3 = -6;
		obs2_z3 = -6;
	}
	randObs7 = rand() % 2;
	randObs8 = rand() % 2;
	randObs9 = rand() % 2;
	randObs10 = rand() % 2;

	if (randObs7 == 1) {
		obs3_x = -1;
		obs3_z = 6;
	}
	else {
		obs3_x = 5;
		obs3_z = 6;
		obs7 = true;
	}

	if (randObs8 == 1) {
		obs3_x2 = 6;
		obs3_z2 = 2;
	}
	else {
		obs3_x2 = 4;
		obs3_z2 = 1;
		obs8 = true;
	}

	if (randObs9 == 1) {
		obs4_x = 2;
		obs4_z = 1;
	}
	else {
		obs4_x = 2;
		obs4_z = 1;
	}

	if (randObs10 == 1) {
		obs4_x2 = -3;
		obs4_z2 = 0;
	}
	else {
		obs4_x2 = -6;
		obs4_z2 = -5;
		obs10 = true;
	}
	glutPostRedisplay();
}

void randCoinsTwo() {
	randCoin1 = rand() % 2;
	randCoin2 = rand() % 2;
	randCoin3 = rand() % 2;
	randCoin4 = rand() % 2;
	randCoin5 = rand() % 2;
	if (randCoin1 == 1) {
		coin_x1 = -3;
		coin_z1 = 6;
	}
	else {
		coin_x1 = 3;
		coin_z1 = 5;
	}

	if (randCoin2 == 1) {
		coin_x2 = -3;
		coin_z2 = 4;
	}
	else {
		coin_x2 = -1;
		coin_z2 = 3;
	}

	if (randCoin3 == 1) {
		coin_x3 = 1;
		coin_z3 = 3;
	}
	else {
		coin_x3 = 1;
		coin_z3 = 6;
	}

	if (randCoin4 == 1) {
		coin_x4 = 5;
		coin_z4 = 3;
	}
	else {
		coin_x4 = 8;
		coin_z4 = 0;
	}

	if (randCoin5 == 1) {
		coin_x5 = 4;
		coin_z5 = -2;
	}
	else {
		coin_x5 = 2;
		coin_z5 = -4;
	}

}

void randCoins() {
	randCoin1 = rand() % 2;
	randCoin2 = rand() % 2;
	randCoin3 = rand() % 2;
	randCoin4 = rand() % 2;
	randCoin5 = rand() % 2;
	randCoin6 = rand() % 2;
	randCoin7 = rand() % 2;
	randCoin8 = rand() % 2;
	randCoin9 = rand() % 2;
	if (randCoin1 == 1) {
		coin_x1 = -3;
		coin_z1 = 6;
	}
	else {
		coin_x1 = 3;
		coin_z1 = 5;
	}

	if (randCoin2 == 1) {
		coin_x2 = -3;
		coin_z2 = 4;
	}
	else {
		coin_x2 = -1;
		coin_z2 = 3;
	}

	if (randCoin3 == 1) {
		coin_x3 = 1;
		coin_z3 = 3;
	}
	else {
		coin_x3 = 1;
		coin_z3 = 6;
	}

	if (randCoin4 == 1) {
		coin_x4 = 5;
		coin_z4 = 3;
	}
	else {
		coin_x4 = 8;
		coin_z4 = 0;
	}

	if (randCoin5 == 1) {
		coin_x5 = 4;
		coin_z5 = -2;
	}
	else {
		coin_x5 = 2;
		coin_z5 = -4;
	}

	if (randCoin6 == 1) {
		coin_x6 = -3;
		coin_z6 = 6;
	}
	else {
		coin_x6 = 7;
		coin_z6 = 4;
	}

	if (randCoin7 == 1) {
		coin_x7 = 6;
		coin_z7 = 1;
	}
	else {
		coin_x7 = -3;
		coin_z7 = 1;
	}

	if (randCoin8 == 1) {
		coin_x8 = -4;
		coin_z8 = -3;
	}
	else {
		coin_x8 = -6;
		coin_z8 = -7;
	}

	if (randCoin9 == 1) {
		coin_x9 = -6;
		coin_z9 = -3;
	}
	else {
		coin_x9 = -3;
		coin_z9 = -3;
	}

}

void firstMaze(void) {
	glColor3f(0.38, 0.36, 0.21);
	glPushMatrix();
	glTranslatef(8, 1, 3);
	glRotatef(90.f, 1, 0, 0);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(8, 1, 5);
	glRotatef(90.f, 1, 0, 0);
	glutSolidCube(1);
	glPopMatrix();
	/*glPushMatrix();
	glTranslatef(8, 1, 4);
	glRotatef(90.f, 1, 0, 0);
	glutSolidCube(1);
	glPopMatrix();*/
	for (int i = 9; i > 4; i--) {
		glPushMatrix();
		glTranslatef(-4, 1, i);
		glRotatef(90.f, 1, 0, 0);
		glutSolidCube(1);
		glPopMatrix();
	}
	/// /////////////// ///

	for (int i = 9; i > 6; i--) {
		glPushMatrix();
		glTranslatef(-2, 1, i);
		glRotatef(90.f, 1, 0, 0);
		glutSolidCube(1);
		glPopMatrix();
	}

	/// /////////////// ///

	for (int i = 5; i > -4; i--) {
		glPushMatrix();
		glTranslatef(i, 1, 5);
		glRotatef(90.f, 1, 0, 0);
		glutSolidCube(1);
		glPopMatrix();
	}
	/// /////////////// ///

	for (int i = 7; i > -2; i--) {
		glPushMatrix();
		glTranslatef(i, 1, 7);
		glRotatef(90.f, 1, 0, 0);
		glutSolidCube(1);
		glPopMatrix();
	}

	/// /////////////// ///

	for (int i = 6; i > 0; i--) {
		if (i != 4) {
			glPushMatrix();
			glTranslatef(7, 1, i);
			glRotatef(90.f, 1, 0, 0);
			glutSolidCube(1);
			glPopMatrix();
		}
	}

	/// /////////////// ///

	for (int i = 4; i > 2; i--) {
		glPushMatrix();
		glTranslatef(5, 1, i);
		glRotatef(90.f, 1, 0, 0);
		glutSolidCube(1);
		glPopMatrix();
	}
	/// /////////////// ///

	for (int i = 5; i > -4; i--) {
		glPushMatrix();
		glTranslatef(i, 1, 2);
		glRotatef(90.f, 1, 0, 0);
		glutSolidCube(1);
		glPopMatrix();
	}
	/// /////////////// ///

	for (int i = 7; i > -2; i--) {
		glPushMatrix();
		glTranslatef(i, 1, 0);
		glRotatef(90.f, 1, 0, 0);
		glutSolidCube(1);
		glPopMatrix();
	}

	/// /////////////// /// 

	for (int i = 2; i > -3; i--) {
		glPushMatrix();
		glTranslatef(-4, 1, i);
		glRotatef(90.f, 1, 0, 0);
		glutSolidCube(1);
		glPopMatrix();
	}

	/// /////////////// ///

	for (int i = 0; i > -4; i--) {
		glPushMatrix();
		glTranslatef(-2, 1, i);
		glRotatef(90.f, 1, 0, 0);
		glutSolidCube(1);
		glPopMatrix();
	}

	/// /////////////// ///

	for (int i = -2; i > -5; i--) {
		glPushMatrix();
		glTranslatef(i, 1, -4);
		glRotatef(90.f, 1, 0, 0);
		glutSolidCube(1);
		glPopMatrix();
	}

	/// /////////////// ///

	for (int i = -5; i > -7; i--) {
		glPushMatrix();
		glTranslatef(i, 1, -2);
		glRotatef(90.f, 1, 0, 0);
		glutSolidCube(1);
		glPopMatrix();
	}

	/// /////////////// ///
	for (int i = -2; i > -8; i--) {
		glPushMatrix();
		glTranslatef(-7, 1, i);
		glRotatef(90.f, 1, 0, 0);
		glutSolidCube(1);
		glPopMatrix();
	}

	/// /////////////// ///

	for (int i = -4; i > -8; i--) {
		glPushMatrix();
		glTranslatef(-5, 1, i);
		glRotatef(90.f, 1, 0, 0);
		glutSolidCube(1);
		glPopMatrix();
	}

	/// /////////////// ///



}

void secondMaze(void) {

	glColor3f(0.54, 0.38, 0.93);

	for (int i = 9; i > 2; i--) {
		glPushMatrix();
		glTranslatef(-4, 1, i);
		glRotatef(90.f, 1, 0, 0);
		glutSolidCube(1);
		glPopMatrix();
	}

	/// /////////////// ///

	for (int i = 9; i > 5; i--) {
		glPushMatrix();
		glTranslatef(-2, 1, i);
		glRotatef(90.f, 1, 0, 0);
		glutSolidCube(1);
		glPopMatrix();
	}

	/// /////////////// ///

	for (int i = 7; i > 5; i--) {
		glPushMatrix();
		glTranslatef(2, 1, i);
		glRotatef(90.f, 1, 0, 0);
		glutSolidCube(1);
		glPopMatrix();
	}

	/// /////////////// ///

	for (int i = 9; i > 5; i--) {
		glPushMatrix();
		glTranslatef(0, 1, i);
		glRotatef(90.f, 1, 0, 0);
		glutSolidCube(1);
		glPopMatrix();
	}
	/// /////////////// ///
	for (int i = 0; i < 5; i++) {
		glPushMatrix();
		glTranslatef(i, 1, 9);
		glRotatef(90.f, 1, 0, 0);
		glutSolidCube(1);
		glPopMatrix();
	}
	/// /////////////// ///
	for (int i = 9; i > 5; i--) {
		glPushMatrix();
		glTranslatef(4, 1, i);
		glRotatef(90.f, 1, 0, 0);
		glutSolidCube(1);
		glPopMatrix();
	}
	/// /////////////// ///

	for (int i = -4; i < 8; i++) {
		glPushMatrix();
		glTranslatef(i, 1, 2);
		glRotatef(90.f, 1, 0, 0);
		glutSolidCube(1);
		glPopMatrix();
	}

	/// /////////////// ///

	for (int i = -2; i < 10; i++) {
		if ((i != 1) && (i != 3)) {
			glPushMatrix();
			glTranslatef(i, 1, 5);
			glRotatef(90.f, 1, 0, 0);
			glutSolidCube(1);
			glPopMatrix();
		}

	}

	/// /////////////// ///

	for (int i = 4; i > -6; i--) {
		glPushMatrix();
		glTranslatef(9, 1, i);
		glRotatef(90.f, 1, 0, 0);
		glutSolidCube(1);
		glPopMatrix();
	}

	/// /////////////// ///

	for (int i = 2; i > -3; i--) {
		glPushMatrix();
		glTranslatef(7, 1, i);
		glRotatef(90.f, 1, 0, 0);
		glutSolidCube(1);
		glPopMatrix();
	}

	/// /////////////// ///

	for (int i = 2; i > -3; i--) {
		glPushMatrix();
		glTranslatef(6, 1, i);
		glRotatef(90.f, 1, 0, 0);
		glutSolidCube(1);
		glPopMatrix();
	}


	/// /////////////// ///

	for (int i = 2; i > -3; i--) {
		glPushMatrix();
		glTranslatef(5, 1, i);
		glRotatef(90.f, 1, 0, 0);
		glutSolidCube(1);
		glPopMatrix();
	}


	/// /////////////// ///

	for (int i = 2; i > -3; i--) {
		glPushMatrix();
		glTranslatef(1, 1, i);
		glRotatef(90.f, 1, 0, 0);
		glutSolidCube(1);
		glPopMatrix();
	}

	/// /////////////// ///

	for (int i = 2; i > -3; i--) {
		glPushMatrix();
		glTranslatef(3, 1, i);
		glRotatef(90.f, 1, 0, 0);
		glutSolidCube(1);
		glPopMatrix();
	}

	/// /////////////// ///

	for (int i = 7; i > -7; i--) {
		if ((i != 4) && (i != 2)) {
			glPushMatrix();
			glTranslatef(i, 1, -2);
			glRotatef(90.f, 1, 0, 0);
			glutSolidCube(1);
			glPopMatrix();
		}

	}

	/// /////////////// ///

	for (int i = 9; i > -5; i--) {
		glPushMatrix();
		glTranslatef(i, 1, -5);
		glRotatef(90.f, 1, 0, 0);
		glutSolidCube(1);
		glPopMatrix();
	}
	/// /////////////// ///

	for (int i = -2; i > -9; i--) {
		glPushMatrix();
		glTranslatef(-7, 1, i);
		glRotatef(90.f, 1, 0, 0);
		glutSolidCube(1);
		glPopMatrix();
	}

	/// /////////////// ///

	for (int i = -5; i > -9; i--) {
		glPushMatrix();
		glTranslatef(-5, 1, i);
		glRotatef(90.f, 1, 0, 0);
		glutSolidCube(1);
		glPopMatrix();
	}

	/// /////////////// ///

	for (int i = -2; i < 9; i++) {
		if ((i != 1) && (i != 3)) {
			glPushMatrix();
			glTranslatef(i, 1, 4);
			glRotatef(90.f, 1, 0, 0);
			glutSolidCube(1);
			glPopMatrix();
		}
	}

	/// /////////////// ///

	for (int i = -6; i < 8; i++) {
		if ((i != 2) && (i != 4)) {
			glPushMatrix();
			glTranslatef(i, 1, -3);
			glRotatef(90.f, 1, 0, 0);
			glutSolidCube(1);
			glPopMatrix();
		}
	}


}

void drawChar() {
	glPushMatrix();
	glTranslatef(charx, chary, charz);
	glRotatef(charAngle, 0, 1, 0);
	glScalef(0.1, 0.1, 0.1);
	character.Draw();
	glPopMatrix();
	cout << "X:";
	cout << charx << endl;
	cout << "Z:";
	cout << charz << endl;
	glutPostRedisplay();
}
void timer(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000.0, timer, 0);
}

void camerafirst() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glRotatef(pitch, 1, 0, 0);
	glRotatef(-charAngle, 0, 1, 0);
	glTranslatef(-charx, -chary, -charz);
}

void camerathird() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glRotatef(pitch, 1, 0, 0);
	glRotatef(-charAngle, 0, 1, 0);
	if (charAngle == 5) {
		glTranslatef(-charx, -chary-1, -charz - 2);
	}
	if (charAngle == -85) {
		glTranslatef(-charx+2, -chary -1, -charz);
	}
	if (charAngle == -175) {
		glTranslatef(-charx, -chary - 1, -charz + 2);
	}
	if (charAngle == -265) {
		glTranslatef(-charx - 2, -chary - 1, -charz);
	}
}



void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 640 / 480, 0.001, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.look();
}

void calcPoints(int x) {
	if ((charx != -6) && (charz != -9)) {
		points += 1;
	}
	if (coins <= 0) {
		coins = 0;
	}
	if (coin1 && (charx == coin_x1) && (charz == coin_z1)) {
		coins += 5;
		PlaySound("coin", NULL, SND_ASYNC);
		coin1 = false;
		light1x += 2;

	}
	if (coin2 && (charx == coin_x2) && (charz == coin_z2)) {
		coins += 5;
		PlaySound("coin", NULL, SND_ASYNC);
		coin2 = false;
		light1x += 2;
	}
	if (coin3 && (charx == coin_x3) && (charz == coin_z3)) {
		coins += 5;
		PlaySound("coin", NULL, SND_ASYNC);
		coin3 = false;
		light1x += 2;
	}
	if (coin4 && (charx == coin_x4) && (charz == coin_z4)) {
		coins += 5;
		PlaySound("coin", NULL, SND_ASYNC);
		coin4 = false;
		light1x += 2;
	}
	if (coin5 && (charx == coin_x5) && (charz == coin_z5)) {
		coins += 5;
		PlaySound("coin", NULL, SND_ASYNC);
		coin5 = false;
		light1x += 0.2;
	}

	if (coin6 && (charx == coin_x6) && (charz == coin_z6)) {
		coins += 5;
		PlaySound("coin", NULL, SND_ASYNC);
		coin6 = false;
		light1x += 2;
	}
	if (coin7 && (charx == coin_x7) && (charz == coin_z7)) {
		coins += 5;
		PlaySound("coin", NULL, SND_ASYNC);
		coin7 = false;
		light1x += 2;
	}
	if (coin8 && (charx == coin_x8) && (charz == coin_z8)) {
		coins += 5;
		PlaySound("coin", NULL, SND_ASYNC);
		coin8 = false;
		light1x += 2;
	}
	if (coin9 && (charx == coin_x9) && (charz == coin_z9)) {
		coins += 5;
		PlaySound("coin", NULL, SND_ASYNC);
		coin9 = false;
		light1x += 2;
	}
	//cout << floor(points) << endl;
}
void print(float x, float y, float z, char* string)
{
	int len, i;
	glRasterPos3f(x, y, z);
	len = (int)strlen(string);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

void myKeyboardTwo(unsigned char button, int x, int y)
{
	switch (button)
	{
	case 'w':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 's':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case 27:
		exit(0);
		break;

	
	case 'f':
		first = true;
		third = false;
		init = false;
		break;

	case 't':
		third = true;
		first = false;
		init = false;
		break;

	case 'i':
		third = false;
		first = false;
		init = true;
		break;



	case 'j':

		if (charAngle == 5) {
			if (charx == -3 && charz > 4) {
				if (!(obs1 && charz == 10) && !(!obs1 && charz == 9))
					charz -= 2;
				else {
					charz--;
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
			if (charx == 1 && charz > 4) {
				if (!(obs2 && charz == 7))
					charz -= 2;
				else {
					charz--;
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
			if (charx == 3 && charz > 4) {
				charz -= 2;
			}
			if (charx == 8 && charz > -3) {
				if (!(obs3 && charz == -1))
					charz -= 2;
				else {
					charz--;
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
			if (charx == 4 && charz > -3 && charz < 2) {
				if (!(!obs3 && charz == 1))
					charz -= 2;
				else {
					charz--;
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
			if (charx == 2 && charz > -3 && charz < 2) {
				charz -= 2;
			}
			if (charx == -6 && charz > -8) {
				if (!(!obs6 && charz == -4))
					charz -= 2;
				else {
					charz--;
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
		}
		if (charAngle == -85 || charAngle == 95) {
			if (charx < 7 && charz == 3) {
				if (!(!(obs2) && charx == 4) && !(obs4 && charx == 0) && !(obs6 && charx == 0))
					charx += 2;
				else {
					charx++;
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
			if (charx == 1 && charz == 8) {
				if (!(!obs5 && charx == 0))
					charx += 2;
				else {
					charx++;
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
			if (charz == -4 && charx >= -6 && charx < 7) {
				if (!(!obs4 && charx == -3) && !((obs5 && charx == -6)))
					charx += 2;
				else {
					charx++;
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
		}
		if (charAngle == -175 || charAngle == 185) {

			if (charx == -3 && charz <= 7) {
				if (!(obs1 && charz == 6) && !(!obs1 && charz == 5))
					charz += 2;
				else {
					charz++;
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
			if (charx == 1 && charz < 7) {
				if (!(obs2 && charz == 3))
					charz += 2;
			}
			if (charx == 3 && charz < 7) {
				charz += 2;
			}
			if (charx == 8 && charz < 2) {
				if (!(obs3 && charz == -5))
					charz += 2;
			}
			if (charx == 4 && charz < 0) {
				if (!(!obs3 && charz == -3))
					charz += 2;
				else {
					charz++;
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
			if (charx == 2 && charz < 0) {
				charz += 2;
			}
			if (charx == -6 && charz < -5) {
				if (!(!obs6 && charz == -8))
					charz += 2;
				else {
					charz++;
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
		}
		if (charAngle == -265 || charAngle == 280) {
			if (charx > -2 && charz == 3) {
				if (!(!(obs2) && charx == 8) && !(obs4 && charx == 4) && !(obs6 && charx == 4))
					charx -= 2;
				else {
					charz--;
					coins--;

					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
			if (charx == 3 && charz == 8) {
				if (!(!obs5 && charx == 4))
					charx -= 2;
				else {
					charz--;
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
			if (charz == -4 && charx > -5 && charx <= 8) {
				if (!(!obs4 && charx == 1) && !((obs5 && charx == -2)))
					charx -= 2;
				else {
					charx--;
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
		}
		//cout << charAngle;
		break;
	}

	glutPostRedisplay();
}

void processSpecialKeysTwo(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:

		if (charAngle == 5) {
			if (charx == -3 && charz > 3) {
				if (!(obs1 && charz == 9) && !(!obs1 && charz == 8)) {
					charz--;
				}
				else {
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
			if (charx == 1 && charz > 3) {
				if (!(obs2 && charz == 6))
					charz--;
				else {
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
			if (charx == 3 && charz > 3) {
				charz--;
			}
			if (charx == 8 && charz > -4) {
				if (!(obs3 && charz == -2))
					charz--;
				else {
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
			if (charx == 4 && charz > -4 && charz < 3) {
				if (!(!obs3 && charz == 0))
					charz--;
				else {
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
			if (charx == 2 && charz > -4 && charz < 3) {
				charz--;
			}
			if (charx == -6 && charz > -9) {
				if (!(!obs6 && charz == -5))
					charz--;
				else {
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
		}
		if (charAngle == -175 || charAngle == 185) {
			if (charx == -3 && charz <= 8) {
				if (!(obs1 && charz == 7) && !(!obs1 && charz == 6))
					charz++;
				else {
					coins--;
				}
			}
			if (charx == 1 && charz < 8) {
				if (!(obs2 && charz == 4))
					charz++;
				else {
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
			if (charx == 3 && charz < 8) {
				charz++;
			}
			if (charx == 8 && charz < 3) {
				if (!(obs3 && charz == -4))
					charz++;
				else {
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
			if (charx == 4 && charz < 1) {
				if (!(!obs3 && charz == -2))
					charz++;
				else {
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
			if (charx == 2 && charz < 1) {
				charz++;
			}
			if (charx == -6 && charz < -4) {
				if (!(!obs6 && charz == -7))
					charz++;
				else {
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
		}
		if (charAngle == -265 || charAngle == 280) {
			if (charx > -3 && charz == 3) {
				if (!(!(obs2) && charx == 7) && !(obs4 && charx == 3) && !(obs6 && charx == 3))
					charx--;
				else {
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
			if (charx > 1 && charx <= 3 && charz == 8) {
				if (!(!obs5 && charx == 3))
					charx--;
				else {
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
			if (charz == -4 && charx > -6 && charx <= 8) {
				if (!(!obs4 && charx == 0) && !((obs5 && charx == -3)))
					charx--;
				else {
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
		}
		if (charAngle == -85 || charAngle == 95) {
			if (charx < 8 && charz == 3) {
				if (!(!(obs2) && charx == 5) && !(obs4 && charx == 1) && !(obs6 && charx == 1))
					charx++;
				else {
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
			if (charx >= 1 && charx < 3 && charz == 8) {
				if (!(!obs5 && charx == 1))
					charx++;
				else {
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
			if (charz == -4 && charx >= -6 && charx < 8) {
				if (!(!obs4 && charx == -2) && !((obs5 && charx == -5)))
					charx++;
				else {
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
		}
		break;
	case GLUT_KEY_RIGHT:
		if (charAngle == -265) {
			charAngle = 5;
		}
		else { charAngle -= 90; }
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void processSpecialKeysOne(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		if (charAngle == 5) {
			if (charx == -3 && charz > 6 && charz <= 9) {
				charz--;
				camera.moveZ(1);

			}

			if (charx == 6 && charz > 1 && charz <= 6) {
				if (!(!obs8 && charz == 3)) {
					charz--;
					camera.moveZ(1);

				}
				else {
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}

			if (charx == -3 && charz > -3 && charz <= 1) {
				if (!((!obs10) && charz == 1)) {
					charz--;
					camera.moveZ(1);

				}
				else {
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
			if (charx == -6 && charz > -9 && charz <= -3) {
				if (!(obs10 && charz == -4)) {
					charz--;
					camera.moveZ(1);

				}
				else {
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}


		}

		if (charAngle == -175 || charAngle == 185) {
			if (charx == -3 && charz >= 6 && charz < 9) {
				charz++;
				camera.moveZ(-1);


			}
			if (charx == 6 && charz >= 1 && charz < 6) {
				if (!(!obs8 && charz == 1)) {
					charz++;
					camera.moveZ(-1);
				}
				else {
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
			if (charx == -3 && charz >= -3 && charz < 1) {
				if (!((!obs10) && charz == -1)) {
					charz++;
					camera.moveZ(-1);
				}
				else {
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
			if (charx == -6 && charz >= -9 && charz < -3) {
				if (!(obs10 && charz == -6)) {
					charz++;
					camera.moveZ(-1);
				}
				else {
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}

		}
		if (charAngle == -265 || charAngle == 280) {
			if (charx > -3 && charx <= 6 && charz == 6) {
				if ((!((!obs7) && charx == 0)) && (!((obs7) && charx == 6)))
				{
					charx--;
					camera.moveX(1);
				}
				else {
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
			if (charx <= 6 && charx > -3 && charz == 1) {
				if (!(obs8 && charx == 5) && (!((!obs9) && charx == 3)))
				{
					charx--;
					camera.moveX(1);
				}
				else {
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}

			if (charx <= -3 && charx > -6 && charz == -3) {
				{charx--;
				camera.moveX(1); }
			}
			if (charx <= 7 && charx > 6 && charz == 4) {
				charx--;
			}

		}

		if (charAngle == -85 || charAngle == 95) {
			if (charx >= -3 && charx < 6 && charz == 6) {
				if (!((!obs7) && charx == -2) && (!((obs7) && charx == 4)))
				{
					charx++;
					camera.moveX(-1);
				}
				else {
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
			if (charx >= -3 && charx < 6 && charz == 1) {
				if (!(obs8 && charx == 3) && (!((!obs9) && charx == 1)))
				{
					charx++;
					camera.moveX(-1);
				}
				else {
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
			if (charx < -3 && charx >= -6 && charz == -3) {
				{charx++;
				camera.moveX(-1);
				}
			}
			if (charx < 7 && charx >= 6 && charz == 4) {
				charx++;
			}
		}

		break;
	case GLUT_KEY_RIGHT:
		if (charAngle == -265) {
			charAngle = 5;

		}
		else {
			charAngle -= 90;
		}
		break;
	default:
		break;
	}

	glutPostRedisplay();
}
void myKeyboardOne(unsigned char button, int x, int y)
{
	switch (button)
	{
	case 'w':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 's':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case 27:
		exit(0);
		break;

	case 'f':
		first = true;
		third = false;
		break;

	case 't':
		third = true;
		first = false;
		break;


	case 'j':
		if (charAngle == 5) {
			if (charx == -3 && charz > 7 && charz <= 9) {
				PlaySound("jump", NULL, SND_ASYNC);
				charz -= 2;
			}
			if (charx == 6 && charz > 2 && charz <= 6) {
				if (!(!obs8 && charz == 4)) {
					PlaySound("jump", NULL, SND_ASYNC);
					charz -= 2;
				}
				else {
					charz--;
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
			if (charx == -3 && charz > -2 && charz <= 1) {
				if (!((!obs10) && charz == 2)) {
					PlaySound("jump", NULL, SND_ASYNC);
					charz -= 2;
				}
				else {
					charz--;
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}

			if (charx == -6 && charz > -8 && charz <= -3) {
				if (!(obs10 && charz == -3)) {
					charz -= 2;
					PlaySound("jump", NULL, SND_ASYNC);
				}
				else {
					charz--;
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}

		}
		if (charAngle == -85 || charAngle == 95) {
			if (charx >= -3 && charx < 5 && charz == 6) {
				if (!((!obs7) && charx == -3) && (!((obs7) && charx == 3))) {
					PlaySound("jump", NULL, SND_ASYNC);
					charx += 2;
				}
				else {
					charx++;
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
			if (charx >= -3 && charx < 5 && charz == 1) {
				if (!(obs8 && charx == 2) && (!((!obs9) && charx == 0)) && (!(obs9 && charx == -1))) {
					PlaySound("jump", NULL, SND_ASYNC);
					charx += 2;
				}

				else {
					charx++;
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
			if (charx < -4 && charx >= -6 && charz == -3) {
				if (!(obs10 && charz == -8)) {
					PlaySound("jump", NULL, SND_ASYNC);
					charx += 2;
				}

				else {
					charx++;
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}

		}
		if (charAngle == -175 || charAngle == 185) {
			if (charx == -3 && charz >= 6 && charz < 8) {
				PlaySound("jump", NULL, SND_ASYNC);
				charz += 2;
			}
			if (charx == 6 && charz >= 1 && charz < 5) {
				if (!(!obs8 && charz == 0)) {
					PlaySound("jump", NULL, SND_ASYNC);
					charz += 2;
				}

				else {
					charz++;
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
			if (charx == -3 && charz >= -3 && charz < 0) {
				if (!((!obs10) && charz == -2)) {
					PlaySound("jump", NULL, SND_ASYNC);
					charz += 2;
				}
				else {
					charz++;
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
			if (charx == -6 && charz >= -9 && charz < -4) {
				if (!(obs10 && charz == -7)) {
					PlaySound("jump", NULL, SND_ASYNC);
					charz += 2;
				}
				else {
					charz++;
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
		}
		if (charAngle == -265 || charAngle == 280) {
			if (charx > -2 && charx <= 6 && charz == 6) {
				if (!((!obs7) && charx == 1) && (!((obs7) && charx == 7))) {
					PlaySound("jump", NULL, SND_ASYNC);
					charx -= 2;
				}
				else {
					charx--;
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
			if (charx <= 6 && charx > -2 && charz == 1) {
				if (!(obs8 && charx == 6) && (!((!obs9) && charx == 4)) && (!(obs9 && charx == 3))) {
					PlaySound("jump", NULL, SND_ASYNC);
					charx -= 2;
				}
				else {
					charx--;
					coins--;
					PlaySound("bom", NULL, SND_ASYNC);
				}
			}
			if (charx <= -3 && charx > -5 && charz == -3) {
				PlaySound("jump", NULL, SND_ASYNC);
				charx -= 2;
			}


		}
		break;
	}

	glutPostRedisplay();

}


void myDisplay()
{

	glPushMatrix();
	glRotatef(45, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	GLfloat lightIntensity[] = { 0.7, 0.7, 0.7, 1.0f };
	GLfloat lightPosition[] = { 0.0f, 100.0f, 0.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);

	// Draw Ground
	//ground();
	RenderGround();
	myInit();

	if (first == true) {
		camerafirst();
	}
	if (third == true) {
		camerathird();
		char* scoreDisplay[20];
		points = points;
		int pointsint = points / 100;
		sprintf((char*)scoreDisplay, "Time: %d", pointsint);
		print(charx, chary + 1, charz, (char*)scoreDisplay);
		cout << points << endl;
		char* livesDisplay[20];
		sprintf((char*)livesDisplay, "Coins: %d", coins);
		print(charx, chary + 1.1, charz, (char*)livesDisplay);
	}
	if (init == true) {
		myInit();
	}

	// Draw maze
	if (level2) {
		firstObstacle();
		secondObstacle();
		secondMaze();
		if (coin1) {
			coin(coin_x1, coin_z1);

		}
		if (coin2) {
			coin(coin_x2, coin_z2);

		}
		if (coin3) {
			coin(coin_x3, coin_z3);

		}
		if (coin4) {
			coin(coin_x4, coin_z4);

		}
		if (coin5) {
			coin(coin_x5, coin_z5);

		}

	}
	else {
		thirdObstacle();
		fourthObstacle();
		firstMaze();
		if (coin6) {
			coin(coin_x6, coin_z6);

		}
		if (coin7) {
			coin(coin_x7, coin_z7);

		}
		if (coin8) {
			coin(coin_x8, coin_z8);

		}
		if (coin9) {
			coin(coin_x9, coin_z9);

		}

	}
	rotAngle += 1;
	calcPoints(0);

	if ((!level2) && (charx == -6) && (charz == -9) &&
		coin6 == false &&
		coin7 == false &&
		coin8 == false &&
		coin9 == false) {
		level2 = true;
		coin1 = true;
		coin2 = true;
		coin3 = true;
		coin4 = true;
		coin5 = true;
		coin6 = false;
		coin7 = false;
		coin8 = false;
		coin9 = false;
		points = 0;
		charx = -3;
		charz = 9;
		light1x = 0;
		PlaySound("yay", NULL, SND_ASYNC);
	}
	else if ((!level2) && (charx == -6) && (charz == -9) && coins < 20 &&
		coin6 == false &&
		coin7 == false &&
		coin8 == false &&
		coin9 == false) {
		coins = 0;
		coin6 = true;
		coin7 = true;
		coin8 = true;
		coin9 = true;
		charx = -3;
		charz = 9;
		light1x = 0;
	}
	if (level2 && (charx == -6) && (charz == -9) && coin1 == false &&
		coin2 == false &&
		coin3 == false &&
		coin4 == false &&
		coin5 == false) {
		PlaySound("yay", NULL, SND_ASYNC);
		exit(0);
	}
	else if (level2 && (charx == -6) && (charz == -9)) {
		coins = coins - 25;
		coin1 = true;
		coin2 = true;
		coin3 = true;
		coin4 = true;
		coin5 = true;
		charx = -3;
		charz = 9;
		light1x = 0;
	}

	// Draw character
	drawChar();
	lightOne();
	lightTwo();
	lightThree();
	if (level2) {

		glutKeyboardFunc(myKeyboardTwo);

		glutSpecialFunc(processSpecialKeysTwo);


	}
	else {
		glutKeyboardFunc(myKeyboardOne);

		glutSpecialFunc(processSpecialKeysOne);
	}

	// Draw house Model
	glPushMatrix();
	glTranslatef(-6, 0.3, -9);
	glRotatef(90.f, 1, 0, 0);
	glScalef(0.3, 0.3, 0.3);
	model_house.Draw();
	glPopMatrix();


	//glColor3f(1, 0, 0);
	char* scoreDisplay[20];
	points = points;
	int pointsint = points / 100;
	sprintf((char*)scoreDisplay, "Time: %d", pointsint);
	print(charx, chary+1, charz, (char*)scoreDisplay);
	cout << points << endl;
	char* livesDisplay[20];
	sprintf((char*)livesDisplay, "Coins: %d", coins);
	print(charx, chary+0.3, charz, (char*)livesDisplay);


	//sky box
	glPushMatrix();
	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	glTranslated(50, 0, 0);
	glRotated(90, 1, 0, 1);
	if (level2) {
		glBindTexture(GL_TEXTURE_2D, sky);
	}
	else {
		glBindTexture(GL_TEXTURE_2D, skyDay);
	}
	gluQuadricTexture(qobj, true);
	gluQuadricNormals(qobj, GL_SMOOTH);
	gluSphere(qobj, 100, 100, 100);
	gluDeleteQuadric(qobj);
	glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();
}

void myMotion(int x, int y)
{
	y = HEIGHT - y;

	if (cameraZoom - y > 0)
	{
		Eye.x += -0.1;
		Eye.z += -0.1;
	}
	else
	{
		Eye.x += 0.1;
		Eye.z += 0.1;
	}

	cameraZoom = y;

	glLoadIdentity();	//Clear Model_View Matrix

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);	//Setup Camera with modified paramters

	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glutPostRedisplay();	//Re-draw scene 
}

void myMouse(int button, int state, int x, int y)
{
	y = HEIGHT - y;

	if (state == GLUT_DOWN)
	{
		cameraZoom = y;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (charAngle == -265) {
			charAngle = 5;
		}
		else { charAngle -= 90; }
	}

	glutPostRedisplay();
}

void myReshape(int w, int h)
{
	if (h == 0) {
		h = 1;
	}

	WIDTH = w;
	HEIGHT = h;

	// set the drawable region of the window
	glViewport(0, 0, w, h);

	// set up the projection matrix 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, (GLdouble)WIDTH / (GLdouble)HEIGHT, zNear, zFar);

	// go back to modelview matrix so we can move the objects about
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
}

void LoadAssets()
{
	// Loading Model files
	model_house.Load("Models/house/house.3DS");
	model_tree.Load("Models/tree/Tree1.3ds");
	character.Load("Models/character/character/Toy N150319.3ds");
	// Loading texture files
	tex_moon.Load("Textures/Moon.bmp");
	tex_sand.Load("Textures/sand.bmp");
	loadBMP(&sky, "Textures/skynight.bmp", true);
	loadBMP(&skyDay, "Textures/blu-sky-3.bmp", true);
	loadBMP(&earth, "Textures/earth.bmp", true);
	loadBMP(&cactus, "Textures/cactus.bmp", true);
	loadBMP(&galaxy, "Textures/SPACE.bmp", true);
	loadBMP(&sandObs, "Textures/sandObs.bmp", true);
	loadBMP(&gold, "Textures/gold.bmp", true);
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(WIDTH, HEIGHT);

	glutInitWindowPosition(100, 100);

	glutCreateWindow("Project");

	glutDisplayFunc(myDisplay);

	genRand();
	randCoins();

	if (level2) {
		glutKeyboardFunc(myKeyboardTwo);

		glutSpecialFunc(processSpecialKeysTwo);
	}
	if (!level2) {
		glutKeyboardFunc(myKeyboardOne);

		glutSpecialFunc(processSpecialKeysOne);
	}

	glutMotionFunc(myMotion);

	glutMouseFunc(myMouse);
	glutReshapeFunc(myReshape);
	myInit();

	LoadAssets();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glutTimerFunc(1000.0, timer, 0);
	glShadeModel(GL_SMOOTH);

	glutMainLoop();
}