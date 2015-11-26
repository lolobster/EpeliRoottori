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

void Polygon::drawSquare(glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color)
{
	this->shader.Use();
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(position, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f* size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

	model = glm::scale(model, glm::vec3(size, 1.0f));

	


}

