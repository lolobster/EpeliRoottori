#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>


class TextureManager
{
public:
	TextureManager();

	void loadTextures(unsigned char *image, int *width, int *height);
	void setTexture();
	// void deleteTexture();	// tarvihteeko jos destruktorissa
								// voi vapauttaa textuurit?

	~TextureManager();
private:
	unsigned char *image;
	int *width;
	int *height;
};

#endif