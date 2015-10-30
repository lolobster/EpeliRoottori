#include "TextManager.h"


TextManager::TextManager()
{

}

TextManager::~TextManager()
{

}

void TextManager::LoadFont(const char *filepath)
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
		std::cout << "The font file could not be read." << std::endl;
	}
}

void TextManager::SetCharacterSize(float size)
{
	error = FT_Set_Pixel_Sizes
		(
		face,    
		0,      
		size	
		);   

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
	// Tällä välin myös renderöintiä sekoitettu mukaan
	// Pitäisi periaatteessa ladata fonttitiedostosta stringin kirjaimen, piirtää sen ja jatkaa niin kauan kuin kirjaimia riittää stringissä
	// Tekee niistä bitmapin ja se pitäisi saada piirrettyä
	int penX = 0, penY = 0;
	FT_GlyphSlot  slot = face->glyph;
	FT_UInt glyphIndex;

	for (int i = 0; i < message.size(); i++)
	{
		error = FT_Load_Char(face, message[i], FT_LOAD_RENDER);

		glyphIndex = FT_Get_Char_Index(face, static_cast<int>(message[i]));

		//my_draw_bitmap(&slot->bitmap, penX + slot->bitmap_left, penY - slot->bitmap_top);

		penX += slot->advance.x >> 6;
	}

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