#pragma once

#include <GL/glew.h>
#include <vector>
#include <string>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>

using namespace std;
class Shader;
class Mesh;

/**
 * @brief      A texture vertex to reference the Texture id and its type.
 */
struct Texture{
	GLuint id;
	string type;
};

class DrawableMesh
{
	DrawableMesh() = delete;

public:
	/**
	 * @brief      Mesh contsructor to initialize per mesh components
	 *
	 * @param[in]  vertices  The vertices
	 * @param[in]  indices   The indices
	 * @param[in]  textures  The textures
	 */
	 DrawableMesh(vector<Texture> &textures, const Mesh* mesh);
	/**
	 * @brief      This function is responsible for issuing the draw calls
	 *
	 * @param[in]  shader  The shader program to use for drawing the mesh
	 * @param[in]  parentTransform  The transform of the parent
	 */
	void draw(Shader *shader, const glm::mat4& globalTransform);
	void cleanup();
private:
	//OpenGL buffers
	//Vertex array, Vertext buffer and Element Buffer
	GLuint VAO, VBO, EBO;
	int nIndices;
	vector<Texture> textures;
	/**
	 * @brief      Setup the necessary buffers to receive the data loaded into the mesh
	 */
	void setupBuffers(const Mesh* mesh);
};
