#include "Model.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <algorithm>
#include <iostream>
#include "Shader.h"
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

void Model::draw(Shader *shader)
{
	for(GLuint i=0; i<meshes.size();i++)
	{
		meshes[i].draw(shader);
	}
	for(int i=0;i<nodes.size();i++)
	{
		nodes[i].draw(shader);
	}
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

void Model::loadModel(string path)
{
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

void Model::processNode(aiNode *node, const aiScene *scene,Model &rootModel)
{
	for(GLuint i=0;i<node->mNumMeshes;i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		rootModel.meshes.push_back(loadMesh(mesh,scene));
		copyAiMat(&(node->mTransformation),rootModel.globalTransform);
		cout<<"finished"<<endl;
	}

	for (GLuint i=0;i<node->mNumChildren;i++)
	{
		rootModel.nodes.push_back(Model());
		rootModel.nodes.back().containingDir = rootModel.containingDir;
		processNode(node->mChildren[i],scene,rootModel.nodes[i]);

	}
}

/*
rootNode = new Node;
rootNode->meshReferences=&meshes;
processNode(scene->mRootNode, scene, rootNode);
}

void Model::processNode(aiNode *node, const aiScene *scene,Node *rootNode)
{
for(GLuint i=0;i<node->mNumMeshes;i++)
{
	aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
	meshes.push_back(loadMesh(mesh,scene));
	copyAiMat(&(node->mTransformation),rootNode->transformation);
	rootNode->meshes.push_back(meshes.size()-1);
}

for (GLuint i=0;i<node->mNumChildren;i++)
{
	rootNode->nodes.push_back(new Node);
	rootNode->nodes.back()->meshReferences=&meshes;
	processNode(node->mChildren[i],scene,rootNode->nodes[i]);
}
}
*/

Mesh Model::loadMesh(aiMesh *mesh, const aiScene *scene)
{
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;

	for(GLuint i =0; i<mesh->mNumVertices; i++)
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


	for(GLuint i=0;i<mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for(GLuint j=0; j<face.mNumIndices;j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	if(mesh->mMaterialIndex >=0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		aiString texturePath;
		if(material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS)
		{
			if(loadedTexturePaths.count(texturePath.C_Str()) == 0)
			{
				//printf("FOUND!\n");
				Texture texture;
				texture.id = textureFromFile(texturePath.C_Str(), containingDir);
				//TODO: THIS IS HARDCODED FOR NOW AS WE ONLY SUPPORT A SINGLE DIFFUSE
				texture.type = "texture_diffuse";
				texture.path = texturePath.C_Str();
				textures.push_back(texture);
				texturesLoaded.push_back(texture);
				loadedTexturePaths.insert(make_pair(texturePath.C_Str(),texturesLoaded.size()-1));
			}
			else
			{
				textures.push_back(texturesLoaded[loadedTexturePaths[texturePath.C_Str()]]);
			}
		}
		else {
			//printf("NOT FOUND!\n");
			Texture texture;
			texture.id = textureFromFile("white.png",containingDir);
			texture.type = "texture_diffuse";
			textures.push_back(texture);
			texturesLoaded.push_back(texture);
			loadedTexturePaths.insert(make_pair(texture.path,texturesLoaded.size()-1));
		}

	}

	return Mesh(vertices, indices, textures, globalTransform);
}

GLuint Model::textureFromFile(const char* path, string containingDir)
{
	string fileName;
    fileName = containingDir + '/' + path;
    GLuint textureID;
    glGenTextures(1, &textureID);
    int width,height;
    unsigned char* image = SOIL_load_image(fileName.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
    // Assign texture to ID
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image);
    return textureID;
}

bool Model::raycast(const vec3& start, const vec3& end, vec3& hitPos, float &tmin)
{
	float t;
	bool hit = false;
	for(Mesh &m : meshes) {
		if(m.raycast(start, end, t)) {
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
