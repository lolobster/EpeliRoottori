
#define GLM_FORCE_PURE
#include "../EpeliRoottori/AnimationManager.h"
#include "../EpeliRoottori/Camera.h"
#include "../EpeliRoottori/Polygon.h"
#include "../EpeliRoottori/Renderer.h"
#include "../EpeliRoottori/Shader.h"
#include "../EpeliRoottori/TextManager.h"
#include "../EpeliRoottori/TextureManager.h"
#include "../EpeliRoottori/Sprite.h"

// GLEW
#define GLEW_STATIC
#include "../3rdparty/include/GL/glew.h"
#include "../3rdparty/include/GLFW/glfw3.h"
#include "../3rdparty/include/glm/glm.hpp"



// Ikkunan koko
const GLuint width = 1200, height = 800;

void key_callback(GLFWwindow* Window, int Key, int ScanCode, int Action, int Mode);

int main()
{

	glfwInit();				// Initialisoidaan GLFW

	// GLFW perusasetukset
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);			// asetetaan OpenGL-
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);			// versio 2.1
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);	// määritellään OpenGL profiili käytettäväksi
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);				// ikkunan kokoa ei voi muuttaa

	// luodaan ikkuna GLFWwindow
	GLFWwindow* window = glfwCreateWindow(width, height, "EPELIROOTTORI", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	glewExperimental = GL_TRUE;

	glewInit();				// Initialisoidaan GLEW

	glViewport(0, 0, width, height);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Renderer renderer = { glm::vec2(width, height) };
	Renderer renderer2 = { glm::vec2(width * 2, height * 2) };
	Renderer renderer3 = { glm::vec2(width * 4, height * 4) };

	AnimationManager anima;
	TextManager tex;
	tex.LoadFont("..//data/fonts/arial.ttf");
	tex.SetText("0");
	tex.SetCharacterSize(30);
	tex.SetPosition(glm::vec2(10, 0));
	tex.SetColor(glm::vec3(0.0, 0.0, 1.0));

	TextManager tex2;
	tex2.LoadFont("..//data/fonts/arial.ttf");
	tex2.SetText("0");
	tex2.SetCharacterSize(30);
	tex2.SetPosition(glm::vec2(width - tex2.GetGlobalBounds().x, 0));
	tex2.SetColor(glm::vec3(0.0, 1.0, 0.0));


	TextManager tex3;
	tex3.LoadFont("..//data/fonts/Arctik5.ttf");
	tex3.SetText("Pong");
	tex3.SetCharacterSize(30);
	tex3.SetPosition(glm::vec2(width / 2.5, 0));
	tex3.SetColor(glm::vec3(0.0, 0.0, 0.0));

	Sprite typhlosion;
	typhlosion.SetAnimation("../data/animations/Typhlosion2.png", glm::vec2(234, 250), 0.2);
	typhlosion.SetPosition(glm::vec2((width - typhlosion.GetBounds().x) / 2, (height - typhlosion.GetBounds().y) / 2));
	typhlosion.SetScale(glm::vec2(0.5, 0.5));

	Sprite kisse;
	kisse.SetTexture("../data/textures/kisse.png");
	kisse.SetColor(glm::vec3(0.0, 0.0, 1.0));
	kisse.SetPosition(glm::vec2(0, (height - kisse.GetBounds().y) / 2));

	Sprite kisse2;
	kisse2.SetTexture("../data/textures/kisse.png");
	kisse2.SetColor(glm::vec3(0.0, 1.0, 0.0));
	kisse2.SetPosition(glm::vec2(width - kisse.GetBounds().x, (height - kisse.GetBounds().y) / 2));

	Sprite animation;
	animation.SetAnimation("../data/animations/gems.png", "../data/animations/anim_gems.xml");
	animation.SetPosition(glm::vec2((width / 2), 250));
	animation.SetScale(glm::vec2(2, 2));

	renderer2.camera->SetPosition(glm::vec2(1, 1));
	renderer3.camera->SetPosition(glm::vec2(1.5, 1.5));

	glm::vec2 dir = { 2.0, 2.0 }, dir2 = { 0.0, 1.0 }, dir3 = { 0.0, -1.0 };
	int score1 = 0, score2 = 0;
	glm::vec3 color = { 0.01, 0.01, 0.01 };

	Polygon polygon(300, 200, 1, 0, 350, 350, 1.0f, 0.4f, 0.3f, "../data/textures/planet.png");
	Polygon polygon2(4, 100, 1, 0, 850, 350, 1.0f, 0.4f, 0.3f, "../data/textures/kisse.png");
	Timer time;
	time.Start();

	while (!glfwWindowShouldClose(window))
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

		// Typhlosion törmää kisseien sivuihin
		// kisse1
		if (kisse.GetPosition().y + kisse.GetGlobalBounds().y > typhlosion.GetPosition().y && kisse.GetPosition().y + kisse.GetGlobalBounds().y - 5 < typhlosion.GetPosition().y && kisse.GetPosition().x < typhlosion.GetPosition().x && kisse.GetPosition().x + kisse.GetGlobalBounds().x > typhlosion.GetPosition().x || kisse.GetPosition().y + kisse.GetGlobalBounds().y > typhlosion.GetPosition().y && kisse.GetPosition().y + kisse.GetGlobalBounds().y - 5 < typhlosion.GetPosition().y && kisse.GetPosition().x < typhlosion.GetPosition().x + typhlosion.GetGlobalBounds().x && kisse.GetPosition().x + kisse.GetGlobalBounds().x > typhlosion.GetPosition().x + typhlosion.GetGlobalBounds().x)
		{
			dir.y = 2.0;
		}
		else if (kisse.GetPosition().y < typhlosion.GetPosition().y + typhlosion.GetGlobalBounds().y && kisse.GetPosition().y + 5 > typhlosion.GetPosition().y + typhlosion.GetGlobalBounds().y && kisse.GetPosition().x < typhlosion.GetPosition().x && kisse.GetPosition().x + kisse.GetGlobalBounds().x > typhlosion.GetPosition().x || kisse.GetPosition().y < typhlosion.GetPosition().y + typhlosion.GetGlobalBounds().y && kisse.GetPosition().y + 5 > typhlosion.GetPosition().y + typhlosion.GetGlobalBounds().y && kisse.GetPosition().x < typhlosion.GetPosition().x + typhlosion.GetGlobalBounds().x && kisse.GetPosition().x + kisse.GetGlobalBounds().x > typhlosion.GetPosition().x + typhlosion.GetGlobalBounds().x)
		{
			dir.y = -2.0;
		}
		else if (kisse.GetPosition().x + kisse.GetGlobalBounds().x > typhlosion.GetPosition().x && kisse.GetPosition().y < typhlosion.GetPosition().y && kisse.GetPosition().y + kisse.GetGlobalBounds().y > typhlosion.GetPosition().y || kisse.GetPosition().x + kisse.GetGlobalBounds().x > typhlosion.GetPosition().x && kisse.GetPosition().y < typhlosion.GetPosition().y + typhlosion.GetGlobalBounds().y && kisse.GetPosition().y + kisse.GetGlobalBounds().y > typhlosion.GetPosition().y + typhlosion.GetGlobalBounds().y)
		{
			dir.x = 2.0;
		}

		// Typhlosion törmää kisseien sivuihin
		// kisse2
		if (kisse2.GetPosition().y + kisse2.GetGlobalBounds().y > typhlosion.GetPosition().y && kisse2.GetPosition().y + kisse2.GetGlobalBounds().y - 5 < typhlosion.GetPosition().y && kisse2.GetPosition().x < typhlosion.GetPosition().x && kisse2.GetPosition().x + kisse2.GetGlobalBounds().x > typhlosion.GetPosition().x || kisse2.GetPosition().y + kisse2.GetGlobalBounds().y > typhlosion.GetPosition().y && kisse2.GetPosition().y + kisse2.GetGlobalBounds().y - 5 < typhlosion.GetPosition().y && kisse2.GetPosition().x < typhlosion.GetPosition().x + typhlosion.GetGlobalBounds().x && kisse2.GetPosition().x + kisse2.GetGlobalBounds().x > typhlosion.GetPosition().x + typhlosion.GetGlobalBounds().x)
		{
			dir.y = 2.0;
		}
		else if (kisse2.GetPosition().y < typhlosion.GetPosition().y + typhlosion.GetGlobalBounds().y && kisse2.GetPosition().y + 5 > typhlosion.GetPosition().y + typhlosion.GetGlobalBounds().y && kisse2.GetPosition().x < typhlosion.GetPosition().x && kisse2.GetPosition().x + kisse2.GetGlobalBounds().x > typhlosion.GetPosition().x || kisse2.GetPosition().y < typhlosion.GetPosition().y + typhlosion.GetGlobalBounds().y && kisse2.GetPosition().y + 5 > typhlosion.GetPosition().y + typhlosion.GetGlobalBounds().y && kisse2.GetPosition().x < typhlosion.GetPosition().x + typhlosion.GetGlobalBounds().x && kisse2.GetPosition().x + kisse2.GetGlobalBounds().x > typhlosion.GetPosition().x + typhlosion.GetGlobalBounds().x)
		{
			dir.y = -2.0;
		}
		else if (kisse2.GetPosition().x < typhlosion.GetPosition().x + typhlosion.GetGlobalBounds().x && kisse2.GetPosition().y < typhlosion.GetPosition().y && kisse2.GetPosition().y + kisse2.GetGlobalBounds().y > typhlosion.GetPosition().y || kisse2.GetPosition().x < typhlosion.GetPosition().x + typhlosion.GetGlobalBounds().x && kisse2.GetPosition().y < typhlosion.GetPosition().y + typhlosion.GetGlobalBounds().y && kisse2.GetPosition().y + kisse2.GetGlobalBounds().y > typhlosion.GetPosition().y + typhlosion.GetGlobalBounds().y)
		{
			dir.x = -2.0;
		}

		// kisse1 liikkumiset
		if (kisse.GetPosition().y < 0)
		{
			dir2 = { 0.0, 1.0 };
		}
		if (kisse.GetPosition().y + kisse.GetGlobalBounds().y > height)
		{
			dir2 = { 0.0, -1.0 };
		}

		// kisse2 liikkumiset
		if (kisse2.GetPosition().y < 0)
		{
			dir3 = { 0.0, 1.0 };
		}
		if (kisse2.GetPosition().y + kisse2.GetGlobalBounds().y > height)
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

		polygon2.Rotate(1);
		polygon.DemoEffect(1);

		typhlosion.Rotate(1);
		typhlosion.Move(dir);
		kisse.Move(dir2);
		kisse2.Move(dir3);

		renderer.Draw(polygon);
		renderer.Draw(polygon2);

		renderer.Draw(typhlosion);
		renderer.Draw(kisse);
		renderer.Draw(kisse2);
		renderer.Draw(tex);
		renderer.Draw(tex2);
		renderer.Draw(tex3);



		renderer.Draw(animation);
		animation.GetAnimationManager()->UpdateAnimation();
		typhlosion.GetAnimationManager()->UpdateAnimation();


		glDisable(GL_TEXTURE_2D);
		glfwSwapBuffers(window);

	}
}

void key_callback(GLFWwindow* Window, int Key, int ScanCode, int Action, int Mode)
{
	if (Key == GLFW_KEY_ESCAPE && Action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(Window, GL_TRUE);
	}
}