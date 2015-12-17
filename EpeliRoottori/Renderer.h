#ifndef RENDERER_H
#define RENDERER_H

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
#include <glm\gtx\rotate_vector.hpp>

#include "Camera.h"
#include "Shader.h"
#include "TextManager.h"
#include "Sprite.h"
#include "Polygon.h"


class Renderer
{
public:
	Renderer(glm::vec2 s);
	~Renderer();
	void Draw(Sprite sprite);
	void Draw(TextManager text);
	void Draw(Polygon polygon);

	Camera *camera;

protected:
	void FinishDrawing();

private:
	GLuint matrixID;
	Shader shader;
	GLuint spriteBuffer, spriteElements, textID, polygonBuffer, polygonElements;
	bool firstRender = true;
	int timer = 0;
};

#endif