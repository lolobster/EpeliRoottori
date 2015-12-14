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
#include "AnimationManager.h"
#include "Sprite.h"
#include "Polygon.h"


class Renderer
{
public:
	Renderer(glm::vec2 s);
	~Renderer();
	void draw(Sprite sprite);
	void draw(TextManager text);
	void draw(Polygon polygon);
	void drawAnimation(AnimationManager anim);

	Camera *cam;

private:
	GLuint matrixID;
	Shader shader;
	GLuint spriteBuffer, spriteElements, textID, polygonBuffer, polygonElements;
	bool firstRender = true;
	int timer = 0;
};

#endif



/*
GLfloat spriteData[] =
{
// Paikat																									// Värit															// Tekstuurien koordinaatit
sprite.GetPosition().x, sprite.GetPosition().y,																sprite.GetColor().x, sprite.GetColor().y, sprite.GetColor().z,		0.0f, 0.0f,
sprite.GetPosition().x + sprite.GetGlobalBounds().x, sprite.GetPosition().y,								sprite.GetColor().x, sprite.GetColor().y, sprite.GetColor().z,		1.0f, 0.0f,
sprite.GetPosition().x + sprite.GetGlobalBounds().x, sprite.GetPosition().y + sprite.GetGlobalBounds().y,	sprite.GetColor().x, sprite.GetColor().y, sprite.GetColor().z,		1.0f, 1.0f,
sprite.GetPosition().x, sprite.GetPosition().y + sprite.GetGlobalBounds().y,								sprite.GetColor().x, sprite.GetColor().y, sprite.GetColor().z,		0.0f, 1.0f,
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