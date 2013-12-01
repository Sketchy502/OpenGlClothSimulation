#include <stdlib.h>
#include <time.h>
#include <glut.h>
#include <math.h>

#include "point.h"

#define TIME_STEP 16

point::point(void)
{
}

int point::getLinkCount()
{
	return 1;
}

point::point(float a, float c, int ident)
{
	id = ident;
	x = a;
	y = c;
	lastX = a;
	lastY = c;
	accX = 0.0;
	accY = -0.0001;	;

	initx = a;
	inity = c;

	previousTime = 0;
	currentTime = 0;
	remainingTime = 0;

}


void point::draw()
{
	glBegin(GL_POINTS);
		glVertex2d(x, y);
	glEnd();
}

void point::animate()
{
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	int elapsedTime =  currentTime - previousTime;
	previousTime = currentTime;

	elapsedTime += remainingTime;

	int timesteps = floor(elapsedTime/(float)TIME_STEP);

	remainingTime = elapsedTime - timesteps * TIME_STEP;

	for(int i = 0; i < timesteps; i++)
	{		

		// Move the point using Verlet intergration
		float nx = (2*x - lastX + accX);
		float ny = (2*y - lastY + accY);

		float tmpx = lastX;
		float tmpy = lastY;

		lastX = x;
		lastY = y;

		x = nx;
		y = ny;

		// Keep points within the bounding area
		if(x <= -1.0)
		{
			lastX = -1.0 - (lastX - x);
			x = -1.0;
		}
		if(x >= 1.0)
		{
			lastX =  1.0 - 1.0*(lastX - x);
			x = 1.0;
		}
		if(y <= -1.0)
		{
			lastY =  -1.0 - 0.6*(lastY - y);
			y = -1.0;
		}
		if(y >= 1.0)
		{
			lastY =  y;
			y = 1.0;
		}

		//Lock the top left and top right points
		if(id == 0 || id == 39)
		{
			x = initx;
			y = inity;
			lastX = initx;
			lastY = inity;
		}
	
	}
}

point::~point(void)
{
	int a = 0;
}
