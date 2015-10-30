#ifndef CAMERA_H
#define CAMERA_H
#define GLM_FORCE_RADIANS

// GLM transformaatioita varten
#include "glm\glm.hpp"
#include <glm/gtx/transform.hpp>
using namespace glm;

class Camera
{
public:
	Camera(vec3 camPos, float camRotate, float camScale);

	void setPosition(vec3 newPos, vec3 camPos);
	const vec3& getPosition();

	void setScale(float camScale);
	float getScale()const{ return camRotate; }

	void setRotation(float camRotate);
	float getRotation(){ return camRotate; }
	~Camera();

private:
	vec3 *camPos;
	float camRotate;
	float camScale;
	
};

#endif