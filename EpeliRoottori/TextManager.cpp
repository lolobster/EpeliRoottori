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

	FT_Done_FreeType(library); // Vapauttaa tesktikirjaston
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

void TextManager::SetColor(glm::vec3 colors)
{
	color = colors;
}

void TextManager::SetPosition(glm::vec2 pos)
{
	position = pos;
}

void TextManager::SetScale(glm::vec2 newScale)
{
	scale = newScale;
}

void TextManager::SetRotation(float rot)
{
	angle = rot;
}

void TextManager::Move(glm::vec2 movement)
{
	position += movement;
}

void TextManager::Scale(glm::vec2 scaleFactor)
{
	scale *= scaleFactor;
}


void TextManager::Rotate(float rot)
{
	angle += rot;
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

void TextManager::RenderText(Shader &s)
{
	if (error == false) // Tarkastaa onko erroreita ennen kuin yrittää renderöidä tekstin välttääkseen ohjelman kaatumisen
	{
		if (firstRender == true) // Tarkastaa tapahtuuko renderöinti ensimmäistä kertaa ja lataa kirjaintekstuurit, jos näin on
		{
			FT_GlyphSlot slot = face->glyph;
			
			for (int i = 0; i < text.size(); i++)
			{
				error = FT_Load_Char(face, text[i], FT_LOAD_RENDER);

				if (i == 0)
				{
					levelingFix == slot->metrics.vertBearingY / 64; // Käytetään tekstin tasaamiseen
				}

				GLubyte* expanded_data = new GLubyte[2 * slot->bitmap.width * slot->bitmap.rows];
				for (int j = 0; j < slot->bitmap.rows; j++)
				{
					for (int k = 0; k < slot->bitmap.width; k++)
					{
						expanded_data[2 * (k + j * slot->bitmap.width)] = 255;
						expanded_data[2 * (k + j * slot->bitmap.width) + 1] = (k >= slot->bitmap.width || j >= slot->bitmap.rows) ? 0 : slot->bitmap.buffer[k + slot->bitmap.width * j];
					}
				}
				GLuint textID;
				glGenTextures(1, &textID);
				glBindTexture(GL_TEXTURE_2D, textID);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, slot->bitmap.width, slot->bitmap.rows, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, expanded_data);
				glActiveTexture(GL_TEXTURE0);
				idVector.push_back(textID);
				delete[] expanded_data;
			}
			firstRender = false;
			glGenBuffers(1, &textBuffer);
			glGenBuffers(1, &textElements);
		}

		float penX = 0, penY = 0;
		FT_GlyphSlot slot = face->glyph;

		for (int i = 0; i < text.size(); i++)
		{

			error = FT_Load_Char(face, text[i], FT_LOAD_RENDER);

			if (slot->metrics.vertBearingY / 64 != levelingFix)
			{
				penY = slot->metrics.vertBearingY / 32;
			}
			else
			{
				penY = 0;
			}

			GLfloat textData[] = // Yksittäisen kirjaimen data
			{
				// Paikat																// Värit						// Tekstuurien koordinaatit
				position.x + penX * scale.x, position.y + penY, color.x, color.y, color.z, 0.0f, 0.0f,
				position.x + (penX + slot->bitmap.width) * scale.x, position.y + penY, color.x, color.y, color.z, 1.0f, 0.0f,
				position.x + (penX + slot->bitmap.width) * scale.x, position.y + penY + slot->bitmap.rows * scale.y, color.x, color.y, color.z, 1.0f, 1.0f,
				position.x + penX * scale.x, position.y + penY + slot->bitmap.rows * scale.y, color.x, color.y, color.z, 0.0f, 1.0f,
			};

			penX += slot->advance.x >> 6;
			penX += slot->advance.y >> 6;

			glBindBuffer(GL_ARRAY_BUFFER, textBuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(textData), textData, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
			glEnableVertexAttribArray(2);

			GLuint elements[] =
			{
				0, 1, 2,
				0, 2, 3
			};

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, textElements);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, idVector[i]);

			s.Use();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}
}