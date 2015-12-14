#include "AnimationManager.h"
#include "Timer.h"
#include "RapidXML\rapidxml.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

AnimationManager::AnimationManager()
{

}


void AnimationManager::loadAnimation(const char *filename, const std::string& resourcePath)
{
	lodepng::load_file(anim_png, filename);
	unsigned error = lodepng::decode(animations, width, height, anim_png);
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
	
	//////////////////////////////////////////////////

	frameWidth = 0;
	frameHeight = 0;

	// Loads the animation data.
	rapidxml::xml_document<> document; // The animation data document.

	// Open the file, read the data to the buffer, close the file, create a string from the data and parse it.
	std::ifstream file(resourcePath);
	std::stringstream buffer;

	buffer << file.rdbuf();

	file.close();

	std::string content(buffer.str());
	document.parse<0>(&content[0]);

	rapidxml::xml_node<>* root = document.first_node(); // Get the root node of xml document.

	// Read frame width and height and load the texture sheet.
	frameWidth = atoi(root->first_attribute("width")->value());
	frameHeight = atoi(root->first_attribute("height")->value());
	//anim(animID, frameWidth, frameHeight);

	int framesInARow = width / frameWidth; // Calculate the number of frames in one a row in the texture sheet.

	// Read the frames.
	for (rapidxml::xml_node<>* i = root->first_node("frame"); i; i = i->next_sibling())
	{
		Frame frame;
		frame.duration = static_cast<float>(atoi(i->first_attribute("duration")->value())); // Read the duration of frame.

		// Calculate the texture coordinates of the frame.
		int index = atoi(i->first_attribute("id")->value());
		frame.texCoords.x = static_cast<float>((index % framesInARow) * frameWidth);
		frame.texCoords.y = static_cast<float>((index / framesInARow) * frameHeight);
		frame.texCoords.z = static_cast<float>(frameWidth);
		frame.texCoords.w = static_cast<float>(frameHeight);

		frames.push_back(frame);
	}

	// Clear data.
	content.clear();
	buffer.clear();
	document.clear();
}

void AnimationManager::updateAnimation()
{

	//Timer timer;
	//// Update only when timer is started and not paused.
	//if (!timer.isPaused() && timer.isStarted())
	//{
	//	// Compare local time to the duration of current frame.
	//	if (timer.getLocalTime() > anim->getFrame(currentFrame).duration)
	//	{
	//		if (currentFrame < loopStartFrame)
	//		{
	//			currentFrame = loopStartFrame;
	//		}

	//		// Advance current frame and check if we have reached the end of the animation.
	//		if (++currentFrame >= loopEndFrame || currentFrame >= anim->getNumberOfFrames())
	//		{
	//			stop(); // Stop the animation.

	//			// Continue if the animation is set to loop.
	//			if (loop)
	//			{
	//				start(); // Restarts the timer.
	//			}
	//		}
	//		else
	//		{
	//			start(); // Restarts the timer.
	//		}
	//	}
	//}
}

AnimationManager::~AnimationManager()
{
	frames.clear();
	delete anim;
}