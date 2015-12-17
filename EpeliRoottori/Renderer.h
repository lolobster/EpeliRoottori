#ifndef RENDERER_H
#define RENDERER_H

#include "Includes.h"
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