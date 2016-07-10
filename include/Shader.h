#pragma once
#include <GL/glew.h>
class Shader{
	GLuint shaderProgram = 0;
public:
	/**
	 *	@breif		Constructs a shader program from 2 shader files
	 */
	Shader(const char*, const char*);
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
};
