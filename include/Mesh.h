#pragma once

#include <GL/glew.h>
#include <vector>
#include <string>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
using namespace std;
class Shader;
/**
 * @brief      A vertex structure that holds per vertex info.
 */
struct Vertex{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};
/**
 * @brief      A texture vertex to reference the Texture id and its type.
 */
struct Texture{
	GLuint id;
	string type;
	string path;
};

class Mesh
{
	Mesh() = delete;
	
public:
	/**
	 * @brief      Mesh contsructor to initialize per mesh components
	 *
	 * @param[in]  vertices  The vertices
	 * @param[in]  indices   The indices
	 * @param[in]  textures  The textures
	 */
	Mesh(vector<Vertex> &vertices, vector<GLuint> &indices, vector<Texture> &textures);
	/**
	 * @brief      This function is responsible for issuing the draw calls
	 *
	 * @param[in]  shader  The shader program to use for drawing the mesh
	 */
	void draw(Shader shader);
private:
	//OpenGL buffers
	//Vertex array, Vertext buffer and Element Buffer
	GLuint VAO, VBO, EBO;
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;
	bool textureSetupDone = false;
	/**
	 * @brief      Setup the necessary buffers to receive the data loaded into the mesh
	 */
	void setupBuffers();
};




