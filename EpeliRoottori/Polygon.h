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
	Polygon(int sides, float radius, float scale, GLfloat rotation, GLfloat x, GLfloat y, GLfloat cx, GLfloat cy, GLfloat cz, const char* texturePath);
	~Polygon();

	void update();
	void drawPolygon(int sides, float radius, float scale, GLfloat rotation, glm::vec2 position, glm::vec3 color, Shader *shader);
	void printData();
	void Rotate(GLfloat degree);
	void DemoEffect(GLfloat degree);
	void Translate(glm::vec2 value);

	GLfloat getX();
	GLfloat getY();
	GLfloat getTextCoordX();
	GLfloat getTextCoordY();
	GLfloat getColorX();
	GLfloat getColorY();
	GLfloat getColorZ();
	GLuint getNumberOfElements();
	GLuint getNumberOfIndices();

	GLfloat* getData();
	GLuint* getIndices();
	int getSize();
	GLuint getGLuintSize();
	GLuint GetTexture();

private:
	GLuint vao, vbo, ebo, numberOfElements, numberOfIndices;
	
	GLfloat x, y, theta, angle, radius, scale,
		textCoordX, textCoordY,
		colorX, colorY, colorZ;

	GLfloat *data;
	GLuint *indices;

	TextureManager tex;

	int size, sides;
	int counter;
};

#endif