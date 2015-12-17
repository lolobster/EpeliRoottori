#pragma once
#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW\glfw3.h>

#include <glm\glm.hpp>

// lodePNG
#include "lodepng.h"

#include "Timer.h"

struct Frame
{
	float duration;
	glm::vec4 texCoords;
	GLuint index;
};


class AnimationManager
{
public:
	AnimationManager();
	~AnimationManager();
	
	void loadAnimation(const char *filename, const std::string& resourcePath);
	void loadAnimation(const char *filename, glm::vec2 frameSize, float frameDuration);

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
	Frame getCurrentFrame() // tälle joku päivityshässäkkä
	{
		return currentFrame;
	}

	int getFrameWidth() const
	{
		return frameWidth;
	}

	int getFrameHeight() const
	{
		return frameHeight;
	}

	int getColumn() const
	{
		return currentFrame.index % columns;
	}

	int getRow() const
	{
		return currentFrame.index / columns;
	}

	glm::vec4* getTexCoords(size_t index)
	{
		assert(index < frames.size());

		return &frames[index].texCoords;
	}

	GLuint getAnimationID(){ return animID; };


	unsigned int GetWidth() {
		return width;
	}
	unsigned int GetHeight() {
		return height;
	}
private:
	Timer timer;
	AnimationManager *anim;
	std::vector<Frame> frames;
	int frameWidth;
	int frameHeight;
	int framesInARow;
	Frame currentFrame;
	bool loopable;

	const char *filename;
	int index;
	GLuint animID;
	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int rows = 0;
	unsigned int columns = 0;

	float timeElapsed = 0;

	std::vector<unsigned char> anim_png;
	std::vector<unsigned char> animations;
};

#endif