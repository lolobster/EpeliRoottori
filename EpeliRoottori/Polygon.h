#ifndef POLYGON_H
#define POLYGON_H


#define GLM_FORCE_RADIANS
#include <cstdio>
#include <cstdlib>
#include <iostream>

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

class Polygon
{
public:
	Polygon(int sides, float size);
	Polygon(float vertices[], int elements[]);
	~Polygon();

	void draw();
	void update();
private:
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	//int vertices[];
	//int elements[];
	float size;
	int sides;
};

#endif