#pragma once
#include <math.h>

class Point2
{
public:
	Point2(float x, float y);
	Point2();
	float getX();
	float getY();
	void setX(float x);
	void setY(float y);
	~Point2();
	static float calcDist(Point2 x, Point2 y);
private:
	float x, y;
};

