#pragma once
#include <GL/glew.h>
#include <vector>
#include "ResourceManager.h"
class CubeMap{
	GLuint cubeVAO, cubeVBO;
	GLuint skyboxVAO, skyboxVBO;
	GLuint cubemapTexture;


	void setupBuffers();
	GLuint loadCubemap(std::vector<const GLchar*>& facesTextures);
public:
	void draw();
	CubeMap(std::vector<const GLchar*>& facesTextures);
};
