#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// lodePNG
#include "lodepng.h"

class TextureManager
{
public:
	TextureManager();

	void setTexture();
	// void deleteTexture();	// tarvihteeko jos destruktorissa voi vapauttaa textuurit?
	void loadTextures(const char *filename);
	GLuint getID();
	unsigned getWidth();
	unsigned getHeight();

	~TextureManager();

private:
	const char *filename;
	std::vector<unsigned char> texture_png;
	std::vector<unsigned char> textures;
	unsigned int width = 0, height = 0;
	GLuint id = 0;

};

#endif