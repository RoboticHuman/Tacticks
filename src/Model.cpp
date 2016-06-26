#include "Model.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Shader.h"


Model::Model(string path)
{
	loadModel(path);
}

void Model::draw(Shader shader)
{
	for(GLuint i=0; i<meshes.size();i++)
	{
		meshes[i].draw(shader);
	}
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

	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene)
{
	for(GLuint i=0;i<node->mNumMeshes;i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(loadMesh(mesh,scene));
	}

	for (GLuint i=0;i<node->mNumChildren;i++)
	{
		processNode(node->mChildren[i],scene);
	}
	
}

Mesh Model::loadMesh(aiMesh *mesh, const aiScene *scene)
{
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;
	printf("number of vertices: %d\n", (int)mesh->mNumVertices);
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
				printf("FOUND!\n");
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
			printf("NOT FOUND!\n");
			Texture texture;
			texture.id = textureFromFile("white.png",containingDir);
			texture.type = "texture_diffuse";
			texture.path = containingDir+"/"+"white.png";
			textures.push_back(texture);
			texturesLoaded.push_back(texture);
			loadedTexturePaths.insert(make_pair(texture.path,texturesLoaded.size()-1));
		}

	}
	return Mesh(vertices, indices, textures);
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