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
	/**
	 * @brief      Loads a shader.
	 *
	 * @param[in]  vsPath      The vertex shader path
	 * @param[in]  fsPath      The fragment shader path
	 * @param[in]  shaderName  The shader name for later reference
	 *
	 * @return     A pointer to the shader object.
	 */
  static Shader* loadShader(const char* vsPath, const char* fsPath, string shaderName);
  /**
   * @brief      Gets the shader using its name.
   *
   * @param[in]  shaderName  The shader name
   *
   * @return     A pointer to the shader object requested.
   */
  static Shader* getShader(string shaderName);
  /**
   * @brief      Loads a texture using a path to the image and loads it into an OpenGL.
   *
   * @param[in]  texturePath  The texture path
   * @param[in]  alpha        Whether or not to use the alpha channel info.
   * @param[in]  texName      The texture/image name
   *
   * @return     A 2D texture object.
   */
  static Texture2D loadTexture(const char* texturePath, GLboolean alpha, string texName);
  /**
   * @brief      Gets the texture using its name.
   *
   * @param[in]  texName  The texture name
   *
   * @return     A 2D texture object with the name supplied.
   */
  static Texture2D getTexture(string texName);
  /**
   * @brief      Deletes shaders, frees texture data.
   */
  static void cleanup();
};
