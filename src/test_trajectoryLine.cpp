#include <GLUT/glut.h>
#include "utils/lines.h"
#include "objects.h"
#include <vector>
#include <stdio.h>

Vertex a = Vertex(10.0, 40.0, 0.0);
Vertex b = Vertex(90.0, 80.0, 0.0);

LineTrajectory lineTrajectory = LineTrajectory(&a, &b, 5000.0, 'B');

Object *monkey;

void UpdateMonkey(int value) {
	if(lineTrajectory.started == false)
		lineTrajectory.Start();

	*(monkey->origin) = lineTrajectory.UpdatePosition();

	if(lineTrajectory.finished == true)
		lineTrajectory.Restart();

	glutPostRedisplay();
	glutTimerFunc(16, UpdateMonkey, 0);
}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT);

    glColor3f (1.0, 1.0, 1.0);

	drawLineDDA(a, b);
	monkey->DrawWireframe();

    //glFlush ();
	glutSwapBuffers();
}

void init (void) 
{
    glClearColor (0.0, 0.0, 0.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
}

int main(int argc, char** argv)
{
	std::vector<Object> obj = readObjFile("modelos/monkey.obj");
	monkey = &obj[0];

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (400, 400); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("::Line Trajectory::");
    init ();
    glutDisplayFunc(display); 
	glutTimerFunc(0, UpdateMonkey, 0);
    glutMainLoop();
    return 0;
}
