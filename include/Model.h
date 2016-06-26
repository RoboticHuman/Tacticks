#pragma once
#include <GL/glew.h>
#include <vector>
#include <string>
#include <map>
#include "SOIL.h"
#include "Mesh.h"
using namespace std;
class Shader;
class aiNode;
class aiScene;
class aiMesh;
class aiString;
class Model
{
public:
	Model(string path);
	void draw(Shader shader);
private:
	vector<Mesh> meshes;
	string containingDir;
	vector<Texture> texturesLoaded;
	map<string, int> loadedTexturePaths;
	void loadModel(string path);
	void processNode(aiNode*, const aiScene* scene);
	Mesh loadMesh(aiMesh*, const aiScene* scene);
	GLuint textureFromFile(const char* path, string containingDir);
};