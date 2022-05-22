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

float yAngle = 0.0f;

POINT p;
bool start = false;



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

int keybBackground, currentColor;

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

	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glTranslated(-5, 1.5, 0);
	glRotated(90, 1, 0, 0);
	glutSolidCylinder(0.03, 1.5, 20, 3);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0, 0.2);
	glTranslated(-5, 1.5, 0.03);
	glutSolidCylinder(0.35, 0.03, 20, 3);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslated(-5, 1.5, 0.051);
	glScaled(4.8, 1.7, 0.2);
	glutSolidCube(0.1);
	glPopMatrix();

}

void masina(float x = 0, float y = -0.1, float z = 2) {
	//cadru 
	
	glColor3f(0.4, 0.4, 0.1);
	glPushMatrix();
	glTranslatef(x + 0, y + 0.6, z + 0);
	glScalef(2, 0.75, 1);
	glutSolidCube(1);	
	glPopMatrix();

	// partea de sus a masinii
	glColor3f(0.4, 0.4, 0.1);
	glPushMatrix();
	glTranslatef(x + 0, y + 1, z + 0);
	glScalef(0.75, 0.75, 0.99);
	glutSolidCube(1);
	glPopMatrix();

	//parbriz + luneta
	glColor3f(0.9, 0.9, 0.9);
	glPushMatrix();
	glTranslatef(x + 0, y + 1, z + 0);
	glScalef(0.77, 0.60, 0.85);
	glutSolidCube(1);
	glPopMatrix();

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
	glColor3f(1, 1, 0);
	glPushMatrix();
	glTranslatef(x + 1 , y + 0.65, z + -0.3);
	glRotatef(90, 0, 1, 0);
	glutSolidCylinder(0.06, 0.06, 20, 20);
	glPopMatrix();

	//far dreapta
	glColor3f(1, 1, 0);
	glPushMatrix();
	glTranslatef(x + 1 , y + 0.65, z + 0.3);
	glRotatef(90, 0, 1, 0);
	glutSolidCylinder(0.06, 0.06, 20, 20);
	glPopMatrix();
}

void strada() {
	
	//asfalt
	
	glPushMatrix();
	glColor3f(0.1, 0.03, 0.03);
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.01f, -4.0f);
	glVertex3f(-100.0f, 0.01f, 4.0f);
	glVertex3f(100.0f, 0.01f, 4.0f);
	glVertex3f(100.0f, 0.01f, -4.0f);
	glEnd();
	glPopMatrix();

	// dunga centru carosabil
	for (int i = -10; i < 10; i++) {

		glPushMatrix();
		glColor3f(0.8, 0.8, 0.8);
		glBegin(GL_QUADS);
		glVertex3f((i * 10), 0.02f, -0.1f);
		glVertex3f((i * 10), 0.02f, 0.1f);
		glVertex3f(((i * 10) - 7), 0.02f, 0.1f);
		glVertex3f(((i * 10) - 7), 0.02f, -0.1f);
		glEnd();
		glPopMatrix();

	}

	// dungi laterale ale carosabililui
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.02f, -3.9f);
	glVertex3f(-100.0f, 0.02f, -3.8f);
	glVertex3f(100.0f, 0.02f, -3.8f);
	glVertex3f(100.0f, 0.02f, -3.9f);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.02f, 3.9f);
	glVertex3f(-100.0f, 0.02f, 3.8f);
	glVertex3f(100.0f, 0.02f, 3.8f);
	glVertex3f(100.0f, 0.02f, 3.9f);
	glEnd();

}

void brad(float x = 0, float y = 0, float z = 0) {
	glPushMatrix();
	glColor3f(0.5f, 0.35f, 0.05f);
	glTranslated(x + 0, y + 0, z + 0);
	glRotatef(270, 1, 0, 0);
	glutSolidCylinder(0.2, 1.2, 20, 20);
	glPopMatrix();



	float j = 1.2;

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
	// SOIL_free_image_data(image);
	// glBindTexture(GL_TEXTURE_2D, 0);

}

void renderScene(void) {
	mousePosition();
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

	glPushMatrix();
	glTranslatef(0 * 10.0, 0, 0 * 10.0);
	glColor3d(0.2, 0.0, 0.6);

	// padure brazi
	for (float i = -95; i <= 95; i += 5)
		for (float j = -30; j <= 30; j += 5) 
			if(abs(j) > 15)
				brad(i, 0, j);

	// miscare masina
	masina(iii);
	iii += 0.05;
	if (iii > 100)
		iii = -100;


	//copac();
	//semnDeCirculatie();

	glPopMatrix();
	glutSwapBuffers();
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



void Initialize(int key)
{
	switch (key)
	{
	case 0:
		glClearColor(0.0, 0.0, 0.0, 1.0);
		break;
	case 1:
		glClearColor(1, 0.0, 0.0, 0.0);
		keybBackground = 1;
		break;
	case 2:
		glClearColor(0.0, 0.0, 0.0, 0.0);
		keybBackground = 2;
		break;
	case 3:
		glClearColor(0.05, 0.05, 0.8, 0.0);
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
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Black", 2);
	glutAddMenuEntry("Blue", 3);

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

