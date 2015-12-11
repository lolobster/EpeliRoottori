#include "TextManager.h"

TextManager::TextManager()
{

}

TextManager::~TextManager()
{
	for (int i = 0; i < idVector.size(); i++)
	{
		glDeleteTextures(1, &idVector[i]); // Poistaa tekstuurit
	}
}

void TextManager::LoadFont(const char *filepath) // Lataa fontin ja asettaa kirjasinkoon
{
	error = FT_Init_FreeType(&library);
	if (error)
	{
		std::cout << "An error occurred during library initialization." << std::endl;
	}
	error = FT_New_Face(library, filepath, 0, &face);
	if (error == FT_Err_Unknown_File_Format)
	{
		std::cout << "The font file is not supported." << std::endl;
	}
	else if (error)
	{
		std::cout << "The font file could not be read. Please, check the filepath." << std::endl;
	}

	error = FT_Set_Char_Size(face, 64 * characterSize, 64 * characterSize, 300, 300);
}

void TextManager::SetCharacterSize(float size)
{
	error = FT_Set_Char_Size(face, 64 * size, 64 * size, 300, 300);
	characterSize = size;
}

void TextManager::SetText(std::string message)
{
	text = message;
}

void TextManager::SetColor(glm::vec3 c)
{
	color = c;
}

void TextManager::SetPosition(glm::vec2 p)
{
	position = p;
}

void TextManager::SetScale(glm::vec2 s)
{
	scale = s;
}

void TextManager::SetRotation(float a)
{
	angle = a;
}

void TextManager::Move(glm::vec2 m)
{
	position += m;
}

void TextManager::Scale(glm::vec2 s)
{
	scale *= s;
}


void TextManager::Rotate(float a)
{
	angle += a;
}

float TextManager::GetCharacterSize()
{
	return characterSize;
}

std::string TextManager::GetText()
{
	return text;
}

glm::vec3 TextManager::GetColor()
{
	return color;
}

glm::vec2 TextManager::GetPosition()
{
	return position;
}

glm::vec2 TextManager::GetScale()
{
	return scale;
}

float TextManager::GetRotation()
{
	return angle;
}

FT_Face TextManager::GetFace()
{
	return face;
}

FT_Error TextManager::GetError()
{
	return error;
}

glm::vec2 TextManager::GetBounds()
{
	float penX = 0, penY = 0;
	if (error == false)
	{
		FT_GlyphSlot slot = face->glyph;
		for (int i = 0; i < text.size(); i++)
		{
			FT_Load_Char(face, text[i], FT_LOAD_RENDER);
			penX += slot->advance.x >> 6;
		}
	}
	return glm::vec2(penX, penY);
}

glm::vec2 TextManager::GetGlobalBounds()
{
	float penX = 0, penY = 0;
	if (error == false)
	{
		FT_GlyphSlot slot = face->glyph;
		for (int i = 0; i < text.size(); i++)
		{
			FT_Load_Char(face, text[i], FT_LOAD_RENDER);
			penX += slot->advance.x >> 6;
		}
	}
	return glm::vec2(penX * scale.x, penY * scale.y);
}