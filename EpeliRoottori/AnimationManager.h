#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW\glfw3.h>

//GLM
#include <glm\glm.hpp>

// lodePNG
#include "lodepng.h"

// RapidXML
#include "RapidXML\rapidxml.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

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
	
	void LoadAnimation(const char *filename, const std::string& resourcePath);
	void LoadAnimation(const char *filename, glm::vec2 frameSize, float frameDuration);
	void UpdateAnimation();

	size_t getNumberOfFrames() const
	{
		return frames.size();
	}

	const Frame& getFrame(size_t index) const
	{
		assert(index < frames.size());

		return frames[index];
	}
	Frame getCurrentFrame()
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
	Frame currentFrame;
	Timer timer;
	AnimationManager *anim;
	std::vector<Frame> frames;
	GLuint animID;

	unsigned int width = 0, height = 0, rows = 0, columns = 0;
	int frameWidth, frameHeight, framesInARow, index;
	bool loopable;
	const char *filename;
	float timeElapsed = 0;

	std::vector<unsigned char> anim_png, animations;
};

#endif