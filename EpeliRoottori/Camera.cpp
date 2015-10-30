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
/*
void Camera::initialize(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glTranslatef(camPos.x, camPos.y, camPos.z);
	gluPerspective(70.0f, 800.0f / 600.0f, 1.0f, 10000.0f);
	gluLookAt(0.0f, 6000.0f, 0.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 1.0f, 0.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

mat4 Camera::getViewMatrix()
{

	gluLookAt(*camPos, *camPos + target, up);

	return view;
}

void Camera::setPosition(vec3 newPos, vec3 camPos)
{
	camPos = newPos;
}

const vec3& Camera::getPosition()
{
	return *camPos;
}

void Camera::setScale(float camScale)
{

}

void Camera::setRotation(float camRotate)
{

}
*/