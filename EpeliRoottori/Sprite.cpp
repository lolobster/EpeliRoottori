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
	animated = false;
}

void Sprite::SetAnimation(const char *filepath, const std::string& resourcePath)
{
	anim.loadAnimation(filepath, resourcePath);
	animated = true;
}

void Sprite::SetAnimation(const char *filepath, glm::vec2 frameSize, float frameDuration)
{
	anim.loadAnimation(filepath, frameSize, frameDuration);
	animated = true;
}

AnimationManager* Sprite::GetAnimationManager() {
	return &anim;
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
	if (animated)
	{
		return glm::vec2(anim.getFrameWidth(), anim.getFrameHeight());
	}
	else
	{
		return glm::vec2(tex.getWidth(), tex.getHeight());
	}
}

glm::vec2 Sprite::GetGlobalBounds()
{
	if (animated)
	{
		return glm::vec2(anim.getFrameWidth() * scale.x, anim.getFrameHeight() * scale.y);
	}
	else
	{
		return glm::vec2(tex.getWidth() * scale.x, tex.getHeight() * scale.y);
	}
}

GLuint Sprite::GetTexture()
{
	return tex.getID();
}

GLuint Sprite::GetAnimID()
{
	return anim.getAnimationID();
}

bool Sprite::GetIfAnimated()
{
	return animated;
}