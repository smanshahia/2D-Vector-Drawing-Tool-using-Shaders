#pragma once
#include "BaseShape.h"
#include "Point2.h"
#include <vector>
#include <iterator>

class PolygonShape : public BaseShape
{
private:
	std::vector<float> vertices;
public:
	PolygonShape();
	~PolygonShape();
	void addHotspot(Point2 x);
	void BaseShape::drawShape(bool EditMode);
	int BaseShape::getHotspots(Point2 mouse);
	void setHotspot(Point2 pos, int num);
	void setVertices();
	void BaseShape::setDrawColor(float r, float g, float b);
	GLuint VAO, VBO;
};

