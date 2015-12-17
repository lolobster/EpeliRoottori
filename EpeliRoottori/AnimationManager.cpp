#include "AnimationManager.h"

#include "RapidXML\rapidxml.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

AnimationManager::AnimationManager()
{
	timer.start();
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
	currentFrame.index = 0;
	loopable = false;

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
	frameWidth = atoi(root->first_attribute("frameWidth")->value());
	frameHeight = atoi(root->first_attribute("frameHeight")->value());

	framesInARow = width / frameWidth; // Calculate the number of frames in one a row in the texture sheet.


	// Read the frames.
	for (rapidxml::xml_node<>* i = root->first_node("frame"); i; i = i->next_sibling())
	{

		Frame frame;
		frame.duration = static_cast<float>(atoi(i->first_attribute("duration")->value())) / 1000; // Read the duration of frame.

		// Onko animaatio x vai y suuntainen?

		index = atoi(i->first_attribute("id")->value());

		int horizontal = atoi(root->first_attribute("horizontal")->value());
		float texX = 0.0f;
		float texY = 0.0f;

		if (horizontal) {
			texX = static_cast<float>((index % framesInARow) * frameWidth);
			texY = static_cast<float>((index / framesInARow) * frameHeight);
		}
		else {
			texX = static_cast<float>((index / framesInARow) * frameHeight);
			texY = static_cast<float>((index % framesInARow) * frameWidth);
		}
		
		int loop = atoi(root->first_attribute("loopable")->value());
		
		if (loop == 1)
		{
			loopable = true;
		}

		// Calculate the texture coordinates of the frame.
		frame.texCoords.x = texX;
		frame.texCoords.y = texY;
		frame.texCoords.z = 0.0f;
		frame.texCoords.w = 0.0f;
		frame.index = index;
		index++;

		frames.push_back(frame);
	}
	// index now has the total amount of frames
	rows = (index + 1) / framesInARow;
	columns = framesInARow;
	
	// Clear data.
	content.clear();
	buffer.clear();
	document.clear();

	currentFrame = frames[0];
}

void AnimationManager::loadAnimation(const char *filename, glm::vec2 frameSize, float frameDuration)
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

	frameWidth = frameSize.x;
	frameHeight = frameSize.y;
	framesInARow = width / frameWidth;
	currentFrame.index = 0;
	loopable = true;

	for (int i = 0; i < width / frameWidth * height / frameHeight; i++)
	{
		Frame frame;
		frame.duration = frameDuration;

		float texX = 0.0f;
		float texY = 0.0f;

		texX = static_cast<float>((index % framesInARow) * frameWidth);
		texY = static_cast<float>((index / framesInARow) * frameHeight);

		frame.texCoords.x = texX;
		frame.texCoords.y = texY;
		frame.texCoords.z = 0.0f;
		frame.texCoords.w = 0.0f;
		frame.index = index;
		index++;

		frames.push_back(frame);
	}
	rows = (index + 1) / framesInARow;
	columns = framesInARow;

	currentFrame = frames[0];
}

void AnimationManager::updateAnimation()
{
	if (timer.getGlobalTime() - timeElapsed > currentFrame.duration)
	{
		if (rows > 1)
		{
			if (currentFrame.index < frames.size() && currentFrame.index + 1 < frames.size())
			{
				currentFrame = frames[currentFrame.index + 1];
			}

			else if (currentFrame.index = frames.size() + 1 && loopable)
			{
				currentFrame = frames[0];
			}
		}

		else
		{
			if (currentFrame.index < frames.size() && currentFrame.index + 1 < frames.size())
			{
				currentFrame = frames[currentFrame.index + 1];
			}

			//// Jostain syystä ei ota koppia kun framet on käyty läpi
			else if (currentFrame.index = frames.size() + 1 && loopable)
			{
				currentFrame = frames[0];
			}

			else
			{
				return;
			}
		}
		timeElapsed += timer.getGlobalTime() - timeElapsed;
	}
}

AnimationManager::~AnimationManager()
{
	frames.clear();
	delete anim;
}