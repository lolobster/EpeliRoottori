#include "Renderer.h"
#include <fstream>

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

bool Renderer::Init()
{
	glewInit();
	//luodaan ohjelma
	ProgramID = glCreateProgram();

	try
	{
		//ladataan vertex Shader
		VertexShader = LoadShaderFromFile("../data/VertexShader.glvs", GL_VERTEX_SHADER);

		//tarkastetaan errorit
		if (VertexShader == NULL)
		{
			std::cout << "error while loading VertexShader" << VertexShader << "\n on line " << __LINE__ << std::endl;
			glDeleteProgram(ProgramID);
			ProgramID = 0;
			return false;
		}
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR WHILE LOADING VERTEX_SHADER!" << std::endl;
	}


	//Vertex shaderin kiinnitys ohjelmaan
	glAttachShader(ProgramID, VertexShader);


	try
	{
		//ladataan Fragment Shader
		FragmentShader = LoadShaderFromFile("../data/FragmentShader.glfs", GL_FRAGMENT_SHADER);

		//tarkastetaan errorit
		if (FragmentShader == NULL)
		{
			std::cout << "error while loading VertexShader" << FragmentShader << "\n on line " << __LINE__ << std::endl;
			glDeleteShader(VertexShader);
			glDeleteProgram(ProgramID);
			ProgramID = NULL;
			return false;
		}
	}

	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR WHILE LOADING FRAGMENT_SHADER!" << std::endl;
	}


	//Fragment Shaderin kiinnitys ohjelmaan
	glAttachShader(ProgramID, FragmentShader);

	//ohjelman linkkaus
	glLinkProgram(ProgramID);

	//tarkastetaan errorit
	GLint LinkSuccess = GL_TRUE;
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &LinkSuccess);

	if (LinkSuccess != GL_TRUE)
	{
		std::cout << "error while linking program: " << ProgramID << std::endl;
		glDeleteShader(VertexShader);
		glDeleteShader(FragmentShader);
		glDeleteProgram(ProgramID);
		ProgramID = NULL;
		return false;
	}

	//poistetaan turhat shader referenssit, GL säilyttää jos ovat ohjelman käytössä
	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);

	return true;
}

GLuint Renderer::LoadShaderFromFile(const std::string filepath, GLenum ShaderType)
{
	GLuint ShaderID = NULL;
	std::string ShaderString;
	std::ifstream SourceFile(filepath.c_str());

	if (SourceFile)
	{
		ShaderString.assign((std::istreambuf_iterator< char >(SourceFile)), std::istreambuf_iterator<char>());
	}
	else
	{
		std::cout << "unable to open source file" << std::endl;
	}

	//shaderille ID
	ShaderID = glCreateShader(ShaderType);

	//shaderin source
	const GLchar* ShaderSource = ShaderString.c_str();
	glShaderSource(ShaderID, 1, (const GLchar**)&ShaderSource, NULL);

	//shaderin compilaus
	glCompileShader(ShaderID);

	//tarkastusta virheiden varalta
	GLint ShaderCompiled = GL_FALSE;
	glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &ShaderCompiled);

	if (ShaderCompiled != GL_TRUE)
	{
		std::cout << "Unable to compile shader \n" << ShaderID << "\n Source: \n" << ShaderSource << std::endl;
		glDeleteShader(ShaderID);
		ShaderID = NULL;
	}
	//else
	//{
	//	std::cout << "unable to open shader file" << filepath.c_str() << std::endl;
	//}

	return ShaderID;

}

void Renderer::OurShader()
{
	glUseProgram(this->ProgramID);
}