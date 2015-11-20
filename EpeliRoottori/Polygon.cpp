#include "Polygon.h"


Polygon::Polygon(float vertices[], int elements[])
{

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	//position
	glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 6* sizeof(GLfloat), (GLvoid*)0);


	//color


	glBindVertexArray(0);
}

Polygon::Polygon(int sides, float size)
{

}

Polygon::~Polygon()
{

}

void Polygon::update()
{

}

