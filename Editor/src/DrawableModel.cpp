#include "DrawableModel.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include <iostream>
#include <Tacticks/Model.h>
#include <Tacticks/Mesh.h>
#include "Shader.h"
using namespace std;
using namespace glm;

DrawableModel::DrawableModel(Model* model)
{
	loadModel(model);
}

void DrawableModel::draw(Shader *shader)
{
	for(DrawableMesh& mesh : meshes)
		mesh.draw(shader, model->getTransform());
	for(DrawableModel& childModel : nodes)
		childModel.draw(shader);
}

void DrawableModel::move(const glm::vec3 &offset)
{
	model->move(offset);
}

void DrawableModel::setPosition(const glm::vec3 &newPosition)
{
	model->setPosition(newPosition);
}

void DrawableModel::loadModel(Model* model)
{
	processNode(model, *this);
}

DrawableModel::DrawableModel()
{

}

void DrawableModel::processNode(Model* model, DrawableModel& rootModel)
{
	this->model = model;
	for(const Mesh& mesh : model->getMeshes())
		rootModel.meshes.push_back(loadMesh(&mesh));
	for(Model& childModel : model->getModels())
		rootModel.nodes.push_back(DrawableModel(&childModel));
}

DrawableMesh DrawableModel::loadMesh(const Mesh* mesh)
{
	vector<Texture> textures;
	for(auto& texturePair : mesh->getTexturePaths()){
		if(texturesLoaded.count(texturePair.first) == 0){
			Texture texture;
			texture.id = textureFromFile(texturePair.first);
			texture.type = texturePair.second;
			texturesLoaded[texturePair.first] = texture;
		}
		textures.push_back(texturesLoaded[texturePair.first]);
	}

	return DrawableMesh(textures, mesh);
}

GLuint DrawableModel::textureFromFile(string path)
{
	GLuint textureID;
    glGenTextures(1, &textureID);
    int width,height;
    unsigned char* image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
    // Assign texture to ID
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image);
    return textureID;
}

bool DrawableModel::raycast(const vec3& start, const vec3& end, vec3& hitPos, float &tmin)
{
	return model->raycast(start, end, hitPos, tmin);
}
