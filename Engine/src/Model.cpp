#include "Model.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <algorithm>
using namespace std;
using namespace glm;

void Model::copyAiMat(const aiMatrix4x4 *from, glm::mat4 &to) {
	to[0][0] = from->a1; to[1][0] = from->a2;
	to[2][0] = from->a3; to[3][0] = from->a4;
	to[0][1] = from->b1; to[1][1] = from->b2;
	to[2][1] = from->b3; to[3][1] = from->b4;
	to[0][2] = from->c1; to[1][2] = from->c2;
	to[2][2] = from->c3; to[3][2] = from->c4;
	to[0][3] = from->d1; to[1][3] = from->d2;
	to[2][3] = from->d3; to[3][3] = from->d4;
}

Model::Model(string path)
{
	loadModel(path);
}

void Model::cleanup()
{
	meshes.clear();
	nodes.clear();
}

const glm::mat4& Model::getTransform() const{
	return globalTransform;
}

void Model::move(const glm::vec3 &offset)
{
	globalTransform = translate(globalTransform,offset);
	for(Model &node: nodes)
	{
		node.move(offset);
	}
}

void Model::setPosition(const glm::vec3 &newPosition)
{
	glm::vec3 offset = glm::vec3(newPosition[0]-globalTransform[3][0],
									newPosition[1]-globalTransform[3][1],
									newPosition[2]-globalTransform[3][2]);

	move(offset);
}

const std::vector<Mesh>& Model::getMeshes() const
{
	return meshes;
}
std::vector<Model>& Model::getModels(){
	return nodes;
}
const std::vector<Model>& Model::getModels() const{
	return nodes;
}

void Model::loadModel(string path)
{
		cleanup();
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_FlipUVs);

		if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			printf("ERROR::ASSIMP:: %s\n", importer.GetErrorString());
			return;
		}

		containingDir = path.substr(0, path.find_last_of('/'));
		processNode(scene->mRootNode, scene, *this);
}

Model::Model()
{

}
void Model::processNode(aiNode *node, const aiScene *scene, Model &rootModel)
{
	copyAiMat(&(node->mTransformation),rootModel.globalTransform);
	for(uint32_t i=0;i<node->mNumMeshes;i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		rootModel.meshes.push_back(loadMesh(mesh,scene));
	}

	for (uint32_t i=0;i<node->mNumChildren;i++)
	{
		rootModel.nodes.push_back(Model());
		rootModel.nodes.back().containingDir = rootModel.containingDir;
		processNode(node->mChildren[i],scene,rootModel.nodes[i]);

	}
}

Mesh Model::loadMesh(aiMesh *mesh, const aiScene *scene)
{
	vector<Vertex> vertices;
	vector<uint32_t> indices;
	vector<pair<string, string>> texturePaths;

	for(uint32_t i =0; i<mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x; vector.y = mesh->mVertices[i].y; vector.z = mesh->mVertices[i].z;

		vertex.position = vector;
		vector.x = mesh->mNormals[i].x; vector.y = mesh->mNormals[i].y; vector.z = mesh->mNormals[i].z;

		vertex.normal = vector;

		if(mesh->mTextureCoords[0])
		{
			glm::vec2 vector;
			vector.x = mesh->mTextureCoords[0][i].x;
			vector.y = mesh->mTextureCoords[0][i].y;
			vertex.texCoords = vector;
		}
		else
		{
			vertex.texCoords = glm::vec2(0.0f, 0.0f);
		}
		vertices.push_back(vertex);
	}


	for(uint32_t i=0;i<mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for(uint32_t j=0; j<face.mNumIndices;j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	aiString texturePath;
	if(material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS)
		texturePaths.push_back(make_pair(containingDir + "/" + texturePath.C_Str(), "texture_diffuse"));
	else
		texturePaths.push_back(make_pair(containingDir + "/white.png", "texture_diffuse"));

	return Mesh(vertices, indices, texturePaths);
}

bool Model::raycast(const vec3& start, const vec3& end, vec3& hitPos, float &tmin)
{
	float t;
	bool hit = false;
	for(Mesh &m : meshes) {
		if(m.raycast(start, end, t,globalTransform)) {
			tmin = std::min(tmin, t);
			hit = true;
		}
	}
	hitPos = start + (end - start) * tmin;
	for (int i=0; i<nodes.size(); i++) {
		hit |= nodes[i].raycast(start, end, hitPos, tmin);
	}
	return hit;
}
