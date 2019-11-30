
/******************************************
COURSE: Computer Graphics
DESCRIPTION:Program that draws a cube's wireframe
NAME: 
*******************************************/

//#include <GL/gl.h>
//#include <GL/glu.h>
#include <GLUT/glut.h>
#include <stdio.h>
#include <vector>
#include "objects.h"

// Constants
#define VERT_PER_FACE 4
#define N_VERTICES    8
#define N_FACES       6

using namespace std;

static GLfloat spin = 0.0;

vector<Object> objetos;


void spinDisplay() {
	spin = spin + 2.0;
	if(spin > 360.0)
		spin = spin - 360.0;
	glutPostRedisplay();
}

// Display function
void display (void)
{
   // Clear all pixels
   glClear (GL_COLOR_BUFFER_BIT);

   glPushMatrix();
   glRotatef(30, 1.0, 1.0, 0.0);

   // Define color
   glColor3f (1.0, 1.0, 1.0);

	for(int i = 0; i < objetos.size(); i++)
		objetos[i].DrawWireframe();
   

	glPopMatrix();
	glutSwapBuffers();

}

void init (void) 
{
   // Select clearing (background) color
   glClearColor (1.0, 1.0, 1.0, 0.0);

   // Initialize viewing values
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
   
   // Rotate the whole scene so that three faces of the cube are seen
}

// Declare initial window size, position, and display mode (single buffer and RGBA)
int main (int argc, char** argv)
{
   objetos = readObjFile("modelos/x-wing.obj");
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (":: C U B E ::");

   init ();

   glutDisplayFunc(display); 
   //glutIdleFunc(spinDisplay);
   glutMainLoop();
   return 0;
}

