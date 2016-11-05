#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "Texture2D.h"

class Sprite {
private:
  Shader *shader;
  glm::vec2 spritePos = glm::vec2(0,0);
  glm::vec2 spriteScale = glm::vec2(1,1);
  bool shouldRecomputeTransform = true;
  GLuint vao;
  Texture2D spriteTexture;
  float rotation = 0;
  glm::mat4 model;
  glm::mat4 projection;
  void init();
public:
  Sprite (Shader *shader,int screenWidth, int screenHeight);
  ~Sprite ();
  /**
   * @brief      Sets the shaders of this sprite using a vertex and fragment shaders.
   *
   * @param[in]  vsPath  The vertex shader path
   * @param[in]  fsPath  The fragment shader path
   */
  void setShaders(const char* vsPath, const char* fsPath);
  /**
   * @brief      Scales a sprite
   *
   * @param[in]  x     The factor to scale in the X axis.
   * @param[in]  y     The factor to scale in the Y axis.
   */
  void scale(float x, float y);
  /**
   * @brief      Move the sprite additively
   *
   * @param[in]  offsetX  The offset in x
   * @param[in]  offsetY  The offset in y
   */
  void move(float offsetX, float offsetY);
  /**
   * @brief      Sets the position of the sprite
   *
   * @param[in]  newPos  The new position
   */
  void setPosition(glm::vec2 newPos);
  /**
   * @brief      Rotates the sprite additively
   *
   * @param[in]  angle  The angle by which the sprite will be rotated
   */
  void rotate(float angle);
  /**
   * @brief      Sets the rotation.
   *
   * @param[in]  angle  The angle to rotate from identity
   */
  void setRotation (float angle);
  /**
   * @brief      Sets the texture.
   *
   * @param[in]  width      The width
   * @param[in]  height     The height
   * @param      data  The texture data to be loaded on the texture
   */
  void setTexture(int width, int height, unsigned char*);
  /**
   * @brief      Gets the transform.
   *
   * @return     The transform.
   */
  glm::mat4 getTransform();
  /**
   * @brief      Draws the sprite using OpenGL draw calls
   */
  void draw();
};
