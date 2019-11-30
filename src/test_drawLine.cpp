#include <GLUT/glut.h>
#include "utils/lines.h"
#include "objects.h"

Vertex a = Vertex(10.0, 40.0, 0.0);
Vertex b = Vertex(90.0, 80.0, 0.0);

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT);

    glColor3f (1.0, 1.0, 1.0);

	drawLineDDA(a, b);
	//drawLineBRE(a, b);
    
    glFlush ();
}

void init (void) 
{
    glClearColor (0.0, 0.0, 0.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
    //gluOrtho2D(0.0, 1.0, 0.0, 1.0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (400, 400); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("::Line algorithms::");
    init ();
    glutDisplayFunc(display); 
    glutMainLoop();
    return 0;
}
