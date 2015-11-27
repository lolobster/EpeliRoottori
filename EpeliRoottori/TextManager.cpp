#include "TextManager.h"

TextManager::TextManager()
{

}

TextManager::~TextManager()
{
	FT_Done_FreeType(library);
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

	error = FT_Set_Char_Size(face, 6400 * characterSize, 6400 * characterSize, 300, 300);
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

void TextManager::SetPosition(glm::vec2 pos)
{
	position = pos;
}

void TextManager::SetColor(glm::vec3 colors)
{
	color = colors;
}

float TextManager::GetCharacterSize()
{
	return characterSize;
}

std::string TextManager::GetText()
{
	return text;
}

GLuint TextManager::turnToBitmap() // 
{
	int pen = 0;
	FT_GlyphSlot  slot = face->glyph;

	for (int i = 0; i < text.size(); i++)
	{
		error = FT_Load_Char(face, text[i], FT_LOAD_RENDER);


		pen += slot->advance.x >> 6;
	}

	GLuint textureID;
		
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, slot->bitmap.width, slot->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, slot->bitmap.buffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return textureID;
}

void TextManager::RenderText(Shader &s)
{
	float size = characterSize / 1000;
	float pen = 0;
	FT_GlyphSlot slot = face->glyph;

	for (int i = 0; i < text.size(); i++)
	{
		GLfloat textData[] =
		{
			//Positions											//Colors						//Texture Coords
			position.x + pen, position.y,						color.x, color.y, color.z,		0.0f, 0.0f,
			position.x + pen + size, position.y,				color.x, color.y, color.z,		1.0f, 0.0f,
			position.x + pen + size, position.y + size,			color.x, color.y, color.z,		1.0f, 1.0f,
			position.x + pen + size, position.y + size,			color.x, color.y, color.z,		1.0f, 1.0f,
			position.x + pen, position.y + size,				color.x, color.y, color.z,		0.0f, 1.0f,
			position.x + pen, position.y,						color.x, color.y, color.z,		0.0f, 0.0f,
		};

		pen += size;

		GLuint textBuffer;

		glGenBuffers(1, &textBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, textBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(textData), textData, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		GLuint elements[] =
		{
			0, 1, 2,
			3, 4, 5,
		};

		GLuint textElements;
		glGenBuffers(1, &textElements);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, textElements);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

		error = FT_Load_Char(face, text[i], FT_LOAD_RENDER);

		GLuint textID;

		glGenTextures(1, &textID);
		glBindTexture(GL_TEXTURE_2D, textID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, slot->bitmap.width, slot->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, slot->bitmap.buffer);
		glActiveTexture(GL_TEXTURE0);

		s.Use();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, textElements);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glDeleteTextures(1, &textID);
	}
}