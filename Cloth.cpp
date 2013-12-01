#include "Cloth.h"


Cloth::Cloth(int size, float initX, float initY, float defaultLength, float elasticity)
{
	_width = size;
	_height = size;

	_initialX = initX;
	_initialY = initY;

	_defaultLength = defaultLength;
	_elasticity = elasticity;
	_initialized = false;
}

Cloth::Cloth(void)
{
}


Cloth::~Cloth(void)
{
}

void Cloth::remove(float x, float y)
{
	float err = 0.005f;
	for(unsigned int i = 0; i < points.size(); i++)
	{
	}
}

void Cloth::initialize()
{
	for(int i = 0; i < _width; i++)
	{
		for(int j = 0; j < _height; j++)
		{
			float xPos = i*_defaultLength + _initialX;
			float yPos = -j*_defaultLength + _initialY;

			int id = i + _width * j;

			points.push_back(point(xPos, yPos, id));
		}
	}

	for (int i =0; i < _width; i++)
	{
		for(int j = 0; j < _height; j++)
		{
			if( j != 0)
				links.push_back(link(points[j + i*_width], points[j + i*_width - 1], _defaultLength, _elasticity));
			if( i != 0)
				links.push_back(link(points[j + i*_width], points[j + i*_width - _height], _defaultLength, _elasticity));
		}
	}

	_initialized = true;
}

bool Cloth::getInitState()
{
	return _initialized;
}

void Cloth::draw()
{
	//Draw links
	for(unsigned int i = 0; i < points.size(); i++)
		points[i].draw();

	for(unsigned int i = 0; i < links.size(); i++)
		links[i].draw();
}

void Cloth::animate()
{

	for(unsigned int i = 0; i < links.size(); i++)
	{
		if(links[i].getRemove() == true)
		{
			links.erase(links.begin()+i);	
			continue;
		}
		links[i].solve();
	}


	for(unsigned int i = 0; i < points.size(); i++)
	{
		if(points[i].getLinkCount() == 0)
		{
			points.erase(points.begin()+i);
			continue;
		}
		points[i].animate();
	}
}