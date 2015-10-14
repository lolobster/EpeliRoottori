#include "TextManager.h"


TextManager::TextManager()
{
	// Defaults to an empty message with white color and charactersize of 12

	text = "";
	color.resize(4,255);
	characterSize = 12.0f;
}

TextManager::~TextManager()
{

}

void TextManager::LoadFont(std::string filepath)
{
	std::ifstream file;
	file.open(filepath);
	if (file.is_open())
	{
		while (!file.eof())
		{

		}
	}
	else
	{
		std::cout << "The font file was not found." << std::endl;
	}
}

void TextManager::SetCharacterSize(float size)
{
	characterSize = size;
}

void TextManager::SetColor(int red, int blue, int green, int opacity)
{
	// Varmaan kirjoittelen vielä värille oman luokan
	// Sen avulla voi sitten muokata yhtä väriarvoa kerrallaan, yms.

	color[0] = red;
	color[1] = blue;
	color[2] = green;
	color[4] = opacity;
}

void TextManager::SetText(std::string message)
{
	text = message;
}

float TextManager::GetCharacterSize()
{
	return characterSize;
}

std::vector<int> TextManager::GetColor()
{
	return color;
}

std::string TextManager::GetText()
{
	return text;
}