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
  void setShaders(const char* vsPath, const char* fsPath);
  void scale(float x, float y);
  void move(float offsetX, float offsetY);
  void setPosition(glm::vec2 newPos);
  void rotate(float angle);
  void setRotation (float angle);
  void setTexture(int width, int height, unsigned char*);
  glm::mat4 getTransform();
  void draw();
};
