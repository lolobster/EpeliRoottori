#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H
#include "lodepng.h"
#include <GL/glew.h>
#include "Color.h"
#include "Shader.h"

#include <iostream>
#include <fstream>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H

class TextManager
{
public:
	TextManager();
	~TextManager();

	void RenderText(Shader &s);

	void LoadFont(const char *filepath);
	void SetCharacterSize(float size);
	void SetText(std::string message);
	void SetColor(glm::vec3 colors);
	void SetPosition(glm::vec2 pos);
	void SetScale(glm::vec2 newScale);
	void SetRotation(float rot);
	void Move(glm::vec2 movement);
	void Scale(glm::vec2 scaleFactor);
	void Rotate(float rot);

	float GetCharacterSize();
	std::string GetText();
	glm::vec3 GetColor();
	glm::vec2 GetPosition();
	glm::vec2 GetScale();
	float GetRotation();

private:
	FT_Library library;
	FT_Face face;
	FT_Error error;
	std::vector<GLuint>idVector;
	bool firstRender = true;

	// Defaults to an empty message with white color and charactersize of 12
	float characterSize = 12.0f;
	std::string text = "";
	glm::vec3 color = { 0.0, 0.0, 0.0 };
	glm::vec2 position = { 0.0, 0.0 };
	glm::vec2 scale = { 1.0, 1.0 };
	float angle = 0;
};

#endif