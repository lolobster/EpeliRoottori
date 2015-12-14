#include "Renderer.h"

Renderer::Renderer(glm::vec2 s)
{
	cam = new Camera{ s };

	shader.Init();
	glGenBuffers(1, &spriteBuffer);
	glGenBuffers(1, &spriteElements);
	glGenTextures(1, &textID);

	matrixID = glGetUniformLocation(shader.GetShaderProgram(), "MVP");
	cam->initialize();
}


Renderer::~Renderer()
{
}

void Renderer::drawAnimation(Sprite anim)
{

	GLfloat spriteData[] =
	{
		// Paikat																									// Värit															// Tekstuurien koordinaatit
		anim.GetPosition().x, anim.GetPosition().y, anim.GetColor().x, anim.GetColor().y, anim.GetColor().z, 0.0f, 0.0f,
		anim.GetPosition().x + anim.GetAnimGlobalBounds().x, anim.GetPosition().y, anim.GetColor().x, anim.GetColor().y, anim.GetColor().z, 1.0f, 0.0f,
		anim.GetPosition().x + anim.GetAnimGlobalBounds().x, anim.GetPosition().y + anim.GetAnimGlobalBounds().y, anim.GetColor().x, anim.GetColor().y, anim.GetColor().z, 1.0f, 1.0f,
		anim.GetPosition().x, anim.GetPosition().y + anim.GetAnimGlobalBounds().y, anim.GetColor().x, anim.GetColor().y, anim.GetColor().z, 0.0f, 1.0f,
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
	glBindTexture(GL_TEXTURE_2D, anim.GetAnimID());

	shader.Use();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glm::mat4 MVP = cam->getViewMatrix();
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
}

void Renderer::draw(Polygon polygon)
{

	if (timer < 0)
	{
		polygon.printData();

		//GLfloat* purkka = new GLfloat[polygon.getSize() * 8];
		//purkka = polygon.getData();
		//for (int i = 0; i < polygon.getSize() * 7; i++)
		//{
		//	std::cout << "  purkka element: " << i << "  " << purkka[i] << std::endl;
		//}

		////GLuint* indices = new GLuint[polygon.getSize()];
		////for (GLuint i = 0; i < polygon.getGLuintSize(); i++)
		////{
		////	std::cout << "indices element: " << i << " " << indices[i] << std::endl;
		////	indices[i] = i;
		////}

		//GLuint* pikkupurkka = new GLuint[polygon.getSize()];
		//pikkupurkka = polygon.getIndices();
		//for (int i = 0; i < polygon.getSize(); i++)
		//{
		//	std::cout << "pikkupurkka element: " << i << " " << pikkupurkka[i] << std::endl;
		//}

		timer = 90000000;
	}
	else
		timer--;

	GLfloat vertices[] =
	{
		//Positions				//Colors			//Texture Coords
		//200.5f, 200.5f,		 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		//100.5f, 100.5f,		 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		//0.5f, 0.5f,			 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		200.5f, 126.5f,		0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		40.5f, 60.0f,		 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		100.5f, 200.5f,		0.3f, 0.3f, 0.3f, 0.0f, 1.0f,		
	};

	glBindBuffer(GL_ARRAY_BUFFER, spriteBuffer);
	glBufferData(GL_ARRAY_BUFFER, polygon.getNumberOfElements() * sizeof(GLfloat), polygon.getData(), GL_STATIC_DRAW); // sizeof(polygon.getData()), polygon.getData(), GL_STATIC_DRAW);
	//pos
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	//tex Coord
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	//

	GLuint elements[] =
	{
		0, 1, 2,
		0, 2, 3,
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, spriteElements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW); //sizeof(polygon.getIndices()), polygon.getIndices(), GL_STATIC_DRAW);

	//Lisää tekstuurit

	

	//draw
	shader.Use();

	glDrawArrays(GL_TRIANGLES, 0, 3 * polygon.getSize());
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//glDrawElements(GL_TRIANGLES, polygon.getSize() * 3, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, 6s);
}

void Renderer::draw(Sprite sprite)
{
	GLfloat spriteData[] =
	{
		// Paikat																									// Värit															// Tekstuurien koordinaatit
		sprite.GetPosition().x, sprite.GetPosition().y,																sprite.GetColor().x, sprite.GetColor().y, sprite.GetColor().z,		0.0f, 0.0f,
		sprite.GetPosition().x + sprite.GetGlobalBounds().x, sprite.GetPosition().y,								sprite.GetColor().x, sprite.GetColor().y, sprite.GetColor().z,		1.0f, 0.0f,
		sprite.GetPosition().x + sprite.GetGlobalBounds().x, sprite.GetPosition().y + sprite.GetGlobalBounds().y,	sprite.GetColor().x, sprite.GetColor().y, sprite.GetColor().z,		1.0f, 1.0f,
		sprite.GetPosition().x, sprite.GetPosition().y + sprite.GetGlobalBounds().y,								sprite.GetColor().x, sprite.GetColor().y, sprite.GetColor().z,		0.0f, 1.0f,
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

	glm::mat4 MVP = cam->getViewMatrix();
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
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
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, slot->bitmap.width, slot->bitmap.rows, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, expanded_data);
			glActiveTexture(GL_TEXTURE0);
			delete[] expanded_data;


			penY = slot->metrics.vertBearingY / 32 - text.GetCharacterSize();

			if (slot->metrics.height / 64 - slot->metrics.horiBearingY / 64 > 0)
			{
				penY += slot->metrics.height / 64 - slot->metrics.horiBearingY / 64;
			}

			GLfloat textData[] = // Yksittäisen kirjaimen data
			{
				// Paikat																																		// Värit													// Tekstuurien koordinaatit
				text.GetPosition().x + penX * text.GetScale().x, text.GetPosition().y + penY,																	text.GetColor().x, text.GetColor().y, text.GetColor().z,	0.0f, 0.0f,
				text.GetPosition().x + (penX + slot->bitmap.width) * text.GetScale().x, text.GetPosition().y + penY,											text.GetColor().x, text.GetColor().y, text.GetColor().z,	1.0f, 0.0f,
				text.GetPosition().x + (penX + slot->bitmap.width) * text.GetScale().x, text.GetPosition().y + penY + slot->bitmap.rows * text.GetScale().y,	text.GetColor().x, text.GetColor().y, text.GetColor().z,	1.0f, 1.0f,
				text.GetPosition().x + penX * text.GetScale().x, text.GetPosition().y + penY + slot->bitmap.rows * text.GetScale().y,							text.GetColor().x, text.GetColor().y, text.GetColor().z,	0.0f, 1.0f,
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

	glm::mat4 MVP = cam->getViewMatrix();
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
}