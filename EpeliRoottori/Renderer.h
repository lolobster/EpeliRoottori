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

#include "Camera.h"
#include "Shader.h"
#include "TextManager.h"
#include "Sprite.h"


class Renderer
{
public:
	Renderer(glm::vec2 s);
	~Renderer();
	void draw(Sprite sprite);
	void draw(TextManager text);

	Camera *cam;

private:
	GLuint matrixID;
	Shader shader;
	GLuint spriteBuffer, spriteElements, textID;;
	bool firstRender = true;
};

#endif