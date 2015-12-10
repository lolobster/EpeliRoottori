#include "Sprite.h"


Sprite::Sprite()
{
	glGenBuffers(1, &spriteBuffer);
	glGenBuffers(1, &spriteElements);
}


Sprite::~Sprite()
{
}

void Sprite::SetTexture(const char *filepath)
{
	tex.loadTextures(filepath);
}

void Sprite::SetPosition(glm::vec2 p)
{
	position = p;
}

void Sprite::SetScale(glm::vec2 s)
{
	scale = s;
}

void Sprite::SetColor(glm::vec3 c)
{
	color = c;
}

void Sprite::SetRotation(float a)
{
	angle = a;
}

void Sprite::Move(glm::vec2 m)
{
	position += m;
}

void Sprite::Scale(glm::vec2 s)
{
	scale *= s;
}

void Sprite::Rotate(float a)
{
	angle += a;
}

glm::vec3 Sprite::GetColor()
{
	return color;
}

glm::vec2 Sprite::GetPosition()
{
	return position;
}

glm::vec2 Sprite::GetScale()
{
	return scale;
}

float Sprite::GetRotation()
{
	return angle;
}

glm::vec2 Sprite::GetBounds()
{
	return glm::vec2(tex.getWidth(), tex.getHeight());
}

void Sprite::draw(Shader &s)
{
	GLfloat spriteData[] =
	{
		// Paikat																// Värit						// Tekstuurien koordinaatit
		position.x, position.y, color.x, color.y, color.z, 0.0f, 0.0f,
		position.x + tex.getWidth() * scale.x, position.y, color.x, color.y, color.z, 1.0f, 0.0f,
		position.x + tex.getWidth() * scale.x, position.y + tex.getHeight() * scale.y, color.x, color.y, color.z, 1.0f, 1.0f,
		position.x, position.y + tex.getHeight() * scale.y, color.x, color.y, color.z, 0.0f, 1.0f,
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
	glBindTexture(GL_TEXTURE_2D, tex.getID());

	s.Use();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}