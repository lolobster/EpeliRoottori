#ifndef SPRITE_H
#define SPRITE_H

#include "Includes.h"

#include "TextureManager.h"
#include "AnimationManager.h"

class Sprite
{
public:
	Sprite();
	~Sprite();

	AnimationManager* GetAnimationManager();

	void SetTexture(const char *filepath);
	void SetAnimation(const char *filepath, const std::string& resourcePath);
	void SetAnimation(const char *filepath, glm::vec2 frameSize, float frameDuration);
	void SetPosition(glm::vec2 p);
	void SetScale(glm::vec2 s);
	void SetRotation(float a);
	void SetColor(glm::vec3 c);
	void Move(glm::vec2 m);
	void Scale(glm::vec2 s);
	void Rotate(float a);

	glm::vec2 GetPosition();
	glm::vec2 GetScale();
	float GetRotation();
	glm::vec3 GetColor();
	glm::vec2 GetBounds();
	glm::vec2 GetGlobalBounds();
	bool GetIfAnimated();
	GLuint GetTexture();
	GLuint GetAnimID();

private:
	bool animated = false;
	TextureManager tex;
	AnimationManager anim;
	GLuint spriteBuffer, spriteElements, texture = 0;
	glm::vec2 position = { 0.0, 0.0 }, scale = { 1.0, 1.0 };
	glm::vec3 color = { 1.0, 1.0, 1.0 };
	float angle = 0;
};

#endif