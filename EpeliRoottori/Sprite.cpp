#include "Sprite.h"


Sprite::Sprite() // Luo tyhj‰n Spriten, johon voi liitt‰‰ tekstuureja
{
	glGenBuffers(1, &spriteBuffer);
	glGenBuffers(1, &spriteElements);
}


Sprite::~Sprite()
{
}

AnimationManager* Sprite::GetAnimationManager()
{
	return &anim;
}

void Sprite::SetTexture(const char *filepath)
{
	tex.LoadTextures(filepath);
	animated = false;
}

void Sprite::SetAnimation(const char *filepath, const std::string& resourcePath)
{
	anim.LoadAnimation(filepath, resourcePath);
	animated = true;
}

void Sprite::SetAnimation(const char *filepath, glm::vec2 frameSize, float frameDuration)
{
	anim.LoadAnimation(filepath, frameSize, frameDuration);
	animated = true;
}

void Sprite::SetPosition(glm::vec2 p)
{
	position = p;
}

void Sprite::SetScale(glm::vec2 s)
{
	scale = s;
}

void Sprite::SetRotation(float a)
{
	angle = a;
}

void Sprite::SetColor(glm::vec3 c)
{
	color = c;
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

glm::vec3 Sprite::GetColor()
{
	return color;
}

glm::vec2 Sprite::GetBounds() // Tarkistaa ensin onko kyseinen sprite animoitu ja palauttaa sen mukaan oikean arvon
{
	if (animated)
	{
		return glm::vec2(anim.getFrameWidth(), anim.getFrameHeight());
	}
	else
	{
		return glm::vec2(tex.GetWidth(), tex.GetHeight());
	}
}

glm::vec2 Sprite::GetGlobalBounds() // Tarkistaa ensin onko kyseinen sprite animoitu ja palauttaa sen mukaan oikean arvon
{
	if (animated)
	{
		return glm::vec2(anim.getFrameWidth() * scale.x, anim.getFrameHeight() * scale.y);
	}
	else
	{
		return glm::vec2(tex.GetWidth() * scale.x, tex.GetHeight() * scale.y);
	}
}

bool Sprite::GetIfAnimated()
{
	return animated;
}

GLuint Sprite::GetTexture()
{
	return tex.GetID();
}

GLuint Sprite::GetAnimID()
{
	return anim.getAnimationID();
}