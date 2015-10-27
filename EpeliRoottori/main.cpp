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

	Renderer render;

	render.Init();

	GLfloat vertices[] =
	{
		// Positions			 // Colors
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,  // Bottom Right
		-0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,  // Bottom Left
		0.0f, 0.5f, 0.0f,		0.0f, 0.0f, 1.0f   // Top

	};

	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};

	GLuint indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};


	
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);
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
	//unbind VAO
	glBindVertexArray(0);
	//glEnableVertexAttribArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);
	
	
	//end of testground

	/*
	GLuint vertexbuffer;

	glGenBuffers(1, &vertexbuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	*/

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//while loop testground
		
		//render
		//clear color buffer
		glClearColor(0.0f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		//draw triangle
		render.OurShader();
		glBindVertexArray(VAO);
		//draw elements
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		
		//end of while loop testground
		//glDisableVertexAttribArray(0);

		

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
