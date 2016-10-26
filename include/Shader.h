#pragma once
#include <GL/glew.h>
class Shader{
	GLuint shaderProgram = 0;
public:
	/**
	 *	@breif		Constructs a shader program from 2 shader files
	 */
	Shader(const char*, const char*);
	Shader()=default;
	~Shader();
	/**
	 *	@breif		Make openGL uses this shaderprogram
	 */
	void use();
	/**
	 *	@breif		Returns an OpenGL reference to the shader program
	 */
	GLuint getShaderProgram();
	/**
	 *	@breif		Returns a reference for a location of an uniform variable in the shader program
	 */
	GLint getUniformLocation(const char*) const;
	/**
	 *	@breif		Returns a reference for a location of an attribute in the shader program
	 */
	GLint getAttribLocation(const char*) const;
	/**
	 *	@breif		Loads a vertex and fragment shader from two given paths, creates and binds the program to the private shaderProgram variable.
	 */
	void loadAndBind(const char* vsPath, const char* fsPath);
};
