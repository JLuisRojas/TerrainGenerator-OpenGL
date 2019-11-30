//#include <GL/gl.h>
//#include <GL/glu.h>
#include <GLUT/glut.h>
#include <stdio.h>
#include <vector>
#include "objects.h"

std::vector<Object> objetos;
Object *monkey;
int dir = 1;
int ticks = 0;

void scaleMonkey(int value) {
	if(dir == 1)
		monkey->Scale(1.01);
	else
		monkey->Scale(0.99);
	glutPostRedisplay();
	glutTimerFunc(16, scaleMonkey, 0);

	ticks++;
	if(ticks % 60 == 0) {
		dir = -dir;
		ticks = 0;
	}
}

// Display function
void display (void)
{
   	glClear (GL_COLOR_BUFFER_BIT);

	monkey->DrawWireframe();

	glutSwapBuffers();
}

void init (void) 
{
   // Select clearing (background) color
   glClearColor (0.0, 0.0, 0.0, 0.0);

   // Initialize viewing values
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
   
   // Rotate the whole scene so that three faces of the cube are seen
}

// Declare initial window size, position, and display mode (single buffer and RGBA)
int main (int argc, char** argv)
{
   objetos = readObjFile("modelos/monkey.obj");
   monkey = &objetos[0];
   monkey->pivot->Print();
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (300, 300); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (":: SCALING MONKEY ::");

   init ();

   glutDisplayFunc(display); 
	glutTimerFunc(0, scaleMonkey, 0);
   glutMainLoop();
   return 0;
}

