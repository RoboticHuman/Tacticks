#pragma once
#include <GL/glew.h>
class Shader{
	GLuint shaderProgram = 0;
public:
	Shader(const char*, const char*);
	~Shader();
	void use();
	GLuint getShaderProgram();
	GLint getUniformLocation(const char*) const;
	GLint getAttribLocation(const char*) const;
};
