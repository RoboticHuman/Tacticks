#include "Sprite.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
using namespace std;
Sprite::Sprite(Shader *shader)
{
  this->shader = shader;
  init();
}

Sprite::~Sprite()
{
  //delete shader;
}

void Sprite::init()
{
  GLuint vbo;

  GLfloat vertices[] = {
    //Position 0.0,0.0 is at the top-left corner.
    //TODO: might need to define a way to set this to arbitrary center later
    //for now a single position is accompanied with its texture coordinate for
    //better space optimization
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,

    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f
  };
  glGenVertexArrays(1, &this->vao);
  glGenBuffers(1, &vbo);

  glBindBuffer(GL_ARRAY_BUFFER,vbo);
  glBufferData(GL_ARRAY_BUFFER,sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindVertexArray(this->vao);
  //enable position attribute in shader associated
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0,4,GL_FLOAT, GL_FALSE, 4* sizeof(GLfloat),(GLvoid*)0);
  glBindBuffer(GL_ARRAY_BUFFER,0);
  glBindVertexArray(0);
}

void Sprite::setShaders(const char* vsPath, const char* fsPath)
{
	shader->loadAndBind(vsPath,fsPath);
}

void Sprite::scale(float x, float y)
{
	spriteScale.x *= x;
	spriteScale.y *= y;
	shouldRecomputeTransform = true;
}

void Sprite::move(float offsetX, float offsetY)
{
	spritePos.x += offsetX;
	spritePos.y +=offsetY;
	shouldRecomputeTransform = true;
}

void Sprite::setPosition(glm::vec2 newPos)
{
	spritePos = newPos;
  shouldRecomputeTransform = true;
}

void Sprite::rotate(float angle)
{
  rotation+=angle;
  shouldRecomputeTransform = true;
}

void Sprite::setRotation(float angle)
{
	rotation = angle;
	shouldRecomputeTransform = true;
}

glm::mat4 Sprite::getTransform(){
	if(shouldRecomputeTransform)
	{
		//translation
		model = glm::translate(model, glm::vec3(spritePos,0.0f));
		//rotation
		model = glm::translate(model,glm::vec3(0.5f * spriteTexture.Width, 0.5f * spriteTexture.Height, 0.0f));
		model = glm::rotate(model, rotation, glm::vec3(0.0f,0.0f,1.0f));
		model = glm::translate(model, glm::vec3(-0.5f*spriteTexture.Width, -0.5f*spriteTexture.Height, 0.0f));
		//scaling
		model = glm::scale(model, glm::vec3(spriteTexture.Width,spriteTexture.Height,1.0f));
	}
	shouldRecomputeTransform = false;
	return model;
}

void Sprite::setTexture(int width, int height, unsigned char* data)
{
  shader->use();
  spriteTexture.Generate(width,height,data);
}

void Sprite::draw()
{
  shader->use();
  glUniformMatrix4fv(shader->getUniformLocation("projection"), 1, GL_FALSE, value_ptr(glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f)));
  glUniformMatrix4fv(shader->getUniformLocation("model"), 1, GL_FALSE, value_ptr(getTransform()));
  //glActiveTexture(GL_TEXTURE0);
  spriteTexture.Bind();
  glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}
