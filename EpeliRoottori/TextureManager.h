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

	void loadTextures(const char *filename, GLuint textureID);
	void setTexture();
	// void deleteTexture();	// tarvihteeko jos destruktorissa voi vapauttaa textuurit?
	GLuint texGLInit(GLuint textureID);

	~TextureManager();

private:
	const char *filename;
	std::vector<unsigned char> png;
	std::vector<unsigned char> textures;
	unsigned width, height;

};

#endif