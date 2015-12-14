#pragma once
#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// lodePNG
#include "lodepng.h"

#include <GLFW\glfw3.h>

#include <glm\glm.hpp>

struct Frame
{
	float duration;
	glm::vec4 texCoords;
};


class AnimationManager
{
public:
	AnimationManager();
	~AnimationManager();
	
	void loadAnimation(const char *filename, const std::string& resourcePath);
	void updateAnimation();

	size_t getNumberOfFrames() const
	{
		return frames.size();
	}

	const Frame& getFrame(size_t index) const
	{
		assert(index < frames.size());

		return frames[index];
	}

	int getFrameWidth() const
	{
		return frameWidth;
	}

	int getFrameHeight() const
	{
		return frameHeight;
	}

	glm::vec4* getTexCoords(size_t index)
	{
		assert(index < frames.size());

		return &frames[index].texCoords;
	}

	GLuint getAnimationID(){ return animID; };

private:
	AnimationManager *anim;
	std::vector<Frame> frames;
	int frameWidth;
	int frameHeight;
	int currentFrame;

	const char *filename;
	GLuint animID;
	unsigned int width = 0;
	unsigned int height = 0;

	std::vector<unsigned char> anim_png;
	std::vector<unsigned char> animations;
};

#endif