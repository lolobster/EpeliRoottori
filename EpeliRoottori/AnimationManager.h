#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// lodePNG
#include "lodepng.h"

class AnimationManager
{
public:
	AnimationManager();

	void loadAnimation(const char *filename);
	GLuint getAnimID(){ return animID; };

	~AnimationManager();

private:
	const char *filename;
	GLuint animID;
	unsigned int width = 0;
	unsigned int height = 0;

	std::vector<unsigned char> png;
	std::vector<unsigned char> animations;
};

#endif