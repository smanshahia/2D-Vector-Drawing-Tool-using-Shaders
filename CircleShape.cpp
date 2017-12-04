#include "CircleShape.h"
#include <math.h>
#include <iostream>

using namespace std;

CircleShape::CircleShape(Point2 center, Point2 edge, int seg)
{
	this->center = center;
	this->edge = edge;
	this->seg = seg;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	setVertices();
}


CircleShape::~CircleShape()
{
}

void CircleShape::drawShape(bool EditMode)
{

	if (EditMode)
	{
		glPointSize(5);
		glBindVertexArray(VAO);
		glDrawArrays(GL_LINE_LOOP, 2, vertices.size() / 2 - 2);
		glDrawArrays(GL_POINTS, 0, 1);
		glDrawArrays(GL_POINTS, 2, 1);
	}
	else
	{
		glBindVertexArray(VAO);
		glDrawArrays(GL_LINE_LOOP, 2, vertices.size() / 2 - 2);
	}
}

void CircleShape::setVertices()
{
	vertices.clear();
	float inc = 2.0f*(22.0f / 7.0f) / seg;
	vertices.push_back(center.getX());
	vertices.push_back(center.getY());
	vertices.push_back(edge.getX());
	vertices.push_back(edge.getY());

	for (int i = 0; i < seg; i++)
	{
		float x = center.getX() + (sin(i * inc) * Point2::calcDist(center, edge));
		float y = center.getY() + (cos(i * inc) * Point2::calcDist(center, edge));
		vertices.push_back(x);
		vertices.push_back(y);
	}

	for (int i = 0; i < vertices.size(); i++)
	{
		cout << vertices[i] << endl;
	}

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_DYNAMIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void CircleShape::setHotspot(Point2 pos, int num)
{
	Point2 temp;
	if (num == 0)
	{
		temp.setX(pos.getX() - center.getX());
		temp.setY(pos.getY() - center.getY());
		center = pos;
		edge.setX(edge.getX() + temp.getX());
		edge.setY(edge.getY() + temp.getY());
	}
	else
		edge = pos;
	setVertices();
}

int CircleShape::getHotspots(Point2 mouse)
{
	if ((mouse.getX() < center.getX() + 0.0075f && mouse.getX() > center.getX() - 0.0075f) && (mouse.getY() < center.getY() + 0.0075f && mouse.getY() > center.getY() - 0.0075f))
	{
		return 0;
	}
	else if ((mouse.getX() < edge.getX() + 0.0075f && mouse.getX() > edge.getX() - 0.0075f) && (mouse.getY() < edge.getY() + 0.0075f && mouse.getY() > edge.getY() - 0.0075f))
	{
		return 1;
	}
	else
		return -1;
}

void CircleShape::setDrawColor(float r, float g, float b)
{

}

void CircleShape::offsetSegment(short offset)
{
	if (offset > 0)
	{
		if (seg < 40)
		{
			seg += offset;
		}
	}
	else
	{
		if (seg > 10)
		{
			seg += offset;
		}

	}
	setVertices();
}