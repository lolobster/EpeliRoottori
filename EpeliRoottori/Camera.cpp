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
	//V = perspective(radians(90.0f), (GLfloat) 1200/(GLfloat) 800, 0.1f, 1000.0f);

}

void Camera::setPosition(GLfloat distance)
{
	M = translate(M, vec3(distance));
}



void Camera::setScale(GLfloat camScale)
{
	M = scale(mat4(1.0f), vec3(camScale));
}

void Camera::setRotation(GLfloat angle)
{
	M = rotate(M, angle, vec3(0.0f ,0.0f, angle));
}
