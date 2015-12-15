#define GLM_FORCE_RADIANS
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>


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
#include "TextManager.h"
#include "Camera.h"
#include "TextureManager.h"
#include "AnimationManager.h"
#include "Polygon.h"
#include "Sprite.h"
#include "Timer.h"

// Ikkunan koko
const GLuint WIDTH = 1200, HEIGHT = 800;

//testground

void key_callback(GLFWwindow* Window, int Key, int ScanCode, int Action, int Mode);
void LateTesti(GLFWwindow* Window, const GLuint width, const GLuint height);
void LateTesti2(GLFWwindow* Window, const GLuint width, const GLuint height);
void TaskuTesti(GLFWwindow* Window, const GLuint width, const GLuint height);
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

	//(Shader shader;
	//shader.Init();
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	Timer time;
	time.start();

	LateTesti(window, WIDTH, HEIGHT);
	//TaskuTesti(window, WIDTH, HEIGHT);

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
	Renderer renderer = { glm::vec2(width, height) };
	Renderer renderer2 = { glm::vec2(width * 2, height * 2) };
	Renderer renderer3 = { glm::vec2(width * 4, height * 4) };

	AnimationManager anima;
	TextManager tex;
	tex.LoadFont("..//data//arial.ttf");
	tex.SetText("0");
	tex.SetCharacterSize(30);
	tex.SetPosition(glm::vec2(10, 0));
	tex.SetColor(glm::vec3(0.0, 0.0, 1.0));

	TextManager tex2;
	tex2.LoadFont("..//data//arial.ttf");
	tex2.SetText("0");
	tex2.SetCharacterSize(30);
	tex2.SetPosition(glm::vec2(width - tex2.GetGlobalBounds().x, 0));
	tex2.SetColor(glm::vec3(0.0, 1.0, 0.0));


	TextManager tex3;
	tex3.LoadFont("..//data//Arctik5.ttf");
	tex3.SetText("Pong");
	tex3.SetCharacterSize(30);
	tex3.SetPosition(glm::vec2(width / 2.5, 0));
	tex3.SetColor(glm::vec3(0.0, 0.0, 0.0));

	Sprite typhlosion;
	typhlosion.SetTexture("../data/Typhlosion.png");
	typhlosion.SetPosition(glm::vec2((width - typhlosion.GetBounds().x) / 2, (height - typhlosion.GetBounds().y) / 2));
	typhlosion.SetScale(glm::vec2(0.5, 0.5));

	Sprite dickbutt;
	dickbutt.SetTexture("../data/Dickbutt.png");
	dickbutt.SetColor(glm::vec3(0.0, 0.0, 1.0));
	dickbutt.SetPosition(glm::vec2(0, (height - dickbutt.GetBounds().y) / 2));

	Sprite dickbutt2;
	dickbutt2.SetTexture("../data/Dickbutt.png");
	dickbutt2.SetColor(glm::vec3(0.0, 1.0, 0.0));
	dickbutt2.SetPosition(glm::vec2(width - dickbutt.GetBounds().x, (height - dickbutt.GetBounds().y) / 2));

	Sprite animation;
	animation.SetAnimation("../data/crystal_pink.png", "../data/anim_test.xml");
	animation.SetPosition(glm::vec2((width / 2), 250));

	renderer2.cam->setPosition(glm::vec2(1, 1));
	renderer3.cam->setPosition(glm::vec2(1.5, 1.5));

	glm::vec2 dir = { 2.0, 2.0 }, dir2 = { 0.0, 1.0 }, dir3 = { 0.0, -1.0 };
	int score1 = 0, score2 = 0;
	glm::vec3 color = { 0.01, 0.01, 0.01 };

	Polygon polygon(8, 200, 1, 0, 350, 350, 1.0f, 0.4f, 0.3f);

	while (!glfwWindowShouldClose(Window))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.2f, 0.2f, 1.0f);

		// Typhlosion koskettaa vasenta tai oikeaa seinää
		if (typhlosion.GetPosition().x > width)
		{
			typhlosion.SetPosition(glm::vec2((width - typhlosion.GetBounds().x) / 2, (height - typhlosion.GetBounds().y) / 2));
			dir.x = -2.0;
			score1++;
			tex.SetText(std::to_string(score1));
		}
		if (typhlosion.GetPosition().x + typhlosion.GetGlobalBounds().x < 0)
		{
			typhlosion.SetPosition(glm::vec2((width - typhlosion.GetBounds().x) / 2, (height - typhlosion.GetBounds().y) / 2));
			dir.x = 2.0;
			score2++;
			tex2.SetText(std::to_string(score2));
			tex2.SetPosition(glm::vec2(width - tex2.GetGlobalBounds().x, 0));
		}

		// Typhlosion kimpoaa katosta ja lattiasta
		if (typhlosion.GetPosition().y + typhlosion.GetGlobalBounds().y > height)
		{
			dir.y = -2.0;
		}
		if (typhlosion.GetPosition().y < 0)
		{
			dir.y = 2.0;
		}

		// Typhlosion törmää dickbuttien sivuihin
		// Dickbutt1
		if (dickbutt.GetPosition().y + dickbutt.GetGlobalBounds().y > typhlosion.GetPosition().y && dickbutt.GetPosition().y + dickbutt.GetGlobalBounds().y - 5 < typhlosion.GetPosition().y && dickbutt.GetPosition().x < typhlosion.GetPosition().x && dickbutt.GetPosition().x + dickbutt.GetGlobalBounds().x > typhlosion.GetPosition().x || dickbutt.GetPosition().y + dickbutt.GetGlobalBounds().y > typhlosion.GetPosition().y && dickbutt.GetPosition().y + dickbutt.GetGlobalBounds().y - 5 < typhlosion.GetPosition().y && dickbutt.GetPosition().x < typhlosion.GetPosition().x + typhlosion.GetGlobalBounds().x && dickbutt.GetPosition().x + dickbutt.GetGlobalBounds().x > typhlosion.GetPosition().x + typhlosion.GetGlobalBounds().x)
		{
			dir.y = 2.0;
		}
		else if (dickbutt.GetPosition().y < typhlosion.GetPosition().y + typhlosion.GetGlobalBounds().y && dickbutt.GetPosition().y + 5 > typhlosion.GetPosition().y + typhlosion.GetGlobalBounds().y && dickbutt.GetPosition().x < typhlosion.GetPosition().x && dickbutt.GetPosition().x + dickbutt.GetGlobalBounds().x > typhlosion.GetPosition().x || dickbutt.GetPosition().y < typhlosion.GetPosition().y + typhlosion.GetGlobalBounds().y && dickbutt.GetPosition().y + 5 > typhlosion.GetPosition().y + typhlosion.GetGlobalBounds().y && dickbutt.GetPosition().x < typhlosion.GetPosition().x + typhlosion.GetGlobalBounds().x && dickbutt.GetPosition().x + dickbutt.GetGlobalBounds().x > typhlosion.GetPosition().x + typhlosion.GetGlobalBounds().x)
		{
			dir.y = -2.0;
		}
		else if (dickbutt.GetPosition().x + dickbutt.GetGlobalBounds().x > typhlosion.GetPosition().x && dickbutt.GetPosition().y < typhlosion.GetPosition().y && dickbutt.GetPosition().y + dickbutt.GetGlobalBounds().y > typhlosion.GetPosition().y || dickbutt.GetPosition().x + dickbutt.GetGlobalBounds().x > typhlosion.GetPosition().x && dickbutt.GetPosition().y < typhlosion.GetPosition().y + typhlosion.GetGlobalBounds().y && dickbutt.GetPosition().y + dickbutt.GetGlobalBounds().y > typhlosion.GetPosition().y + typhlosion.GetGlobalBounds().y)
		{
			dir.x = 2.0;
		}

		// Typhlosion törmää dickbuttien sivuihin
		// Dickbutt2
		if (dickbutt2.GetPosition().y + dickbutt2.GetGlobalBounds().y > typhlosion.GetPosition().y && dickbutt2.GetPosition().y + dickbutt2.GetGlobalBounds().y - 5 < typhlosion.GetPosition().y && dickbutt2.GetPosition().x < typhlosion.GetPosition().x && dickbutt2.GetPosition().x + dickbutt2.GetGlobalBounds().x > typhlosion.GetPosition().x || dickbutt2.GetPosition().y + dickbutt2.GetGlobalBounds().y > typhlosion.GetPosition().y && dickbutt2.GetPosition().y + dickbutt2.GetGlobalBounds().y - 5 < typhlosion.GetPosition().y && dickbutt2.GetPosition().x < typhlosion.GetPosition().x + typhlosion.GetGlobalBounds().x && dickbutt2.GetPosition().x + dickbutt2.GetGlobalBounds().x > typhlosion.GetPosition().x + typhlosion.GetGlobalBounds().x)
		{
			dir.y = 2.0;
		}
		else if (dickbutt2.GetPosition().y < typhlosion.GetPosition().y + typhlosion.GetGlobalBounds().y && dickbutt2.GetPosition().y + 5 > typhlosion.GetPosition().y + typhlosion.GetGlobalBounds().y && dickbutt2.GetPosition().x < typhlosion.GetPosition().x && dickbutt2.GetPosition().x + dickbutt2.GetGlobalBounds().x > typhlosion.GetPosition().x || dickbutt2.GetPosition().y < typhlosion.GetPosition().y + typhlosion.GetGlobalBounds().y && dickbutt2.GetPosition().y + 5 > typhlosion.GetPosition().y + typhlosion.GetGlobalBounds().y && dickbutt2.GetPosition().x < typhlosion.GetPosition().x + typhlosion.GetGlobalBounds().x && dickbutt2.GetPosition().x + dickbutt2.GetGlobalBounds().x > typhlosion.GetPosition().x + typhlosion.GetGlobalBounds().x)
		{
			dir.y = -2.0;
		}
		else if (dickbutt2.GetPosition().x < typhlosion.GetPosition().x + typhlosion.GetGlobalBounds().x && dickbutt2.GetPosition().y < typhlosion.GetPosition().y && dickbutt2.GetPosition().y + dickbutt2.GetGlobalBounds().y > typhlosion.GetPosition().y || dickbutt2.GetPosition().x < typhlosion.GetPosition().x + typhlosion.GetGlobalBounds().x && dickbutt2.GetPosition().y < typhlosion.GetPosition().y + typhlosion.GetGlobalBounds().y && dickbutt2.GetPosition().y + dickbutt2.GetGlobalBounds().y > typhlosion.GetPosition().y + typhlosion.GetGlobalBounds().y)
		{
			dir.x = -2.0;
		}

		// Dickbutt1 liikkumiset
		if (dickbutt.GetPosition().y < 0)
		{
			dir2 = { 0.0, 1.0 };
		}
		if (dickbutt.GetPosition().y + dickbutt.GetGlobalBounds().y > height)
		{
			dir2 = { 0.0, -1.0 };
		}

		// Dickbutt2 liikkumiset
		if (dickbutt2.GetPosition().y < 0)
		{
			dir3 = { 0.0, 1.0 };
		}
		if (dickbutt2.GetPosition().y + dickbutt2.GetGlobalBounds().y > height)
		{
			dir3 = { 0.0, -1.0 };
		}

		if (tex3.GetColor().x < 0)
		{
			color = glm::vec3(0.01, 0.01, 0.01);
		}
		if (tex3.GetColor().x > 1)
		{
			color = glm::vec3(-0.01, -0.01, -0.01);
		}

		tex3.SetColor(tex3.GetColor() + color);

		typhlosion.Rotate(1);
		typhlosion.Move(dir);
		dickbutt.Move(dir2);
		dickbutt2.Move(dir3);

		//renderer3.draw(typhlosion);
		//renderer3.draw(dickbutt);
		//renderer3.draw(dickbutt2);
		//renderer3.draw(tex);
		//renderer3.draw(tex2);
		//renderer3.draw(tex3);

		//renderer2.draw(typhlosion);
		//renderer2.draw(dickbutt);
		//renderer2.draw(dickbutt2);
		//renderer2.draw(tex);
		//renderer2.draw(tex2);
		//renderer2.draw(tex3);

		renderer.draw(typhlosion);
		renderer.draw(dickbutt);
		renderer.draw(dickbutt2);
		renderer.draw(tex);
		renderer.draw(tex2);
		renderer.draw(tex3);
		renderer.draw(polygon);
	
		renderer.drawAnimation(animation);
		animation.GetAnimationManager()->updateAnimation();
		//anima.updateAnimation();
		/*
		
		p.drawPolygon(6, 1, 100, 0, vec2(300, 700), vec3(0.0f, 0.0f, 0.0f));
		p.drawPolygon(3, 1, 100, 0, vec2(500, 1000), vec3(1.0f, 0.0f, 0.0f));
		p.drawPolygon(4, 1, 100, 0, vec2(700, 500), vec3(1.0f, 1.0f, 0.0f));
		p.drawPolygon(56, 1, 100, 0, vec2(800, 250), vec3(0.0f, 0.0f, 1.0f));
		p.drawPolygon(68, 1, 100, 0, vec2(400, 400), vec3(1.0f, 0.0f, 0.0f));
		*/

		glDisable(GL_TEXTURE_2D);
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

void TaskuTesti(GLFWwindow* Window, const GLuint width, const GLuint height)
{
	Shader shader;
	shader.Init();

	//-----------------------------------------------------//

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
		-0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,	/*0.0f, 0.0f,*/
		 0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	/*1.0f, 0.0f,*/
		 0.5f, 0.5f, -0.5f,		0.0f, 0.0f, 1.0f,	/*1.0f, 1.0f,*/
		 0.5f, 0.5f, -0.5f,		0.3f, 0.3f, 0.3f,	/*1.0f, 1.0f,*/
		-0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 0.0f,	/*0.0f, 1.0f,*/
		-0.5f, -0.5f, -0.5f,	0.3f, 0.3f, 0.3f,	/*0.0f, 0.0f,*/

		-0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	/*0.0f, 0.0f,*/
		0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	/*1.0f, 0.0f,*/
		0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	/*1.0f, 1.0f,*/
		0.5f, 0.5f, 0.5f,		0.3f, 0.3f, 0.3f,	/*1.0f, 1.0f,*/
		-0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	/*0.0f, 1.0f,*/
		-0.5f, -0.5f, 0.5f,		0.3f, 0.3f, 0.3f,	/*0.0f, 0.0f,*/

		-0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	/*1.0f, 0.0f,*/
		-0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	/*1.0f, 1.0f,*/
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	/*0.0f, 1.0f,*/
		-0.5f, -0.5f, -0.5f,	0.3f, 0.3f, 0.3f,	/*0.0f, 1.0f,*/
		-0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	/*0.0f, 0.0f,*/
		-0.5f, 0.5f, 0.5f,		0.3f, 0.3f, 0.3f,	/*1.0f, 0.0f,*/

		0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	/*1.0f, 0.0f,*/
		0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	/*1.0f, 1.0f,*/
		0.5f, -0.5f, -0.5f,		0.0f, 0.0f, 1.0f,	/*0.0f, 1.0f,*/
		0.5f, -0.5f, -0.5f,		0.3f, 0.3f, 0.3f,	/*0.0f, 1.0f,*/
		0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	/*0.0f, 0.0f,*/
		0.5f, 0.5f, 0.5f,		0.3f, 0.3f, 0.3f,	/*1.0f, 0.0f,*/

		-0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,	/*0.0f, 1.0f,*/
		0.5f, -0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	/*1.0f, 1.0f,*/
		0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 0.1f,	/*1.0f, 0.0f,*/
		0.5f, -0.5f, 0.5f,		0.3f, 0.3f, 0.3f,	/*1.0f, 0.0f,*/
		-0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	/*0.0f, 0.0f, */
		-0.5f, -0.5f, -0.5f,	0.3f, 0.3f, 0.3f,	/*0.0f, 1.0f,*/

		-0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 0.0f,	/*0.0f, 1.0f,*/
		0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	/*1.0f, 1.0f,*/
		0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	/*1.0f, 0.0f,*/
		0.5f, 0.5f, 0.5f,		0.3f, 0.3f, 0.3f,	/*1.0f, 0.0f,*/
		-0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	/*0.0f, 0.0f, */
		-0.5f, 0.5f, -0.5f,		0.3f, 0.3f, 0.3f,	/*0.0f, 1.0f*/
	};
	
	//static const GLfloat g_color_buffer_data[] = {
	//	0.583f, 0.771f, 0.014f,
	//	0.609f, 0.115f, 0.436f,
	//	0.327f, 0.483f, 0.844f,
	//	0.822f, 0.569f, 0.201f,
	//	0.435f, 0.602f, 0.223f,
	//	0.310f, 0.747f, 0.185f,
	//	0.597f, 0.770f, 0.761f,
	//	0.559f, 0.436f, 0.730f,
	//	0.359f, 0.583f, 0.152f,
	//	0.483f, 0.596f, 0.789f,
	//	0.559f, 0.861f, 0.639f,
	//	0.195f, 0.548f, 0.859f,
	//	0.014f, 0.184f, 0.576f,
	//	0.771f, 0.328f, 0.970f,
	//	0.406f, 0.615f, 0.116f,
	//	0.676f, 0.977f, 0.133f,
	//	0.971f, 0.572f, 0.833f,
	//	0.140f, 0.616f, 0.489f,
	//	0.997f, 0.513f, 0.064f,
	//	0.945f, 0.719f, 0.592f,
	//	0.543f, 0.021f, 0.978f,
	//	0.279f, 0.317f, 0.505f,
	//	0.167f, 0.620f, 0.077f,
	//	0.347f, 0.857f, 0.137f,
	//	0.055f, 0.953f, 0.042f,
	//	0.714f, 0.505f, 0.345f,
	//	0.783f, 0.290f, 0.734f,
	//	0.722f, 0.645f, 0.174f,
	//	0.302f, 0.455f, 0.848f,
	//	0.225f, 0.587f, 0.040f,
	//	0.517f, 0.713f, 0.338f,
	//	0.053f, 0.959f, 0.120f,
	//	0.393f, 0.621f, 0.362f,
	//	0.673f, 0.211f, 0.457f,
	//	0.820f, 0.883f, 0.371f,
	//	0.982f, 0.099f, 0.879f
	//};
	//

	//GLuint colorbuffer;
	//glGenBuffers(1, &colorbuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

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

	//static const GLfloat g_vertex_buffer_data[] = {
	//	-1.0f, -1.0f, 0.0f,
	//	1.0f, -1.0f, 0.0f,
	//	0.0f, 1.0f, 0.0f,
	//};

	//GLuint indices[] = {
	//	0, 1, 2,	//3, 2, 0, // first triangle
	//	3, 4, 5,	//3, 1, 0,  // second triangle
	//	6, 7, 8, // first triangle
	//	9, 10, 11, // second triangle
	//	12
	//};

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

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//unbind VAO
	glBindVertexArray(0);
	

	//-----------------Camera--------------------//

	GLuint MatrixID = glGetUniformLocation(shader.GetShaderProgram(), "MVP");
	
	//Camera cam;

	//cam.initialize();

	GLfloat distance = 0.0;
	bool direction = false;
	GLfloat angle = 0.0f;

	//-------------------------------------------------------//

	while (!glfwWindowShouldClose(Window))
		{
			glfwPollEvents();

			glClearColor(0.2f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		

			shader.Use();

			if (distance > 0.5)
			{
				direction = false;
			}
			else if (distance < -0.5)
			{
				direction = true;
			}

			if (direction == true)
			{
				//cam.setPosition(distance);
				distance += 0.001;

				//cam.setRotation(angle);
				angle += 0.005f;
			}
			else if (direction == false)
			{
				//cam.setPosition(distance);
				distance -= 0.001;	

				//cam.setRotation(angle);
				angle += 0.005f;
			}


			//mat4 MVP = cam.getViewMatrix();
			
			//MVP;
			//glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

			glBindVertexArray(VAO);
			
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0);

			
			glBindVertexArray(0);



			// Swap the screen buffers
			glfwSwapBuffers(Window);			
		}
	// ---- Create transformation ---- //
	
	
	
}

