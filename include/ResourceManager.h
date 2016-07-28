#pragma once
#include <map>
#include <string>
#include <GL/glew.h>
#include "Texture2D.h"
#include "Shader.h"
using namespace std;
class ResourceManager {
private:
  ResourceManager(){}
  static map<string, Shader*> shaders;
  static map<string, Texture2D> textures;
public:
  static Shader* loadShader(const char* vsPath, const char* fsPath, string shaderName);
  static Shader* getShader(string shaderName);
  static Texture2D loadTexture(const char* texturePath, GLboolean alpha, string texName);
  static Texture2D getTexture(string texName);
  static void cleanup();
};
