#ifndef LINK_H
#define LINK_H

#include "point.h"

class link : Drawable
{
public:
	link(point &a, point &b, float length, float elasticity);
	link();
	~link(void);

	point* A;
	point* B;
	
    void solve();
	void draw();
	void animate();

	bool getRemove();
	
private:
	float _red;

	float _restingDistance;
	float _elasticity;
	
	bool _remove;
};

#endif