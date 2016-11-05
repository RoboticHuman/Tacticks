#include "ResourceManager.h"
#include <SOIL/SOIL.h>

map<string, Texture2D> ResourceManager::textures;
map<string, Shader*> ResourceManager::shaders;

Shader* ResourceManager::loadShader(const char* vsPath, const char* fsPath, string shaderName)
{
  shaders[shaderName] = new Shader(vsPath,fsPath);
  return shaders[shaderName];
}

Shader* ResourceManager::getShader(string shaderName)
{
  return shaders[shaderName];
}

Texture2D ResourceManager::loadTexture(const char* texturePath, GLboolean alpha, string texName)
{
  Texture2D tempTexture;
  if(alpha)
  {
    tempTexture.Internal_Format = GL_RGBA;
    tempTexture.Image_Format = GL_RGBA;
  }
  int width, height;
  unsigned char* texImage = SOIL_load_image(texturePath,&width,&height, 0, tempTexture.Image_Format == GL_RGBA? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
  tempTexture.Generate(width,height,texImage);
  SOIL_free_image_data(texImage);
  textures[texName] = tempTexture;
  return textures[texName];
}

Texture2D ResourceManager::getTexture(string texName)
{
  return textures[texName];
}

void ResourceManager::cleanup()
{
  for (auto shader:shaders) glDeleteProgram(shader.second->getShaderProgram());
  for (auto shader:shaders) delete shader.second;
  for (auto texture:textures) glDeleteTextures(1, &texture.second.ID);
}
