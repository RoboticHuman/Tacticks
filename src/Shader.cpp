#include "Shader.h"
#include "Utility.h"

Shader::Shader(const char* vsfpath, const char* fsfpath)
{
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
