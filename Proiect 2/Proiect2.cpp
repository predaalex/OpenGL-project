#include<gl/freeglut.h>
#include <iostream>
#include<math.h>
#include <Windows.h>
#include <WinUser.h>
#include "SOIL.h"

#define PI 3.1415927

#define middleX 960;
#define middleY 540;
// angle of rotation for the camera direction
float angle = 0.0;
// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f, ly = 1;
// XZ position of the camera
float x = 0.0f, z = 5.0f, y = 1.0f;
float lateralX, lateralY, lateralZ, lAngle;

int keybBackground, currentColor;

float yAngle = 0.0f;

POINT p;
bool start = false;


float iii = -100;
// -----------------------------------------


const double TWO_PI = 6.2831853;
GLsizei winWidth = 500, winHeight = 500;
GLuint regHex;
static GLfloat rotTheta = 0.0;

class scrPt
{
public:
	GLint x, y;
};


GLfloat texpts[2][2][2] = { {{1.0, 1.0}, {1.0, 0.0}},
			{{0.0, 1.0}, {0.0, 0.0}} };

#define	imageWidth 64
#define	imageHeight 64

GLubyte image[3 * imageWidth * imageHeight];
GLuint texture1;

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-20.0, 780.0, 0.0, 600.0, -1.0, 1.0);

	scrPt hexVertex;
	GLdouble hexTheta;
	GLint k;

	glClearColor(1.0, 1.0, 1.0, 1.0);
	regHex = glGenLists(1);
	glNewList(regHex, GL_COMPILE);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (k = 0; k < 31; k++)
	{
		hexTheta = TWO_PI * k / 31;
		hexVertex.x = 100 * cos(hexTheta);
		hexVertex.y = 100 * sin(hexTheta);
		glVertex2i(hexVertex.x, hexVertex.y);
	}
	glEnd();
	glEndList();

}

void changeSize(int w, int h)
{

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;

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

#pragma region Obiecte

void brad(float x = 0, float y = 0, float z = 0) {
	GLfloat trunchi[] = { 0.5f, 0.35f, 0.05f, 1 };
	GLfloat frunze[] = { 0, 0.3, 0, 1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, trunchi);

	glPushMatrix();
	glColor3f(0.5f, 0.35f, 0.05f);
	glTranslated(x + 0, y + 0, z + 0);
	glRotatef(270, 1, 0, 0);
	glutSolidCylinder(0.2, 1.2, 20, 20);
	glPopMatrix();



	float j = 1.2;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, frunze);
	for (float i = 10; i > 0; i--) {
		glPushMatrix();
		glColor3f(0, 0.3, 0);
		glTranslated(x + 0, y + j, z + 0);
		glRotatef(270, 1, 0, 0);
		glutSolidCone(0.1 * i, 0.5f, 5, 2);
		glPopMatrix();

		j += 0.4;
	}
}

void copac() {

	glColor3f(1.0f, 1.0f, 1.0f);

	// Draw Body
	//glTranslatef(0.0f, 0.75f, 0.0f);
	//glutSolidSphere(0.75f, 20, 20);
	glColor3f(0, 0.9, 0);


	// Draw Head
	glPushMatrix();
	glTranslatef(0.0f, 1.75f, 0.0f);
	glutSolidSphere(1, 20, 20);

	glPopMatrix();
	// Draw Eyes
	if (currentColor == 0)
		glColor3f(1, 0, 0);
	if (currentColor == 1)
		glColor3f(0.7, 0, 0);

	glPushMatrix();
	glTranslatef(0.90f, 1.20f, 0.18f);
	glutSolidSphere(0.15f, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.0f, 1.50f, 0.18f);
	glutSolidSphere(0.15f, 10, 10);
	glPopMatrix();

	glColor3f(0.5f, 0.35f, 0.05f);
	glTranslated(0, -1, 0);
	glRotatef(270, 1, 0, 0);
	glutSolidCone(1.0f, 2.5f, 10, 2);
	glPopMatrix();
}

void semnDeCirculatie() {

	GLfloat stalp[] = { 0.5, 0.5, 0.5, 1 };
	GLfloat cercSemn[] = { 1, 0, 0.2, 1 };
	GLfloat dreptunghi[] = { 1, 1, 1, 1 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, stalp);

	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glTranslated(-5, 1.5, 0);
	glRotated(90, 1, 0, 0);
	glutSolidCylinder(0.03, 1.5, 20, 3);
	glPopMatrix();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cercSemn);
	glPushMatrix();
	glColor3f(1, 0, 0.2);
	glTranslated(-5, 1.5, 0.03);
	glutSolidCylinder(0.35, 0.03, 20, 3);
	glPopMatrix();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, dreptunghi);
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslated(-5, 1.5, 0.051);
	glScaled(4.8, 1.7, 0.2);
	glutSolidCube(0.1);
	glPopMatrix();

}

void masina(float x = 0, float y = -0.1, float z = 2) {
	//cadru 
	GLfloat caroserie[] = { 0.4, 0.4, 0.1, 1.0 };
	GLfloat plafon[] = { 0.4, 0.4, 0.1, 1 };
	GLfloat geamuri[] = { 0.9, 0.9, 0.9, 1 };
	GLfloat roti[] = { 0.2, 0.2, 0.2, 1 };
	GLfloat faruri[] = { 1, 1, 0, 1 };
	GLfloat stopuri[] = { 0.8, 0, 0, 1 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, caroserie);
	//cadru

	glColor3f(0.4, 0.4, 0.1);
	glPushMatrix();
	glTranslatef(x + 0, y + 0.6, z + 0);
	glScalef(2, 0.75, 1);
	glutSolidCube(1);
	glPopMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, plafon);
	// partea de sus a masinii
	glColor3f(0.4, 0.4, 0.1);
	glPushMatrix();
	glTranslatef(x + 0, y + 1, z + 0);
	glScalef(0.75, 0.75, 0.99);
	glutSolidCube(1);
	glPopMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, geamuri);
	//parbriz + luneta
	glColor3f(0.9, 0.9, 0.9);
	glPushMatrix();
	glTranslatef(x + 0, y + 1, z + 0);
	glScalef(0.77, 0.60, 0.85);
	glutSolidCube(1);
	glPopMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, roti);
	//roata stanga spate
	glColor3f(0.2, 0.2, 0.2);
	glPushMatrix();
	glTranslatef(x + 0.5, y + 0.3, z + 0.5);
	glutSolidCylinder(0.2, 0.2, 20, 20);
	glPopMatrix();


	//roata stanga fata
	glColor3f(0.2, 0.2, 0.2);
	glPushMatrix();
	glTranslatef(x + -0.5, y + 0.3, z + 0.5);
	glutSolidCylinder(0.2, 0.2, 20, 20);
	glPopMatrix();

	//roata dreapta spate
	glColor3f(0.2, 0.2, 0.2);
	glPushMatrix();
	glTranslatef(x + 0.5, y + 0.3, z + -0.7);
	glutSolidCylinder(0.2, 0.2, 20, 20);
	glPopMatrix();


	//roata dreapta fata
	glColor3f(0.2, 0.2, 0.2);
	glPushMatrix();
	glTranslatef(x + -0.5, y + 0.3, z + -0.7);
	glutSolidCylinder(0.2, 0.2, 20, 20);
	glPopMatrix();

	//stop stanga
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, stopuri);
	glColor3f(0.8, 0, 0);
	glPushMatrix();
	glTranslatef(x + -1.05, y + 0.65, z + -0.3);
	glRotatef(90, 0, 1, 0);
	glutSolidCylinder(0.06, 0.06, 20, 20);
	glPopMatrix();

	//stop dreapta
	glColor3f(0.8, 0, 0);
	glPushMatrix();
	glTranslatef(x + -1.05, y + 0.65, z + 0.3);
	glRotatef(90, 0, 1, 0);
	glutSolidCylinder(0.06, 0.06, 20, 20);
	glPopMatrix();

	//far stanga
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, faruri);
	glColor3f(1, 1, 0);
	glPushMatrix();
	glTranslatef(x + 1, y + 0.65, z + -0.3);
	glRotatef(90, 0, 1, 0);
	glutSolidCylinder(0.06, 0.06, 20, 20);
	glPopMatrix();

	//far dreapta
	glColor3f(1, 1, 0);
	glPushMatrix();
	glTranslatef(x + 1, y + 0.65, z + 0.3);
	glRotatef(90, 0, 1, 0);
	glutSolidCylinder(0.06, 0.06, 20, 20);
	glPopMatrix();
}

void masinaPolitie(float x = 0, float y = 0, float z = 0)
{
	GLfloat caroserieAlb[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat caroserieBleumarin[] = { 0.0, 0.0, 0.2, 1.0 };
	GLfloat geam[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat cauciuc[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat janta[] = { 0.5, 0.5, 0.5 , 1.0 };
	GLfloat ax[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat semnalizare[] = { 0.8, 0.3, 0.0, 1.0 };
	GLfloat girofar[] = { 0.8, 0.1, 0.1, 0.6 };
	GLfloat faruri[] = { 0.8, 0.8, 0.0, 1.0 };
	GLfloat stopuri[] = { 0.8, 0, 0, 1.0 };
	
	// spate
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, caroserieBleumarin);
	glColor3f(0.0, 0.0, 0.2);
	glPushMatrix();
	glTranslatef(x + 0, y + 0.4, z + 0);
	glScalef(1, 0.5, 1.5);
	glutSolidCube(1);
	glPopMatrix();

	//portiere
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, caroserieAlb);
	glColor3f(0.8, 0.8, 0.8);
	glPushMatrix();
	glTranslatef(x + 1, y + 0.4, z + 0);
	glScalef(1, 0.5, 1.5);
	glutSolidCube(1);
	glPopMatrix();

	// capota
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, caroserieBleumarin);
	glColor3f(0.0, 0.0, 0.2);
	glPushMatrix();
	glTranslatef(x + 2, y + 0.4, z + 0);
	glScalef(1, 0.5, 1.5);
	glutSolidCube(1);
	glPopMatrix();

	// faruri
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, faruri);
	glColor3f(0.8, 0.8, 0.0);
	glPushMatrix();
	glTranslatef(x + 2.33, y + 0.5, z + 0.5);
	glRotatef(90, 0, 1, 0);
	glutSolidCylinder(0.1, 0.2, 20, 20);
	glPopMatrix();

	glColor3f(0.8, 0.8, 0.0);
	glPushMatrix();
	glTranslatef(x + 2.33, y + 0.5, z - 0.5);
	glRotatef(90, 0, 1, 0);
	glutSolidCylinder(0.1, 0.2, 20, 20);
	glPopMatrix();

	// stopuri
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, stopuri);
	glColor3f(0.8, 0, 0);
	glPushMatrix();
	glTranslatef(x - 0.4, y + 0.5, z - 0.5);
	glScalef(0.3, 0.1, 0.3);
	glutSolidCube(1);
	glPopMatrix();

	glColor3f(0.8, 0, 0);
	glPushMatrix();
	glTranslatef(x - 0.4, y + 0.5, z + 0.5);
	glScalef(0.3, 0.1, 0.3);
	glutSolidCube(1);
	glPopMatrix();

	// semnalizari
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, semnalizare);
	glColor3f(0.8, 0.5, 0);
	glPushMatrix();
	glTranslatef(x + 1.7, y + 0.5, z + 0.61);
	glScalef(0.1, 0.05, 0.3);
	glutSolidCube(1);
	glPopMatrix();

	glColor3f(0.8, 0.5, 0);
	glPushMatrix();
	glTranslatef(x + 1.7, y + 0.5, z - 0.61);
	glScalef(0.1, 0.05, 0.3);
	glutSolidCube(1);
	glPopMatrix();

	// partea de sus a masinii
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, caroserieBleumarin);
	glColor3f(0, 0, 0.2);
	glPushMatrix();
	glTranslatef(x + 0.8, y + 0.83, z + 0);
	glScalef(1.2, 0.4, 1.3);
	glutSolidCube(1);
	glPopMatrix();

	// geamuri
	// parbriz
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, geam);
	glColor3f(0.8, 0.8, 0.8);
	glPushMatrix();
	glTranslatef(x + 1.36, y + 0.83, z + 0);
	glScalef(0.1, 0.33, 1.2);
	glutSolidCube(1);
	glPopMatrix();

	// geam stanga
	glColor3f(0.8, 0.8, 0.8);
	glPushMatrix();
	glTranslatef(x + 0.8, y + 0.83, z - 0.61);
	glScalef(1, 0.33, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	// geam dreapta
	glColor3f(0.8, 0.8, 0.8);
	glPushMatrix();
	glTranslatef(x + 0.8, y + 0.83, z + 0.61);
	glScalef(1, 0.33, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	// luneta
	glColor3f(0.8, 0.8, 0.8);
	glPushMatrix();
	glTranslatef(x + 0.24, y + 0.83, z + 0);
	glScalef(0.1, 0.33, 1);
	glutSolidCube(1);
	glPopMatrix();

	// roti
	// spate dreapta
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cauciuc);
	glColor3f(0.1, 0.1, 0.1);
	glPushMatrix();
	glTranslatef(x + 0.1, y + 0.25, z + 0.6);
	glScalef(1, 1, 1);
	glutSolidCylinder(0.25, 0.2, 25, 20);
	glPopMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, janta);
	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix();
	glTranslatef(x + 0.1, y + 0.25, z + 0.61);
	glutSolidCylinder(0.17, 0.2, 25, 20);
	glPopMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ax);
	glColor3f(0.2, 0.2, 0.2);
	glPushMatrix();
	glTranslatef(x + 0.1, y + 0.25, z + 0.615);
	glutSolidCylinder(0.07, 0.2, 25, 20);
	glPopMatrix();

	// spate stanga
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cauciuc);
	glColor3f(0.1, 0.1, 0.1);
	glPushMatrix();
	glTranslatef(x + 0.1, y + 0.25, z - 0.8);
	glScalef(1, 1, 1);
	glutSolidCylinder(0.25, 0.2, 25, 20);
	glPopMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, janta);
	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix();
	glTranslatef(x + 0.1, y + 0.25, z - 0.81);
	glutSolidCylinder(0.17, 0.2, 25, 20);
	glPopMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ax);
	glColor3f(0.2, 0.2, 0.2);
	glPushMatrix();
	glTranslatef(x + 0.1, y + 0.25, z - 0.815);
	glutSolidCylinder(0.07, 0.2, 25, 20);
	glPopMatrix();

	// fata dreapta
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cauciuc);
	glColor3f(0.1, 0.1, 0.1);
	glPushMatrix();
	glTranslatef(x + 2, y + 0.25, z + 0.6);
	glScalef(1, 1, 1);
	glutSolidCylinder(0.25, 0.2, 25, 20);
	glPopMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, janta);
	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix();
	glTranslatef(x + 2, y + 0.25, z + 0.61);
	glutSolidCylinder(0.17, 0.2, 25, 20);
	glPopMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ax);
	glColor3f(0.2, 0.2, 0.2);
	glPushMatrix();
	glTranslatef(x + 2, y + 0.25, z + 0.615);
	glutSolidCylinder(0.07, 0.2, 25, 20);
	glPopMatrix();

	// fata stanga
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cauciuc);
	glColor3f(0.1, 0.1, 0.1);
	glPushMatrix();
	glTranslatef(x + 2, y + 0.25, z - 0.8);
	glScalef(1, 1, 1);
	glutSolidCylinder(0.25, 0.2, 25, 20);
	glPopMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, janta);
	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix();
	glTranslatef(x + 2, y + 0.25, z - 0.81);
	glutSolidCylinder(0.17, 0.2, 25, 20);
	glPopMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ax);
	glColor3f(0.2, 0.2, 0.2);
	glPushMatrix();
	glTranslatef(x + 2, y + 0.25, z - 0.815);
	glutSolidCylinder(0.07, 0.2, 25, 20);
	glPopMatrix();

	// girofar
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, girofar);
	glColor4f(0.8, 0.1, 0.1, 0.6);
	glPushMatrix();
	glTranslatef(x + 0.8, y + 1.2, z + 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 1, 1);
	glutSolidCylinder(0.1, 0.2, 25, 20);
	glPopMatrix();
}

#pragma endregion

void strada() {
	GLfloat asfalt[] = { 0.1, 0.03, 0.03, 1 };
	GLfloat dungiGalbene[] = { 0.8, 0.8, 0.0, 1 };
	GLfloat dungiAlbe[] = { 0.8, 0.8, 0.8, 1 };
	//GLfloat dungiAlbe[] = { 0.8, 0.8, 0.0, 1 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, asfalt);
	//asfalt

	glPushMatrix();
	glColor3f(0.1, 0.03, 0.03);
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.01f, -10.0f);
	glVertex3f(-100.0f, 0.01f, 10.0f);
	glVertex3f(100.0f, 0.01f, 10.0f);
	glVertex3f(100.0f, 0.01f, -10.0f);
	glEnd();
	glPopMatrix();

	// dungi  carosabil
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, dungiGalbene);

	glPushMatrix();
	glColor3f(0.8, 0.8, 0.0);

	glBegin(GL_QUADS);
	glVertex3f(-100, 0.02f, 0.1f);
	glVertex3f(-100, 0.02f, 0.2f);
	glVertex3f(100, 0.02f, 0.2f);
	glVertex3f(100, 0.02f, 0.1f);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(-100, 0.02f, -0.1f);
	glVertex3f(-100, 0.02f, -0.2f);
	glVertex3f(100, 0.02f, -0.2f);
	glVertex3f(100, 0.02f, -0.1f);
	glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, dungiAlbe);

	glColor3f(0.8, 0.8, 0.8);

	for (int i = -10; i < 10; i++) {

		glBegin(GL_QUADS);
		glVertex3f((i * 10), 0.02f, 4.9f);
		glVertex3f((i * 10), 0.02f, 5.1f);
		glVertex3f(((i * 10) - 7), 0.02f, 5.1f);
		glVertex3f(((i * 10) - 7), 0.02f, 4.9f);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f((i * 10), 0.02f, -5.1f);
		glVertex3f((i * 10), 0.02f, -4.9f);
		glVertex3f(((i * 10) - 7), 0.02f, -4.9f);
		glVertex3f(((i * 10) - 7), 0.02f, -5.1f);
		glEnd();
		glPopMatrix();

	}

	// dungi laterale ale carosabililui


	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.02f, -9.9f);
	glVertex3f(-100.0f, 0.02f, -9.8f);
	glVertex3f(100.0f, 0.02f, -9.8f);
	glVertex3f(100.0f, 0.02f, -9.9f);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.02f, 9.9f);
	glVertex3f(-100.0f, 0.02f, 9.8f);
	glVertex3f(100.0f, 0.02f, 9.8f);
	glVertex3f(100.0f, 0.02f, 9.9f);
	glEnd();

}

void LoadTexture(void)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	int width, height;
	unsigned char* image = SOIL_load_image("iarba.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	// glBindTexture(GL_TEXTURE_2D, 0);

}

#pragma region Functii mouse si tastatura

void mousePosition() {

	if (GetCursorPos((&p)) && start) {
		float diffX = p.x - middleX;
		float diffY = p.y - middleY;
		angle += diffX * 0.001;
		lx = sin(angle);
		lz = -cos(angle);
		if (yAngle - diffY * 0.0015 >= -1.7 && yAngle - diffY * 0.0015 <= 1.7)
		{
			yAngle -= diffY * 0.0015;
		}
		printf("%f\n", yAngle);
		ly = sin(yAngle);
		//std::cout << "Pozitie x mouse" << angle << std::endl;
		SetCursorPos(960, 540);

	}
}

void mouse2(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			start = false;
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
		}
		break;
	case GLUT_MIDDLE_BUTTON:
		if (state == GLUT_DOWN) {
			start = true;
			angle += 0.2;
			ly = sin(angle);
			glutSetCursor(GLUT_CURSOR_NONE);
		}
		break;

	}
}

void processNormalKeys(unsigned char key, int xx, int yy)
{
	float fraction = 0.1f;
	if (key == 'a') {
		std::cout << "old " << lx << '\n';
		lx = sin(angle + 80);
		lz = -cos(angle + 80);
		x += lx * fraction;
		z += lz * fraction;
		std::cout << "new " << lx << '\n';
	}
	if (key == 'd') {
		lx = sin(angle + 80);
		lz = -cos(angle + 80);
		x -= lx * fraction;
		z -= lz * fraction;
	}
	if (key == 'w') {
		x += lx * fraction;
		z += lz * fraction;
	}
	if (key == 's') {
		x -= lx * fraction;
		z -= lz * fraction;
	}
	if (key == 'm') {
		y += 0.1;
	}
	if (key == 'n') {
		y -= 0.1;
	}
	if (key == 'e') {
		yAngle += 0.1;
		ly = sin(yAngle);
	}
	if (key == 'r') {
		yAngle -= 0.1;
		ly = sin(yAngle);
	}
	if (key == 27)
		exit(0);
}

void processSpecialKeys(int key, int xx, int yy) {

	float fraction = 0.1f;

	switch (key) {
	case GLUT_KEY_LEFT:
		angle -= 0.03f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_RIGHT:
		angle += 0.03f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_UP:
		x += lx * fraction;
		z += lz * fraction;
		break;
	case GLUT_KEY_DOWN:
		x -= lx * fraction;
		z -= lz * fraction;
		break;
	case GLUT_KEY_F1:
		exit(0);
		break;
	}
}

#pragma endregion

void renderScene(void) {
	mousePosition();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	// sursa de lumina 0
	glEnable(GL_LIGHT0);
	GLfloat pozitial0[] = { 1.0, 5.0, 3.0, 0.0 };
	GLfloat rosu[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat alb[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat negru[] = { 0.0, 0.0, 0.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, pozitial0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, alb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, alb);
	//glLightfv (GL_LIGHT0, GL_DIFFUSE, alb);	
	glLightfv(GL_LIGHT0, GL_SPECULAR, negru);
	//glLightfv (GL_LIGHT0, GL_SPECULAR, rosu);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.1);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.2);
	// Clear Color and Depth Buffers

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	gluLookAt(x, y, z,
		x + lx, y + ly, z + lz,
		0.0f, 1.1f, 0.0f);

	// texture on ground
	glColor3f(0.5, 0.2, 0);
	glEnable(GL_TEXTURE_2D);
	LoadTexture();

	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0); glColor3f(1.0, 0.1, 0.1);  glVertex3f(-100.0f, 0.0f, -100.0f);
	glTexCoord2f(1.0, 0.0); glColor3f(0.1, 1.0, 0.1);  glVertex3f(-100.0f, 0.0f, 100.0f);
	glTexCoord2f(0.0, 0.0); glColor3f(1.0, 1.0, 0.1); glVertex3f(100.0f, 0.0f, 100.0f);
	glTexCoord2f(0.0, 1.0); glColor3f(0.0, 0.1, 1.0); glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	strada();

	// padure brazi
	for (float i = -95; i <= 95; i += 5)
		for (float j = -30; j <= 30; j += 5)
			if (abs(j) > 15)
				brad(i, 0, j);

	glPushMatrix();
	glRotated(90, 0, 1, 0);
	glTranslatef(17, 0, 0);

	semnDeCirculatie();
	glPopMatrix();
	//masina de politie

	masinaPolitie(iii - 10, 0, 2);

	// miscare masina
	masina(iii);
	iii += 0.1;
	if (iii > 100)
		iii = -100;

	glColor3d(0.2, 0.0, 0.6);

	

	//copac();
	//glRotatef(90, 0, 0, 1);
	
	glutSwapBuffers();
}

void Initialize(int key)
{
	switch (key)
	{
	case 0:
		glClearColor(1.0, 1.0, 1.0, 1.0);
		break;
	case 1:
		glClearColor(0.46, 0.80, 0.85, 0.8);
		keybBackground = 1;
		break;
	case 2:
		glClearColor(0.7, 0.34, 0, 0.8);
		keybBackground = 2;
		break;
	case 3:
		glClearColor(0.17, 0.17, 0.3, 0.8);
		keybBackground = 3;
		break;
	}

}

void callback_Main(int key)
{
	if (key == 0)
	{
		exit(0);
	}
}
void callback_Color(int key)
{
	currentColor = key;
}



int main(int argc, char** argv) {


	// init GLUT and create window
	int menuMain, menuBackground, menuColor;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);

	glutCreateWindow("Scena 3D cu oameni de zapada");

	init();

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle

	menuBackground = glutCreateMenu(Initialize);
	glutAddMenuEntry("Zi", 1);
	glutAddMenuEntry("Seara", 2);
	glutAddMenuEntry("Noapte", 3);

	menuColor = glutCreateMenu(callback_Color);
	glutAddMenuEntry("Light Red ", 0);
	glutAddMenuEntry("Dark Red ", 1);

	menuMain = glutCreateMenu(callback_Main);
	glutMouseFunc(mouse2);
	glutAddSubMenu("Culoare cer ", menuBackground);
	glutAddSubMenu("Culoare mere ", menuColor);
	glutAddMenuEntry("Iesire ", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();

	return 1;
}