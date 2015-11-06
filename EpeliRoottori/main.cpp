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
#include <glm/gtc/type_ptr.hpp>

//Meidän omat includet
#include "Renderer.h"
#include "Shader.h"

// Ikkunan koko
const GLuint WIDTH = 1200, HEIGHT = 800;

//testground

void key_callback(GLFWwindow* Window, int Key, int ScanCode, int Action, int Mode);
void LateTesti(GLFWwindow* Window, const GLuint width, const GLuint height);
void TaskuTesti1(GLFWwindow* Window, const GLuint width, const GLuint height);
void Taskutesti2();
//end of testground

int main(void)
{	

	glfwInit();				// Initialisoidaan GLFW

	// GLFW perusasetukset
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);			// asetetaan OpenGL-
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);			// versio 2.1
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);	// määritellään OpenGL profiili käytettäväksi
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);				// ikkunan kokoa ei voi muuttaa


	// luodaan ikkuna GLFWwindow
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "EPELIROOTTORI", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	glewExperimental = GL_TRUE;

	glewInit();				// Initialisoidaan GLEW

	glViewport(0, 0, WIDTH, HEIGHT);

	Shader shader;
	shader.Init();
	
	//LateTesti(window, WIDTH, HEIGHT);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//väri bufferin tyhjennys
		glClearColor(0.0f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);	
	}
	return 0;
	
}

void LateTesti(GLFWwindow* Window, const GLuint width, const GLuint height)
{
	Shader shader;
	shader.Init();

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	static const GLfloat g_vertex_buffer_data[] =
	{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
	};

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	GLuint MatrixID = glGetUniformLocation(shader.GetShaderProgram(), "MVP");

	glm::vec3 x_axis(1.0, 0.0, 0.0);
	glm::vec3 y_axis(0.0, 1.0, 0.0);
	glm::vec3 z_axis(0.0, 0.0, 1.0);
	glm::vec3 cam_pos(0, 0, 0);
	glm::vec3 cam_up = y_axis;
	glm::vec3 cam_right = x_axis;
	glm::vec3 cam_front = -z_axis;
	glm::mat4 P = glm::lookAt(cam_pos, cam_pos + cam_front, cam_up);
	glm::mat4 V = glm::ortho(-1.0f, 1.0f, -1.0f*height / width, 1.0f*height / width);
	glm::mat4 M;
	glm::mat4 MVP;
	float distance = 0.0;
	bool direction = false;

	while (!glfwWindowShouldClose(Window))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.2f, 0.2f, 1.0f);

		if (distance > 1.0)
		{
			direction = false;
		}
		else if (distance < -1.0)
		{
			direction = true;
		}

		if (direction == true)
		{
			M = glm::translate(glm::vec3(distance, 0.0, 0.0));
			distance += 0.001;
		}
		else if (direction == false)
		{
			M = glm::translate(glm::vec3(distance, 0.0, 0.0));
			distance -= 0.001;
		}

		MVP = P * V * M;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		glEnableVertexAttribArray(0);
		glDrawArrays(GL_TRIANGLES, 0, 3 * 2);
		glDisableVertexAttribArray(0);

		shader.Use();	

		glfwSwapBuffers(Window);
	}
}

void key_callback(GLFWwindow* Window, int Key, int ScanCode, int Action, int Mode)
{
	if (Key == GLFW_KEY_ESCAPE && Action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(Window, GL_TRUE);
	}
}

void TaskuTesti2(GLFWwindow* Window, const GLuint width, const GLuint height)
{
	//shader.Use();
	// ---- Create transformation ---- //
	/*
	glm::mat4 view;
	glm::mat4 projection;
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

	GLint modelLoc = glGetUniformLocation(shader.GetShaderProgram(), "model");
	GLint viewLoc = glGetUniformLocation(shader.GetShaderProgram(), "view");
	GLint projLoc = glGetUniformLocation(shader.GetShaderProgram(), "projection");


	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(VAO);

	for (GLuint i = 0; i < 10; i++)
	{
		glm::mat4 model;
		model = glm::translate(model, cubesPos[i]);
		GLfloat angle = 20.0f * i;
		model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
	}

	glBindVertexArray(0);
	// ---- End of create transformation ---- //


	//draw triangle
	//GLfloat timeValue = glfwGetTime();
	//GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
	//GLint vertexColorLocation = glGetUniformLocation(shader.GetShaderProgram(), "ourColor");
	//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
	//
	//shader.Use();
	//glBindVertexArray(VAO);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//glBindVertexArray(0);
	//
	//end of while loop testground	
	*/
}

void taskuTesti2()
{
	//GLfloat vertices[] =
	//{
	//	// Positions			 // Colors			//Texture Coords
	//	 0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	//1.0f, 0.0f,	// Bottom Right
	//	-0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	//1.0f, 0.0f,	// Bottom Left
	//	 0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 0.1f,	//0.0f, 0.0f,	// Top Right
	//	-0.5f,  0.5f, 0.0f,		0.3f, 0.3f, 0.3f	//0.0f, 1.0f	// Top Left
	//};

	GLfloat vertices[] = {
		//Positions				//Colors			//Texture Coords
		-0.5f, -0.5f, -0.5f,	//1.0f, 0.0f, 0.0f,	//0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,	//0.0f, 1.0f, 0.0f,	//1.0f, 0.0f,
		0.5f, 0.5f, -0.5f,	//0.0f, 0.0f, 1.0f,	//1.0f, 1.0f,
		0.5f, 0.5f, -0.5f,		//0.3f, 0.3f, 0.3f,	//1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f,		//1.0f, 0.0f, 0.0f,	//0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	//0.3f, 0.3f, 0.3f,	//0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f,	//1.0f, 0.0f, 0.0f,	//0.0f, 0.0f,
		0.5f, -0.5f, 0.5f,		//0.0f, 1.0f, 0.0f,	//1.0f, 0.0f,
		0.5f, 0.5f, 0.5f,	//0.0f, 0.0f, 1.0f,	//1.0f, 1.0f,
		0.5f, 0.5f, 0.5f,	//0.3f, 0.3f, 0.3f,	//1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f,	//1.0f, 0.0f, 0.0f,	//0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,	//0.3f, 0.3f, 0.3f,	//0.0f, 0.0f,

		-0.5f, 0.5f, 0.5f,	//1.0f, 0.0f, 0.0f,	//1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f,	//0.0f, 1.0f, 0.0f,	//1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	//0.0f, 0.0f, 1.0f,	//0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	//0.3f, 0.3f, 0.3f,	//0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,	//1.0f, 0.0f, 0.0f,	//0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f,	//0.3f, 0.3f, 0.3f,	//1.0f, 0.0f,

		0.5f, 0.5f, 0.5f,		//1.0f, 0.0f, 0.0f,	//1.0f, 0.0f,
		0.5f, 0.5f, -0.5f,		//0.0f, 1.0f, 0.0f,	//1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,		//0.0f, 0.0f, 1.0f,	//0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,		//0.3f, 0.3f, 0.3f,	//0.0f, 1.0f,
		0.5f, -0.5f, 0.5f,		//1.0f, 0.0f, 0.0f,	//0.0f, 0.0f,
		0.5f, 0.5f, 0.5f,		//0.3f, 0.3f, 0.3f,	//1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,	//1.0f, 0.0f, 0.0f,	//0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,	//0.0f, 1.0f, 0.0f,	//1.0f, 1.0f,
		0.5f, -0.5f, 0.5f,	//0.0f, 0.0f, 0.1f,	//1.0f, 0.0f,
		0.5f, -0.5f, 0.5f,	//0.3f, 0.3f, 0.3f,	//1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f,	//1.0f, 0.0f, 0.0f,	//0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	//0.3f, 0.3f, 0.3f,	//0.0f, 1.0f,

		-0.5f, 0.5f, -0.5f,	//1.0f, 0.0f, 0.0f,	//0.0f, 1.0f,
		0.5f, 0.5f, -0.5f,	//0.0f, 1.0f, 0.0f,	//1.0f, 1.0f,
		0.5f, 0.5f, 0.5f,	//0.0f, 0.0f, 1.0f,	//1.0f, 0.0f,
		0.5f, 0.5f, 0.5f,	//0.3f, 0.3f, 0.3f,	//1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f,	//1.0f, 0.0f, 0.0f,	//0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f,	//0.3f, 0.3f, 0.3f,	//0.0f, 1.0f
	};

	static const GLfloat g_color_buffer_data[] = {
		0.583f, 0.771f, 0.014f,
		0.609f, 0.115f, 0.436f,
		0.327f, 0.483f, 0.844f,
		0.822f, 0.569f, 0.201f,
		0.435f, 0.602f, 0.223f,
		0.310f, 0.747f, 0.185f,
		0.597f, 0.770f, 0.761f,
		0.559f, 0.436f, 0.730f,
		0.359f, 0.583f, 0.152f,
		0.483f, 0.596f, 0.789f,
		0.559f, 0.861f, 0.639f,
		0.195f, 0.548f, 0.859f,
		0.014f, 0.184f, 0.576f,
		0.771f, 0.328f, 0.970f,
		0.406f, 0.615f, 0.116f,
		0.676f, 0.977f, 0.133f,
		0.971f, 0.572f, 0.833f,
		0.140f, 0.616f, 0.489f,
		0.997f, 0.513f, 0.064f,
		0.945f, 0.719f, 0.592f,
		0.543f, 0.021f, 0.978f,
		0.279f, 0.317f, 0.505f,
		0.167f, 0.620f, 0.077f,
		0.347f, 0.857f, 0.137f,
		0.055f, 0.953f, 0.042f,
		0.714f, 0.505f, 0.345f,
		0.783f, 0.290f, 0.734f,
		0.722f, 0.645f, 0.174f,
		0.302f, 0.455f, 0.848f,
		0.225f, 0.587f, 0.040f,
		0.517f, 0.713f, 0.338f,
		0.053f, 0.959f, 0.120f,
		0.393f, 0.621f, 0.362f,
		0.673f, 0.211f, 0.457f,
		0.820f, 0.883f, 0.371f,
		0.982f, 0.099f, 0.879f
	};

	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

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
		0.0f, 1.0f, 0.0f,
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


}

