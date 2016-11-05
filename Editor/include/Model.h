#pragma once
#include <GL/glew.h>
#include <vector>
#include <string>
#include <map>
#include <SOIL/SOIL.h>
#include "Mesh.h"
#include <assimp/matrix4x4.h>
#include <glm/vec3.hpp>
using namespace std;

class aiNode;
class aiScene;
class aiMesh;
class aiString;

struct Node
{
	glm::mat4 transformation;
	vector<int> meshes;
	vector<Node*> nodes;
	vector<Mesh>* meshReferences;
};

class Model
{
public:
	/**
	 * @brief      Model constructor to load the entire model with all its sub-meshes from a file path
	 *
	 * @param[in]  path  The path to the model file
	 */
	Model(string path);

	Model();
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
	vector<Mesh> meshes;
	vector<Model> nodes;
	glm::mat4 globalTransform;
	string containingDir;
	vector<Texture> texturesLoaded;
	void copyAiMat(const aiMatrix4x4 *from, glm::mat4 &to);

	map<string, int> loadedTexturePaths;
	/**
	 * @brief      This function starts the loading process and is called by the constructor
	 *
	 * @param[in]  path  The path to the model passed from the constructor
	 */
	void loadModel(string path);
	/**
	 * @brief      This function is responsible for traversing ASSIMP's tree to preserve parent-child relations
	 *
	 * @param      node   The node
	 * @param[in]  scene  ASSIMP's scene data structure
	 */
	void processNode(aiNode* node, const aiScene* scene,Model& rootNode);
	/**
	 * @brief      Loads an internal mesh and does the binding of buffers and and textures.
	 *
	 * @param      node   The node
	 * @param[in]  scene  The scene
	 *
	 * @return     A mesh fully loaded in OpenGl with texture binding to be stored in teh meshes vector.
	 */
	Mesh loadMesh(aiMesh* node, const aiScene* scene);
	/**
	 * @brief      Function that does necessary texture and uniform samplers setup
	 *
	 * @param[in]  path           The path to the texture obtained from ASSIMP in "loadMesh"
	 * @param[in]  containingDir  The containing dir name
	 *
	 * @return     an unsigned int handle of the texture for OpenGL
	 */
	GLuint textureFromFile(const char* path, string containingDir);
};
