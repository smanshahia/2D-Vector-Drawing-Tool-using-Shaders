#include "PolygonShape.h"



PolygonShape::PolygonShape()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
}


PolygonShape::~PolygonShape()
{
}

void PolygonShape::drawShape(bool EditMode)
{
	glPointSize(5);
	if (EditMode)
	{
		glBindVertexArray(VAO);
		glDrawArrays(GL_LINE_LOOP, 0, vertices.size() / 2);
		glDrawArrays(GL_POINTS, 0, vertices.size() / 2);
	}
	else
	{
		glBindVertexArray(VAO);
		glDrawArrays(GL_LINE_LOOP, 0, vertices.size() / 2);
	}
}


void PolygonShape::setVertices()
{
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_DYNAMIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void PolygonShape::setDrawColor(float r, float g, float b)
{

}

void PolygonShape::addHotspot(Point2 x)
{
	vertices.push_back(x.getX());
	vertices.push_back(x.getY());

	setVertices();
}

int PolygonShape::getHotspots(Point2 mouse)
{
	float x = mouse.getX();
	float y = mouse.getY();
	for (int i = 0; i < vertices.size(); i += 2)
	{
		if ((x < vertices[i] + 0.0075f && x > vertices[i] - 0.0075f) && (y < vertices[i + 1] + 0.0075f && y > vertices[i + 1] - 0.0075f))
		{
			return i;
		}
	}
	return -1;
}

void PolygonShape::setHotspot(Point2 pos, int i)
{
	vertices[i] = pos.getX();
	vertices[i + 1] = pos.getY();

	setVertices();
}