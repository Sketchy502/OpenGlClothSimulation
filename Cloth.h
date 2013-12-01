#ifndef CLOTH_H
#define CLOTH_H

#include<vector>

#include "Drawable.h"
#include"point.h"
#include "link.h"

class Cloth : Drawable
{
public:
	Cloth(void);
	Cloth(int size, float initX, float initY, float defaultLength, float elasticity);

	~Cloth(void);

	void initialize();
	bool getInitState();
	void remove(float x, float y);

	void draw();
	void animate();

private:
	int _width, _height;
	float _initialX, _initialY;
	float _elasticity, _defaultLength;
	bool _initialized;

	std::vector<point> points;
	std::vector<link> links;
};

#endif

