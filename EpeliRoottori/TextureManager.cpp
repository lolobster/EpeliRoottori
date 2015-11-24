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

GLuint TextureManager::texGLInit(GLuint textureID)  // lataa pixelidatan openGL:ään
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID); //everything we're about to do is about this texture
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &textures[0]);
	glGenerateMipmap(GL_TEXTURE_2D);

	return textureID;

	glBindTexture(GL_TEXTURE_2D, 0);
	//we COULD free the image vectors memory right about now. But we'll do it when there's a need to. At the beginning of the reloadtexture func, makes sure it happens when we need it to.
}