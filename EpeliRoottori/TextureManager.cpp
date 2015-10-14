#include <iostream>
#include "TextureManager.h"
#include "Renderer.h"



struct TextureCache
{
	std::string filename;

	GLuint width;
	GLuint height;
};

TextureManager::TextureManager()
{

}


TextureManager::~TextureManager()
{

}

void TextureManager::loadTextures(unsigned char* image, int* width, int* height)
{
/// shaderiin flippi tekstuureille

	/*

	image = SOIL_load_image("Dickbutt.png", width, height, 0, SOIL_LOAD_RGB);
	

	if (*image == NULL) // lataus ei onnistu --> virheilmotus
	{
		std::cout << "ei vittu lataa: " << SOIL_last_result() << std::endl;
	}
	*/
}