#include "Shader.h"
#include "Utility.h"
#include <cstdio>
Shader::Shader(const char* vsfpath, const char* fsfpath)
{
	loadAndBind(vsfpath, fsfpath);
}

void Shader::loadAndBind(const char* vsfpath, const char* fsfpath)
{
	if(shaderProgram != 0) glDeleteProgram(shaderProgram);
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLchar* vertexSource = readAllFile(vsfpath);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	GLchar* fragmentSource = readAllFile(fsfpath);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	delete []vertexSource;
	delete []fragmentSource;
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
}

Shader::~Shader()
{
	if(shaderProgram != 0) glDeleteProgram(shaderProgram);
}

void Shader::use()
{
	if(shaderProgram != 0) glUseProgram(shaderProgram);
}

GLuint Shader::getShaderProgram()
{
	return shaderProgram;
}
GLint Shader::getUniformLocation(const char* name) const
{
	return glGetUniformLocation(shaderProgram, name);
}
GLint Shader::getAttribLocation(const char* name) const
{
	return glGetAttribLocation(shaderProgram, name);
}
