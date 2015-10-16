#include <iostream>
#include "TextureManager.h"
#include "Renderer.h"


/*
struct TextureCache
{
	std::string filename;

	GLuint width;
	GLuint height;
};
*/

TextureManager::TextureManager()
{

}


TextureManager::~TextureManager()
{

}

// ladataan PNG ensin muistiin ja dekoodataan siellä pixeleiksi
void TextureManager::loadTextures(const char* filename)
{
	std::vector<unsigned char> png;
	std::vector<unsigned char> texture;		
	unsigned width, height;

	// ladataan & dekoodataan
	lodepng::load_file(png, filename);
	unsigned error = lodepng::decode(texture, width, height, png);

	if (error) // lataus ei onnistu --> virheilmotus
	{
		std::cout << "ei vittu lataa " << error << ": " << lodepng_error_text(error) << std::endl;
	}

	// pixelit on vektorissa "texture"
}