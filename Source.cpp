#include <windows.h>  // sunt mentionate fisiere (biblioteci) care urmeaza sa fie incluse 
#include <gl/freeglut.h> // nu trebuie uitat freeglut.h (sau glut.h sau gl.h & glu.h)
#include <math.h>

void init(void)  // initializare fereastra de vizualizare
{
	glClearColor(1.0, 1.0, 1.0, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare

	glMatrixMode(GL_PROJECTION);  // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
	gluOrtho2D(0.0, 800.0, 0.0, 600.0); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
}

int x = 20;
void sasiuDubita() {
	
	//spate dubita

	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);

		glVertex2f(0, 0);
		glVertex2f(70, 0);
		glVertex2f(70, 100);
		glVertex2f(0, 100);

	glEnd();


	// dugi pe remorca

	glLineWidth(1.0);

	glColor3f(0.7, 0.7, 0.7);
	glBegin(GL_LINES);
		for (int i = 20; i <= 80; i = i + 20)
		{
			glColor3f(0.7, 0.7, 0.7);
			glVertex2i(0, i);
			glVertex2i(70, i);	
		}
	glEnd();

	// conexiune cabina si remorca dubita

	glLineWidth(4.0);
	glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex2i(20, 102);
		glVertex2i(50, 102);
	glEnd();

	// cabina dubita
	
	glColor3f(0.7, 0, 0);
	glBegin(GL_POLYGON);

		glVertex2f(10, 104);
		glVertex2f(60, 104);
		glVertex2f(60, 135);
		glVertex2f(10, 135);

	glEnd();
	
}

void geamuriDubita() {
	
	//parbriz
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
		glVertex2f(17, 125);
		glVertex2f(53, 125);
		glVertex2f(53, 130);
		glVertex2f(17, 130);
	glEnd();
	

}

void faruriDubita() {

	//faruri

	glColor3f(1.0, 1.0, 0);
	glBegin(GL_POLYGON);
		glVertex2f(10, 130);
		glVertex2f(15, 130);
		glVertex2f(15, 135);
		glVertex2f(10, 135);
	glEnd();

	glColor3f(1.0, 1.0, 0);
	glBegin(GL_POLYGON);
		glVertex2f(55, 130);
		glVertex2f(60, 130);
		glVertex2f(60, 135);
		glVertex2f(55, 135);
	glEnd();
	//stopuri

	glColor3f(0.7, 0, 0);
	glBegin(GL_POLYGON);
		glVertex2f(10, 0);
		glVertex2f(15, 0);
		glVertex2f(15, 5);
		glVertex2f(10, 5);
	glEnd();

	glColor3f(0.7, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2f(55, 0);
	glVertex2f(60, 0);
	glVertex2f(60, 5);
	glVertex2f(55, 5);
	glEnd();


}

void rotiDubita() {

	// stanga fata
	glColor3f(0.0, 0.0, 0);
	glBegin(GL_POLYGON);
		glVertex2f(5, 110);
		glVertex2f(10, 110);
		glVertex2f(10, 125);
		glVertex2f(5, 125);
	glEnd();

	// dreapta fata
	glColor3f(0.0, 0.0, 0);
	glBegin(GL_POLYGON);
		glVertex2f(60, 110);
		glVertex2f(65, 110);
		glVertex2f(65, 125);
		glVertex2f(60, 125);
	glEnd();	
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

void semnInterzisAmbeleSensuri(int x, int y) {

	//stalpul

	glColor3f(0.4, 0.4, 0.4);
	glLineWidth(3);
	glBegin(GL_LINES);
		glVertex2i(x + 25, y + 0);
		glVertex2i(x + 25, y + 55);
	glEnd();

	glColor3f(0.9, 0, 0);
	DrawCircle(25, 65, 30, 100);

	glColor3f(1, 1, 1);
	DrawCircle(25, 65, 26, 100);
}
void desen(void) // procedura desenare  
{

	semnInterzisAmbeleSensuri(0, 0);
	//sasiuDubita();
	//geamuriDubita();
	//faruriDubita();
	//rotiDubita();


	glFlush(); // proceseaza procedurile OpenGL cat mai rapid
}
void main(int argc, char** argv)
{
	glutInit(&argc, argv); // initializare GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // se utilizeaza un singur buffer | modul de colorare RedGreenBlue (= default)
	glutInitWindowPosition(100, 100); // pozitia initiala a ferestrei de vizualizare (in coordonate ecran)
	glutInitWindowSize(800, 600); // dimensiunile ferestrei 
	glutCreateWindow("Puncte & Segmente"); // creeaza fereastra, indicand numele ferestrei de vizualizare - apare in partea superioara

	init(); // executa procedura de initializare
	glClear(GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare
	glutDisplayFunc(desen); // procedura desen este invocata ori de cate ori este nevoie
	glutMainLoop(); // ultima instructiune a programului, asteapta (eventuale) noi date de intrare
}