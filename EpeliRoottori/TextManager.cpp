#include "TextManager.h"

// Pit‰isi periaatteessa toimia jotenkin t‰ll‰ v‰lin
// Saattaa olla, ett‰ k‰y kaikki stringin kirjaimet l‰pi mutta j‰tt‰‰ vain viimeisen muistiin
// Jatkan eteenp‰in, kun tekstuurien lataus onnistuu

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

void TextManager::SetText(std::string message)
{
	text = message;
}

float TextManager::GetCharacterSize()
{
	return characterSize;
}

std::string TextManager::GetText()
{
	return text;
}

GLuint TextManager::turnToBitmap()
{
	int penX = 0, penY = 0;
	FT_GlyphSlot  slot = face->glyph;
	FT_UInt glyphIndex;

	for (int i = 0; i < text.size(); i++)
	{
		error = FT_Load_Char(face, text[i], FT_LOAD_RENDER);

		glyphIndex = FT_Get_Char_Index(face, static_cast<int>(text[i]));

		FT_Bitmap bmp;
		bmp = slot->bitmap, penX + slot->bitmap_left, penY - slot->bitmap_top;

		penX += slot->advance.x >> 6;
	}

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, bmp.width, bmp.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, &bmp.buffer);

	return textureID;
}