// CS3241Lab1.cpp : Defines the entry point for the console application.
#include <cmath>
#include <iostream>
#include <time.h>
#include "GL/glut.h"

using namespace std;

#define numStars 100
#define numPlanets 9

class planet
{
public:
	float distFromRef;
	float angularSpeed;
	GLfloat color[3];
	float size;
	float angle;

	planet()
	{
		distFromRef = 0;
		angularSpeed = 0;
		color[0] = color[1] = color[2] = 0;
		size = 0;
		angle = 0;
	}
};
float red=0.0;
GLfloat PI = 3.14;
float alpha = 0.0, k=1;
float tx = 0.0, ty=0.0;
planet planetList[numPlanets];
bool increase;

void drawArc(double cx, double cy, float r,
			 int startDeg, int endDeg)
{
	int i;
	//glColor3f(0,102.0/255.0,102.0/255.0);
	glBegin(GL_POLYGON);
	for(i=startDeg;i<=endDeg;i++){
		glVertex2f(cx+r*sin(2.0*PI*i/360.0),cy+r*cos(2.0*PI*i/360.0));

	}
	glEnd();
}

void drawLine()
{
	glBegin(GL_LINE_STRIP);
	glVertex2f(-4, 0);
	glVertex2f(4, 0);
	glEnd();
}

void drawGuitar(){
	glPushMatrix();
	glScalef(k, k, k);	
	glTranslatef(tx, ty, 0);	
	glRotatef(alpha, 0, 0, 1);


	glTranslatef(38,3,0);
	glRotatef(-45,0,0,1);
	glTranslatef(0,-3,0);
	glColor3f(64/255.0,0/255.0,0/255.0);

	glScalef(2,3,1);
	glBegin(GL_POLYGON);
	glVertex2f(-6, 0);
	glVertex2f(6, 0);
	glVertex2f(6, -1);
	glVertex2f(-6, -1);
	glEnd();

	glScalef(1.5,1,1);
	glTranslatef(-1.5,-0.5,0);
	drawArc(0,0,1.5,0,360);
	glTranslatef(-2.5,0,0);
	drawArc(0,0,2,0,360);
	glTranslatef(-10,0,0);

	glRotatef(270,0,0,1);
	glTranslatef(0,18,0);
	glBegin(GL_POLYGON);
	glVertex2f(-0.8, 0);
	glVertex2f(0.8, 0);
	glVertex2f(0.5, -1.5);
	glVertex2f(-0.5, -1.5);
	glEnd();
	glColor3f(0,0,0);
	glTranslatef(0,-6.5,0);
	drawArc(0,0,0.7,0,360);
	glRotatef(90,0,0,1);
	glTranslatef(2.5,0.3,0);
	drawLine();
	glTranslatef(0,-0.3,0);
	drawLine();
	glTranslatef(0,-0.3,0);
	drawLine();
	glRotatef(270,0,0,1);
	glTranslatef(-0.3,-4,0);
	glBegin(GL_POLYGON);
	glVertex2f(-0.8, 0);
	glVertex2f(0.8, 0);
	glVertex2f(0.8,-0.5);
	glVertex2f(-0.8, -0.5);
	glEnd();
	glTranslatef(-0.8,7.5,0);
	glBegin(GL_POLYGON);
	glVertex2f(-0.3, 0);
	glVertex2f(0.3, 0);
	glVertex2f(0.3,-0.2);
	glVertex2f(-0.3, -0.2);
	glEnd();
	glTranslatef(0,-0.5,0);
	glBegin(GL_POLYGON);
	glVertex2f(-0.3, 0);
	glVertex2f(0.3, 0);
	glVertex2f(0.3,-0.2);
	glVertex2f(-0.3, -0.2);
	glEnd();
	glPopMatrix();

}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-10, 10, -10, 10, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init(void)
{
	glClearColor (0.0, 0.0, 0.3, 1.0);
	glShadeModel (GL_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	//controls transformation
	glScalef(k, k, k);	
	glTranslatef(tx, ty, 0);	
	glRotatef(alpha, 0, 0, 1);

	//draw stuff here!
	time_t seconds = time (NULL);
	struct tm * timeinfo = localtime(&seconds);
	double angle = 360-(float)timeinfo->tm_sec/60*360;
	glRotatef(angle,0,0,1);
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glColor4f(red,0,0,0.5);
	glBegin(GL_POLYGON);
	glVertex3f(-2,-1,0);
	glVertex3f(2,-1,0);
	glVertex3f(2,1,0);
	glVertex3f(-2,1,0);
	glEnd();
	glColor4f(0,1,1,0.4);
	glBegin(GL_POLYGON);
	glVertex3f(-1,-2,0);
	glVertex3f(1,-2,0);
	glVertex3f(1,2,0);
	glVertex3f(-1,2,0);
	glEnd();
	

	glPopMatrix();
	glFlush ();
}

void idle()
{
	//update animation here
	if(red>1) increase=false;
	else if(red<0) increase=true;
	if(increase)red+=0.001;
	else red-=0.001;
	
	glutPostRedisplay();	//after updating, draw the screen again
}

void keyboard (unsigned char key, int x, int y)
{
	//keys to control scaling - k
	//keys to control rotation - alpha
	//keys to control translation - tx, ty
	switch (key) {

	case 'a':
		alpha+=10;
		glutPostRedisplay();
		break;

	case 'd':
		alpha-=10;
		glutPostRedisplay();
		break;

	case 'q':
		k+=0.1;
		glutPostRedisplay();
		break;

	case 'e':
		if(k>0.1)
			k-=0.1;
		glutPostRedisplay();
		break;

	case 'z':
		tx-=0.1;
		glutPostRedisplay();
		break;

	case 'c':
		tx+=0.1;
		glutPostRedisplay();
		break;

	case 's':
		ty-=0.1;
		glutPostRedisplay();
		break;

	case 'w':
		ty+=0.1;
		glutPostRedisplay();
		break;

	default:
		break;
	}
}

int main(int argc, char **argv)
{
	cout<<"CS3241 Lab 2\n\n";
	cout<<"+++++CONTROL BUTTONS+++++++\n\n";
	cout<<"Scale Up/Down: Q/E\n";
	cout<<"Rotate Clockwise/Counter-clockwise: A/D\n";
	cout<<"Move Up/Down: W/S\n";
	cout<<"Move Left/Right: Z/C\n";

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (50, 50);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);	
	//glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}
