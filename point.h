#ifndef POINT_H
#define POINT_H

#include <vector>

#include "Drawable.h"

class link;

class point : Drawable
{
public:

	point(void);
	point(float x, float y, int id);

	void draw();
	void animate();

	int getLinkCount();

	~point(void);

	float x, y;
	int id;

private:

	float initx, inity;

	float lastX, lastY;
	float accX, accY;
	
	int previousTime;
	int currentTime;
	int remainingTime;
};

#endif