#ifndef SPRITE_H
#define SPRITE_H
#include "TextureManager.h"
#include "AnimationManager.h"
#include "Shader.h"
#include <glm/glm.hpp>

class Sprite
{
public:
	Sprite();
	~Sprite();

	void SetTexture(const char *filepath);
	void SetAnimation(const char *filepath, const std::string& resourcePath);
	void SetPosition(glm::vec2 p);
	void SetScale(glm::vec2 s);
	void SetColor(glm::vec3 c);
	void SetRotation(float a);
	void Move(glm::vec2 m);
	void Scale(glm::vec2 s);
	void Rotate(float a);

	glm::vec3 GetColor();
	glm::vec2 GetPosition();
	glm::vec2 GetScale();
	float GetRotation();
	glm::vec2 GetBounds();
	glm::vec2 GetGlobalBounds();
	GLuint GetTexture();


	glm::vec2 GetAnimBounds();
	glm::vec2 GetAnimGlobalBounds();
	GLuint GetAnimID();

private:
	TextureManager tex;
	AnimationManager anim;
	GLuint spriteBuffer;
	GLuint spriteElements;
	GLuint texture = 0;
	float angle = 0;
	glm::vec2 position = { 0.0, 0.0 }, scale = { 1.0, 1.0 };
	glm::vec3 color = { 1.0, 1.0, 1.0 };
};

#endif