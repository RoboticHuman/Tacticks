#pragma once
#include <vector>
#include <string>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <cstdint>
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
	 Mesh(std::vector<Vertex> &vertices, std::vector<uint32_t> &indices,std::vector<std::string>& texturePaths);
	 bool raycast(const glm::vec3& start, const glm::vec3& end, float& tmin	, glm::mat4& globalTransform);
protected:
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	std::vector<std::string> texturePaths;
};
