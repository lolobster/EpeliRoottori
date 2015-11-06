#include "Camera.h"


Camera::Camera(float camRotate, float camScale)
{
	camRotate = 0;
	camScale = 1;

	//initialize();
}


Camera::~Camera()
{
}

void Camera::initialize(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glTranslatef(camPos.x, camPos.y, camPos.z);
	perspective(70.0f, 800.0f / 600.0f, 1.0f, 10000.0f);

	mat4 view;
	view = lookAt(vec3(0.0f, 0.0f, 3.0f),		// reight vector
		vec3(0.0f, 0.0f, 0.0f),		// up vector
		vec3(0.0f, 1.0f, 0.0f));		// direction vector

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

mat4 Camera::getViewMatrix()
{
	mat4 view;
	view = lookAt(vec3(0.0f, 0.0f, 3.0f),		// reight vector
				  vec3(0.0f, 0.0f, 0.0f),		// up vector
				  vec3(0.0f, 1.0f, 0.0f));		// direction vector

	return view;
}

void Camera::setPosition(vec3 newPos, vec3 camPos)
{
	camPos = newPos;
}



void Camera::setScale(GLfloat camScale)
{

}

void Camera::setRotation(GLfloat camRotate)
{
	GLfloat camX = sin(glfwGetTime()) * camRotate;
	
	view = lookAt(vec3(camX, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

	mat4 projection;
	projection = perspective(45.0f, (GLfloat)1200.0f / (GLfloat)800.0f, 0.1f, 100.0f);
}
