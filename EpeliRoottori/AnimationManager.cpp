#include "AnimationManager.h"
#include <iostream>

AnimationManager::AnimationManager()
{
}


AnimationManager::~AnimationManager()
{
}

void AnimationManager::loadAnimation(const char *filename)
{
	lodepng::load_file(png, filename);
	unsigned error = lodepng::decode(animations, width, height, png);
	if (error) // lataus ei onnistu --> virheilmotus
	{
		std::cout << "PNG load failed " << error << ": " << lodepng_error_text(error) << std::endl;
	}

	glGenTextures(1, &animID);
	glBindTexture(GL_TEXTURE_2D, animID); //everything we're about to do is about this texture
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &animations[0]);
	glGenerateMipmap(GL_TEXTURE_2D);

	animations.clear();
	glBindTexture(GL_TEXTURE_2D, 0);
}