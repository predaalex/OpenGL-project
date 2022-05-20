//SURSA:  lighthouse3D:  http://www.lighthouse3d.com/tutorials/glut-tutorial/keyboard-example-moving-around-the-world/ 

#include<gl/freeglut.h>
#include <iostream>
#include<math.h>
#include <Windows.h>
#include <WinUser.h>
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
		if (yAngle - diffY * 0.0015  >= -1.7 && yAngle - diffY * 0.0015 <= 1.7)
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

void brad() {
	glPushMatrix();
	glColor3f(0.5f, 0.35f, 0.05f);
	glTranslated(5, 0, 0);
	glutSolidCylinder(0.2, 2, 10, 2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0.2f, 0);
	glRotated(90, 0, 0, 0);
	glTranslated(5, 0, 1);
	glutSolidCone(0.7f, 2, 10, 2);
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

void renderScene(void) {
	mousePosition();
	// Clear Color and Depth Buffers

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	gluLookAt(x, y, z,
		x + lx, y + ly, z + lz,
		0.0f, 1.1f, 0.0f);

	// Draw ground
	glColor3f(0.5, 0.2, 0);
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(-100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();

	glPushMatrix();
	glTranslatef(0 * 10.0, 0, 0 * 10.0);
	glColor3d(0.2, 0.0, 0.6);
	copac();
	brad();
	semnDeCirculatie();
	glPopMatrix();
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

