#include <GLUT/glut.h>
#include "utils/curves.h"
#include "objects.h"
#include <vector>
#include <stdio.h>

Vertex p1 = Vertex(2.0, 10.0, 0.0);
Vertex p2 = Vertex(4.0, 15.0, 0.0);
Vertex p3 = Vertex(6.0, 5.0, 1.0);
Vertex p4 = Vertex(10, 10.0, 3.0);

BezierTrajectory curveTrajectory = BezierTrajectory(&p1, &p2, &p3, &p4, 5000.0);

Object *monkey;

void UpdateMonkey(int value) {
	if(curveTrajectory.started == false)
		curveTrajectory.Start();

	*(monkey->origin) = curveTrajectory.UpdatePosition();

	if(curveTrajectory.finished == true)
		curveTrajectory.Restart();

	glutPostRedisplay();
	glutTimerFunc(16, UpdateMonkey, 0);
}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT);

    glColor3f (1.0, 1.0, 1.0);

    drawBezier(p1, p2, p3, p4);
	monkey->DrawWireframe();

    //glFlush ();
	glutSwapBuffers();
}

void init (void) 
{
    glClearColor (0.0, 0.0, 0.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, 0.0, 20.0, -10.0, 10.0);
	glRotatef(90, 0.0, 1.0, 0.0);
}

int main(int argc, char** argv)
{
	std::vector<Object> obj = readObjFile("modelos/monkey.obj");
	monkey = &obj[0];

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (400, 400); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("::Curve Trajectory::");
    init ();
    glutDisplayFunc(display); 
	glutTimerFunc(0, UpdateMonkey, 0);
    glutMainLoop();
    return 0;
}
