#ifndef CAMERA_H
#define CAMERA_H
#define GLEW_STATIC

// GLM transformaatioita varten
#include "glm\glm.hpp"
#include <glm/gtx/transform.hpp>
#include <GL\glew.h>

// GLFW
#include <GLFW/glfw3.h>

using namespace glm;

class Camera
{
public:
	Camera();
	
	void initialize();
	
	mat4 getViewMatrix(){
		MVP = M * V * P;
		return MVP; };

	void setPosition(GLfloat distance);
	
	void setScale(GLfloat camScale);
	//GLfloat getScale()const{ return camRotate; }

	void setRotation(GLfloat angle);
	//mat4 getRotation(){ return MVP; }

	
	


	~Camera();

private:
	vec3 camPos;
	vec3 camTarget = vec3(0.0f, 0.0f, 0.0f);
	vec3 camDirection = normalize(camPos - camTarget);

	//vec3 up = vec3(0.0f, 1.0f, 0.0f);
	vec3 camRight;
	vec3 camUp;

	GLfloat camX = 1.0f;
	GLfloat camY = 1.0f;
	GLfloat camZ = 1.0f;

	mat4 M; // translation
	mat4 V; // projection
	mat4 P; // target
	mat4 MVP; // view

	GLfloat camRotate;
	GLfloat camScale;
	
};

#endif