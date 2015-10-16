#include "TextManager.h"


TextManager::TextManager()
{

}

TextManager::~TextManager()
{

}

void TextManager::LoadFont(const char *filepath)
{
	FT_Library library;
	FT_Face face;
	FT_Error error;

	error = FT_Init_FreeType(&library);
	if (error)
	{
		std::cout << "An error occurred during library initialization." << std::endl;
	}
	error = FT_New_Face(library, filepath, 0, &face);
	if (error == FT_Err_Unknown_File_Format)
	{
		std::cout << "The font file is unsupported." << std::endl;
	}
	else if (error)
	{
		std::cout << "The font file could not be read." << std::endl;
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