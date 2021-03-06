#ifndef POLYGON_H
#define POLYGON_H

#include "Includes.h"
#include "Shader.h"
#include "TextureManager.h"

struct vertex{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textCoords;
};

class Polygon
{
public:
	//std::vector<vertex> vertices;
	//std::vector<GLuint> indices;
	//std::vector<Texture> textures;

	
	//Polygon(int sides);
	Polygon(int sides, float radius, float scale, GLfloat rotation, GLfloat x, GLfloat y, GLfloat cx, GLfloat cy, GLfloat cz);
	Polygon(int sides, float radius, float scale, GLfloat rotation, GLfloat x, GLfloat y, GLfloat cx, GLfloat cy, GLfloat cz, const char* texturePath);
	~Polygon();

	void Update();
	void DrawPolygon(int sides, float radius, float scale, GLfloat rotation, glm::vec2 position, glm::vec3 color, Shader *shader);
	void PrintData();
	void Rotate(GLfloat degree);
	void DemoEffect(GLfloat degree);
	void Translate(glm::vec2 value);

	GLfloat GetX();
	GLfloat GetY();
	GLfloat GetTextCoordX();
	GLfloat GetTextCoordY();
	GLfloat GetColorX();
	GLfloat GetColorY();
	GLfloat GetColorZ();
	GLuint GetNumberOfElements();
	GLuint GetNumberOfIndices();

	GLfloat* GetData();
	GLuint* GetIndices();
	int GetSize();
	GLuint GetGLuintSize();
	GLuint GetTexture();

private:
	GLuint vao, vbo, ebo, numberOfElements, numberOfIndices;
	
	GLfloat x, y, theta, angle, radius, scale,
		textCoordX, textCoordY,
		colorX, colorY, colorZ;

	GLfloat *data;
	GLuint *indices;

	TextureManager tex;

	int size, sides;
	int counter;
};

#endif