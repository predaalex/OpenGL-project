
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <GL/freeglut.h>
#include <iostream>

using namespace std;

const double TWO_PI = 6.2831853;
double i = 0.;
// unde se va opri masina pe axa x, cand face schimbarea de benzi
double xFinal = 50;
double j = 1.0;
double k = 700;
bool faruri = TRUE;
bool girofar = TRUE;
double vitezaTrafic = 0.15;
GLsizei winWidth = 1000, winHeight = 800;
GLuint traficID;
double pozMere[20];
int nrMere = 0;
int masina = 0, culoare = 0;
static GLfloat rotTheta = 0.0;
int hitboxPlayer[5], hitboxObstacol[5];
bool hitbox = false;

class scrPt
{
public:
	GLfloat x, y, z;
	void print(const char* text = " ") {
		cout << text << ' ' << x << ' ' << y << ' ' << z << endl;
	}
	scrPt operator + (scrPt const& a) {
		scrPt res;
		res.x = x + a.x;
		res.y = y + a.y;
		res.z = z + a.z;
		return res;
	}
	scrPt operator - (scrPt const& a) {
		scrPt res;
		res.x = x - a.x;
		res.y = y - a.y;
		res.z = z - a.z;
		return res;
	}
};


void miscare(void) {
	// pentru girofar
	j += 0.05;
	if (j > 360) {
		j = 0;
	}
	/*
	if (j < 0) {
		j = 360;
	}
	*/
	// pentru schimbarea benzii
	if (i > xFinal) {
		i -= 0.5;
	}
	if (i < xFinal) {
		i += 0.5;
	}

	// pentru decor
	k -= 0.5;
	//if (k < -700)
	//	k = 700;


	glutPostRedisplay();
}

time_t start, finish;

static void init(void)
{
	time(&start);
	scrPt cerc;
	GLdouble theta;
	GLint aux;
	GLint n = 2000;

	// 159 / 255 , 61 / 255 , 0 , 1
	glClearColor(0.6235294, 0.239215, 0, 1);
	gluOrtho2D(-600, 600, -400, 400);


	traficID = glGenLists(1);



	for (aux = 0; aux < 20; aux++)
	{
		glColor3f(0, 1, 0);
		glRectf(20, 100 + aux * 20, 60, 160 + aux * 20);

		glColor3f(0.5, 0, 0.5);
		glRectf(-120, 250 + aux * 20, -80, 310 + aux * 20);
	}
	glEndList();

	// pentru opacitatea culorilor
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

int random(int min, int max) //range : [min, max]
{
	static bool first = true;
	if (first)
	{
		srand(time(NULL));
		first = false;
	}
	return min + rand() % ((max + 1) - min);
}

void DrawCircle(float cx, float cy, float r, int num_segments)
{
	glBegin(GL_POLYGON);
	for (int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

		float x = r * cosf(theta);//calculate the x component
		float y = r * sinf(theta);//calculate the y component

		glVertex2f(x + cx, y + cy);//output vertex

	}
	glEnd();
}

void mouse(int button, int state, int x, int y)
{
}

void processNormalKeys(unsigned char key, int x, int y)
{
	if (key == 'f')
	{
		faruri = !faruri;
		cout << "faruri =" << faruri << endl;
	}

	if (key == 'g')
	{
		girofar = !girofar;
		cout << "girofar = " << girofar << endl;
	}

	if (key == 'h')
	{
		hitbox = !hitbox;
	}
}

void processSpecialKeys(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT:
		if (xFinal > -350)
		{
			xFinal = xFinal - 200;
		}
		break;
	case GLUT_KEY_RIGHT:
		if (xFinal < 250)
		{
			xFinal = xFinal + 200;
		}
		break;
	default:
		break;
	}

}

void semnPrioritate(int x, int y) {

	//stalpul

	glColor3f(0.4, 0.4, 0.4);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2i(x + 15, y + 0);
	glVertex2i(x + 15, y + 55);
	glEnd();

	// panoul

	glColor3f(0.9, 0.9, 0);
	glBegin(GL_POLYGON);
	glVertex2f(x + 15, y + 45);
	glVertex2f(x - 15, y + 75);
	glVertex2f(x + 15, y + 105);
	glVertex2f(x + 45, y + 75);
	glEnd();

	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex2f(x + 15, y + 55);
	glVertex2f(x - 5, y + 75);
	glVertex2f(x + 15, y + 95);
	glVertex2f(x + 35, y + 75);
	glEnd();

}

void semnCedeazaTrecerea(int x, int y)
{
	//stalpul

	glColor3f(0.4, 0.4, 0.4);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2i(x + 15, y + 0);
	glVertex2i(x + 15, y + 55);
	glEnd();

	// panoul
	glColor3f(0.9, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(x + 15, y + 45);
	glVertex2f(x + 45, y + 105);
	glVertex2f(x - 15, y + 105);
	glEnd();

	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex2f(x + 15, y + 60);
	glVertex2f(x + 33, y + 100);
	glVertex2f(x - 3, y + 100);
	glEnd();
}

void semnInterzisAmbeleSensuri(int x, int y) {

	//stalpul

	glColor3f(0.4, 0.4, 0.4);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2i(x + 25, y + 0);
	glVertex2i(x + 25, y + 55);
	glEnd();

	// panoul
	glColor3f(0.9, 0, 0);
	DrawCircle(x + 25, y + 65, 30, 100);

	glColor3f(1, 1, 1);
	DrawCircle(x + 25, y + 65, 24, 100);
}

void semnPrioritateSpate(int x, int y)
{
	// panoul

	glColor3f(0.2, 0.2, 0.2);
	glBegin(GL_POLYGON);
	glVertex2f(x + 15, y + 45);
	glVertex2f(x - 15, y + 75);
	glVertex2f(x + 15, y + 105);
	glVertex2f(x + 45, y + 75);
	glEnd();

	//stalpul

	glColor3f(0.4, 0.4, 0.4);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2i(x + 15, y + 0);
	glVertex2i(x + 15, y + 55);
	glEnd();
}

void semnCedeazaTrecereaSpate(int x, int y)
{
	// panoul
	glColor3f(0.2, 0.2, 0.2);
	glBegin(GL_POLYGON);
	glVertex2f(x + 15, y + 45);
	glVertex2f(x + 45, y + 105);
	glVertex2f(x - 15, y + 105);
	glEnd();

	//stalpul

	glColor3f(0.4, 0.4, 0.4);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2i(x + 15, y + 0);
	glVertex2i(x + 15, y + 55);
	glEnd();
}

void semnRotundSpate(int x, int y)
{
	// panoul
	glColor3f(0.2, 0.2, 0.2);
	DrawCircle(x + 25, y + 65, 30, 100);

	//stalpul

	glColor3f(0.4, 0.4, 0.4);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2i(x + 25, y + 0);
	glVertex2i(x + 25, y + 55);
	glEnd();
}

int genPozMere()
{
	nrMere = random(7, 19);
	int x = 0, y = 0;
	for (int aux = 0; aux < 2 * nrMere; aux += 2)
	{
		while (pozMere[aux] == 0 || pozMere[aux + 1] == 0)
		{
			double c1 = random(x - 50, x + 50);
			double c2 = random(y + 40, y + 140);
			if (powf(c1, 2) + powf(c2 - 90, 2) <= 2500)
			{
				pozMere[aux] = c1;
				pozMere[aux + 1] = c2;
			}
		}
	}
	return nrMere;
}

void copac(int x, int y)
{
	// trunchi
	glColor3f(0.6, 0.4, 0.3);
	glBegin(GL_POLYGON);
	glVertex2f(x - 15, y);
	glVertex2f(x + 15, y);
	glVertex2f(x + 15, y + 60);
	glVertex2f(x - 15, y + 60);
	glEnd();

	// coroana
	glColor3f(0.0, 0.6, 0.0);
	DrawCircle(x, y + 90, 50, 50);
	glColor3f(1.0, 0.0, 0.0);

	//mere
	for (int aux = 0; aux < 2 * nrMere; aux += 2)
	{
		DrawCircle(x + pozMere[aux], y + pozMere[aux + 1], 5, 50);
	}
}

int offset = 0;

#pragma region Masini
void masinaPolitie(int x = 20, int y = -180)
{
	// MASINA DE POLITIE
	{
		// sasiu
		glColor3f(0, 0, 0);
		glRectf(x, y, x + 60, y + 35);
		glColor3f(1, 1, 1);
		glRectf(x, y + 35, x + 60, y + 65);
		glColor3f(0, 0, 0);
		glRectf(x, y + 65, x + 60, y + 90);


		// stopuri
		glColor3f(1, 0, 0);
		glRectf(x + 5, y - 5, x + 15, y);
		glColor3f(1, 0, 0);
		glRectf(x + 45, y - 5, x + 55, y);

		// faruri
		glColor3f(0.4, 0.4, 0);
		glRectf(x + 5, y + 90, x + 15, y + 95);
		glColor3f(0.4, 0.4, 0);
		glRectf(x + 45, y + 90, x + 55, y + 95);

		if (faruri == TRUE)
		{
			// faruri
			glColor3f(0.8, 0.5, 0);
			glRectf(x + 5, y + 90, x + 15, y + 95);
			glColor3f(0.8, 0.5, 0);
			glRectf(x + 45, y + 90, x + 55, y + 95);

			glColor3f(1, 1, 0);
			glBegin(GL_TRIANGLES);
			glVertex2f(x + 10, y + 95);
			glVertex2f(x - 20, y + 180);
			glVertex2f(x + 40, y + 180);

			glVertex2f(x + 50, y + 95);
			glVertex2f(x + 20, y + 180);
			glVertex2f(x + 80, y + 180);

			glEnd();
		}

		// GIROFAR
		glColor3f(0.6, 0.0, 0.0);
		DrawCircle(x + 30, y + 45, 5, 50);

		if (girofar == TRUE)
		{
			glPushMatrix();
			glTranslated(x + 30, y + 45, 0);
			glRotated(j, 0, 0, 1);
			glTranslated(-(x + 30), -(y + 45), 0);

			//lumini

			glColor3f(1.0, 0.1, 0.0);
			DrawCircle(x + 30, y + 45, 5, 50);

			glColor4f(1, 0, 0, 0.5);
			glBegin(GL_TRIANGLES);
			glVertex2f(x - 10, y + 65);
			glVertex2f(x + 30, y + 45);
			glVertex2f(x - 10, y + 35);
			glEnd();


			glColor4f(0, 0, 1, 0.5);
			glBegin(GL_TRIANGLES);
			glVertex2f(x + 30, y + 45);
			glVertex2f(x + 70, y + 65);
			glVertex2f(x + 70, y + 35);
			glEnd();
			glPopMatrix();
		}
		// hitbox

		hitboxPlayer[0] = x;
		hitboxPlayer[1] = x + 60;
		hitboxPlayer[2] = y;
		hitboxPlayer[3] = y + 90;

		if (hitbox == true)
		{
			glColor3f(1.0, 0.0, 0.0);
			glBegin(GL_LINE_LOOP);
			glVertex2d(hitboxPlayer[0], hitboxPlayer[2]);
			glVertex2d(hitboxPlayer[1], hitboxPlayer[2]);
			glVertex2d(hitboxPlayer[1], hitboxPlayer[3]);
			glVertex2d(hitboxPlayer[0], hitboxPlayer[3]);
			glEnd();
		}
		glPopMatrix();
		glFlush();
	}
}

void masinaSportVerde(int x = 20, int y = -180)
{
	// MASINA SPORT VERDE
	{
		glColor3f(0, 0.7, 0.1);
		glBegin(GL_POLYGON);
		// stanga jos
		glVertex2f(x + 10, y + 14);
		glVertex2f(x + 14, y + 10);


		// dreapta jos
		glVertex2f(x + 56, y + 10);
		glVertex2f(x + 60, y + 14);

		// stanga sus
		glVertex2f(x + 60, y + 106);
		glVertex2f(x + 56, y + 110);

		// dreapta sus
		glVertex2f(x + 14, y + 110);
		glVertex2f(x + 10, y + 106);

		glEnd();

		//parbriz
		glColor3f(0, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(x + 20, y + 75);
		glVertex2f(x + 20, y + 90);
		glVertex2f(x + 25, y + 95);
		glVertex2f(x + 45, y + 95);
		glVertex2f(x + 50, y + 90);
		glVertex2f(x + 50, y + 75);
		glEnd();

		//luneta stanga (depinde cum te uiti)
		glColor3f(0, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(x + 20, y + 25);
		glVertex2f(x + 20, y + 45);
		glVertex2f(x + 25, y + 55);
		glVertex2f(x + 30, y + 55);
		glVertex2f(x + 30, y + 25);
		glEnd();

		//luneta dreapta (depinde cum te uiti)
		glColor3f(0, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(x + 40, y + 25);
		glVertex2f(x + 40, y + 55);
		glVertex2f(x + 45, y + 55);
		glVertex2f(x + 50, y + 45);
		glVertex2f(x + 50, y + 25);
		glEnd();

		//geam stanga
		glColor3f(0, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(x + 17, y + 53);
		glVertex2f(x + 21, y + 58);
		glVertex2f(x + 21, y + 68);
		glVertex2f(x + 17, y + 73);
		glEnd();

		//geam dreapta
		glColor3f(0, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(x + 52, y + 53);
		glVertex2f(x + 48, y + 58);
		glVertex2f(x + 48, y + 68);
		glVertex2f(x + 52, y + 73);
		glEnd();

		glColor3f(0.7, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(x + 20, y + 10);
		glVertex2f(x + 30, y + 10);
		glVertex2f(x + 30, y + 15);
		glVertex2f(x + 20, y + 15);
		glEnd();

		glColor3f(0.7, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(x + 40, y + 10);
		glVertex2f(x + 50, y + 10);
		glVertex2f(x + 50, y + 15);
		glVertex2f(x + 40, y + 15);
		glEnd();

		//faruri

		glColor3f(0.4, 0.4, 0);
		glBegin(GL_POLYGON);
		glVertex2f(x + 20, y + 105);
		glVertex2f(x + 30, y + 105);
		glVertex2f(x + 30, y + 110);
		glVertex2f(x + 20, y + 110);
		glEnd();

		glColor3f(0.4, 0.4, 0);
		glBegin(GL_POLYGON);
		glVertex2f(x + 40, y + 105);
		glVertex2f(x + 50, y + 105);
		glVertex2f(x + 50, y + 110);
		glVertex2f(x + 40, y + 110);
		glEnd();

		if (faruri == TRUE)
		{
			// faruri
			glColor3f(0.8, 0.8, 0);
			glRectf(x + 20, y + 105, x + 30, y + 110);
			glColor3f(0.8, 0.8, 0);
			glRectf(x + 40, y + 105, x + 50, y + 110);

			glColor3f(1, 1, 0);
			glBegin(GL_TRIANGLES);
			glVertex2f(x + 25, y + 110);
			glVertex2f(x + 55, y + 210);
			glVertex2f(x - 5, y + 210);

			glVertex2f(x + 45, y + 110);
			glVertex2f(x + 75, y + 210);
			glVertex2f(x + 15, y + 210);

			glEnd();
		}

		// stanga fata
		glColor3f(0.0, 0.0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(x + 10, y + 75);
		glVertex2f(x + 10, y + 90);
		glVertex2f(x + 6, y + 90);
		glVertex2f(x + 6, y + 75);
		glEnd();

		// dreapta fata
		glColor3f(0.0, 0.0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(x + 60, y + 75);
		glVertex2f(x + 60, y + 90);
		glVertex2f(x + 64, y + 90);
		glVertex2f(x + 64, y + 75);
		glEnd();

		// stanga spate

		glColor3f(0.0, 0.0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(x + 10, y + 25);
		glVertex2f(x + 10, y + 40);
		glVertex2f(x + 6, y + 40);
		glVertex2f(x + 6, y + 25);
		glEnd();

		glColor3f(0.0, 0.0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(x + 60, y + 25);
		glVertex2f(x + 60, y + 40);
		glVertex2f(x + 64, y + 40);
		glVertex2f(x + 64, y + 25);
		glEnd();

		// hitbox
		hitboxPlayer[0] = x + 5;
		hitboxPlayer[1] = x + 65;
		hitboxPlayer[2] = y + 10;
		hitboxPlayer[3] = y + 110;

		if (hitbox == true)
		{
			glColor3f(1.0, 0.0, 0.0);
			glBegin(GL_LINE_LOOP);
			glVertex2d(hitboxPlayer[0], hitboxPlayer[2]);
			glVertex2d(hitboxPlayer[1], hitboxPlayer[2]);
			glVertex2d(hitboxPlayer[1], hitboxPlayer[3]);
			glVertex2d(hitboxPlayer[0], hitboxPlayer[3]);
			glEnd();
		}
		glFlush();
	}
}

void masinaSportRosie(int x = 20, int y = -180)
{
	// MASINA SPORT ROSIE
	{
		glColor3f(0.4, 0.0, 0.1);
		glBegin(GL_POLYGON);
		// stanga jos
		glVertex2f(x + 10, y + 14);
		glVertex2f(x + 14, y + 10);


		// dreapta jos
		glVertex2f(x + 56, y + 10);
		glVertex2f(x + 60, y + 14);

		// stanga sus
		glVertex2f(x + 60, y + 106);
		glVertex2f(x + 56, y + 110);

		// dreapta sus
		glVertex2f(x + 14, y + 110);
		glVertex2f(x + 10, y + 106);

		glEnd();

		//dunga
		glColor3f(0.9, 0.9, 0.9);
		glBegin(GL_POLYGON);

		glVertex2f(x + 25, y + 10);
		glVertex2f(x + 45, y + 10);

		glVertex2f(x + 45, y + 110);
		glVertex2f(x + 25, y + 110);


		glEnd();

		//parbriz
		glColor3f(0, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(x + 20, y + 75);
		glVertex2f(x + 20, y + 90);
		glVertex2f(x + 25, y + 95);
		glVertex2f(x + 45, y + 95);
		glVertex2f(x + 50, y + 90);
		glVertex2f(x + 50, y + 75);
		glEnd();

		//luneta stanga (depinde cum te uiti)
		glColor3f(0, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(x + 20, y + 25);
		glVertex2f(x + 20, y + 45);
		glVertex2f(x + 25, y + 55);
		glVertex2f(x + 30, y + 55);
		glVertex2f(x + 30, y + 25);
		glEnd();

		//luneta dreapta (depinde cum te uiti)
		glColor3f(0, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(x + 40, y + 25);
		glVertex2f(x + 40, y + 55);
		glVertex2f(x + 45, y + 55);
		glVertex2f(x + 50, y + 45);
		glVertex2f(x + 50, y + 25);
		glEnd();

		//geam stanga
		glColor3f(0, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(x + 17, y + 53);
		glVertex2f(x + 21, y + 58);
		glVertex2f(x + 21, y + 68);
		glVertex2f(x + 17, y + 73);
		glEnd();

		//geam dreapta
		glColor3f(0, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(x + 52, y + 53);
		glVertex2f(x + 48, y + 58);
		glVertex2f(x + 48, y + 68);
		glVertex2f(x + 52, y + 73);
		glEnd();

		glColor3f(0.7, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(x + 20, y + 10);
		glVertex2f(x + 30, y + 10);
		glVertex2f(x + 30, y + 15);
		glVertex2f(x + 20, y + 15);
		glEnd();

		glColor3f(0.7, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(x + 40, y + 10);
		glVertex2f(x + 50, y + 10);
		glVertex2f(x + 50, y + 15);
		glVertex2f(x + 40, y + 15);
		glEnd();

		//faruri

		glColor3f(0.4, 0.4, 0);
		glBegin(GL_POLYGON);
		glVertex2f(x + 20, y + 105);
		glVertex2f(x + 30, y + 105);
		glVertex2f(x + 30, y + 110);
		glVertex2f(x + 20, y + 110);
		glEnd();

		glColor3f(0.4, 0.4, 0);
		glBegin(GL_POLYGON);
		glVertex2f(x + 40, y + 105);
		glVertex2f(x + 50, y + 105);
		glVertex2f(x + 50, y + 110);
		glVertex2f(x + 40, y + 110);
		glEnd();

		if (faruri == TRUE)
		{
			// faruri
			glColor3f(0.8, 0.8, 0);
			glRectf(x + 20, y + 105, x + 30, y + 110);
			glColor3f(0.8, 0.8, 0);
			glRectf(x + 40, y + 105, x + 50, y + 110);

			glColor3f(1, 1, 0);
			glBegin(GL_TRIANGLES);
			glVertex2f(x + 25, y + 110);
			glVertex2f(x + 55, y + 210);
			glVertex2f(x - 5, y + 210);

			glVertex2f(x + 45, y + 110);
			glVertex2f(x + 75, y + 210);
			glVertex2f(x + 15, y + 210);

			glEnd();
		}

		// stanga fata
		glColor3f(0.0, 0.0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(x + 10, y + 75);
		glVertex2f(x + 10, y + 90);
		glVertex2f(x + 6, y + 90);
		glVertex2f(x + 6, y + 75);
		glEnd();

		// dreapta fata
		glColor3f(0.0, 0.0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(x + 60, y + 75);
		glVertex2f(x + 60, y + 90);
		glVertex2f(x + 64, y + 90);
		glVertex2f(x + 64, y + 75);
		glEnd();

		// stanga spate

		glColor3f(0.0, 0.0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(x + 10, y + 25);
		glVertex2f(x + 10, y + 40);
		glVertex2f(x + 6, y + 40);
		glVertex2f(x + 6, y + 25);
		glEnd();

		glColor3f(0.0, 0.0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(x + 60, y + 25);
		glVertex2f(x + 60, y + 40);
		glVertex2f(x + 64, y + 40);
		glVertex2f(x + 64, y + 25);
		glEnd();

		// hitbox
		hitboxPlayer[0] = x + 5;
		hitboxPlayer[1] = x + 65;
		hitboxPlayer[2] = y + 10;
		hitboxPlayer[3] = y + 110;

		if (hitbox == true)
		{
			glColor3f(1.0, 0.0, 0.0);
			glBegin(GL_LINE_LOOP);
			glVertex2d(hitboxPlayer[0], hitboxPlayer[2]);
			glVertex2d(hitboxPlayer[1], hitboxPlayer[2]);
			glVertex2d(hitboxPlayer[1], hitboxPlayer[3]);
			glVertex2d(hitboxPlayer[0], hitboxPlayer[3]);
			glEnd();
		}
		glFlush();
	}
}

void camion(int x = 20, int y = -180)
{
	// CAMION
	{
		//spate dubita

		glColor3f(0.5, 0.5, 0.5);
		glBegin(GL_POLYGON);

		glVertex2f(x + 0, y + 0);
		glVertex2f(x + 70, y + 0);
		glVertex2f(x + 70, y + 100);
		glVertex2f(x + 0, y + 100);

		glEnd();


		// dugi pe remorca

		glLineWidth(1.0);

		glColor3f(0.7, 0.7, 0.7);
		glBegin(GL_LINES);
		for (int i = 20; i <= 80; i = i + 20)
		{
			glColor3f(0.7, 0.7, 0.7);
			glVertex2i(x + 0, y + i);
			glVertex2i(x + 70, y + i);
		}
		glEnd();

		// conexiune cabina si remorca dubita

		glLineWidth(4.0);
		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex2i(x + 20, y + 102);
		glVertex2i(x + 50, y + 102);
		glEnd();

		// cabina dubita

		glColor3f(0.7, 0, 0);
		glBegin(GL_POLYGON);

		glVertex2f(x + 10, y + 104);
		glVertex2f(x + 60, y + 104);
		glVertex2f(x + 60, y + 135);
		glVertex2f(x + 10, y + 135);

		glEnd();

		//parbriz
		glColor3f(0, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(x + 17, y + 125);
		glVertex2f(x + 53, y + 125);
		glVertex2f(x + 53, y + 130);
		glVertex2f(x + 17, y + 130);
		glEnd();

		//faruri
		glColor3f(0.4, 0.4, 0);
		glBegin(GL_POLYGON);
		glVertex2f(x + 10, y + 130);
		glVertex2f(x + 15, y + 130);
		glVertex2f(x + 15, y + 135);
		glVertex2f(x + 10, y + 135);
		glEnd();

		glColor3f(0.4, 0.4, 0);
		glBegin(GL_POLYGON);
		glVertex2f(x + 55, y + 130);
		glVertex2f(x + 60, y + 130);
		glVertex2f(x + 60, y + 135);
		glVertex2f(x + 55, y + 135);
		glEnd();

		if (faruri == TRUE)
		{
			// faruri
			glColor3f(0.8, 0.8, 0);
			glRectf(x + 10, y + 130, x + 15, y + 135);
			glColor3f(0.8, 0.8, 0);
			glRectf(x + 55, y + 130, x + 60, y + 135);

			glColor3f(1, 1, 0);
			glBegin(GL_TRIANGLES);
			glVertex2f(x + 12.5, y + 135);
			glVertex2f(x + 42.5, y + 200);
			glVertex2f(x - 27.5, y + 200);

			glVertex2f(x + 57.5, y + 135);
			glVertex2f(x + 97.5, y + 200);
			glVertex2f(x + 27.5, y + 200);
			glEnd();
		}

		//stopuri

		glColor3f(0.7, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(x + 10, y + 0);
		glVertex2f(x + 15, y + 0);
		glVertex2f(x + 15, y + 5);
		glVertex2f(x + 10, y + 5);
		glEnd();

		glColor3f(0.7, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(x + 55, y + 0);
		glVertex2f(x + 60, y + 0);
		glVertex2f(x + 60, y + 5);
		glVertex2f(x + 55, y + 5);
		glEnd();

		// stanga fata
		glColor3f(0.0, 0.0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(x + 5, y + 110);
		glVertex2f(x + 10, y + 110);
		glVertex2f(x + 10, y + 125);
		glVertex2f(x + 5, y + 125);
		glEnd();

		// dreapta fata
		glColor3f(0.0, 0.0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(x + 60, y + 110);
		glVertex2f(x + 65, y + 110);
		glVertex2f(x + 65, y + 125);
		glVertex2f(x + 60, y + 125);
		glEnd();
		// hitbox
		hitboxPlayer[0] = x;
		hitboxPlayer[1] = x + 70;
		hitboxPlayer[2] = y;
		hitboxPlayer[3] = y + 135;

		if (hitbox == true)
		{
			glColor3f(1.0, 0.0, 0.0);
			glBegin(GL_LINE_LOOP);
			glVertex2d(hitboxPlayer[0], hitboxPlayer[2]);
			glVertex2d(hitboxPlayer[1], hitboxPlayer[2]);
			glVertex2d(hitboxPlayer[1], hitboxPlayer[3]);
			glVertex2d(hitboxPlayer[0], hitboxPlayer[3]);
			glEnd();
		}
		glFlush();
	}
}

#pragma endregion

#pragma region Scor
void score() {
	glColor3f(0, 0, 0);
	glRectf(-595, -380, -405, -250);
}

void top() {
	glColor3f(0, 1, 0);
	glRectf(-570 + offset, -268, -510 + offset, -258);
}

void middle() {
	glColor3f(0, 1, 0);
	glRectf(-570 + offset, -320, -510 + offset, -310);
}

void bottom() {
	glColor3f(0, 1, 0);
	glRectf(-570 + offset, -372, -510 + offset, -362);
}

void leftDown() {
	glColor3f(0, 1, 0);
	glRectf(-580 + offset, -367, -570 + offset, -317);
}

void leftUp() {
	glColor3f(0, 1, 0);
	glRectf(-580 + offset, -313, -570 + offset, -263);
}

void rightDown() {
	glColor3f(0, 1, 0);
	glRectf(-510 + offset, -367, -500 + offset, -317);
}

void rightUp() {
	glColor3f(0, 1, 0);
	glRectf(-510 + offset, -313, -500 + offset, -263);
}

void zero() {
	top();
	rightUp();
	rightDown();
	leftDown();
	leftUp();
	bottom();
}

void one() {
	rightDown();
	rightUp();
}

void two() {
	top();
	rightUp();
	middle();
	leftDown();
	bottom();
}

void three() {
	top();
	middle();
	bottom();
	rightUp();
	rightDown();
}

void jhin() {
	middle();
	rightUp();
	rightDown();
	leftUp();
}

void five() {
	top();
	leftUp();
	middle();
	rightDown();
	bottom();
}

void six() {
	top();
	middle();
	bottom();
	leftDown();
	rightDown();
	leftUp();
}

void seven() {
	top();
	rightUp();
	rightDown();
}

void eight() {
	top();
	rightUp();
	rightDown();
	middle();
	leftDown();
	leftUp();
	bottom();
}

void nine() {
	top();
	rightUp();
	rightDown();
	middle();
	leftUp();
	bottom();
}

void showDigit(int number, bool left) {
	if (left) {
		offset = -6;
		switch (number) {
		case 0:
			zero();
			break;
		case 1:
			one();
			break;
		case 2:
			two();
			break;
		case 3:
			three();
			break;
		case 4:
			jhin();
			break;
		case 5:
			five();
			break;
		case 6:
			six();
			break;
		case 7:
			seven();
			break;
		case 8:
			eight();
			break;
		case 9:
			nine();
			break;
		}
	}
	else {
		offset = 84;
		switch (number) {
		case 0:
			zero();
			break;
		case 1:
			one();
			break;
		case 2:
			two();
			break;
		case 3:
			three();
			break;
		case 4:
			jhin();
			break;
		case 5:
			five();
			break;
		case 6:
			six();
			break;
		case 7:
			seven();
			break;
		case 8:
			eight();
			break;
		case 9:
			nine();
			break;
		}
	}
}

void showScore() {
	time(&finish);
	score();
	int score;
	score = (int)difftime(finish, start);
	int firstDigit, secondDigit;
	firstDigit = score / 10 % 10;
	secondDigit = score % 10;
	showDigit(firstDigit, true);
	showDigit(secondDigit, false);
}
#pragma endregion

#pragma region Clepsidra
float angle;
bool rotation = false;
time_t timp;

void changeAngle() {
	if (angle < 180) {
		if (angle + 0.468 > 180)
			angle = 180;
		else
			angle += 0.468;
	}
	if (angle == 180) {
		angle = 0;
		rotation = false;
	}
}

void Hourglass() {
	time(&finish);
	timp = (int)difftime(finish, start);
	int elapsedTime;
	elapsedTime = timp % 10;
	float offsetX = 5.55, offsetY = 7;
	if (elapsedTime == 0 && timp > 3) {
		rotation = true;
		elapsedTime = 9;
	}
	if (rotation == true)
		changeAngle();
	// sticla jos
	glPushMatrix();
	glTranslated(-497, -167, 0); // translatia in puncul initial
	glRotatef(angle, 0, 0, 1);
	glTranslated(497, 167, 0);
	glLineWidth(2.0);
	glBegin(GL_TRIANGLES);
	glColor3f(0.1, 0.2, 0.3);
	glVertex2f(-497, -167);
	glVertex2f(-447, -230);
	glVertex2f(-547, -230);
	glEnd();
	glPopMatrix();
	//sticla sus
	glPushMatrix();
	glTranslated(-497, -167, 0); // translatia in puncul initial
	glRotatef(angle, 0, 0, 1);
	glTranslated(497, 167, 0);
	glBegin(GL_TRIANGLES);
	glColor3f(0.1, 0.2, 0.3);
	glVertex2f(-497, -167);
	glVertex2f(-447, -104);
	glVertex2f(-547, -104);
	glEnd();
	glPopMatrix();
	//nisip jos
	glPushMatrix();
	glTranslated(-497, -167, 0); // translatia in puncul initial
	glRotatef(angle, 0, 0, 1);
	glTranslated(497, 167, 0);
	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex2f(-447, -230);
	glVertex2f(-547, -230);
	glVertex2f(-547 + elapsedTime * offsetX, -230 + elapsedTime * offsetY);
	glVertex2f(-447 - elapsedTime * offsetX, -230 + elapsedTime * offsetY);
	glEnd();
	glPopMatrix();
	//nisip sus
	glPushMatrix();
	glTranslated(-497, -167, 0); // translatia in puncul initial
	glRotatef(angle, 0, 0, 1);
	glTranslated(497, 167, 0);
	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 0);
	glVertex2f(-497, -167);
	glVertex2f(-447 - elapsedTime * offsetX, -104 - elapsedTime * offsetY);
	glVertex2f(-547 + elapsedTime * offsetX, -104 - elapsedTime * offsetY);
	glEnd();
	glPopMatrix();
	//linie nisip
	if (!rotation) {
		glBegin(GL_LINES);
		glVertex2f(-497, -167);
		glVertex2f(-497, -230);
		glEnd();
	}
}
#pragma endregion

#pragma region Generare Obstacole
int obstaclePosition, type, position, xPositions[] = { -270, -70, 70, 270 };
bool shouldGenerate = true;
double translateDistance;

int chooseObstacle() {
	srand(time(NULL));
	return rand() % 2;
}

int generatePosition() {
	srand(time(NULL));
	return rand() % 4;
}

void generateObstacles() {
	if (shouldGenerate) {
		shouldGenerate = false;
		type = chooseObstacle();
		position = generatePosition();
		translateDistance = 0;
	}
	if (!shouldGenerate) {
		glPushMatrix();
		glTranslatef(0, translateDistance, 0);
		if (xPositions[position] == -270 || xPositions[position] == -70)
		{
			glTranslated(xPositions[position], 500, 0);
			glRotated(180, 0, 0, 1);
			glTranslated(-xPositions[position], -500, 0);
		}
		glLineWidth(2.0);
		switch (type) {
		case 0:
			masinaSportRosie(xPositions[position], 500);
			break;
		case 1:
			masinaSportVerde(xPositions[position], 500);
			break;
		}
		hitboxObstacol[0] = xPositions[position] - 25;
		hitboxObstacol[1] = xPositions[position] + 25;
		hitboxObstacol[2] = 500 + translateDistance;
		hitboxObstacol[3] = 600 + translateDistance;

		if (hitbox == true)
		{
			glColor3f(0.0, 1.0, 0.0);
			glBegin(GL_LINE_LOOP);
			glVertex2d(hitboxObstacol[0], hitboxObstacol[2]);
			glVertex2d(hitboxObstacol[1], hitboxObstacol[2]);
			glVertex2d(hitboxObstacol[1], hitboxObstacol[3]);
			glVertex2d(hitboxObstacol[0], hitboxObstacol[3]);
			glEnd();
		}

		glPopMatrix();
		translateDistance -= 1;
		if (translateDistance < -1000) {
			shouldGenerate = true;
		}
	}
}
#pragma endregion

#pragma region Coliziuni
int calculColiziuni(int xo, int yo)
{
	int xps, xpd, ypj, yps, xos, xod, yoj, yos;
	xps = hitboxPlayer[0]; xpd = hitboxPlayer[1]; ypj = hitboxPlayer[2]; yps = hitboxPlayer[3];
	xos = hitboxObstacol[0]; xod = hitboxObstacol[1]; yoj = hitboxObstacol[2]; yos = hitboxObstacol[3];
	if (xo > xps + i && xo < xpd + i && yo < yps && yo > ypj)
		return 0;
	return 1;
}

int detectieColiziuni(void)
{
	int v1[] = { 0, 0, 1, 1 };
	int v2[] = { 2, 3, 2, 3 };
	int ok = 1;
	for (int i = 0; i <= 3; i++)
	{
		ok = calculColiziuni(hitboxObstacol[v1[i]], hitboxObstacol[v2[i]]);
		if (ok == 0)
			break;
	}
	cout << hitboxPlayer[0] + i << "    " << hitboxPlayer[1] + i << endl;
	return ok;
}

#pragma endregion

void desenDrum(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	// DRUMUL
	glColor3f(0.2, 0.2, 0.2);
	glRectf(-400., -1000., 400., 1000.);
	// Linia ce separa benzile
	glColor3f(1, 1, 0);
	glRectf(-15., -1000., -5., 1000.);
	glRectf(5., -1000., 15., 1000.);
	glColor3f(1, 1, 1);
	glRectf(-400., -1000., -390., 1000.);
	glRectf(390., -1000., 400., 1000.);
	glRectf(-205., -1000., -195., 1000.);
	glRectf(195., -1000., 205., 1000.);



	glPushMatrix();
	glTranslated(0, k, 0);
	copac(500, 500);
	copac(500, 700);
	copac(500, 1000);
	semnCedeazaTrecereaSpate(500, 800);
	copac(500, 1200);
	copac(500, 1500);
	copac(500, 1800);

	copac(-500, 500);
	copac(-500, 700);
	semnCedeazaTrecerea(500, 800);
	copac(-500, 1000);
	copac(-500, 1200);
	copac(-500, 1500);
	copac(-500, 1800);
	semnPrioritate(-500, 2200);
	glPopMatrix();

	generateObstacles();

	Hourglass();
	glPopMatrix();

	showScore();

	// initializare pentru tranzitii
	glPushMatrix();
	glTranslated(i, 0, 0);

	if (masina == 0)
	{
		masinaPolitie();
	}

	else if (masina == 1)
	{
		masinaSportVerde();
	}

	else if (masina == 2)
	{
		masinaSportRosie();
	}

	else if (masina == 3)
	{
		camion();
	}
	int col = detectieColiziuni();
	if (col == 0)
	{
		cout << "poc";
		cout << "Player " << hitboxPlayer[0] + i << "   " << hitboxPlayer[1] + i << "   " << hitboxPlayer[2] << "   " << hitboxPlayer[3] << endl;
		cout << "Obstacol " << hitboxObstacol[0] << "   " << hitboxObstacol[1] << "   " << hitboxObstacol[2] << "   " << hitboxObstacol[3] << endl;
		MessageBox(NULL, L"Game Over", L"Final Joc", MB_OK | MB_ICONINFORMATION);
		exit(0);
	}

	glutSwapBuffers();
	glFlush();
}



void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, (GLsizei)newWidth, (GLsizei)newHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-600, 600, -400, 400);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);
}

void main_menu(int key)
{
	if (key == 0)
	{
		exit(0);
	}
}

void select_masina(int key)
{
	masina = key;
}

void main(int argc, char** argv)
{
	int meniuMain, meniuMasina, meniuCuloare;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(150, 150);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Evita masinile");
	init();
	nrMere = genPozMere();

	glutReshapeFunc(winReshapeFcn);
	glutDisplayFunc(desenDrum);

	glutIdleFunc(miscare);
	glutMouseFunc(mouse);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);


	meniuMasina = glutCreateMenu(select_masina);
	glutAddMenuEntry("Masina de politie", 0);
	glutAddMenuEntry("Masina sport verde", 1);
	glutAddMenuEntry("Masina sport rosie", 2);
	glutAddMenuEntry("Camion", 3);

	meniuMain = glutCreateMenu(main_menu);

	glutAddSubMenu("Selectie masina", meniuMasina);
	glutAddMenuEntry("Iesire", 0);

	glutAttachMenu(GLUT_MIDDLE_BUTTON);

	glutMainLoop();

}

