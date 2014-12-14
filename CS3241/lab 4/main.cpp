// CS3241Lab1.cpp : Defines the entry point for the console application.
//#include <cmath>
#include "math.h"
#include <iostream>
#include <fstream>
#include "GL\glut.h"

#define MAXPTNO 1000
#define NLINESEGMENT 32
#define NOBJECTONCURVE 8
#define PI 3.14159

using namespace std;
std::string text1,text2,text3,text4,text5;
// Global variables that you can use
struct Point {
	int x,y;
};

// Storage of control points
int nPt = 0;
Point ptList[MAXPTNO];


// Display options
bool displayControlPoints = true;
bool displayControlLines = true;
bool displayTangentVectors = false;
bool displayObjects = false;
bool C1Continuity = false;
bool displayDragon = false;
bool displayBallerina=false;
//for text display 
void drawText(const char *text,int length , int x, int y){
	glMatrixMode(GL_PROJECTION);
	double *matrix= new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX,matrix);
	glLoadIdentity();
	glOrtho(0,800,0,600,-5,5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x,y);
	for(int i=0;i<length;i++){
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,(int)text[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}
void drawRightArrow()
{
	glColor3f(0,1,0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0,0);
	glVertex2f(100,0);
	glVertex2f(95,5);
	glVertex2f(100,0);
	glVertex2f(95,-5);
	glEnd();
}

void drawThorn(){
	glColor3f(1,0,0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0,-20);
	glVertex2f(-10,0);
	glVertex2f(10,0);
	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	int count=4;

	if(displayTangentVectors){
		glColor3f(1,0,1);
		text1 ="Displaying tangent lines!";
		drawText(text1.data(),text1.size(),300,70);
	}
	else
		text1="";
	if(displayObjects){
		glColor3f(1,0,1);
		text2 ="We are the beautiful objects!";
		drawText(text2.data(),text2.size(),300,50);
	}
	if(C1Continuity){
		glColor3f(1,0,1);
		text3 ="I am a continuos curve!";
		drawText(text3.data(),text3.size(),300,30);
	}
	if(displayDragon){
		glColor3f(1,0,1);
		text4 ="I am a fiery dragon!";
		drawText(text4.data(),text4.size(),300,10);

	}
	if(displayBallerina){
		glColor3f(1,0,1);
		text5 ="Always dance to your own rhythm...";
		drawText(text5.data(),text5.size(),300,90);

	}

	if(displayControlPoints)
	{

		glPointSize(5);
		glBegin(GL_POINTS);
		for(int i=0;i<nPt; i++)
		{
			if(C1Continuity && i==count){ 
				glColor3f(1,0,0);
				glVertex2d(2*ptList[i-1].x-ptList[i-2].x,2*ptList[i-1].y-ptList[i-2].y);
				glColor3f(0.5,0.5,0.5);
				glVertex2d(ptList[i].x,ptList[i].y);
				count+=3;
			}
			else{
				glColor3f(0,0,0);
				glVertex2d(ptList[i].x,ptList[i].y);
			}
		}
		glEnd();
		glPointSize(1);

	}

	count=4;
	if(displayControlLines){
		glColor3f(0,0,1);
		glBegin(GL_LINE_STRIP);
		for(int i=0;i<nPt;i++){

			if(C1Continuity && i==count){

				glVertex2d(2*ptList[i-1].x-ptList[i-2].x,2*ptList[i-1].y-ptList[i-2].y);
				count+=3;
			}
			else{
				double x1=ptList[i].x;
				double y1=ptList[i].y;
				glVertex2d(x1,y1);
			}
		}
		glEnd();
	}

	count=1;
	if(displayTangentVectors||displayObjects){
		double xNew,yNew;
		double xtan=0,ytan=0;
		float dx=0,dy=0,angle=0;;
		for(int i=0;i+3<nPt;i+=3){

			if(i>=3 && C1Continuity){
				xNew=2*ptList[i].x-ptList[i-1].x;
				yNew=2*ptList[i].y-ptList[i-1].y;
			}
			else{
				xNew=ptList[count].x;
				yNew=ptList[count].y;
			}
			for(double t=0;t<=1;t=t+1.0/NOBJECTONCURVE)
			{
				glPushMatrix();
				xtan=pow(1-t,3)*ptList[i].x+3*pow(1-t,2)*t*xNew+3*(1-t)*t*t*ptList[i+2].x+pow(t,3)*ptList[i+3].x;
				ytan=pow(1-t,3)*ptList[i].y+3*pow(1-t,2)*t*yNew+3*(1-t)*t*t*ptList[i+2].y+pow(t,3)*ptList[i+3].y;

				dx=-3*pow(1-t,2)*(ptList[i].x)+3*pow(1-t,2)*ptList[i+1].x-(6*(1-t)*t*(ptList[i+1].x))-(3*pow(t,2)*(ptList[i+2].x))+(6*t*(1-t)*ptList[i+2].x+3*pow(t,2)*ptList[i+3].x);
				dy=-3*pow(1-t,2)*(ptList[i].y)+3*pow(1-t,2)*ptList[i+1].y-(6*(1-t)*t*(ptList[i+1].y))-(3*pow(t,2)*(ptList[i+2].y))+(6*t*(1-t)*ptList[i+2].y+3*pow(t,2)*ptList[i+3].y);

				//dP(t) / dt =  -3(1-t)^2 * P0 + 3(1-t)^2 * P1 - 6t(1-t) * P1 - 3t^2 * P2 + 6t(1-t) * P2 + 3t^2 * P3

				angle=((180.0/PI)*atan(dy/dx));
				if(dx<0){
					glPushMatrix();
					glTranslatef(xtan,ytan,0);
					glRotatef(angle+180.0,0,0,1);
					if(displayTangentVectors)
						drawRightArrow();
					if(displayObjects)
						drawThorn();
					glPopMatrix();
				}
				else{

					glPushMatrix();
					glTranslatef(xtan,ytan,0);
					glRotatef(angle,0,0,1);
					if(displayTangentVectors)
						drawRightArrow();
					if(displayObjects)
						drawThorn();
					glPopMatrix();

				}

				glPopMatrix();
			}
			count+=3;
		}
	}


	//drawing bezier curve using the parametric eq p(t)
	if(!C1Continuity)
	{
		for(int i=0;i+3<nPt;i+=3){
			glColor3f(1,0,0);
			glBegin(GL_LINE_STRIP);
			for(double t=0;t<=1;t=t+1.0/NLINESEGMENT)
			{
				double x=pow(1-t,3)*ptList[i].x+3*pow(1-t,2)*t*ptList[i+1].x+3*(1-t)*t*t*ptList[i+2].x+pow(t,3)*ptList[i+3].x;
				double y=pow(1-t,3)*ptList[i].y+3*pow(1-t,2)*t*ptList[i+1].y+3*(1-t)*t*t*ptList[i+2].y+pow(t,3)*ptList[i+3].y;
				glVertex2f(x,y);
			}
			glEnd();
		}
	}
	if(C1Continuity){

		double x_2=ptList[1].x;
		double y_2=ptList[1].y;
		glBegin(GL_LINE_STRIP);
		for(int i=0;i+3<nPt;i+=3){

			if(i>=3){
				x_2=2*ptList[i].x-ptList[i-1].x;
				y_2=2*ptList[i].y-ptList[i-1].y;
			}
			glColor3f(0,1,0);
			for(double t=0;t<=1;t=t+1.0/NLINESEGMENT)
			{
				double x=pow(1-t,3)*ptList[i].x+3*pow(1-t,2)*t*x_2+3*(1-t)*t*t*ptList[i+2].x+pow(t,3)*ptList[i+3].x;
				double y=pow(1-t,3)*ptList[i].y+3*pow(1-t,2)*t*y_2+3*(1-t)*t*t*ptList[i+2].y+pow(t,3)*ptList[i+3].y;
				glVertex2f(x,y);
			}


		}
		glEnd();
	}

	glPopMatrix();
	glutSwapBuffers ();
}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,w,h,0);  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}



void init(void)
{
	glClearColor (1.0,1.0,1.0, 1.0);
}

void readFile()
{

	std::ifstream file;
	file.open("savefile.txt");
	file >> nPt;

	if(nPt>MAXPTNO)
	{
		cout << "Error: File contains more than the maximum number of points." << endl;
		nPt = MAXPTNO;
	}

	for(int i=0;i<nPt;i++)
	{
		file >> ptList[i].x;
		file >> ptList[i].y;
	}
	file.close();// is not necessary because the destructor closes the open file by default
}

void readFile2()
{

	std::ifstream file;
	file.open("savefile2.txt");
	file >> nPt;

	if(nPt>MAXPTNO)
	{
		cout << "Error: File contains more than the maximum number of points." << endl;
		nPt = MAXPTNO;
	}

	for(int i=0;i<nPt;i++)
	{
		file >> ptList[i].x;
		file >> ptList[i].y;
	}
	file.close();// is not necessary because the destructor closes the open file by default
}

void writeFile()
{
	std::ofstream file;
	file.open("savefile.txt");
	file << nPt << endl;

	for(int i=0;i<nPt;i++)
	{
		file << ptList[i].x << " ";
		file << ptList[i].y << endl;
	}
	file.close();// is not necessary because the destructor closes the open file by default
}

void writeFile2()
{
	std::ofstream file;
	file.open("savefile2.txt");
	file << nPt << endl;

	for(int i=0;i<nPt;i++)
	{
		file << ptList[i].x << " ";
		file << ptList[i].y << endl;
	}
	file.close();// is not necessary because the destructor closes the open file by default
}



void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
	case 'r':
	case 'R':
		readFile();
		displayDragon=!displayDragon;
		break;

	case 'w':
	case 'W':
		writeFile();
		break;

	case 'T':
	case 't':
		displayTangentVectors = !displayTangentVectors;
		break;

	case 'o':
	case 'O':
		displayObjects = !displayObjects;
		break;

	case 'p':
	case 'P':
		displayControlPoints = !displayControlPoints;
		break;

	case 'L':
	case 'l':
		displayControlLines = !displayControlLines;
		break;

	case 'C':
	case 'c':
		C1Continuity = !C1Continuity;
		break;

	case 'e':
	case 'E':
		// Do something to erase all the control points added
		nPt=0;
		break;
	case 's':
	case 'S':
		writeFile2();
		break;
	case 'b':
	case'B':
		displayBallerina=!displayBallerina;
		readFile2();
		break;
	case 'z':
	case'Z':
		//to undo
		if(nPt>0)
			nPt-=1;
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



void mouse(int button, int state, int x, int y)
{
	/*button: GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, or GLUT_RIGHT_BUTTON */
	/*state: GLUT_UP or GLUT_DOWN */
	enum
	{
		MOUSE_LEFT_BUTTON = 0,
		MOUSE_MIDDLE_BUTTON = 1,
		MOUSE_RIGHT_BUTTON = 2,
		MOUSE_SCROLL_UP = 3,
		MOUSE_SCROLL_DOWN = 4
	};
	if((button == MOUSE_LEFT_BUTTON)&&(state == GLUT_UP))
	{
		if(nPt==MAXPTNO)
		{
			cout << "Error: Exceeded the maximum number of points." << endl;
			return;
		}
		ptList[nPt].x=x;
		ptList[nPt].y=y;
		nPt++;
	}
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	cout<<"CS3241 Lab 4"<< endl<< endl;
	cout << "Left mouse click: Add a control point"<<endl;
	cout << "Q: Quit" <<endl;
	cout << "P: Toggle displaying control points" <<endl;
	cout << "L: Toggle displaying control lines" <<endl;
	cout << "E: Erase all points (Clear)" << endl;
	cout << "C: Toggle C1 continuity" <<endl;	
	cout << "T: Toggle displaying tangent vectors" <<endl;
	cout << "O: Toggle displaying objects" <<endl;
	cout << "R: Read in control points from \"savefile.txt\"" <<endl;
	cout << "W: Write control points to \"savefile.txt\"" <<endl;
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (50, 50);
	glutCreateWindow ("CS3241 Assignment 4");
	init ();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}
