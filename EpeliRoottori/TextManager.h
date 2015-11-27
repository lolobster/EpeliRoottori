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

	void LoadFont(const char *filepath);
	void SetCharacterSize(float size);
	void SetPosition(glm::vec2 pos);
	void SetColor(glm::vec3 colors);
	void SetText(std::string message);
	GLuint turnToBitmap();
	float GetCharacterSize();
	std::string GetText();
	void RenderText(Shader &s);

private:
	// Defaults to an empty message with white color and charactersize of 12
	FT_Library library;
	FT_Face face;
	FT_Bitmap bmp;
	FT_Error error;
	std::string text = "";
	float characterSize = 12.0f;
	glm::vec2 position = { 0.0, 0.0 };
	glm::vec3 color = { 0.0, 0.0, 0.0 };
};

#endif