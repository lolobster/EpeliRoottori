#include "Camera.h"


Camera::Camera()
{
	M;
	V;
	P;
	MVP;

	camPos;
	//initialize();
}


Camera::~Camera()
{
}

void Camera::initialize(void)
{
	vec3 x_axis(camX, 0.0, 0.0);
	vec3 y_axis(0.0, camY, 0.0);
	vec3 z_axis(0.0, 0.0, camZ);
	
	camPos = vec3(0.0f, 0.0f, 0.0f);
	
	camUp = y_axis;
	camRight = x_axis;
	vec3 camFront = -z_axis;
	P = lookAt(camPos, camPos + camFront, camUp);
	V = ortho(-1.0f, 1.0f, -1.0f * 800 / 1200, 1.0f * 800 / 1200);
	M;
	MVP;

}

void Camera::setPosition(GLfloat distance)
{
	M = glm::translate(vec3(distance, 0.0, 0.0));
}



void Camera::setScale(GLfloat camScale)
{

}

void Camera::setRotation(GLfloat angle)
{
	/*
	camX = sin(glfwGetTime()) * camRotate;
	camZ = sin(glfwGetTime()) * camRotate;
	
	MVP = lookAt(vec3(camX, 0.0f, camZ), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

	
	V = perspective(45.0f, (GLfloat)1200.0f / (GLfloat)800.0f, 0.1f, 100.0f);
	*/
	M = glm::rotate(M, angle, glm::vec3(1.0, 0.0, 1.0));
}
