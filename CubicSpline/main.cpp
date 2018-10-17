/*
#define GLUT_DISABLE_ATEXIT_HACK

#include <windows.h>
#include <iostream>
#include <GL\glut.h>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;

//float WinWidth = (2 / 3.0) * glutGet(GLUT_SCREEN_WIDTH) ;
float WinHeight = (2 / 3.0) * glutGet(GLUT_SCREEN_HEIGHT);
float WinWidth = WinHeight;

float Xwidth = WinWidth;
float Ywidth = WinHeight;

float Xstep = 1;
float Ystep = 1;

vector<double> _X(WinWidth);
vector<double> _Y(WinWidth);

void DrawGrid();
void Display();
void Initialize();

void DrawFunction(vector<double>& X, vector<double>& Y);

void InitVectorX(vector<double>& x);
void InitVectorY(vector<double>& y);

void InitVectorX(vector<double>& x) {
	float Xi = -Xwidth / 2;
	for (int i = 0; i < WinWidth; i++, Xi += Xstep) {
		x[i] = Xi;
	}
}

void InitVectorY(vector<double>& y) {
	float Yi = -Ywidth / 2;
	for (int i = 0; i < WinWidth; i++, Yi += Ystep) {
		y[i] = Yi;
	}
}

void DrawFunction(vector<double>& X, vector<double>& Y) {
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < WinWidth; i++) {
		glVertex2f(X[i], Y[i]);
	}
	glEnd();
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT);
	DrawGrid();
	DrawFunction(_X, _Y);
	glFlush();
}

void DrawGrid()
{
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	
	glVertex2f(0, WinHeight / 2);
	glVertex2f(0, -WinHeight / 2);

	glVertex2f(-WinWidth / 2, 0);
	glVertex2f(WinWidth / 2, 0);
	
	glEnd();
}

void Initialize() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-WinWidth / 2, WinWidth / 2, -WinHeight / 2, WinHeight / 2, -5.0, 5.0);

	InitVectorX(_X);
	InitVectorY(_Y);
}

int main1(int argc, char ** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WinWidth, WinHeight);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("Our first GLUT application!");
	glutDisplayFunc(Display);
	Initialize();
	glutMainLoop();
	return 0;
}

*/