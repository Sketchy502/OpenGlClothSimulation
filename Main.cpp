#include <iostream>
#include <vector>

#include <glut.h>

#include "point.h"
#include "link.h"
#include "Cloth.h"

std::vector<Cloth> cloths(0);
float aspect;

void animate(void)
{
	for(unsigned int i = 0;i < cloths.size(); i++)
	{
		if(cloths[i].getInitState() == false)
			cloths[i].initialize();
	}

	for(unsigned int i = 0; i < cloths.size(); i++)
		cloths[i].animate();

	glutPostRedisplay();
}

void display(void)
{
	// Set bg colour and camera positon
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	//initialize cloths, not the best idea as checking every draw update
	for(unsigned int i = 0;i < cloths.size(); i++)
	{
		if(cloths[i].getInitState() == false)
			cloths[i].initialize();
	}

	//Draw cloths
	for(unsigned int i = 0; i < cloths.size(); i++)
		cloths[i].draw();

	// Draw boarder
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_LOOP);
		glVertex2d(-1.0,-1.0);
		glVertex2d(-1.0,1.0);
		glVertex2d(1.0,1.0);
		glVertex2d(1.0,-1.0);
	glEnd();

	glutSwapBuffers();
}

void idle(void)
{
	animate();
}

void keyPressed(unsigned char key, int x, int y)
{
	switch (key)
	{
	//escape key
	case 27:
		glutDestroyWindow(1);
		exit(0);
		break;
	default:
		break;
	}

}

void reshape(int width, int height)
{
	if( height == 0)
		height = 1;

	aspect = (float)width/(float)height;

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(width >= height)
		gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
	else
		gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);

	glMatrixMode(GL_MODELVIEW);
}

void mousePressed(int button, int state, int x, int y)
{
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	//Set window size as 2/3 screen size and locate centered
	glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH)*2/3, glutGet(GLUT_SCREEN_HEIGHT)*2/3);
	glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH)/6,glutGet(GLUT_SCREEN_HEIGHT)/6);

	//Set the window Title
	glutCreateWindow("OpenGL Cloth Physics - Ashley Eldridge");

	//Set GLUT functions
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);

	glutKeyboardFunc(keyPressed);
	glutMouseFunc(mousePressed);

	//Add a cloth
	cloths.push_back( Cloth(40,  -0.5f, 0.5f, 0.02f, 6.0f));

	glutMainLoop();

}