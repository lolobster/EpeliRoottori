#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
public:
	Camera();
	virtual void update();
	void setPosition(float x, float y, float z);
	virtual ~Camera();

private:
	float x;
	float y;
	float z;
};

#endif