#include "Camera.h"


Camera::Camera(vec3 camPos, float camRotate, float camScale)
{
	camPos.x = 100;
	camPos.y = 100;
	camPos.z = 0;

	camRotate = 0;
	camScale = 1;
}


Camera::~Camera()
{
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