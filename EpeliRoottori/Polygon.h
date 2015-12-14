#ifndef POLYGON_H
#define POLYGON_H

#define _USE_MATH_DEFINES
#define GLM_FORCE_RADIANS
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

//omia
#include <iostream>
#include <math.h>

#include "Shader.h"
#include "TextureManager.h"


struct vertex{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textCoords;
};

class Polygon
{
public:
	//std::vector<vertex> vertices;
	//std::vector<GLuint> indices;
	//std::vector<Texture> textures;

	
	//Polygon(int sides);
	Polygon(int sides, float radius, float scale, GLfloat rotation, GLfloat x, GLfloat y, GLfloat cx, GLfloat cy, GLfloat cz);
	~Polygon();

	void drawSquare(glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color, std::string textureName, Shader *shader);
	void update();
	void drawPolygon(int sides, float radius, float scale, GLfloat rotation, glm::vec2 position, glm::vec3 color, Shader *shader);
	void drawPolygon(Shader *shader);
	//void drawPolygon(int sides, float radius, float scale, GLfloat rotation, glm::vec2 position, glm::vec3 color);
	void printData();

	GLfloat getX();
	GLfloat getY();
	GLfloat getTextCoordX();
	GLfloat getTextCoordY();
	GLfloat getColorX();
	GLfloat getColorY();
	GLfloat getColorZ();



	GLfloat* getData();
	GLuint* getIndices();
	int getSize();
	GLuint getGLuintSize();

private:
	//GLuint vao, vbo, ebo;
	
	GLfloat x, y, theta, angle,
		textCoordX, textCoordY,
		colorX, colorY, colorZ;

	GLfloat *data;
	GLuint *indices;

	int size;
	int counter;
};

#endif



/*
GLfloat spriteData[] =
{
// Paikat																									// Värit															// Tekstuurien koordinaatit
sprite.GetPosition().x, sprite.GetPosition().y,																sprite.GetColor().x, sprite.GetColor().y, sprite.GetColor().z,		0.0f, 0.0f,
sprite.GetPosition().x + sprite.GetGlobalBounds().x, sprite.GetPosition().y,								sprite.GetColor().x, sprite.GetColor().y, sprite.GetColor().z,		1.0f, 0.0f,
sprite.GetPosition().x + sprite.GetGlobalBounds().x, sprite.GetPosition().y + sprite.GetGlobalBounds().y,	sprite.GetColor().x, sprite.GetColor().y, sprite.GetColor().z,		1.0f, 1.0f,
sprite.GetPosition().x, srite.GetPosition().y + sprite.GetGlobalBounds().y,								sprite.GetColor().x, sprite.GetColor().y, sprite.GetColor().z,		0.0f, 1.0f,
};

glBindBuffer(GL_ARRAY_BUFFER, spriteBuffer);
glBufferData(GL_ARRAY_BUFFER, sizeof(spriteData), spriteData, GL_STATIC_DRAW);
glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)0);
glEnableVertexAttribArray(0);
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
glEnableVertexAttribArray(1);
glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
glEnableVertexAttribArray(2);

GLuint elements[] =
{
0, 1, 2,
0, 2, 3
};

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, spriteElements);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, sprite.GetTexture());

shader.Use();
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

glm::mat4 MVP = cam->getViewMatrix();
glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);


*/