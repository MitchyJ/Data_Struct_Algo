#include "drawHouses.h"


void drawMyHouse(GLuint texSet[])
{
	//plot dimension
	//x: -4:4
	//y: 0:12
	//z: -4:4

	//bounding volume
	glPushMatrix();
	glTranslatef(0, 6, 0);
	glScalef(8, 12, 8);	
	glColor3f(1.0, 1.0, 1.0);
	glutWireCube(1);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
	//…
	glBindTexture(GL_TEXTURE_2D, texSet[29]);
	glBegin(GL_QUADS);
	glTexCoord2d(0,0);glVertex3f(-1.4, 0, -1);
	glTexCoord2d(0.5,0);glVertex3f(0, 0, -1);
	glTexCoord2d(0.5,1);glVertex3f(0, 3, -1);
	glTexCoord2d(0,1);glVertex3f(-1.4, 3, -1);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2d(0.5,0);glVertex3f(0, 0, -1);
	glTexCoord2d(1,0);glVertex3f(1, 0, 0);
	glTexCoord2d(1,1);glVertex3f(1, 3, 0);
	glTexCoord2d(0.5,1);glVertex3f(0, 3, -1);
	glEnd();
	//…
	glDisable(GL_TEXTURE_2D);


}