#include "Camera.h"


Camera::Camera(glm::vec2 s)
{
	size = s;
}


Camera::~Camera()
{
}

void Camera::initialize(void)
{
	glm::vec3 x_axis(camX, 0.0, 0.0);
	glm::vec3 y_axis(0.0, camY, 0.0);
	glm::vec3 z_axis(0.0, 0.0, camZ);
	
	camPos = glm::vec3(0.0f, 0.0f, 0.0f);
	camUp = y_axis;
	camRight = x_axis;
	camFront = -z_axis;

	P = lookAt(camPos, camPos + camFront, camUp);
	V = glm::ortho(0.f, size.x, size.y, 0.f);
}

void Camera::SetPosition(glm::vec2 distance)
{
	M = glm::translate(M, glm::vec3(distance.x, -distance.y, 0.0));
}

void Camera::SetScale(GLfloat camScale)
{
	M = glm::scale(glm::mat4(1.0f), glm::vec3(camScale));
}

void Camera::SetRotation(GLfloat angle)
{
	M = glm::rotate(M, angle, glm::vec3(0.0f, 0.0f, angle));
}

void Camera::SetSize(glm::vec2 s)
{
	size = s;
	V = glm::ortho(0.f, size.x, size.y, 0.f);
}

glm::mat4 Camera::GetViewMatrix()
{
	MVP = M * V * P;
	return MVP;
};