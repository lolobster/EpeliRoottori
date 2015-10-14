#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

#include <iostream>
#include <fstream>
#include <vector>

class TextManager
{
public:
	TextManager();
	~TextManager();

	void LoadFont(std::string filepath);
	void SetCharacterSize(float size);
	void SetColor(int red, int blue, int green, int opacity);
	void SetText(std::string message);
	float GetCharacterSize();
	std::vector<int> GetColor();
	std::string GetText();

private:
	std::string text = "";
	std::vector<int> color;
	float characterSize = 12.0f;
};

#endif