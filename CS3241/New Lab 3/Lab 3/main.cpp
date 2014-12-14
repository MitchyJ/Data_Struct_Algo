// CS3241Lab1.cpp : Defines the entry point for the console application.
//#include <cmath>
#include <Windows.h>
#include "math.h"
#include <iostream>
#include <fstream>
#include "GL\glut.h"


#define M_PI 3.141592654

// global variable

bool m_Smooth = FALSE;
bool m_Highlight = FALSE;
GLfloat angle = 0;   /* in degrees */
GLfloat angle2 = 0;   /* in degrees */
GLfloat zoom = 1.0;
int mouseButton = 0;
int moving, startx, starty;

#define NO_OBJECT 4;
int current_object = 0;

using namespace std;

void setupLighting()
{
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);

	// Lights, material properties
	GLfloat	ambientProperties[]  = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat	diffuseProperties[]  = {0.8f, 0.8f, 0.8f, 1.0f};
	GLfloat	specularProperties[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat lightPosition[] = {-100.0f,100.0f,100.0f,1.0f};

	glClearDepth( 1.0 );

	glLightfv( GL_LIGHT0, GL_POSITION, lightPosition);

	glLightfv( GL_LIGHT0, GL_AMBIENT, ambientProperties);
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseProperties);
	glLightfv( GL_LIGHT0, GL_SPECULAR, specularProperties);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);

	// Default : lighting
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

}
void drawArc(double cx, double cy, float r,
			 int startDeg, int endDeg)
{
	int i;
	glBegin(GL_POLYGON);
	for(i=startDeg;i<=endDeg;i++){
		glVertex2f(cx+r*sin(2.0*M_PI*i/360.0),cy+r*cos(2.0*M_PI*i/360.0));

	}
	glEnd();
}
void drawTorus(double a,double c){
	//float no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
	//float mat_ambient[] = {0.3f, 0.3f, 0.3f, 1.0f};
	//float mat_ambient_color[] = {0.8f, 0.8f, 0.2f, 1.0f};
	//float mat_diffuse[] = {0.8f, 0.5f, 0.8f, 1.0f};
	//float no_shininess = 0.0f;
	//float mat_shininess=15.0f;
	//float mat_specular[]={0.5f,0.5f,0.5f,1.0f};
	//float mat_emission[] = {0.3f, 0.2f, 0.2f, 0.0f};
	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

	//if(m_Highlight)
	//{
	//	// your codes for highlight here
	//	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
	//} else {
	//	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	//	glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
	//}

	//glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	int i,j;
	int n = 20;
	for(i=0;i<n;i++)
		for(j=0;j<2*n;j++)
			if(m_Smooth)
			{
				glBegin(GL_POLYGON);

				glNormal3d(((c+a*cos(2*i*M_PI/n))*cos(2*(j)*M_PI/n)),((c+a*cos((2*i)*M_PI/n))*sin(2*(j)*M_PI/n)),(a*sin((2*i)*M_PI/n)));
				glVertex3d(((c+a*cos(2*i*M_PI/n))*cos(2*(j)*M_PI/n)),((c+a*cos((2*i)*M_PI/n))*sin(2*(j)*M_PI/n)),(a*sin((2*i)*M_PI/n)));

				glNormal3d(((c+a*cos(2*(i+1)*M_PI/n))*cos(2*(j)*M_PI/n)),((c+a*cos(2*(i+1)*M_PI/n))*sin(2*(j)*M_PI/n)),(a*sin(2*(i+1)*M_PI/n)));
				glVertex3d(((c+a*cos(2*(i+1)*M_PI/n))*cos(2*(j)*M_PI/n)),((c+a*cos(2*(i+1)*M_PI/n))*sin(2*(j)*M_PI/n)),(a*sin(2*(i+1)*M_PI/n)));

				glNormal3d(((c+a*cos(2*(i+1)*(M_PI/n)))*cos(2*(j+1)*M_PI/n)),((c+a*cos(2*(i+1)*M_PI/n))*sin(2*(j+1)*M_PI/n)),(a*sin(2*(i+1)*M_PI/n)));
				glVertex3d(((c+a*cos(2*(i+1)*(M_PI/n)))*cos(2*(j+1)*M_PI/n)),((c+a*cos(2*(i+1)*M_PI/n))*sin(2*(j+1)*M_PI/n)),(a*sin(2*(i+1)*M_PI/n)));

				glNormal3d(((c+a*cos((2*i)*(M_PI/n)))*cos(2*(j+1)*M_PI/n)),((c+a*cos((2*i)*M_PI/n))*sin(2*(j+1)*M_PI/n)),(a*sin((2*i)*M_PI/n)));
				glVertex3d(((c+a*cos((2*i)*(M_PI/n)))*cos(2*(j+1)*M_PI/n)),((c+a*cos((2*i)*M_PI/n))*sin(2*(j+1)*M_PI/n)),(a*sin((2*i)*M_PI/n)));

				glEnd();
			} else	{
				glBegin(GL_POLYGON);
				// Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
				glNormal3d(((c+a*cos(2*(i+0.5)*M_PI/n))*cos(2*(j+0.5)*M_PI/n)),((c+a*cos(2*(i+0.5)*M_PI/n))*sin(2*(j+0.5)*M_PI/n)),(a*sin(2*(i+0.5)*M_PI/n)));
				glVertex3d(((c+a*cos(2*i*M_PI/n))*cos(2*(j)*M_PI/n)),((c+a*cos((2*i)*M_PI/n))*sin(2*(j)*M_PI/n)),(a*sin((2*i)*M_PI/n)));
				glVertex3d(((c+a*cos(2*(i+1)*M_PI/n))*cos(2*(j)*M_PI/n)),((c+a*cos(2*(i+1)*M_PI/n))*sin(2*(j)*M_PI/n)),(a*sin(2*(i+1)*M_PI/n)));
				glVertex3d(((c+a*cos(2*(i+1)*(M_PI/n)))*cos(2*(j+1)*M_PI/n)),((c+a*cos(2*(i+1)*M_PI/n))*sin(2*(j+1)*M_PI/n)),(a*sin(2*(i+1)*M_PI/n)));
				glVertex3d(((c+a*cos((2*i)*(M_PI/n)))*cos(2*(j+1)*M_PI/n)),((c+a*cos((2*i)*M_PI/n))*sin(2*(j+1)*M_PI/n)),(a*sin((2*i)*M_PI/n)));


				//glNormal3d(((c+a*cos(i))*cos(j)),((c+a*cos(i))*sin(j)),(a*sin(i)));
				//glVertex3d(((c+a*cos(i))*cos(j)),((c+a*cos(i))*sin(j)),(a*sin(i)));
				//glVertex3d(((c+a*cos(i))*cos(j+1)),((c+a*cos(i))*sin(j+1)),(a*sin(i+1)));
				//glVertex3d(((c+a*cos(i+1))*cos(j+1)),((c+a*cos(i+1))*sin(j+1)),(a*sin(i+1)));
				//glVertex3d(((c+a*cos(i+1))*cos(j)),((c+a*cos(i+1))*sin(j)),(a*sin(i)));
				glEnd();
			}
}
void drawRect(double edge,double l){
	//float no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
	//float mat_ambient[] = {0.3f, 0.3f, 0.3f, 1.0f};
	//float mat_ambient_color[] = {0.8f, 0.8f, 0.2f, 1.0f};
	//float mat_diffuse[] = {0.8f, 0.5f, 0.8f, 1.0f};
	//float no_shininess = 0.0f;
	//float mat_shininess=15.0f;
	//float mat_specular[]={0.5f,0.5f,0.5f,1.0f};
	//float mat_emission[] = {0.3f, 0.2f, 0.2f, 0.0f};
	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);


	glPushMatrix();
	if(m_Smooth)
	{

		glBegin(GL_POLYGON);
		glNormal3f(0.5,0.5,0.5);
		glVertex3f(  l*edge, -edge, -edge );     
		glVertex3f(  l*edge,  edge, -edge );      
		glVertex3f( l*-edge,  edge, -edge );      
		glVertex3f( l*-edge, -edge, -edge );     
		glEnd();


		glBegin(GL_POLYGON);
		glNormal3f(0.5,0.5,0.5);
		glVertex3f( l*-edge, -edge, edge );
		glVertex3f( l*-edge,  edge, edge );
		glVertex3f(  l*edge,  edge, edge );
		glVertex3f(  l*edge, -edge, edge );
		glEnd();


		glBegin(GL_POLYGON);
		glNormal3f(0.5,0.5,0.5);
		glVertex3f( l*edge, -edge, edge );
		glVertex3f( l*edge,  edge, edge );
		glVertex3f(  l*edge,  edge, -edge );
		glVertex3f(  l*edge, -edge, -edge );
		glEnd();


		glBegin(GL_POLYGON);
		glNormal3f(0.5,0.5,0.5);
		glVertex3f( l*-edge, -edge, -edge );
		glVertex3f( -l*edge,  edge, -edge );
		glVertex3f(  -l*edge,  edge, edge );
		glVertex3f(  -l*edge, -edge, edge );
		glEnd();

		glBegin(GL_POLYGON);
		glNormal3f(0.5,0.5,0.5);
		glVertex3f( -l*edge, edge, edge );
		glVertex3f( -l*edge,  edge, -edge );
		glVertex3f(  l*edge,  edge, -edge );
		glVertex3f(  l*edge, edge, edge );
		glEnd();


		glBegin(GL_POLYGON);
		glNormal3f(0.5,0.5,0.5);
		glVertex3f( -l*edge, -edge, -edge );
		glVertex3f( -l*edge,  -edge, edge );
		glVertex3f(  l*edge,  -edge, edge );
		glVertex3f(  l*edge, -edge, -edge );
		glEnd();
	}
	else
	{
		glBegin(GL_POLYGON);
		glNormal3f(0.5,0.5,0.5);
		glVertex3f(  l*edge, -edge, -edge );     
		glVertex3f(  l*edge,  edge, -edge );      
		glVertex3f( l*-edge,  edge, -edge );      
		glVertex3f( l*-edge, -edge, -edge );     
		glEnd();


		glBegin(GL_POLYGON);
		glNormal3f(0.5,0.5,0.5);
		glVertex3f( l*-edge, -edge, edge );
		glVertex3f( l*-edge,  edge, edge );
		glVertex3f(  l*edge,  edge, edge );
		glVertex3f(  l*edge, -edge, edge );
		glEnd();


		glBegin(GL_POLYGON);
		glNormal3f(0.5,0.5,0.5);
		glVertex3f( l*edge, -edge, edge );
		glVertex3f( l*edge,  edge, edge );
		glVertex3f(  l*edge,  edge, -edge );
		glVertex3f(  l*edge, -edge, -edge );
		glEnd();


		glBegin(GL_POLYGON);
		glNormal3f(0.5,0.5,0.5);
		glVertex3f( l*-edge, -edge, -edge );
		glVertex3f( -l*edge,  edge, -edge );
		glVertex3f(  -l*edge,  edge, edge );
		glVertex3f(  -l*edge, -edge, edge );
		glEnd();

		glBegin(GL_POLYGON);
		glNormal3f(0.5,0.5,0.5);
		glVertex3f( -l*edge, edge, edge );
		glVertex3f( -l*edge,  edge, -edge );
		glVertex3f(  l*edge,  edge, -edge );
		glVertex3f(  l*edge, edge, edge );
		glEnd();


		glBegin(GL_POLYGON);
		glNormal3f(0.5,0.5,0.5);
		glVertex3f( -l*edge, -edge, -edge );
		glVertex3f( -l*edge,  -edge, edge );
		glVertex3f(  l*edge,  -edge, edge );
		glVertex3f(  l*edge, -edge, -edge );
		glEnd();
	}

	glPopMatrix();

	//int i,j;
	//int n = 20;
	//for(i=0;i<n;i++)
	//	for(j=0;j<2*n;j++)
	//		if(m_Smooth)
	//		{
	//			glBegin(GL_POLYGON);

	//			// the normal of each vertex is actaully its own coordinates normalized for a sphere

	//			glEnd();
	//		} else	{

	//			// Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
	//			glBegin(GL_POLYGON); // draw one face
	//			glNormal3d(0,0,0);
	//			glVertex3d(0.5,0.5,-0.5);
	//			glVertex3d(-0.5,0.5,-0.5);
	//			glVertex3d(-0.5,-0.5,-0.5);
	//			glVertex3d(0.5,-0.5,-0.5);
	//			glEnd();
	//			if(i<4)
	//				glRotatef(90,0,1,0); // rotate 90 degree (x4)
	//			else if(i==5) 
	//				glRotatef(90,1,0,0);
	//			else if(i==6)
	//				glRotatef(180,1,0,0);
	//			glEnd();
	//		}


}
void drawCube(float edge)
{

	glPushMatrix();
	if(m_Smooth)
	{
		glBegin(GL_POLYGON);
		glNormal3f(edge/2,edge/2,edge/2);
		glVertex3f(  edge, -edge, -edge );     
		glVertex3f(  edge,  edge, -edge );      
		glVertex3f( -edge,  edge, -edge );      
		glVertex3f( -edge, -edge, -edge );     
		glEnd();

		// White side - BACK
		glBegin(GL_POLYGON);
		glNormal3f(edge/2,edge/2,edge/2);
		glVertex3f( -edge, -edge, edge );
		glVertex3f( -edge,  edge, edge );
		glVertex3f(  edge,  edge, edge );
		glVertex3f(  edge, -edge, edge );
		glEnd();

		// Purple side - RIGHT
		glBegin(GL_POLYGON);
		glNormal3f(edge/2,edge/2,edge/2);
		glVertex3f( edge, -edge, edge );
		glVertex3f( edge,  edge, edge );
		glVertex3f(  edge,  edge, -edge );
		glVertex3f(  edge, -edge, -edge );
		//glVertex3f( 0.5, -0.5, -0.5 );
		//glVertex3f( 0.5,  0.5, -0.5 );
		//glVertex3f( 0.5,  0.5,  0.5 );
		//glVertex3f( 0.5, -0.5,  0.5 );
		glEnd();

		// Green side - LEFT
		glBegin(GL_POLYGON);
		glNormal3f(edge/2,edge/2,edge/2);
		glVertex3f( -edge, -edge, -edge );
		glVertex3f( -edge,  edge, -edge );
		glVertex3f(  -edge,  edge, edge );
		glVertex3f(  -edge, -edge, edge );
		/*glVertex3f( -0.5, -0.5,  0.5 );
		glVertex3f( -0.5,  0.5,  0.5 );
		glVertex3f( -0.5,  0.5, -0.5 );
		glVertex3f( -0.5, -0.5, -0.5 );*/
		glEnd();

		// Blue side - TOP
		glBegin(GL_POLYGON);
		glNormal3f(edge/2,edge/2,edge/2);
		glVertex3f( -edge, edge, edge );
		glVertex3f( -edge,  edge, -edge );
		glVertex3f(  edge,  edge, -edge );
		glVertex3f(  edge, edge, edge );
		//glVertex3f(  0.5,  0.5,  0.5 );
		//glVertex3f(  0.5,  0.5, -0.5 );
		//glVertex3f( -0.5,  0.5, -0.5 );
		//glVertex3f( -0.5,  0.5,  0.5 );
		glEnd();

		// Red side - BOTTOM
		glBegin(GL_POLYGON);
		//glColor3f(   1.0,  0.0,  0.0 );
		glNormal3f(edge/2,edge/2,edge/2);
		glVertex3f( -edge, -edge, -edge );
		glVertex3f( -edge,  -edge, edge );
		glVertex3f(  edge,  -edge, edge );
		glVertex3f(  edge, -edge, -edge );

		//glVertex3f(  0.5, -0.5, -0.5 );
		//glVertex3f(  0.5, -0.5,  0.5 );
		//glVertex3f( -0.5, -0.5,  0.5 );
		//glVertex3f( -0.5, -0.5, -0.5 );
		glEnd();
	}
	else
	{
		glBegin(GL_POLYGON);
		glNormal3f(edge/2,edge/2,edge/2);
		glVertex3f(  edge, -edge, -edge );     
		glVertex3f(  edge,  edge, -edge );      
		glVertex3f( -edge,  edge, -edge );      
		glVertex3f( -edge, -edge, -edge );     
		glEnd();

		// White side - BACK
		glBegin(GL_POLYGON);
		glNormal3f(edge/2,edge/2,edge/2);
		glVertex3f( -edge, -edge, edge );
		glVertex3f( -edge,  edge, edge );
		glVertex3f(  edge,  edge, edge );
		glVertex3f(  edge, -edge, edge );
		glEnd();

		// Purple side - RIGHT
		glBegin(GL_POLYGON);
		glNormal3f(edge/2,edge/2,edge/2);
		glVertex3f( edge, -edge, edge );
		glVertex3f( edge,  edge, edge );
		glVertex3f(  edge,  edge, -edge );
		glVertex3f(  edge, -edge, -edge );
		//glVertex3f( 0.5, -0.5, -0.5 );
		//glVertex3f( 0.5,  0.5, -0.5 );
		//glVertex3f( 0.5,  0.5,  0.5 );
		//glVertex3f( 0.5, -0.5,  0.5 );
		glEnd();

		// Green side - LEFT
		glBegin(GL_POLYGON);
		glNormal3f(edge/2,edge/2,edge/2);
		glVertex3f( -edge, -edge, -edge );
		glVertex3f( -edge,  edge, -edge );
		glVertex3f(  -edge,  edge, edge );
		glVertex3f(  -edge, -edge, edge );
		/*glVertex3f( -0.5, -0.5,  0.5 );
		glVertex3f( -0.5,  0.5,  0.5 );
		glVertex3f( -0.5,  0.5, -0.5 );
		glVertex3f( -0.5, -0.5, -0.5 );*/
		glEnd();

		// Blue side - TOP
		glBegin(GL_POLYGON);
		glNormal3f(edge/2,edge/2,edge/2);
		glVertex3f( -edge, edge, edge );
		glVertex3f( -edge,  edge, -edge );
		glVertex3f(  edge,  edge, -edge );
		glVertex3f(  edge, edge, edge );
		//glVertex3f(  0.5,  0.5,  0.5 );
		//glVertex3f(  0.5,  0.5, -0.5 );
		//glVertex3f( -0.5,  0.5, -0.5 );
		//glVertex3f( -0.5,  0.5,  0.5 );
		glEnd();

		// Red side - BOTTOM
		glBegin(GL_POLYGON);
		//glColor3f(   1.0,  0.0,  0.0 );
		glNormal3f(edge/2,edge/2,edge/2);
		glVertex3f( -edge, -edge, -edge );
		glVertex3f( -edge,  -edge, edge );
		glVertex3f(  edge,  -edge, edge );
		glVertex3f(  edge, -edge, -edge );

		//glVertex3f(  0.5, -0.5, -0.5 );
		//glVertex3f(  0.5, -0.5,  0.5 );
		//glVertex3f( -0.5, -0.5,  0.5 );
		//glVertex3f( -0.5, -0.5, -0.5 );
		glEnd();
	}

	glPopMatrix();
}
void drawPartialCone(double r,double h){
	int i,j;
	int n = 20;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			if(m_Smooth)
			{
				glBegin(GL_POLYGON);
				glNormal3d(((h-(((h/(2*n))*j)))/h)*r*cos(2*i*M_PI/n),((h-(((h/(2*n))*j)))/h)*r*sin(2*i*M_PI/n),(h/(2*n))*j);
				glVertex3d(((h-(((h/(2*n))*j)))/h)*r*cos(2*i*M_PI/n),((h-(((h/(2*n))*j)))/h)*r*sin(2*i*M_PI/n),(h/(2*n))*j);

				glNormal3d(((h-(((h/(2*n))*j)))/h)*r*cos(2*(i+1)*M_PI/n),((h-(((h/(2*n))*j)))/h)*r*sin(2*(i+1)*M_PI/n),(h/(2*n))*j);
				glVertex3d(((h-(((h/(2*n))*j)))/h)*r*cos(2*(i+1)*M_PI/n),((h-(((h/(2*n))*j)))/h)*r*sin(2*(i+1)*M_PI/n),(h/(2*n))*j);

				glNormal3d(((h-(((h/(2*n))*(j+1))))/h)*r*cos(2*(i+1)*M_PI/n),((h-(((h/(2*n))*(j+1))))/h)*r*sin(2*(i+1)*M_PI/n),(h/(2*n))*(j+1));
				glVertex3d(((h-(((h/(2*n))*(j+1))))/h)*r*cos(2*(i+1)*M_PI/n),((h-(((h/(2*n))*(j+1))))/h)*r*sin(2*(i+1)*M_PI/n),(h/(2*n))*(j+1));

				glNormal3d(((h-(((h/(2*n))*(j+1))))/h)*r*cos(2*i*M_PI/n),((h-(((h/(2*n))*(j+1))))/h)*r*sin(2*i*M_PI/n),(h/(2*n))*(j+1));
				glVertex3d(((h-(((h/(2*n))*(j+1))))/h)*r*cos(2*i*M_PI/n),((h-(((h/(2*n))*(j+1))))/h)*r*sin(2*i*M_PI/n),(h/(2*n))*(j+1));

				glEnd();
			} else	{
				glBegin(GL_POLYGON);

				glNormal3d(((h-(((h/(2*n))*(j+0.5))))/h)*r*cos(2*(i+0.5)*M_PI/n),((h-(((h/(2*n))*(j+0.5))))/h)*r*sin(2*(i+0.5)*M_PI/n),(h/(2*n))*(j+0.5));
				glVertex3d(((h-(((h/(2*n))*j)))/h)*r*cos(2*i*M_PI/n),((h-(((h/(2*n))*j)))/h)*r*sin(2*i*M_PI/n),(h/(2*n))*j);
				glVertex3d(((h-(((h/(2*n))*j)))/h)*r*cos(2*(i+1)*M_PI/n),((h-(((h/(2*n))*j)))/h)*r*sin(2*(i+1)*M_PI/n),(h/(2*n))*j);
				glVertex3d(((h-(((h/(2*n))*(j+1))))/h)*r*cos(2*(i+1)*M_PI/n),((h-(((h/(2*n))*(j+1))))/h)*r*sin(2*(i+1)*M_PI/n),(h/(2*n))*(j+1));
				glVertex3d(((h-(((h/(2*n))*(j+1))))/h)*r*cos(2*i*M_PI/n),((h-(((h/(2*n))*(j+1))))/h)*r*sin(2*i*M_PI/n),(h/(2*n))*(j+1));
				glEnd();
			}

}
void drawCone(double r,double h){
	int i,j;
	int n = 20;
	for(i=0;i<n;i++)
		for(j=0;j<2*n;j++)
			if(m_Smooth)
			{
				glBegin(GL_POLYGON);
				glNormal3d(((h-(((h/(2*n))*j)))/h)*r*cos(2*i*M_PI/n),((h-(((h/(2*n))*j)))/h)*r*sin(2*i*M_PI/n),(h/(2*n))*j);
				glVertex3d(((h-(((h/(2*n))*j)))/h)*r*cos(2*i*M_PI/n),((h-(((h/(2*n))*j)))/h)*r*sin(2*i*M_PI/n),(h/(2*n))*j);

				glNormal3d(((h-(((h/(2*n))*j)))/h)*r*cos(2*(i+1)*M_PI/n),((h-(((h/(2*n))*j)))/h)*r*sin(2*(i+1)*M_PI/n),(h/(2*n))*j);
				glVertex3d(((h-(((h/(2*n))*j)))/h)*r*cos(2*(i+1)*M_PI/n),((h-(((h/(2*n))*j)))/h)*r*sin(2*(i+1)*M_PI/n),(h/(2*n))*j);

				glNormal3d(((h-(((h/(2*n))*(j+1))))/h)*r*cos(2*(i+1)*M_PI/n),((h-(((h/(2*n))*(j+1))))/h)*r*sin(2*(i+1)*M_PI/n),(h/(2*n))*(j+1));
				glVertex3d(((h-(((h/(2*n))*(j+1))))/h)*r*cos(2*(i+1)*M_PI/n),((h-(((h/(2*n))*(j+1))))/h)*r*sin(2*(i+1)*M_PI/n),(h/(2*n))*(j+1));

				glNormal3d(((h-(((h/(2*n))*(j+1))))/h)*r*cos(2*i*M_PI/n),((h-(((h/(2*n))*(j+1))))/h)*r*sin(2*i*M_PI/n),(h/(2*n))*(j+1));
				glVertex3d(((h-(((h/(2*n))*(j+1))))/h)*r*cos(2*i*M_PI/n),((h-(((h/(2*n))*(j+1))))/h)*r*sin(2*i*M_PI/n),(h/(2*n))*(j+1));

				glEnd();
			} else	{
				glBegin(GL_POLYGON);

				glNormal3d(((h-(((h/(2*n))*(j+0.5))))/h)*r*cos(2*(i+0.5)*M_PI/n),((h-(((h/(2*n))*(j+0.5))))/h)*r*sin(2*(i+0.5)*M_PI/n),(h/(2*n))*(j+0.5));
				glVertex3d(((h-(((h/(2*n))*j)))/h)*r*cos(2*i*M_PI/n),((h-(((h/(2*n))*j)))/h)*r*sin(2*i*M_PI/n),(h/(2*n))*j);
				glVertex3d(((h-(((h/(2*n))*j)))/h)*r*cos(2*(i+1)*M_PI/n),((h-(((h/(2*n))*j)))/h)*r*sin(2*(i+1)*M_PI/n),(h/(2*n))*j);
				glVertex3d(((h-(((h/(2*n))*(j+1))))/h)*r*cos(2*(i+1)*M_PI/n),((h-(((h/(2*n))*(j+1))))/h)*r*sin(2*(i+1)*M_PI/n),(h/(2*n))*(j+1));
				glVertex3d(((h-(((h/(2*n))*(j+1))))/h)*r*cos(2*i*M_PI/n),((h-(((h/(2*n))*(j+1))))/h)*r*sin(2*i*M_PI/n),(h/(2*n))*(j+1));
				glEnd();
			}

} 
void color(double r,double g,double b,double a){
	float no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
	float mat_ambient[] = {0.3f, 0.3f, 0.3f, 1.0f};
	float mat_ambient_color[] = {0.8f, 0.8f, 0.2f, 1.0f};
	float mat_diffuse[] = {r ,g,b,a};
	float no_shininess = 0.0f;
	float mat_shininess=15.0f;
	float mat_specular[]={0.5f,0.5f,0.5f,0.1f};
	float mat_emission[] = {0.3f, 0.2f, 0.2f, 0.0f};
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

	if(m_Highlight)
	{
		// your codes for highlight here
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
	} else {
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
	}

	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

}
void drawPartialSphere(double r){
	int i,j;
	int n = 20;
	for(i=0;i<n/5;i++)
		for(j=0;j<2*n;j++)
			if(m_Smooth)
			{
				glBegin(GL_POLYGON);

				// the normal of each vertex is actaully its own coordinates normalized for a sphere

				// your normal here
				glNormal3d(sin(i*M_PI/n)*cos(j*M_PI/n),cos(i*M_PI/n)*cos(j*M_PI/n),sin(j*M_PI/n));
				glVertex3d(r*sin(i*M_PI/n)*cos(j*M_PI/n),r*cos(i*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));

				// your normal here
				glNormal3d(sin((i+1)*M_PI/n)*cos(j*M_PI/n),cos((i+1)*M_PI/n)*cos(j*M_PI/n),sin(j*M_PI/n));
				glVertex3d(r*sin((i+1)*M_PI/n)*cos(j*M_PI/n),r*cos((i+1)*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));

				// your normal here
				glNormal3d(sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),sin((j+1)*M_PI/n));
				glVertex3d(r*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));

				// your normal here
				glNormal3d(sin(i* M_PI/n)*cos((j+1)* M_PI/n),cos(i*M_PI/n)*cos((j+1)*M_PI/n),sin((j+1)*M_PI/n));
				glVertex3d(r*sin(i*M_PI/n)*cos((j+1)*M_PI/n),r*cos(i*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
				glEnd();
			} else	{
				glBegin(GL_POLYGON);
				// Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
				glNormal3d(sin((i+0.5)*M_PI/n)*cos((j+0.5)*M_PI/n),cos((i+0.5)*M_PI/n)*cos((j+0.5)*M_PI/n),sin((j+0.5)*M_PI/n));
				glVertex3d(r*sin(i*M_PI/n)*cos(j*M_PI/n),r*cos(i*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
				glVertex3d(r*sin((i+1)*M_PI/n)*cos(j*M_PI/n),r*cos((i+1)*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
				glVertex3d(r*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
				glVertex3d(r*sin(i*M_PI/n)*cos((j+1)*M_PI/n),r*cos(i*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
				glEnd();
			}
}
void drawSphere(double r)
{
	int i,j;
	int n = 20;
	for(i=0;i<n;i++)
		for(j=0;j<2*n;j++)
			if(m_Smooth)
			{
				glBegin(GL_POLYGON);

				// the normal of each vertex is actaully its own coordinates normalized for a sphere

				// your normal here
				glNormal3d(sin(i*M_PI/n)*cos(j*M_PI/n),cos(i*M_PI/n)*cos(j*M_PI/n),sin(j*M_PI/n));
				glVertex3d(r*sin(i*M_PI/n)*cos(j*M_PI/n),r*cos(i*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));

				// your normal here
				glNormal3d(sin((i+1)*M_PI/n)*cos(j*M_PI/n),cos((i+1)*M_PI/n)*cos(j*M_PI/n),sin(j*M_PI/n));
				glVertex3d(r*sin((i+1)*M_PI/n)*cos(j*M_PI/n),r*cos((i+1)*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));

				// your normal here
				glNormal3d(sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),sin((j+1)*M_PI/n));
				glVertex3d(r*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));

				// your normal here
				glNormal3d(sin(i* M_PI/n)*cos((j+1)* M_PI/n),cos(i*M_PI/n)*cos((j+1)*M_PI/n),sin((j+1)*M_PI/n));
				glVertex3d(r*sin(i*M_PI/n)*cos((j+1)*M_PI/n),r*cos(i*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
				glEnd();
			} else	{
				glBegin(GL_POLYGON);
				// Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
				glNormal3d(sin((i+0.5)*M_PI/n)*cos((j+0.5)*M_PI/n),cos((i+0.5)*M_PI/n)*cos((j+0.5)*M_PI/n),sin((j+0.5)*M_PI/n));
				glVertex3d(r*sin(i*M_PI/n)*cos(j*M_PI/n),r*cos(i*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
				glVertex3d(r*sin((i+1)*M_PI/n)*cos(j*M_PI/n),r*cos((i+1)*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
				glVertex3d(r*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
				glVertex3d(r*sin(i*M_PI/n)*cos((j+1)*M_PI/n),r*cos(i*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
				glEnd();
			}

}
void drawNewCylinder(double r,double h){
	int i,j;
	int n = 20;
	for(i=0;i<n;i++)
		for(j=0;j<2*n;j++)
			if(m_Smooth)
			{
				glBegin(GL_POLYGON);
				glNormal3d((r*(cos(2*i*M_PI/n))),(r*(sin(2*i*M_PI/n))),(h/(2*n))*j);
				glVertex3d((r*(cos(2*i*M_PI/n))),(r*(sin(2*i*M_PI/n))),(h/(2*n))*j);

				glNormal3d((r*(cos(2*(i+1)*M_PI/n))),(r*(sin(2*(i+1)*M_PI/n))),(h/(2*n))*j);
				glVertex3d((r*(cos(2*(i+1)*M_PI/n))),(r*(sin(2*(i+1)*M_PI/n))),(h/(2*n))*j);

				glNormal3d((r*(cos(2*(i+1)*M_PI/n))),(r*(sin(2*(i+1)*M_PI/n))),(h/(2*n))*(j+1));
				glVertex3d((r*(cos(2*(i+1)*M_PI/n))),(r*(sin(2*(i+1)*M_PI/n))),(h/(2*n))*(j+1));

				glNormal3d((r*(cos(2*i*M_PI/n))),(r*(sin(2*i*M_PI/n))),(h/(2*n))*(j+1));
				glVertex3d((r*(cos(2*i*M_PI/n))),(r*(sin(2*i*M_PI/n))),(h/(2*n))*(j+1));

				glEnd();
			} else	{
				glBegin(GL_POLYGON);
				glNormal3d((r*(cos(2*(i+0.5)*M_PI/n))),(r*(sin(2*(i+0.5)*M_PI/n))),	(h/(2*n))*(j+0.5));
				glVertex3d((r*(cos(2*i*M_PI/n))),(r*(sin(2*i*M_PI/n))),(h/(2*n))*j);
				glVertex3d((r*(cos(2*(i+1)*M_PI/n))),(r*(sin(2*(i+1)*M_PI/n))),(h/(2*n))*j);
				glVertex3d((r*(cos(2*(i+1)*M_PI/n))),(r*(sin(2*(i+1)*M_PI/n))),(h/(2*n))*(j+1));
				glVertex3d((r*(cos(2*i*M_PI/n))),(r*(sin(2*i*M_PI/n))),(h/(2*n))*(j+1));
				glEnd();
			}

}
void drawCylinder(double r,double h){

	int i,j;
	int n = 20;
	for(i=0;i<n;i++)
		for(j=0;j<h;j++)
			if(m_Smooth)
			{
				glBegin(GL_POLYGON);
				glNormal3d((r*(cos(2*i*M_PI/n))),(r*(sin(2*i*M_PI/n))),j);
				glVertex3d((r*(cos(2*i*M_PI/n))),(r*(sin(2*i*M_PI/n))),j);

				glNormal3d((r*(cos(2*(i+1)*M_PI/n))),(r*(sin(2*(i+1)*M_PI/n))),j);
				glVertex3d((r*(cos(2*(i+1)*M_PI/n))),(r*(sin(2*(i+1)*M_PI/n))),j);

				glNormal3d((r*(cos(2*(i+1)*M_PI/n))),(r*(sin(2*(i+1)*M_PI/n))),(j+1));
				glVertex3d((r*(cos(2*(i+1)*M_PI/n))),(r*(sin(2*(i+1)*M_PI/n))),(j+1));

				glNormal3d((r*(cos(2*i*M_PI/n))),(r*(sin(2*i*M_PI/n))),(j+1));
				glVertex3d((r*(cos(2*i*M_PI/n))),(r*(sin(2*i*M_PI/n))),(j+1));

				glEnd();
			} else	{
				glBegin(GL_POLYGON);
				glNormal3d((r*(cos(2*(i+0.5)*M_PI/n))),(r*(sin(2*(i+0.5)*M_PI/n))),(j+0.5));
				glVertex3d((r*(cos(2*i*M_PI/n))),(r*(sin(2*i*M_PI/n))),j);
				glVertex3d((r*(cos(2*(i+1)*M_PI/n))),(r*(sin(2*(i+1)*M_PI/n))),j);
				glVertex3d((r*(cos(2*(i+1)*M_PI/n))),(r*(sin(2*(i+1)*M_PI/n))),(j+1));
				glVertex3d((r*(cos(2*i*M_PI/n))),(r*(sin(2*i*M_PI/n))),(j+1));
				glEnd();
			}

}
void drawPartialEllipsoid(double a,double b,double c){
	int i,j;
	int n = 20;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			if(m_Smooth)
			{
				glBegin(GL_POLYGON);

				glNormal3d(a*((cos(i*M_PI/n))*sin(j*M_PI/n)),b*((sin(i*M_PI/n))*sin(j*M_PI/n)),c*(cos(j*M_PI/n)));
				glVertex3d(a*((cos(i*M_PI/n))*sin(j*M_PI/n)),b*((sin(i*M_PI/n))*sin(j*M_PI/n)),c*(cos(j*M_PI/n)));
				glNormal3d(a*((cos((i+1)*M_PI/n))*sin(j*M_PI/n)),b*((sin((i+1)*M_PI/n))*sin(j*M_PI/n)),c*(cos(j*M_PI/n)));
				glVertex3d(a*((cos((i+1)*M_PI/n))*sin(j*M_PI/n)),b*((sin((i+1)*M_PI/n))*sin(j*M_PI/n)),c*(cos(j*M_PI/n)));
				glNormal3d(a*((cos((i+1)*M_PI/n))*sin((j+1)*M_PI/n)),b*((sin((i+1)*M_PI/n))*sin((j+1)*M_PI/n)),c*(cos((j+1)*M_PI/n)));
				glVertex3d(a*((cos((i+1)*M_PI/n))*sin((j+1)*M_PI/n)),b*((sin((i+1)*M_PI/n))*sin((j+1)*M_PI/n)),c*(cos((j+1)*M_PI/n)));
				glNormal3d(a*((cos(i*M_PI/n))*sin((j+1)*M_PI/n)),b*((sin(i*M_PI/n))*sin((j+1)*M_PI/n)),c*(cos((j+1)*M_PI/n)));
				glVertex3d(a*((cos(i*M_PI/n))*sin((j+1)*M_PI/n)),b*((sin(i*M_PI/n))*sin((j+1)*M_PI/n)),c*(cos((j+1)*M_PI/n)));
				// the normal of each vertex is actaully its own coordinates normalized for a sphere
				glEnd();
			} else	{
				glBegin(GL_POLYGON);
				// Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
				glNormal3d(a*((cos((i+0.5)*M_PI/n))*sin((j+0.5)*M_PI/n)),b*((sin((i+0.5)*M_PI/n))*sin((j+0.5)*M_PI/n)),c*(cos((j+0.5)*M_PI/n)));
				glVertex3d(a*((cos(i*M_PI/n))*sin(j*M_PI/n)),b*((sin(i*M_PI/n))*sin(j*M_PI/n)),c*(cos(j*M_PI/n)));
				glVertex3d(a*((cos((i+1)*M_PI/n))*sin(j*M_PI/n)),b*((sin((i+1)*M_PI/n))*sin(j*M_PI/n)),c*(cos(j*M_PI/n)));
				glVertex3d(a*((cos((i+1)*M_PI/n))*sin((j+1)*M_PI/n)),b*((sin((i+1)*M_PI/n))*sin((j+1)*M_PI/n)),c*(cos((j+1)*M_PI/n)));
				glVertex3d(a*((cos(i*M_PI/n))*sin((j+1)*M_PI/n)),b*((sin(i*M_PI/n))*sin((j+1)*M_PI/n)),c*(cos((j+1)*M_PI/n)));
				glEnd();
			}

}
void drawEllipsoid(double a,double b,double c){

	int i,j;
	int n = 20;
	for(i=0;i<n;i++)
		for(j=0;j<2*n;j++)
			if(m_Smooth)
			{
				glBegin(GL_POLYGON);

				glNormal3d(a*((cos(i*M_PI/n))*sin(j*M_PI/n)),b*((sin(i*M_PI/n))*sin(j*M_PI/n)),c*(cos(j*M_PI/n)));
				glVertex3d(a*((cos(i*M_PI/n))*sin(j*M_PI/n)),b*((sin(i*M_PI/n))*sin(j*M_PI/n)),c*(cos(j*M_PI/n)));
				glNormal3d(a*((cos((i+1)*M_PI/n))*sin(j*M_PI/n)),b*((sin((i+1)*M_PI/n))*sin(j*M_PI/n)),c*(cos(j*M_PI/n)));
				glVertex3d(a*((cos((i+1)*M_PI/n))*sin(j*M_PI/n)),b*((sin((i+1)*M_PI/n))*sin(j*M_PI/n)),c*(cos(j*M_PI/n)));
				glNormal3d(a*((cos((i+1)*M_PI/n))*sin((j+1)*M_PI/n)),b*((sin((i+1)*M_PI/n))*sin((j+1)*M_PI/n)),c*(cos((j+1)*M_PI/n)));
				glVertex3d(a*((cos((i+1)*M_PI/n))*sin((j+1)*M_PI/n)),b*((sin((i+1)*M_PI/n))*sin((j+1)*M_PI/n)),c*(cos((j+1)*M_PI/n)));
				glNormal3d(a*((cos(i*M_PI/n))*sin((j+1)*M_PI/n)),b*((sin(i*M_PI/n))*sin((j+1)*M_PI/n)),c*(cos((j+1)*M_PI/n)));
				glVertex3d(a*((cos(i*M_PI/n))*sin((j+1)*M_PI/n)),b*((sin(i*M_PI/n))*sin((j+1)*M_PI/n)),c*(cos((j+1)*M_PI/n)));
				// the normal of each vertex is actaully its own coordinates normalized for a sphere
				glEnd();
			} else	{
				glBegin(GL_POLYGON);
				// Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
				glNormal3d(a*((cos((i+0.5)*M_PI/n))*sin((j+0.5)*M_PI/n)),b*((sin((i+0.5)*M_PI/n))*sin((j+0.5)*M_PI/n)),c*(cos((j+0.5)*M_PI/n)));
				glVertex3d(a*((cos(i*M_PI/n))*sin(j*M_PI/n)),b*((sin(i*M_PI/n))*sin(j*M_PI/n)),c*(cos(j*M_PI/n)));
				glVertex3d(a*((cos((i+1)*M_PI/n))*sin(j*M_PI/n)),b*((sin((i+1)*M_PI/n))*sin(j*M_PI/n)),c*(cos(j*M_PI/n)));
				glVertex3d(a*((cos((i+1)*M_PI/n))*sin((j+1)*M_PI/n)),b*((sin((i+1)*M_PI/n))*sin((j+1)*M_PI/n)),c*(cos((j+1)*M_PI/n)));
				glVertex3d(a*((cos(i*M_PI/n))*sin((j+1)*M_PI/n)),b*((sin(i*M_PI/n))*sin((j+1)*M_PI/n)),c*(cos((j+1)*M_PI/n)));
				glEnd();
			}
}
void drawShape(){
	glPushMatrix();{
		color(0/255.0, 0/255.0, 255/255.0, 1.0f);
		glTranslatef(0,5.1,0);
		drawSphere(0.25);
	}
	glPopMatrix();
	glPushMatrix();{
		color(255/255.0, 255/255.0, 255/255.0, 1.0f);
		glTranslatef(0,1.4,0);
		glRotatef(90,1,0,0);
		glScalef(8,1,1);
		for(int i=0;i<6;i++){
			glRotatef(30,0,1,0);
			drawEllipsoid(0.06,0.18,0.26);
		}

	}glPopMatrix();
	glPushMatrix();{
		color(225/255.0, 237/255.0, 7/255.0, 1.0f);
		glRotatef(90,1,0,0);
		for(int i=0;i<6;i++){
			drawCone(0.25,0.8);
			glRotatef(72,0,1,0);
		}
	}
	glPopMatrix();
	glPushMatrix();{
		color(255/255.0, 0/255.0, 0/255.0, 1.0f);
		glTranslatef(0.28,1.07,0);
		drawSphere(0.08);
		glTranslatef(-0.56,0,0);
		drawSphere(0.08);
	}
	glPopMatrix();
	glPushMatrix();{
		glTranslatef(0.28,4.98,0);
		drawSphere(0.08);
		glTranslatef(-0.56,0,0);
		drawSphere(0.08);
	}
	glPopMatrix();
	glPushMatrix();{

		glTranslatef(0,1.07,0.28);
		drawSphere(0.08);
		glTranslatef(0,0,-0.56);
		drawSphere(0.08);
	}
	glPopMatrix();
	glPushMatrix();{
		glTranslatef(0,4.98,0.28);
		drawSphere(0.08);
		glTranslatef(0,0,-0.56);
		drawSphere(0.08);
	}
	glPopMatrix();

	glPushMatrix();{
		color(202/255.0, 11/255.0, 45/255.0, 1.0f);
		for(int i=0;i<6;i++){
			drawPartialSphere(1);
			glTranslatef(0,0.001,0.001);
			glRotatef(72,0,1,0);
		}
	}
	glPopMatrix();
	glPushMatrix();{
		color(38/255.0, 242/255.0, 2/255.0, 1.0f);
		glTranslatef(0,1.08,0);
		glRotatef(90,1,0,0);
		drawTorus(0.1,0.2);
		glRotatef(-90,1,0,0);
		glTranslatef(0,3.92,0);
		glRotatef(90,1,0,0);
		drawTorus(0.1,0.2);
	}
	glPopMatrix();
	glPushMatrix();{
		color(35/255.0, 153/255.0, 177/255.0, 1.0f);
		glTranslatef(0,1,0);
		glRotatef(-90,1,0,0);
		drawNewCylinder(0.2,4);
	}
	glPopMatrix();
}
void drawDrums(){

	glPushMatrix();{
		color(122/255.0, 3/255.0, 15/255.0, 1.0f);
		drawNewCylinder(0.55,0.9);
		glTranslatef(0,0,0.9);
		color(172/255.0, 172/255.0, 172/255.0, 1.0f);
		drawNewCylinder(0.55,0.05);
		glTranslatef(0,0,-0.95);
		color(172/255.0, 172/255.0, 172/255.0, 1.0f);
		drawNewCylinder(0.55,0.05);
		color(255/255.0, 255/255.0, 255/255.0, 1.0f);
		glTranslatef(0,0,0.05);
		drawArc(0,0,0.54,0,360);
		glTranslatef(0,0,0.91);
		drawArc(0,0,0.54,0,360);
	}
	glPopMatrix();
	glPushMatrix();
	{
		for(int i=0;i<10;i++){
			glRotatef(36,0,0,1);

			glPushMatrix();
			{	
				color(172/255.0, 172/255.0, 172/255.0, 1.0f);
				glTranslatef(0,0.55,0);
				drawNewCylinder(0.01,0.3);
			}
			glPopMatrix();
		}
	}
	glPopMatrix();
	glPushMatrix();{
		for(int i=0;i<10;i++){
			glRotatef(36,0,0,1);
			glPushMatrix();
			{	
				color(172/255.0, 172/255.0, 172/255.0, 1.0f);

				glTranslatef(0,0.55,0.6);
				drawNewCylinder(0.01,0.3);
			}
			glPopMatrix();
		}
	}
	glPopMatrix();
	glPushMatrix();{
		for(int i=0;i<10;i++){
			glRotatef(36,0,0,1);
			glPushMatrix();
			{	
				color(172/255.0, 172/255.0, 172/255.0, 1.0f);
				glTranslatef(0,0.55,0.28);
				glRotatef(90,0,1,0);
				drawRect(0.015,3);
			}
			glPopMatrix();
		}
	}
	glPopMatrix();

	glPushMatrix();{
		for(int i=0;i<10;i++){
			glRotatef(36,0,0,1);
			glPushMatrix();
			{	
				color(172/255.0, 172/255.0, 172/255.0, 1.0f);
				glTranslatef(0,0.55,0.65);
				glRotatef(90,0,1,0);
				drawRect(0.015,3);
			}
			glPopMatrix();
		}
	}
	glPopMatrix();
}
void drawSupport(){

	glPushMatrix();{
		color(172/255.0, 172/255.0, 172/255.0, 1.0f);
		glTranslatef(-0.25,-0.8,1.25);
		glRotatef(195,0,1,0);
		drawPartialCone(0.1,0.3);
	}
	glPopMatrix();
	glPushMatrix();{
		color(172/255.0, 172/255.0, 172/255.0, 1.0f);
		glTranslatef(-0.28,-0.8,1.15);
		glRotatef(195,0,1,0);
		drawNewCylinder(0.048,0.4);
	}
	glPopMatrix();

	glPushMatrix();
	{
		color(172/255.0, 172/255.0, 172/255.0, 1.0f);
		glTranslatef(-0.38,-0.8,0.78);
		glRotatef(165,0,1,0);
		glRotatef(-65,1,0,0);
		drawSphere(0.05);
		drawNewCylinder(0.03,0.2);
	}
	glPopMatrix();
	glPushMatrix();
	{
		color(172/255.0, 172/255.0, 172/255.0, 1.0f);
		glTranslatef(-0.38,-0.8,0.78);
		glRotatef(-195,0,1,0);
		glRotatef(65,1,0,0);
		drawNewCylinder(0.03,0.2);
	}
	glPopMatrix();

	glPushMatrix();
	{
		color(172/255.0, 172/255.0, 172/255.0, 1.0f);
		glTranslatef(-0.32,-0.98,0.85);
		glRotatef(195,0,1,0);
		drawNewCylinder(0.03,0.35);
	}
	glPopMatrix();

	glPushMatrix();
	{
		color(172/255.0, 172/255.0, 172/255.0, 1.0f);
		glTranslatef(-0.31,-0.61,0.85);
		glRotatef(195,0,1,0);
		drawNewCylinder(0.03,0.35);
	}
	glPopMatrix();

	glPushMatrix();
	{
		color(172/255.0, 172/255.0, 172/255.0, 1.0f);
		glTranslatef(-0.4,-0.98,0.55);
		glRotatef(165,0,1,0);
		glRotatef(65,1,0,0);
		drawSphere(0.05);
		drawNewCylinder(0.03,0.35);
	}
	glPopMatrix();
	glPushMatrix();
	{
		color(172/255.0, 172/255.0, 172/255.0, 1.0f);
		glTranslatef(-0.39,-0.61,0.55);
		glRotatef(135,0,1,0);
		glRotatef(-65,1,0,0);
		drawSphere(0.05);
		drawNewCylinder(0.03,0.35);
	}
	glPopMatrix();
	glPushMatrix();
	{
		color(172/255.0, 172/255.0, 172/255.0, 1.0f);
		glTranslatef(0.1,0.3,2.7);
		glRotatef(90,1,0,0);
		drawArc(0,0,0.1,0,360);
		drawNewCylinder(0.1,0.1);
	}
	glPopMatrix();

	glPushMatrix();
	{
		color(172/255.0, 172/255.0, 172/255.0, 1.0f);
		glTranslatef(0.1,0.25,2.7);
		glRotatef(70,0,1,0);
		drawNewCylinder(0.03,1.5);
	}
	glPopMatrix();

	glPushMatrix();
	{
		color(172/255.0, 172/255.0, 172/255.0, 1.0f);
		glTranslatef(0.1,0.25,2.7);
		glRotatef(-40,0,1,0);
		drawNewCylinder(0.03,1.5);
	}
	glPopMatrix();


	glTranslatef(0,-2.1,0);
	glPushMatrix();
	{
		color(172/255.0, 172/255.0, 172/255.0, 1.0f);
		glTranslatef(0.1,0.3,2.7);
		glRotatef(90,1,0,0);
		drawArc(0,0,0.1,0,360);
		drawNewCylinder(0.1,0.1);
	}
	glPopMatrix();

	glPushMatrix();
	{
		color(172/255.0, 172/255.0, 172/255.0, 1.0f);
		glTranslatef(0.1,0.25,2.7);
		glRotatef(70,0,1,0);
		drawNewCylinder(0.03,1.5);
	}
	glPopMatrix();

	glPushMatrix();
	{
		color(172/255.0, 172/255.0, 172/255.0, 1.0f);
		glTranslatef(0.1,0.25,2.7);
		glRotatef(-40,0,1,0);
		drawNewCylinder(0.03,1.5);
	}
	glPopMatrix();


}
void drawFloorTom(){
	//floor tom
	glPushMatrix();{
		glTranslatef(2,0,0);
		glRotatef(-5,0,1,0);
		glRotatef(8,0,0,1);
		glScalef(1.3,1.3,1.2);
		drawDrums();
	}
	glPopMatrix();

	glPushMatrix();{

		glTranslatef(1.95,0,0);
		for(int i=0;i<4;i++){
			glRotatef(90,0,0,1);
			glPushMatrix();
			{
				glTranslatef(0.74,0,0.6);
				drawCube(0.05);
			}glPopMatrix();
		}

	}
	glPopMatrix();

	glPushMatrix();{
		glTranslatef(1.95,0,0);
		for(int i=0;i<4;i++){
			glRotatef(90,0,0,1);
			glPushMatrix();
			{
				glTranslatef(0.74,0,0.2);
				drawNewCylinder(0.03,1.6);
			}glPopMatrix();
		}

	}
	glPopMatrix();

}
void drawSnareDrum(){
	glPushMatrix();{
		glTranslatef(1,0,0);
		glScalef(1.2,1.2,0.4);
		drawDrums();
	}
	glPopMatrix();
}
void drawSnareSuport(){
	//big 
	glPushMatrix();{
		glTranslatef(1,0,0);
		for(int i=0;i<3;i++){
			glRotatef(120,0,0,1);
			glPushMatrix();{
				glTranslatef(-0.6,0,0.35);
				glRotatef(60,0,1,0);
				drawNewCylinder(0.02,0.7);
			}glPopMatrix();
		}
	}glPopMatrix();
	//smaller
	glPushMatrix();{
		glTranslatef(1,0,0.6);
		for(int i=0;i<3;i++){
			glRotatef(120,0,0,1);
			glPushMatrix();{
				glTranslatef(-0.15,0,0.02);
				glRotatef(40,0,1,0);
				drawNewCylinder(0.01,0.2);
			}glPopMatrix();
		}
	}glPopMatrix();

	glPushMatrix();{
		glTranslatef(1,0,0.6);
		drawNewCylinder(0.02,1);
	}
	glPopMatrix();

	glPushMatrix();{
		glTranslatef(1,0,2.2);
		glRotatef(180,0,1,0);
		for(int i=0;i<3;i++){
			glRotatef(120,0,0,1);
			glPushMatrix();{
				glTranslatef(-0.5,0,0.35);
				glRotatef(45,0,1,0);
				drawNewCylinder(0.02,0.7);
			}glPopMatrix();
		}
	}glPopMatrix();

	glPushMatrix();{
		glTranslatef(1,0,1.4);
		glRotatef(60,0,0,1);
		for(int i=0;i<3;i++){
			glRotatef(120,0,0,1);
			glPushMatrix();{
				glTranslatef(-0.1,0,0.02);
				glRotatef(40,0,1,0);
				drawNewCylinder(0.01,0.15);
			}glPopMatrix();
		}
	}glPopMatrix();
}
void drawRideCymbal(){
	glPushMatrix();{
		color(194/255.0, 183/255.0, 37/255.0, 1.0f);
		glRotatef(165,0,1,0);
		drawCone(1.1,0.2);
	}
	glPopMatrix();
	glPushMatrix();{
		color(172/255.0, 172/255.0, 172/255.0, 1.0f);
		glTranslatef(0,0,-0.18);
		glRotatef(-40,0,1,0);
		drawNewCylinder(0.02,1.3);
	}
	glPopMatrix();

	glPushMatrix();{
		glTranslatef(-0.45,0.075,0.4);
		glRotatef(90,1,0,0);
		drawArc(0,0,0.069,0,360);
		drawNewCylinder(0.07,0.15);
		glTranslatef(0,0,0.1);
		drawArc(0,0,0.069,0,360);
	}
	glPopMatrix();
	glPushMatrix();{
		glTranslatef(-2.1,0,-0.3);
		glScalef(1.5,1.5,2.2);
		glRotatef(15,0,1,0);
		//stand
		glPushMatrix();{
			glTranslatef(1,0,0.6);
			drawNewCylinder(0.02,1.7);
		}
		glPopMatrix();

		glPushMatrix();{
			glTranslatef(1,0,2.9);
			glRotatef(180,0,1,0);
			for(int i=0;i<3;i++){
				glRotatef(120,0,0,1);
				glPushMatrix();{
					glTranslatef(-0.5,0,0.35);
					glRotatef(45,0,1,0);
					drawNewCylinder(0.02,0.7);
				}glPopMatrix();
			}
		}glPopMatrix();

		glPushMatrix();{
			glTranslatef(1,0,2.1);
			glRotatef(60,0,0,1);
			for(int i=0;i<3;i++){
				glRotatef(120,0,0,1);
				glPushMatrix();{
					glTranslatef(-0.1,0,0.02);
					glRotatef(40,0,1,0);
					drawNewCylinder(0.01,0.15);
				}glPopMatrix();
			}
		}glPopMatrix();
	}glPopMatrix();
}
void drawHiHat(){
	glPushMatrix();{
		color(194/255.0, 183/255.0, 37/255.0, 1.0f);
		glRotatef(190,0,1,0);
		drawCone(0.5,0.05);
	}
	glPopMatrix();

	glPushMatrix();{
		color(194/255.0, 183/255.0, 37/255.0, 1.0f);
		glTranslatef(0,0,0.05);
		glRotatef(370,0,1,0);
		drawCone(0.5,0.05);
	}
	glPopMatrix();

	glPushMatrix();{
		glTranslatef(-1.2,0,-0.7);
		color(172/255.0, 172/255.0, 172/255.0, 1.0f);
		glRotatef(15,0,1,0);
		//stand
		glPushMatrix();{
			glTranslatef(1,0,0.6);
			drawNewCylinder(0.02,2.4);
		}
		glPopMatrix();

		glPushMatrix();{
			glTranslatef(1,0,3.8);
			glRotatef(180,0,1,0);
			for(int i=0;i<3;i++){
				glRotatef(120,0,0,1);
				glPushMatrix();{
					glTranslatef(-0.5,0,0.5);
					glRotatef(45,0,1,0);
					drawNewCylinder(0.02,0.7);
				}glPopMatrix();
			}
		}glPopMatrix();

		glPushMatrix();{
			glTranslatef(1,0,2.9);
			glRotatef(60,0,0,1);
			for(int i=0;i<3;i++){
				glRotatef(120,0,0,1);
				glPushMatrix();{
					glTranslatef(-0.1,0,0.02);
					glRotatef(40,0,1,0);
					drawNewCylinder(0.01,0.15);
				}glPopMatrix();
			}
		}glPopMatrix();
	}glPopMatrix();
}
void drawDrumSet(){
	//toms
	glPushMatrix();
	{
		glRotatef(-30,1,0,0);
		drawDrums();
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(0,-1.5,0);
		glRotatef(30,1,0,0);
		drawDrums();
	}
	glPopMatrix();

	//bass drum
	glPushMatrix();
	{
		glTranslatef(-0.5,-0.8,2.45);
		glRotatef(105,0,1,0);
		glScalef(2,2,1);
		drawDrums();
	}
	glPopMatrix();

	glPushMatrix();{
		drawSupport();
	}
	glPopMatrix();
	//floor tom
	glPushMatrix();{
		glTranslatef(-0.8,-2.2,1.8);
		glRotatef(10,0,1,0);
		drawFloorTom();
	}
	glPopMatrix();
	//snare drum
	glPushMatrix();{
		glTranslatef(0,0.6,1.6);
		glRotatef(10,0,1,0);
		drawSnareDrum();
		drawSnareSuport();
	}glPopMatrix();
	glPushMatrix();{
		//ride cymbal
		glTranslatef(-0.1,-2.8,-0.6);
		glRotatef(25,0,0,1);
		drawRideCymbal();
	}glPopMatrix();

	glTranslatef(1,1.3,0.9);
	drawHiHat();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glTranslatef(0, 0, -6);

	glRotatef(angle2, 1.0, 0.0, 0.0);
	glRotatef(angle, 0.0, 1.0, 0.0);

	glScalef(zoom,zoom,zoom);

	switch (current_object) {
	case 0:
		color(25/255.0, 255/255.0, 255/255.0, 1.0f);
		drawSphere(1);
		break;
	case 1:
		// draw your second primitive object here
		color(255/255.0, 25/255.0, 255/255.0, 1.0f);
		drawCone(1,2);
		break;
	case 2:
		// draw your first composite object here
		drawShape();
		break;
	case 3:
		// draw your second composite object here
		glTranslatef(0.9,1,0);
		glRotatef(90,1,0,0);
		glScalef(0.7,0.7,0.7);
		glPushMatrix();{
			glRotatef(-90,0,0,1);
			drawDrumSet();
		}
		glPopMatrix();
		break;
	default:
		break;
	};
	glPopMatrix();
	glutSwapBuffers ();
}




void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
	case 'p':
	case 'P':
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		break;			
	case 'w':
	case 'W':
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		break;			
	case 'v':
	case 'V':
		glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
		break;			
	case 's':
	case 'S':
		m_Smooth = !m_Smooth;
		break;
	case 'h':
	case 'H':
		m_Highlight = !m_Highlight;
		break;

	case '1':
	case '2':
	case '3':
	case '4':
		current_object = key - '1';
		break;

	case 'Q':
	case 'q':
		exit(0);
		break;

	default:
		break;
	}

	glutPostRedisplay();
}



void
	mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) {
		mouseButton = button;
		moving = 1;
		startx = x;
		starty = y;
	}
	if (state == GLUT_UP) {
		mouseButton = button;
		moving = 0;
	}
}

void motion(int x, int y)
{
	if (moving) {
		if(mouseButton==GLUT_LEFT_BUTTON)
		{
			angle = angle + (x - startx);
			angle2 = angle2 + (y - starty);
		}
		else zoom += ((y-starty)*0.001);
		startx = x;
		starty = y;
		glutPostRedisplay();
	}

}

int main(int argc, char **argv)
{
	cout<<"CS3241 Lab 3"<< endl<< endl;

	cout << "1-4: Draw different objects"<<endl;
	cout << "S: Toggle Smooth Shading"<<endl;
	cout << "H: Toggle Highlight"<<endl;
	cout << "W: Draw Wireframe"<<endl;
	cout << "P: Draw Polygon"<<endl;
	cout << "V: Draw Vertices"<<endl;
	cout << "Q: Quit" <<endl<< endl;

	cout << "Left mouse click and drag: rotate the object"<<endl;
	cout << "Right mouse click and drag: zooming"<<endl;

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (50, 50);
	glutCreateWindow ("CS3241 Assignment 3");
	glClearColor (128/255.0,255/255.0,128/255.0, 1.0);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	setupLighting();
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST); 
	glDepthMask(GL_TRUE);

	glMatrixMode(GL_PROJECTION);
	gluPerspective( /* field of view in degree */ 40.0,
		/* aspect ratio */ 1.0,
		/* Z near */ 1.0, /* Z far */ 80.0);
	glMatrixMode(GL_MODELVIEW);
	glutMainLoop();

	return 0;
}
