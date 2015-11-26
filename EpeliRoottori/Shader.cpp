#include "Shader.h"
#include <fstream>

Shader::Shader()
{
}


Shader::~Shader()
{
}

bool Shader::Init()
{
	glewInit();
	//luodaan ohjelma
	ProgramID = glCreateProgram();

	//ladataan vertex Shader
	VertexShaderID = LoadShaderFromFile("../data/VertexShader.glvs", GL_VERTEX_SHADER);

	//tarkastetaan errorit
	if (VertexShaderID == NULL)
	{
		std::cout << "error while loading VertexShader" << VertexShaderID << "\n on line " << __LINE__ << std::endl;
		glDeleteProgram(ProgramID);
		ProgramID = 0;
		return false;
	}


	//Vertex shaderin kiinnitys ohjelmaan
	glAttachShader(ProgramID, VertexShaderID);

	//ladataan Fragment Shader
	FragmentShaderID = LoadShaderFromFile("../data/FragmentShader.glfs", GL_FRAGMENT_SHADER);

	//tarkastetaan errorit
	if (FragmentShaderID == NULL)
	{
		std::cout << "error while loading FragmentShader" << FragmentShaderID << "\n on line " << __LINE__ << std::endl;
		glDeleteShader(VertexShaderID);
		glDeleteProgram(ProgramID);
		ProgramID = NULL;
		return false;
	}

	//Fragment Shaderin kiinnitys ohjelmaan
	glAttachShader(ProgramID, FragmentShaderID);

	//ohjelman linkkaus
	glLinkProgram(ProgramID);

	//tarkastetaan errorit
	GLint LinkSuccess = GL_TRUE;
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &LinkSuccess);

	if (LinkSuccess != GL_TRUE)
	{
		std::cout << "error while linking program: " << ProgramID << std::endl;
		glDeleteShader(VertexShaderID);
		glDeleteShader(FragmentShaderID);
		glDeleteProgram(ProgramID);
		ProgramID = NULL;
		return false;
	}

	//poistetaan turhat shader referenssit, GL s�ilytt�� ne automaattisesti mik�li ne ovat ohjelman k�yt�ss�
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return true;
}

GLuint Shader::LoadShaderFromFile(const std::string filepath, GLenum ShaderType)
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

	return ShaderID;

}

void Shader::Use()
{
	glUseProgram(this->ProgramID);
}

GLuint Shader::GetShaderProgram()
{
	return ProgramID;
}

Shader &Shader::setActive()
{
	glUseProgram(this->ProgramID);
	return *this;
}

//void Shader::setFloat(const GLchar *name, GLfloat value, GLboolean useShader = false)
//{
//	if (useShader)
//		this->Use();
//	glUniform1f(glGetUniformLocation(this->ProgramID, name), value);
//}
//
//void Shader::setInteger(const GLchar *name, GLfloat value, GLboolean useShader = false)
//{
//	if (useShader)
//		this->Use();
//	glUniform1i(glGetUniformLocation(this->ProgramID, name), value);
//}
