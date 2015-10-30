#ifndef SHADER_H
#define SHADER_H

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


class Shader
{
public:
	Shader();
	~Shader();

	//initialisoi shaderit, pistä ohjelman alkuun
	bool Init();
	void Uninit(void);
	void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	GLuint LoadShaderFromFile(const std::string filepath, GLenum ShaderType);
	void Use();
	GLuint GetShaderProgram();


private:
	GLuint ProgramID;
	GLuint MatrixID;
	GLuint VertexShaderID;
	GLuint FragmentShaderID;

};

#endif