#include "Renderer.h"
#include "AnimationManager.h"

Renderer::Renderer(glm::vec2 s) // Ottaa vastaan kameran koon, pääasiassa kannattaa pitää samana kuin ikkunan koko
{
	// Alustaa kameran ja varjostimet
	camera = new Camera{ s };
	shader.Init();
	matrixID = glGetUniformLocation(shader.GetShaderProgram(), "MVP");
	camera->initialize();
	glGenBuffers(1, &spriteBuffer);
	glGenBuffers(1, &spriteElements);
	glGenTextures(1, &textID);
}


Renderer::~Renderer()
{
}

void Renderer::Draw(Polygon polygon)
{
	//Debug
	//if (timer < 0)
	//{
	//	polygon.printData();
	//	timer = 90000000;
	//}
	//else
	//	timer--;

	glBindBuffer(GL_ARRAY_BUFFER, spriteBuffer);
	glBufferData(GL_ARRAY_BUFFER, polygon.GetNumberOfElements() * sizeof(GLfloat), polygon.GetData(), GL_STATIC_DRAW); // sizeof(polygon.getData()), polygon.getData(), GL_STATIC_DRAW);
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

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, spriteElements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, polygon.GetNumberOfIndices() * sizeof(GLuint), polygon.GetIndices() , GL_STATIC_DRAW); //sizeof(polygon.getIndices()), polygon.getIndices(), GL_STATIC_DRAW);

	//Lisää tekstuurit

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, polygon.GetTexture());

	//draw
	shader.Use();

	//glDrawArrays(GL_TRIANGLES, 0, 36);//3 * polygon.getSize());
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glDrawElements(GL_TRIANGLES, polygon.GetNumberOfIndices(), GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, 6s);
}

void Renderer::Draw(Sprite sprite) // Spriten piirtäminen tapahtuu eri tavalla riippuen siitä onko sillä animaatio vai ei
{
	if (sprite.GetIfAnimated()) 
	{
		// Lasketaan tekstuurikoordinaatit
		AnimationManager* manager = sprite.GetAnimationManager();
		Frame frame = manager->getCurrentFrame();

		float texture_width = manager->GetWidth();
		float texture_height = manager->GetHeight();

		float sourceRight = frame.texCoords.x + manager->getFrameWidth();
		float sourceBottom = frame.texCoords.y + manager->getFrameHeight();

		glm::fvec2 topLeft = { frame.texCoords.x / texture_width, frame.texCoords.y / texture_height };
		glm::fvec2 topRight = { sourceRight / texture_width, frame.texCoords.y / texture_height };
		glm::fvec2 bottomLeft = { topLeft.x, sourceBottom / texture_height };
		glm::fvec2 bottomRight = { topRight.x, bottomLeft.y };

		// Lasketaan pisteiden paikat
		glm::vec2 pos1 = sprite.GetPosition() + glm::rotate(glm::vec2(-manager->getFrameWidth() * sprite.GetScale().x / 2.0f, -manager->getFrameHeight() * sprite.GetScale().y / 2.0f), glm::radians(sprite.GetRotation())) + glm::vec2(manager->getFrameWidth() * sprite.GetScale().x / 2.0f, manager->getFrameHeight() * sprite.GetScale().y / 2.0f);
		glm::vec2 pos2 = sprite.GetPosition() + glm::rotate(glm::vec2(manager->getFrameWidth() * sprite.GetScale().x / 2.0f, -manager->getFrameHeight() * sprite.GetScale().y / 2.0f), glm::radians(sprite.GetRotation())) + glm::vec2(manager->getFrameWidth() * sprite.GetScale().x / 2.0f, manager->getFrameHeight() * sprite.GetScale().y / 2.0f);
		glm::vec2 pos3 = sprite.GetPosition() + glm::rotate(glm::vec2(-manager->getFrameWidth() * sprite.GetScale().x / 2.0f, manager->getFrameHeight() * sprite.GetScale().y / 2.0f), glm::radians(sprite.GetRotation())) + glm::vec2(manager->getFrameWidth() * sprite.GetScale().x / 2.0f, manager->getFrameHeight() * sprite.GetScale().y / 2.0f);
		glm::vec2 pos4 = sprite.GetPosition() + glm::rotate(glm::vec2(manager->getFrameWidth() * sprite.GetScale().x / 2.0f, manager->getFrameHeight() * sprite.GetScale().y / 2.0f), glm::radians(sprite.GetRotation())) + glm::vec2(manager->getFrameWidth() * sprite.GetScale().x / 2.0f, manager->getFrameHeight() * sprite.GetScale().y / 2.0f);

		GLfloat spriteData[] =
		{
			// Paikat		// Värit													   // Tekstuurien koordinaatit
			pos1.x, pos1.y, sprite.GetColor().x, sprite.GetColor().y, sprite.GetColor().z, bottomLeft.x, bottomLeft.y,
			pos2.x, pos2.y, sprite.GetColor().x, sprite.GetColor().y, sprite.GetColor().z, bottomRight.x, bottomRight.y,
			pos3.x, pos3.y, sprite.GetColor().x, sprite.GetColor().y, sprite.GetColor().z, topLeft.x, topLeft.y,
			pos4.x, pos4.y, sprite.GetColor().x, sprite.GetColor().y, sprite.GetColor().z, topRight.x, topRight.y,
		};

		glBindBuffer(GL_ARRAY_BUFFER, spriteBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(spriteData), spriteData, GL_STATIC_DRAW);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, sprite.GetAnimID());
	}
	else
	{
		// Lasketaan pisteiden paikat
		glm::vec2 pos1 = sprite.GetPosition() + glm::rotate(glm::vec2(-sprite.GetGlobalBounds().x / 2.0f, -sprite.GetGlobalBounds().y / 2.0f), glm::radians(sprite.GetRotation())) + glm::vec2(sprite.GetGlobalBounds().x / 2.0f, sprite.GetGlobalBounds().y / 2.0f);
		glm::vec2 pos2 = sprite.GetPosition() + glm::rotate(glm::vec2(sprite.GetGlobalBounds().x / 2.0f, -sprite.GetGlobalBounds().y / 2.0f), glm::radians(sprite.GetRotation())) + glm::vec2(sprite.GetGlobalBounds().x / 2.0f, sprite.GetGlobalBounds().y / 2.0f);
		glm::vec2 pos3 = sprite.GetPosition() + glm::rotate(glm::vec2(-sprite.GetGlobalBounds().x / 2.0f, sprite.GetGlobalBounds().y / 2.0f), glm::radians(sprite.GetRotation())) + glm::vec2(sprite.GetGlobalBounds().x / 2.0f, sprite.GetGlobalBounds().y / 2.0f);
		glm::vec2 pos4 = sprite.GetPosition() + glm::rotate(glm::vec2(sprite.GetGlobalBounds().x / 2.0f, sprite.GetGlobalBounds().y / 2.0f), glm::radians(sprite.GetRotation())) + glm::vec2(sprite.GetGlobalBounds().x / 2.0f, sprite.GetGlobalBounds().y / 2.0f);

		GLfloat spriteData[] =
		{
			// Paikat		// Värit													   // Tekstuurien koordinaatit
			pos1.x, pos1.y, sprite.GetColor().x, sprite.GetColor().y, sprite.GetColor().z, 0.0f, 1.0f,
			pos2.x, pos2.y, sprite.GetColor().x, sprite.GetColor().y, sprite.GetColor().z, 1.0f, 1.0f,
			pos3.x, pos3.y, sprite.GetColor().x, sprite.GetColor().y, sprite.GetColor().z, 0.0f, 0.0f,
			pos4.x, pos4.y, sprite.GetColor().x, sprite.GetColor().y, sprite.GetColor().z, 1.0f, 0.0f,
		};

		glBindBuffer(GL_ARRAY_BUFFER, spriteBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(spriteData), spriteData, GL_STATIC_DRAW);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, sprite.GetTexture());
	}

	FinishDrawing();
}

void Renderer::Draw(TextManager text)
{
	if (text.GetError() == false)
	{
		float penX = 0, penY = 0; // Kertovat kuinka paljon eteenpäin kirjainten pitää liikkua
		FT_GlyphSlot slot = text.GetFace()->glyph;

		for (int i = 0; i < text.GetText().size(); i++) // Käy tekstin kirjain kirjaimelta läpi
		{
			// Tehdään ja asetetaan tekstuuri
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

			// Lasketaan kirjaimen paikka y-akselilla
			penY = slot->metrics.vertBearingY / 32 - text.GetCharacterSize();

			if (slot->metrics.height / 64 - slot->metrics.horiBearingY / 64 > 0)
			{
				penY += slot->metrics.height / 64 - slot->metrics.horiBearingY / 64;
			}

			GLfloat textData[] = // Yksittäisen kirjaimen data
			{
				// Paikat																																			// Värit												 // Tekstuurien koordinaatit
				text.GetPosition().x + penX * text.GetScale().x, text.GetPosition().y + penY,																		text.GetColor().x, text.GetColor().y, text.GetColor().z, 0.0f, 1.0f,
				text.GetPosition().x + (penX + slot->bitmap.width) * text.GetScale().x, text.GetPosition().y + penY,												text.GetColor().x, text.GetColor().y, text.GetColor().z, 1.0f, 1.0f,
				text.GetPosition().x + penX * text.GetScale().x, text.GetPosition().y + penY + slot->bitmap.rows * text.GetScale().y,								text.GetColor().x, text.GetColor().y, text.GetColor().z, 0.0f, 0.0f,
				text.GetPosition().x + (penX + slot->bitmap.width) * text.GetScale().x, text.GetPosition().y + penY + slot->bitmap.rows * text.GetScale().y,		text.GetColor().x, text.GetColor().y, text.GetColor().z, 1.0f, 0.0f,
			};

			// Lasketaan kirjaimen x-koordinaatin muutos
			penX += slot->advance.x >> 6;

			glBindBuffer(GL_ARRAY_BUFFER, spriteBuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(textData), textData, GL_STATIC_DRAW);

			FinishDrawing();
		}
	}
}

void Renderer::FinishDrawing()
{
	// Antaa datan varjostimille
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	GLuint elements[] =
	{
		0, 1, 2,
		1, 2, 3
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, spriteElements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	// Piirtäminen
	shader.Use();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// Kameran päivitys
	glm::mat4 MVP = camera->GetViewMatrix();
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
}