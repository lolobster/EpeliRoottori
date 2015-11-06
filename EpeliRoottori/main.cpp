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

//Meid‰n omat includet
#include "Renderer.h"
#include "Shader.h"

// Ikkunan koko
const GLuint WIDTH = 1200, HEIGHT = 800;

//testground

void key_callback(GLFWwindow* Window, int Key, int ScanCode, int Action, int Mode);

//end of testground

int main(void)
{	

	glfwInit();				// Initialisoidaan GLFW

	// GLFW perusasetukset
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);			// asetetaan OpenGL-
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);			// versio 2.1
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);	// m‰‰ritell‰‰n OpenGL profiili k‰ytett‰v‰ksi
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);				// ikkunan kokoa ei voi muuttaa


	// luodaan ikkuna GLFWwindow
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "EPELIROOTTORI", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	glewExperimental = GL_TRUE;

	glewInit();				// Initialisoidaan GLEW

	glViewport(0, 0, WIDTH, HEIGHT);

	//testground	

	//Renderer render;
	//render.Init();
	Shader shader;
	shader.Init();

	//GLfloat vertices[] =
	//{
	//	// Positions			 // Colors			//Texture Coords
	//	 0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	//1.0f, 0.0f,	// Bottom Right
	//	-0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	//1.0f, 0.0f,	// Bottom Left
	//	 0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 0.1f,	//0.0f, 0.0f,	// Top Right
	//	-0.5f,  0.5f, 0.0f,		0.3f, 0.3f, 0.3f	//0.0f, 1.0f	// Top Left
	//};

	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
		 0.5f, 0.5f,  -0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
		 0.5f, 0.5f, -0.5f,		0.3f, 0.3f, 0.3f,	1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 0.0f,	0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	0.3f, 0.3f, 0.3f,	0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		 0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,	0.3f, 0.3f, 0.3f,	1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,	1.0f, 0.0f, 0.0f,	0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,	0.3f, 0.3f, 0.3f,	0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,	1.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	0.3f, 0.3f, 0.3f,	0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,	0.3f, 0.3f, 0.3f,	1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,		0.0f, 0.0f, 1.0f,	0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,		0.3f, 0.3f, 0.3f,	0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,		0.3f, 0.3f, 0.3f,	1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,	0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 0.1f,	1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,	0.3f, 0.3f, 0.3f,	1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	0.3f, 0.3f, 0.3f,	0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,	1.0f, 0.0f, 0.0f,	0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,	0.3f, 0.3f, 0.3f,	1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,	0.3f, 0.3f, 0.3f,	0.0f, 1.0f
	};

	glm::vec3 cubesPos[] =
	{
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(2.0f, 5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f, 3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f, 2.0f, -2.5f),
		glm::vec3(1.5f, 0.2f, -1.5f),
		glm::vec3(-1.3f, 1.0f, -1.5f)
	};

	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
	};

	GLuint indices[] = {
		3, 2, 0, // first triangle
		3, 1, 0  // second triangle
	};


	
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	//position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);


	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(2);

	//glBindBuffer(GL_ARRAY_BUFFER, EBO);

	//unbind VAO
	glBindVertexArray(0);	
	
	//end of testground

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//while loop testground
		
		//render
		//v‰ri bufferin tyhjennys
		glClearColor(0.0f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// ---- Create transformation ---- //

		glm::mat4 view;
		glm::mat4 projection;
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

		//GLint modelLoc = glGetUniformLocation();

		// ---- End of create transformation ---- //


		//draw triangle
		//GLfloat timeValue = glfwGetTime();
		//GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
		//GLint vertexColorLocation = glGetUniformLocation(shader.GetShaderProgram(), "ourColor");
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		shader.Use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		
		//end of while loop testground	

		glfwSwapBuffers(window);	
	}

	//testground stuff
	
	//glDeleteVertexArrays(1, &VAO);
	//glCreateBuffers(1, &VBO);
	//glfwTerminate();
	return 0;
	
	//end of testground stuff
}

void key_callback(GLFWwindow* Window, int Key, int ScanCode, int Action, int Mode)
{
	if (Key == GLFW_KEY_ESCAPE && Action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(Window, GL_TRUE);
	}
}
