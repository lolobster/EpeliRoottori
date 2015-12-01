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

Polygon::Polygon()
{

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

void Polygon::drawPolygon(int sides, float radius, float scale, GLfloat rotation, glm::vec2 position, glm::vec3 color)
{

	float theta = 2.0f * M_PI / float(sides);
	float tangentialFactor = tanf(theta);
	float radialFactor = cosf(theta);
	float x = radius * scale;
	float y = rotation;

	//glClear(GL_COLOR_BUFFER_BIT);
	//glColor3i(color.x, color.y, color.z);



	

	//glGenBuffers(1, &vbo);
	//glBindBuffer(GL_ARRAY_BUFFER, vao);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATUC_DRAW);

	//glDisable(GL_TEXTURE_2D);

	glBegin(GL_POLYGON);
	for (int i = 0; i < sides; i++)
	{
		glVertex2f(x + position.x, y + position.y);

		float ix = -y;
		float iy = x;

		x += ix * tangentialFactor;
		y += iy * tangentialFactor;

		x *= radialFactor;
		y *= radialFactor;
		
	
		glVertexAttrib3f(1, color.x, color.y, color.z);		
		//glColor3f(color.x, color.y, color.z);
	}
	glEnd();




}
