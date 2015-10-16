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

	void loadTextures(const char *filename);
	void setTexture();
	// void deleteTexture();	// tarvihteeko jos destruktorissa
								// voi vapauttaa textuurit?

	~TextureManager();
private:
	const char *filename;

};

#endif