#ifndef CAMERA_H
#define CAMERA_H
#define GLEW_STATIC

// GLM transformaatioita varten
#include "glm\glm.hpp"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <GL\glew.h>

// GLFW
#include <GLFW/glfw3.h>

class Camera
{
public:
	Camera(glm::vec2 s);
	
	void initialize();
	
	glm::mat4 getViewMatrix(){
		MVP = M * V * P;
		return MVP; };

	void setPosition(GLfloat distance);
	
	void setScale(GLfloat camScale);
	//GLfloat getScale()const{ return camRotate; }

	void setRotation(GLfloat angle);
	//mat4 getRotation(){ return MVP; }

	
	


	~Camera();

private:
	glm::vec3 camPos;
	//vec3 camTarget = vec3(0.0f, 0.0f, 0.0f);
	//vec3 camDirection = normalize(camPos - camTarget);

	//vec3 up = vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 camRight;
	glm::vec3 camUp;
	glm::vec3 camFront;

	GLfloat camX = 1.0f;
	GLfloat camY = 1.0f;
	GLfloat camZ = 1.0f;

	glm::mat4 M; // translation
	glm::mat4 V; // projection
	glm::mat4 P; // target
	glm::mat4 MVP; // view

	GLfloat camRotate;
	GLfloat camScale;
	
	glm::vec2 size;
};

#endif