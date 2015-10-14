#include "Renderer.h"
#include <fstream>

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::Init(GLFWwindow* win)
{
	Program = glCreateProgram();

	//VertexShader = LoadShaderFromFile("")

	//glAttachShader(Program, Vertexshader); <--- tarvii vertexshaderin 
	//glAttachShader(Program, Fragmentshader); <--- tarvii fragmentshadetrin

	//MatrixID = glGetUniformLocation(Program, "MVP"); //vähän kyssäri mitä tämän pitäisi tehdä




	/*GLFWwindow* window = win;
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//load vertex shader
	GLuint vertexShader = loadShaderFromFile();

	//GLuint programID = LoadShaderFromFile("VertexShader.vertexshader", "FragmentShader.fragmentshader");
	GLuint MVP_MatrixID = glGetUniformLocation(programID, "MVP");

	glGenVertexArrays(1, &VertexArrayID);

	TextureID = glGetUniformLocation(programID, "myTextureSampler");
	Texture = loadBMP_custom("./pointsprite.bmp");

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glDisable(GL_MULTISAMPLE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	*/
}

void Renderer::LoadShaderFromFile(std::string filepath, GLenum ShaderType)
{
	GLuint ShaderID = 0;
	std::string shaderString;
	std::ifstream sourceFile(filepath.c_str());

	if (sourceFile)
	{

	}
	else
	{
		std::cout << "unable to open source file" << std::endl;
	}




}
