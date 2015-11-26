#ifndef POLYGON_H
#define POLYGON_H


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
#include <iostream>
#include "Shader.h"


struct vertex{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textCoords;
};

class Polygon
{
public:
	std::vector<vertex> vertices;
	std::vector<GLuint> indices;
	//std::vector<Texture> textures;


	Polygon(int sides, float size);
	Polygon(float vertices[], int elements[]);
	~Polygon();

	void drawSquare(glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color);
	void update();
private:
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	//int vertices[];
	//int elements[];
	float size;
	int sides;
	Shader shader;
};

#endif