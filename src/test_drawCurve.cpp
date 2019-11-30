#include <GLUT/glut.h>
#include "utils/curves.h"
#include "objects.h"

// Curve 00
Vertex c0_p1 = Vertex(2.0, 2.0, 0.0);
Vertex c0_p2 = Vertex(5.0, 5.0, 0.0);
Vertex c0_p3 = Vertex(5.0, 5.0, 0.0);
Vertex c0_p4 = Vertex(5.0, 2.0, 0.0);
// Curve 01
Vertex c1_p1 = Vertex(8.0, 2.0, 0.0);
Vertex c1_p2 = Vertex(13.0, 2.0, 0.0);
Vertex c1_p3 = Vertex(11.0, 8.0, 0.0);
Vertex c1_p4 = Vertex(11.0, 2.0, 0.0);
// Curve 02
Vertex c2_p1 = Vertex(14.0, 2.0, 0.0);
Vertex c2_p2 = Vertex(15.0, -4.0, 0.0);
Vertex c2_p3 = Vertex(16.0, 8.0, 0.0);
Vertex c2_p4 = Vertex(17.0, 2.0, 0.0);
// Curve 03
Vertex c3_p1 = Vertex(2.0, 8.0, 0.0);
Vertex c3_p2 = Vertex(0.0, 8.0, 0.0);
Vertex c3_p3 = Vertex(5.0, 12.0, 0.0);
Vertex c3_p4 = Vertex(5.0, 8.0, 0.0);
// Curve 04
Vertex c4_p1 = Vertex(8.0, 8.0, 0.0);
Vertex c4_p2 = Vertex(6.0, 12.0, 0.0);
Vertex c4_p3 = Vertex(9.0, 12.0, 0.0);
Vertex c4_p4 = Vertex(11.0, 8.0, 0.0);
// Curve 05
Vertex c5_p1 = Vertex(14.0, 8.0, 0.0);
Vertex c5_p2 = Vertex(14.0, 12.0, 0.0);
Vertex c5_p3 = Vertex(17.0, 12.0, 0.0);
Vertex c5_p4 = Vertex(17.0, 8.0, 0.0);

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT);

    glColor3f (1.0, 1.0, 1.0);

	float dt = 0.01;

    drawBezier(c0_p1, c0_p2, c0_p3, c0_p4, dt);
    drawBezier(c1_p1, c1_p2, c1_p3, c1_p4, dt);
    drawBezier(c2_p1, c2_p2, c2_p3, c2_p4, dt);
    drawBezier(c3_p1, c3_p2, c3_p3, c3_p4, dt);
    drawBezier(c4_p1, c4_p2, c4_p3, c4_p4, dt);
    drawBezier(c5_p1, c5_p2, c5_p3, c5_p4, dt);

    glFlush ();
}

void init (void) 
{
    glClearColor (1.0, 1.0, 1.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 20.0, -2.0, 13.0, -1.0, 1.0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (400, 300); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("::Bezier Curves::");
    init ();
    glutDisplayFunc(display); 
    glutMainLoop();
    return 0;
}
