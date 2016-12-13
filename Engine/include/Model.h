#pragma once
#include <vector>
#include <string>
#include <map>
#include <SOIL/SOIL.h>
#include "Mesh.h"
#include <assimp/matrix4x4.h>
#include <glm/vec3.hpp>
#include <map>
#include <assimp/Importer.hpp>
class aiNode;
class aiScene;
class aiMesh;
class aiString;
class Importer;

class Model
{
public:
	/**
	 * @brief      Model constructor to load the entire model with all its sub-meshes from a file path
	 *
	 * @param[in]  path  The path to the model file
	 */
	Model(std::string path, bool cacheThisModel=true);
	Model();

	void move(const glm::vec3 &offset);
	void setPosition(const glm::vec3 &newPosition);
	const std::vector<Mesh>& getMeshes() const;
	const glm::mat4& getTransform() const;
	std::vector<Model>& getModels();
	const std::vector<Model>& getModels() const;
	bool raycast(const glm::vec3& start, const glm::vec3& end, glm::vec3& hitPos, float &tmin);
	/**
	 * @brief      This function starts the loading process and is called by the constructor
	 *
	 * @param[in]  path  The path to the model passed from the constructor
	 */
	void loadModel(std::string path, bool cacheThisModel);
	static const std::map<std::string, Assimp::Importer*>& getModelCache() {return modelCache;}
private:
	static std::map<std::string, Assimp::Importer*> modelCache;
	void cleanup();
	std::vector<Mesh> meshes;
	std::vector<Model> nodes;
	glm::mat4 globalTransform;
	std::string containingDir;
	std::string lastLoadedModelPath;
	void copyAiMat(const aiMatrix4x4 *from, glm::mat4 &to);
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
};
