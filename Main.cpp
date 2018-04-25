#include <GL/glut.h>
#include <GL/GL.h>
#include <fstream>
#include "GLMovement.hpp"
#include "Read.hpp"
#include <fstream>

int Iteration_size = GetIterSize();

Thing T1(Iteration_size);
Thing T2(Iteration_size);
Thing T3(Iteration_size);

int main(int argc, char **argv)
{
	SetCoords(T1, T2, T3, Iteration_size);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Draw");
		
	glutDisplayFunc(&display);
	glutIdleFunc(&display);

	glutKeyboardFunc(&keyPressed);
	glutSpecialFunc(&specialKeyPressed);

	InitGL(640, 480);
	glutMainLoop();
	return 1;
}