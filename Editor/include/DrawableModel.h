#pragma once
#include <GL/glew.h>
#include <vector>
#include <string>
#include <map>
#include <SOIL/SOIL.h>
#include "DrawableMesh.h"
#include <assimp/matrix4x4.h>
#include <glm/vec3.hpp>

class aiNode;
class aiScene;
class aiMesh;
class aiString;
class Model;
class Mesh;

class DrawableModel
{
public:
	/**
	 * @brief      Model constructor to load the entire model with all its sub-meshes from a file path
	 *
	 * @param[in]  path  The path to the model file
	 */
	DrawableModel(Model* model);

	DrawableModel();
	~DrawableModel(){cleanup();}
	DrawableModel(DrawableModel&& oldmodel) ;
	void cleanup();
	/**
	 * @brief      The drawing function, it draws all the internal meshes of the model
	 *
	 * @param      shader  The shader used for drawing this model
	 */
	void draw(Shader *shader);

	bool raycast(const glm::vec3& start, const glm::vec3& end, glm::vec3& hitPos, float &tmin);

	void move(const glm::vec3 &offset);
	void setPosition(const glm::vec3 &newPosition);
private:
	Model* model;
	std::vector<DrawableMesh> meshes;
	std::vector<DrawableModel> nodes;
	std::map<std::string, Texture> texturesLoaded;

	/**
	 * @brief      This function starts the loading process and is called by the constructor
	 *
	 * @param[in]  path  The path to the model passed from the constructor
	 */
	void loadModel(Model* model);
	/**
	 * @brief      This function is responsible for traversing ASSIMP's tree to preserve parent-child relations
	 *
	 * @param      node   The node
	 * @param[in]  scene  ASSIMP's scene data structure
	 */
	void processNode(Model* model, DrawableModel& rootNode);
	/**
	 * @brief      Loads an internal mesh and does the binding of buffers and and textures.
	 *
	 * @param      node   The node
	 * @param[in]  scene  The scene
	 *
	 * @return     A mesh fully loaded in OpenGl with texture binding to be stored in teh meshes vector.
	 */
	DrawableMesh loadMesh(const Mesh* mesh);
	/**
	 * @brief      Function that does necessary texture and uniform samplers setup
	 *
	 * @param[in]  path           The path to the texture obtained from ASSIMP in "loadMesh"
	 * @param[in]  containingDir  The containing dir name
	 *
	 * @return     an unsigned int handle of the texture for OpenGL
	 */
	GLuint textureFromFile(std::string path);
};
