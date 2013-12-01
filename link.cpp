#include "link.h"
#include "glut.h"
#include <math.h>
#include <algorithm>

link::link()
{

}

link::link(point &a, point &b, float length, float elasticity)
{
	A = &a;
	B = &b;

	_restingDistance = length;
	_elasticity = elasticity;
	_red = 1.0f;

	_remove = false;
}

bool link::getRemove()
{
	return _remove;
}

void link::draw()
{
	glColor3f(1.0f, _red, _red);
	glBegin(GL_LINE_LOOP);
		glVertex2d(A->x,A->y);
		glVertex2d(B->x,B->y);
	glEnd();
}

void link::animate()
{}

void link::solve()
{
	float diffX = A->x - B->x;
	float diffY = A->y - B->y;
	float d = sqrt(diffX * diffX + diffY * diffY);

	if(d > _elasticity * _restingDistance)
	{
		_remove = true;
		return;
	}

	float difference = (_restingDistance - d) / d;

	_red =std::min(1.0 - ((d - _restingDistance) / d), 1.0);

	float translateX = diffX * 0.4f * difference;
	float translateY = diffY * 0.4f * difference;

	A->x += translateX;
	A->y += translateY;

	B->x -= translateX;
	B->y -= translateY;
	
}


link::~link(void)
{
}
