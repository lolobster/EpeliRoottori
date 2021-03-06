#include "TextureManager.h"

TextureManager::TextureManager()
{

}


TextureManager::~TextureManager()
{

}

void TextureManager::LoadTextures(const char *filename)
{
	lodepng::load_file(texture_png, filename);
	unsigned error = lodepng::decode(textures, width, height, texture_png);
	if (error) // lataus ei onnistu --> virheilmotus
	{
		std::cout << "PNG load failed " << error << ": " << lodepng_error_text(error) << std::endl;
	}

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &textures[0]);
	glGenerateMipmap(GL_TEXTURE_2D);

	textures.clear();
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint TextureManager::GetID()
{
	return id;
}

unsigned TextureManager::GetWidth()
{
	return width;
}

unsigned TextureManager::GetHeight()
{
	return height;
}