#ifndef CAMERA_H
#define CAMERA_H
#define GLM_FORCE_RADIANS
#define GLEW_STATIC

// GLM transformaatioita varten
#include "glm\glm.hpp"
#include <glm/gtx/transform.hpp>
#include <GL\glew.h>

using namespace glm;

class Camera
{
public:
	Camera(float camRotate, float camScale);
	/*
	void initialize();
	mat4 getViewMatrix();

	void setPosition(vec3 newPos, vec3 camPos);
	const vec3& getPosition();

	void setScale(float camScale);
	float getScale()const{ return camRotate; }

	void setRotation(float camRotate);
	float getRotation(){ return camRotate; }
	*/
	~Camera();

private:
	vec3 *camPos;
	vec3 camTarget;
	vec3 camUp;
	mat4 view;

	float camRotate;
	float camScale;
	
};

#endif