#include <GL/glew.h>
#include <vector>
#include <string>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>

using namespace std;
class Shader;

#pragma once

class Mesh
{

public:
	/**
	 * @brief      This function is responsible for issuing the draw calls
	 *
	 * @param[in]  shader  The shader program to use for drawing the mesh
	 * @param[in]  parentTransform  The transform of the parent
	 */
	virtual void draw(Shader *shader) = 0;
	// $$$$$$$$$$$$$$
	// TESTING PUT BACK IN PRIVATE
	vector<GLuint> indices;

protected:
	//OpenGL buffers
	//Vertex array, Vertext buffer and Element Buffer
	GLuint VAO, VBO, EBO;

	glm::mat4& globalTransform;
	/**
	 * @brief      Setup the necessary buffers to receive the data loaded into the mesh
	 */
	virtual void setupBuffers() = 0;
	Mesh (glm::mat4& parentTransform):globalTransform(parentTransform){};
};
