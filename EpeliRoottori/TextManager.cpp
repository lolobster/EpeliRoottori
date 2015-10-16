#include "TextManager.h"


TextManager::TextManager()
{

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

void TextManager::SetColor(float red, float blue, float green, float alpha)
{
	color.r = red;
	color.b = blue;
	color.g = green;
	color.a = alpha;
}

void TextManager::SetText(std::string message)
{
	text = message;
}

float TextManager::GetCharacterSize()
{
	return characterSize;
}

Color TextManager::GetColor()
{
	return color;
}

std::string TextManager::GetText()
{
	return text;
}