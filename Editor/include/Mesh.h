#pragma once

#include <GL/glew.h>
#include <vector>
#include <string>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>

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
	 Mesh(vector<Vertex> &vertices, vector<GLuint> &indices, vector<Texture> &textures, glm::mat4& parentTransform);
	/**
	 * @brief      This function is responsible for issuing the draw calls
	 *
	 * @param[in]  shader  The shader program to use for drawing the mesh
	 * @param[in]  parentTransform  The transform of the parent
	 */
	void draw(Shader *shader, glm::mat4& globalTransform);
	/**
	 * @brief      Raycasts a ray with all triangles in a mesh
	 *
	 * @param[in]  start  start of the ray
	 * @param[in]  end  end of the ray
	 * @param      t  the scaling factor based on the distance of the hit point along the ray direction from the start of the ray.
	 *
	 * @return     Whether a hit was captured or not.
	 */
	bool raycast(const glm::vec3&, const glm::vec3&, float&, glm::mat4& globalTransform);
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
