#include "RectShape.h"



RectShape::RectShape()
{
	a = Point2(0, 0);
	b = Point2(0, 0);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	setVertices();	
}

RectShape::RectShape(Point2 a, Point2 b)
{
	this->a = a;
	this->b = b;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	setVertices();
}

void RectShape::setVertices()
{
	vertices[0] = a.getX();
	vertices[1] = a.getY();
	vertices[2] = b.getX();
	vertices[3] = a.getY();
	vertices[4] = b.getX();
	vertices[5] = b.getY();
	vertices[6] = a.getX();
	vertices[7] = b.getY();

	
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void RectShape::setHotspot(Point2 pos, int num)
{
	if (num == 0)
	{
		a = pos;
	}
	else
		b = pos;
	setVertices();
}


RectShape::~RectShape()
{
}

void RectShape::drawShape(bool EditMode)
{
	glPointSize(5);
	if (EditMode)
	{
		glBindVertexArray(VAO);
		glDrawArrays(GL_LINE_LOOP, 0, 4);
		glDrawArrays(GL_POINTS, 0, 1);
		glDrawArrays(GL_POINTS, 2, 1);
	}
	else
	{
		glBindVertexArray(VAO);
		glDrawArrays(GL_LINE_LOOP, 0, 4);
	}

}

int RectShape::getHotspots(Point2 mouse) 
{
	if ((mouse.getX() < a.getX() + 0.0075f && mouse.getX() > a.getX() - 0.0075f) && (mouse.getY() < a.getY() + 0.0075f && mouse.getY() > a.getY() - 0.0075f))
	{
		return 0;
	}
	else if ((mouse.getX() < b.getX() + 0.0075f && mouse.getX() > b.getX() - 0.0075f) && (mouse.getY() < b.getY() + 0.0075f && mouse.getY() > b.getY() - 0.0075f))
	{
		return 1;
	}
	else
		return -1;
}

void RectShape::setDrawColor(float r, float g, float b)
{

}
