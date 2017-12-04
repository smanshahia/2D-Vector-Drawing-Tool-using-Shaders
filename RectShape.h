#pragma once
#include "Point2.h"
#include "BaseShape.h"
#include <vector>

class RectShape: public BaseShape
{
private:
	Point2 a, b;
	float vertices[8];
public:
	RectShape();
	RectShape(Point2 a, Point2 b);
	~RectShape();
	void BaseShape::drawShape(bool EditMode);
	void setHotspot(Point2 pos, int num);
	void setVertices();
	int BaseShape::getHotspots(Point2 mouse);
	void BaseShape::setDrawColor(float r, float g, float b);
	GLuint VAO, VBO;
};

