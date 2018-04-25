#include <GL/glut.h>	// Для GLUT_KEYs
#include <iostream>		// cout/отладка
#include <math.h>		// Для математики
#include <windows.h>	// Для Sleep()
#include <stdlib.h>		// Для очистки консоли
#include "GLMovement.hpp"
#include "Read.hpp"


/*ASCII коды для специальных кнопок*/
#define ESCAPE 27

const float piover180 = 0.0174532925f;
int window;

float xpos = 0;											// Начальная координата x
float ypos = -10;										// y 
float zpos = 10;										// z

GLfloat yrot;											// Поворот в градусах право/лево

extern Thing T1;										// Объявлены в Main
extern Thing T2;
extern Thing T3;
extern int Iteration_size;
int Iter = 0;											// Номер итерации, который будет нарисован

void keyPressed(unsigned char key, int x, int y)
{
	switch (key)
	{
	case ESCAPE:
		glutDestroyWindow(window);
		exit(1);
		break;

	default:
		break;
	}
}

void specialKeyPressed(int key, int x, int y)
{
	Sleep(1);
	switch (key)
	{
	case GLUT_KEY_DOWN:									// Переместиться назад
		xpos += (float)sin(yrot*piover180) * 0.2f;
		zpos += (float)cos(yrot*piover180) * 0.2f;
		break;

	case GLUT_KEY_UP:									// Переместиться вперед
		xpos -= (float)sin(yrot*piover180) * 0.2f;
		zpos -= (float)cos(yrot*piover180) * 0.2f;
		break;

	case GLUT_KEY_LEFT:									// Повернуться влево
		yrot += 3.0f;
		break;

	case GLUT_KEY_RIGHT:								// Повернуться вправо
		yrot -= 3.0f;
		break;

	case GLUT_KEY_PAGE_DOWN:							// Спуститься вниз
		ypos += 1.0f;
		break;

	case GLUT_KEY_PAGE_UP:								// Подняться наверх
		ypos -= 1.0f;
		break;
	}
}

GLvoid InitGL(GLsizei Width, GLsizei Height)											// We call this right after our OpenGL window is created.
{
	glClearColor(0, 0, 0, 0);
	glClearDepth(1);
	glDepthFunc(GL_LEQUAL);
	//glDepthFunc(GL_LESS);																// Не знаю почему, GL_LESS отказывается работаь
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();																	// Reset The Projection Matrix
	//gluLookAt(0, 0, 0, 1, 1, 1, 0, 1, 0);

	gluPerspective(90, 640/480, 0, 100);												// Calculate The Aspect Ratio Of The Window
	glMatrixMode(GL_MODELVIEW);
}

void display(void)
{
	GLfloat xtrans = -xpos;
	GLfloat ytrans = ypos;
	GLfloat ztrans = -zpos;
	GLfloat y1 = 360.0f - yrot;
	int test = 0;
	test += 1;
	Iter = Iter + 30;																	// Скорость увеличена в 30 раз!

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);									// Clear The Screen And The Depth Buffer
	glLoadIdentity();
	glRotatef(y1, 0, 1.0f, 0);
	glTranslatef(xtrans, ytrans, ztrans);

	if(Iter < Iteration_size)															// Пока есть что рисовать (в исходном файле 80к итераций)
	{
		// Рисование сфер
		GLUquadricObj *quadObj1;
		quadObj1 = gluNewQuadric();
		glPushMatrix();
		glTranslatef(T1.x[Iter] / 10, T1.y[Iter] / 10, T1.z[Iter] / 10);				// Все координаты уменьшены в 10 раз, чтобы не бегать далеко
		glTranslated(0.001, -0.001, 0.0);
		glColor4ub(200, 0, 0, 0);
		gluQuadricDrawStyle(quadObj1, GLU_FILL);
		gluSphere(quadObj1, 1.0, 30, 30);
		gluDeleteQuadric(quadObj1);
		glPopMatrix();

		GLUquadricObj *quadObj2;
		quadObj2 = gluNewQuadric();
		glPushMatrix();
		glTranslatef(T2.x[Iter] / 10, T2.y[Iter] / 10, T2.z[Iter] / 10);
		glTranslated(0.001, -0.001, 0.0);
		glColor4ub(0, 200, 0, 0);
		gluQuadricDrawStyle(quadObj2, GLU_FILL);
		gluSphere(quadObj2, 1.0, 30, 30);
		gluDeleteQuadric(quadObj2);
		glPopMatrix();

		GLUquadricObj *quadObj3;
		quadObj3 = gluNewQuadric();
		glPushMatrix();
		glTranslatef(T3.x[Iter] / 10, T3.y[Iter] / 10, T3.z[Iter] / 10);
		glTranslated(0.001, -0.001, 0.0);
		glColor4ub(0, 0, 200, 0);
		gluQuadricDrawStyle(quadObj3, GLU_FILL);
		gluSphere(quadObj3, 1.0, 30, 30);
		gluDeleteQuadric(quadObj3);
		glPopMatrix();

		// Рисование векторов 
		glBegin(GL_LINES);
		glColor3d(1, 0.6, 0.6); 
		glVertex3d(T1.x[Iter] / 10, T1.y[Iter] / 10, T1.z[Iter] / 10);
		glVertex3d(T1.x[Iter] / 10 + T1.xspeed[Iter] * 1000, T1.y[Iter] / 10 + T1.yspeed[Iter] * 1000, T1.z[Iter] / 10 + T1.zspeed[Iter] * 1000);
		glEnd();

		glBegin(GL_LINES);
		glColor3d(1, 0.6, 0.6);
		glVertex3d(T2.x[Iter] / 10, T2.y[Iter] / 10, T2.z[Iter] / 10);
		glVertex3d(T2.x[Iter] / 10 + T2.xspeed[Iter] * 1000, T2.y[Iter] / 10 + T2.yspeed[Iter] * 1000, T2.z[Iter] / 10 + T2.zspeed[Iter] * 1000); 
		glEnd();

		glBegin(GL_LINES);
		glColor3d(1, 0.6, 0.6);
		glVertex3d(T3.x[Iter] / 10, T3.y[Iter] / 10, T3.z[Iter] / 10);
		glVertex3d(T3.x[Iter] / 10 + T3.xspeed[Iter] * 1000, T3.y[Iter] / 10 + T3.yspeed[Iter] * 1000, T3.z[Iter] / 10 + T3.zspeed[Iter] * 1000); 
		glEnd();

		std::cout << "Iteration = " << Iter << "\n";										// Вывод в консоль информации о текущей итерации
		std::cout << "T1.x =" << T1.x[Iter] << "\tT1.y = " << T1.y[Iter] << "\tT1.z = " << T1.z[Iter] << "\nT1.xspeed = " << T1.xspeed[Iter] << "\t\tT1.yspeed = " << T1.yspeed[Iter] << "\t\tT1.zspeed = " << T1.zspeed[Iter] << "\n";
		std::cout << "T2.x =" << T2.x[Iter] << "\tT2.y = " << T2.y[Iter] << "\tT2.z = " << T2.z[Iter] << "\nT2.xspeed = " << T2.xspeed[Iter] << "\t\tT2.yspeed = " << T2.yspeed[Iter] << "\t\tT2.zspeed = " << T2.zspeed[Iter] << "\n";
		std::cout << "T3.x =" << T3.x[Iter] << "\tT3.y = " << T3.y[Iter] << "\tT3.z = " << T3.z[Iter] << "\nT3.xspeed = " << T3.xspeed[Iter] << "\t\tT3.yspeed = " << T3.yspeed[Iter] << "\t\tT3.zspeed = " << T3.zspeed[Iter] << "\n";
		std::cout << "My x =" << xtrans << "\tMy y =" << ytrans << "\tMy z = " << ztrans << "\n";
		system("cls");																		// Очищение консоли для статичности выведенной информации в консоли
	}
	glutSwapBuffers();
}