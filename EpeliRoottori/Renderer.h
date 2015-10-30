#ifndef RENDERER_H
#define RENDERER_H

#define GLM_FORCE_RADIANS
#include <cstdio>
#include <cstdlib>
#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>


class Renderer
{
public:
	Renderer();
	~Renderer();

	void Draw();

	//initialisoi renderöinnin, pistä ohjelman alkuun
	bool Init();
	void Uninit(void);
	void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	GLuint LoadShaderFromFile(const std::string filepath, GLenum ShaderType);
	void Use();
	//GLuint UseShader();
	GLuint GetShaderProgram();


private:
	GLuint ProgramID;
	GLuint MatrixID;
	GLuint VertexShaderID;
	GLuint FragmentShaderID;

};

#endif