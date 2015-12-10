#include <iostream>
#include "TextureManager.h"
#include "Renderer.h"
#include "Shader.h"


TextureManager::TextureManager()
{

}


TextureManager::~TextureManager()
{

}

// ladataan PNG ensin muistiin ja dekoodataan siellä pixeleiksi
void TextureManager::loadTextures(const char* filename, GLuint textureID)
{
	// ladataan & dekoodataan
	lodepng::load_file(png, filename);
	unsigned error = lodepng::decode(textures, width, height, png);

	if (error) // lataus ei onnistu --> virheilmotus
	{
		std::cout << "PNG load failed " << error << ": " << lodepng_error_text(error) << std::endl;
	}
	// pixelit on vektorissa "texture"

	texGLInit(textureID);
	
}

void TextureManager::texGLInit(GLuint textureID)  // lataa pixelidatan openGL:ään
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID); //everything we're about to do is about this texture
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &textures[0]);
	glGenerateMipmap(GL_TEXTURE_2D);

	textures.clear();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureManager::loadTextures(const char *filename)
{
	lodepng::load_file(png, filename);
	unsigned error = lodepng::decode(textures, width, height, png);
	if (error) // lataus ei onnistu --> virheilmotus
	{
		std::cout << "PNG load failed " << error << ": " << lodepng_error_text(error) << std::endl;
	}

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id); //everything we're about to do is about this texture
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &textures[0]);
	glGenerateMipmap(GL_TEXTURE_2D);

	textures.clear();
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint TextureManager::getID()
{
	return id;
}

unsigned TextureManager::getWidth()
{
	return width;
}

unsigned TextureManager::getHeight()
{
	return height;
}