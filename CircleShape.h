#pragma once
#include "BaseShape.h"
#include "Point2.h"
#include <vector>
#include <math.h>

class CircleShape :public BaseShape
{
private:
	std::vector<float> vertices;
	Point2 center, edge;
	unsigned int seg;
public:
	GLuint VAO, VBO;
	CircleShape(Point2 center, Point2 edge, int seg);
	~CircleShape();
	void BaseShape::drawShape(bool EditMode);
	int BaseShape::getHotspots(Point2 mouse);
	void setHotspot(Point2 pos, int num);
	void setVertices();
	void BaseShape::setDrawColor(float r, float g, float b);
	void offsetSegment(short offset);
};

