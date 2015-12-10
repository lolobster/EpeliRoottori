#include "Renderer.h"

Renderer::Renderer()
{
	shader.Init();
	glGenBuffers(1, &spriteBuffer);
	glGenBuffers(1, &spriteElements);
	glGenTextures(1, &textID);
}


Renderer::~Renderer()
{
}

void Renderer::draw(Sprite sprite)
{
	GLfloat spriteData[] =
	{
		// Paikat																// Värit						// Tekstuurien koordinaatit
		sprite.GetPosition().x, sprite.GetPosition().y, sprite.GetColor().x, sprite.GetColor().y, sprite.GetColor().z, 0.0f, 0.0f,
		sprite.GetPosition().x + sprite.GetBounds().x * sprite.GetScale().x, sprite.GetPosition().y, sprite.GetColor().x, sprite.GetColor().y, sprite.GetColor().z, 1.0f, 0.0f,
		sprite.GetPosition().x + sprite.GetBounds().x * sprite.GetScale().x, sprite.GetPosition().y + sprite.GetBounds().y * sprite.GetScale().y, sprite.GetColor().x, sprite.GetColor().y, sprite.GetColor().z, 1.0f, 1.0f,
		sprite.GetPosition().x, sprite.GetPosition().y + sprite.GetBounds().y * sprite.GetScale().y, sprite.GetColor().x, sprite.GetColor().y, sprite.GetColor().z, 0.0f, 1.0f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, spriteBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(spriteData), spriteData, GL_STATIC_DRAW);
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

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, spriteElements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, sprite.GetTexture());

	shader.Use();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::draw(TextManager text)
{
	if (text.GetError() == false)
	{
		float penX = 0, penY = 0;
		FT_GlyphSlot slot = text.GetFace()->glyph;

		for (int i = 0; i < text.GetText().size(); i++)
		{
			FT_Load_Char(text.GetFace(), text.GetText()[i], FT_LOAD_RENDER);

			GLubyte* expanded_data = new GLubyte[2 * slot->bitmap.width * slot->bitmap.rows];
			for (int j = 0; j < slot->bitmap.rows; j++)
			{
				for (int k = 0; k < slot->bitmap.width; k++)
				{
					expanded_data[2 * (k + j * slot->bitmap.width)] = 255;
					expanded_data[2 * (k + j * slot->bitmap.width) + 1] = (k >= slot->bitmap.width || j >= slot->bitmap.rows) ? 0 : slot->bitmap.buffer[k + slot->bitmap.width * j];
				}
			}

			glBindTexture(GL_TEXTURE_2D, textID);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, slot->bitmap.width, slot->bitmap.rows, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, expanded_data);
			glActiveTexture(GL_TEXTURE0);
			delete[] expanded_data;


			penY = slot->metrics.vertBearingY / 32;

			GLfloat textData[] = // Yksittäisen kirjaimen data
			{
				// Paikat																// Värit						// Tekstuurien koordinaatit
				text.GetPosition().x + penX * text.GetScale().x, text.GetPosition().y + penY, text.GetColor().x, text.GetColor().y, text.GetColor().z, 0.0f, 0.0f,
				text.GetPosition().x + (penX + slot->bitmap.width) * text.GetScale().x, text.GetPosition().y + penY, text.GetColor().x, text.GetColor().y, text.GetColor().z, 1.0f, 0.0f,
				text.GetPosition().x + (penX + slot->bitmap.width) * text.GetScale().x, text.GetPosition().y + penY + slot->bitmap.rows * text.GetScale().y, text.GetColor().x, text.GetColor().y, text.GetColor().z, 1.0f, 1.0f,
				text.GetPosition().x + penX * text.GetScale().x, text.GetPosition().y + penY + slot->bitmap.rows * text.GetScale().y, text.GetColor().x, text.GetColor().y, text.GetColor().z, 0.0f, 1.0f,
			};

			penX += slot->advance.x >> 6;

			glBindBuffer(GL_ARRAY_BUFFER, spriteBuffer);
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

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, spriteElements);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textID);

			shader.Use();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}
}