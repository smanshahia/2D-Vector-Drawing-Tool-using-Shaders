#pragma once
#include "Point2.h"
#include "BaseShape.h"

class LineShape: public BaseShape
{
private:
	Point2 a, b;
	float vertices[4];
public:
	LineShape(Point2 a, Point2 b);
	~LineShape();
	void BaseShape::drawShape(bool EditMode);
	int BaseShape::getHotspots(Point2 mouse);
	void setHotspot(Point2 pos, int num);
	void setVertices();
	void BaseShape::setDrawColor(float r, float g, float b);
	GLuint VAO, VBO;
};

