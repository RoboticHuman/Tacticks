#include "DrawableMesh.h"
#include "Shader.h"
#include <Tacticks/Mesh.h>
#include <algorithm>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <ResourceManager.h>
#define GLM_SWIZZLE_XYZW
#include <glm/glm.hpp>
using namespace glm;
using namespace std;


DrawableMesh::DrawableMesh(vector<Texture> &textures, const Mesh* mesh)
{
    this->textures = textures;
	this->setupBuffers(mesh);
}

void DrawableMesh::cleanup()
{
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glDeleteVertexArrays(1,&VAO);
  glDeleteBuffers(1,&VBO);
  glDeleteBuffers(1,&EBO);
  for(auto& texture: textures) glDeleteTextures(1,&texture.id);
}

void DrawableMesh::setupBuffers(const Mesh* mesh)
{
	auto& vertices = mesh->getVertices();
	auto& indices = mesh->getIndices();
	nIndices = indices.size();
	//generate vertex array
	glGenVertexArrays(1, &VAO);
	//generate vertex buffer object to store vertex data
	glGenBuffers(1, &VBO);
	//generate element buffer object to allow for indexed drawing
	glGenBuffers(1, &EBO);

	//let OpenGL bind to the vertex array we generated above
	glBindVertexArray(VAO);
	//let OpenGL bind to the vertex buffer object before we can copy vertex data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//copy vertex data into vertex buffer object
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof (Vertex), &vertices[0], GL_STATIC_DRAW);
	//let OpenGL bind to the element buffer so that we copy the vertex indices to it.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
	//enable vertex attribute "position" in vertex shader at layout location 0.
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),(GLvoid*)0);

	//enable vertex attribute "normals" in vertex shader at layout location 1.
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	//enable vertex attribute "texCoords" in vertex shader at layout location 2.
	glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));

    glBindVertexArray(0);
}

void DrawableMesh::draw(Shader *shader,const glm::mat4& globalTransform)
{

		GLuint diffuseSamplerIndex = 1;
		GLuint specularSamplerIndex = 1;
		for(GLuint i=0; i<textures.size();i++)
		{
			glActiveTexture(GL_TEXTURE0+i);
			if(textures[i].type == "texture_diffuse")
				glUniform1i(glGetUniformLocation(shader->getShaderProgram(),(textures[i].type+ std::to_string(diffuseSamplerIndex++)).c_str()),i);
			else if(textures[i].type == "texture_specular")
				glUniform1i(glGetUniformLocation(shader->getShaderProgram(),(textures[i].type+ std::to_string(specularSamplerIndex++)).c_str()),i);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}
		glActiveTexture(GL_TEXTURE0);


	GLuint transformLocation = ResourceManager::getShader("meshShader")->getUniformLocation("meshTransform");
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, value_ptr(globalTransform));
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT,0);
	glBindVertexArray(0);
}