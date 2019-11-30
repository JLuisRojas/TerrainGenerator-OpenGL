#include <stdio.h>
#include <stdlib.h>
#include <GLUT/glut.h>
#include "objects.h"
#include "map/terrainMesh.h"
#include "xWing.h"

xWing *xwing;
TerrainMesh *terrain;

static GLfloat spin = 0.0;
int refreshMillis = 50;      // Refresh period in milliseconds

Vertex *camPos;

void spinDisplay(int value) {
	spin = spin + 1.0;
	if(spin > 360.0)
		spin = spin - 360.0;

    terrain->Move();
    xwing->Update();

	glutPostRedisplay();
	glutTimerFunc(refreshMillis, spinDisplay, 0);
}

// Display function
void display (void)
{
   	glClear (GL_COLOR_BUFFER_BIT);
	glPushMatrix();

    // Camara offset
    float y_cam_separation = 2.0;
    float z_cam_separation = -16.0;

    // Obtains the current position of the ship
    Vertex x_pos = xwing->GetPosition();
    // Calcuales the camera position
    Vertex cam_pos(x_pos.x, x_pos.y + y_cam_separation, x_pos.z + z_cam_separation);
	
    // Smooth factor
	int smooth = 6;
    // Calculates the difference from the last position, to the current with smooth change
	float dx = (x_pos.x+cam_pos.x - camPos->x)/smooth;
	float dy = (x_pos.y+y_cam_separation - camPos->y)/smooth;
	float dz = (x_pos.z +cam_pos.z - camPos->z)/smooth;

	camPos->x += dx;
	camPos->y += dy;
	camPos->z += dz;

	gluLookAt(camPos->x, camPos->y, camPos->z, x_pos.x, camPos->y, x_pos.z, 0.0, 1.0, 0.0);
    // TEST
	//gluLookAt (100.0, 80.0, 0.0, 0.0, 10.0, 0.0, 0.0, 1.0, 0.0);
    
    Vertex cam2(camPos->x, camPos->y+20, 100.0);

    terrain->DrawTerrain();
    xwing->model->SortFaces();
    xwing->UpdateVisibility(*camPos);
    xwing->Draw();

	glPopMatrix();

	glutSwapBuffers();
	//glFlush();
}

void keyboard(unsigned char key, int x, int y) {
	switch(key) {
		case 'q':
            xwing->norms = true;
            terrain->correction = true;
			break;

		case 'w':
            xwing->wireframe = false;
            terrain->coloring = true;
			break;

		case 'z':
			break;
	}
	//glutPostRedisplay();
}

void init (void) 
{
   // Select clearing (background) color
   glClearColor (0.0, 0.0, 0.0, 0.0);
   //glClearColor (1.0, 1.0, 1.0, 0.0);

   // Initialize viewing values
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   //glOrtho(-50.0, 50.0, -37.0, 37.0, -100.0, 200.0);
   gluPerspective(45.0, 800.0/600.0, 0.1, 300.0);
   
   // Rotate the whole scene so that three faces of the cube are seen
}

// Declare initial window size, position, and display mode (single buffer and RGBA)
int main (int argc, char** argv)
{
	terrain = new TerrainMesh(120, 120, 20);
	terrain->Generate();

    xwing = new xWing(3, terrain);

	//gluLookAt (0.0, 40.0, 80.0, 0.0, 10.0, 0.0, 0.0, 1.0, 0.0);
	camPos = new Vertex(0.0, 1.0, 0.0);

   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (800, 600); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (":: TERRAIN GENERATOR ::");

   init ();

    glutDisplayFunc(display); 
    glutKeyboardFunc(keyboard);
	glutTimerFunc(0, spinDisplay, 0);
   glutMainLoop();

   return 0;
}
