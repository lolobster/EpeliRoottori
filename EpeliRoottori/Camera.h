#ifndef CAMERA_H
#define CAMERA_H

#include "Includes.h"

class Camera
{
public:
	Camera(glm::vec2 s);
	~Camera();
	
	void initialize();

	void SetPosition(glm::vec2 distance);
	void SetScale(GLfloat camScale);
	void SetRotation(GLfloat angle);
	void SetSize(glm::vec2 s);

	glm::mat4 GetViewMatrix();

private:
	glm::vec3 camPos, camRight, camUp, camFront;

	GLfloat camX = 1.0f, camY = 1.0f, camZ = 1.0f;

	glm::mat4 M; // translaatio
	glm::mat4 V; // projektio
	glm::mat4 P; // kohde
	glm::mat4 MVP; // näkymä

	GLfloat camRotate, camScale;
	
	glm::vec2 size;
};

#endif