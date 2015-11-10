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
	//mat4 getViewMatrix();

	void setPosition(vec3 newPos, vec3 camPos);
	
	void setScale(GLfloat camScale);
	GLfloat getScale()const{ return camRotate; }

	void setRotation(GLfloat camRotate);
	mat4 getRotation(){ return view; }
	


	~Camera();

private:
	vec3 camPos = vec3(0.0f, 0.0f, 0.0f);
	vec3 camTarget = vec3(0.0f, 0.0f, 0.0f);
	vec3 camDirection = normalize(camPos - camTarget);

	vec3 up = vec3(0.0f, 1.0f, 0.0f);
	vec3 camRight = normalize(cross(up, camDirection));
	vec3 camUp = cross(camTarget, camRight);

	GLfloat camX;
	GLfloat camY;
	GLfloat camZ;

	mat4 view;
	mat4 projection;

	GLfloat camRotate;
	GLfloat camScale;
	
};

#endif