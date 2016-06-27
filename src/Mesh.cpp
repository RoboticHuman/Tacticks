#include "Mesh.h"
#include "Shader.h"
#include <iostream>

Mesh::Mesh(vector<Vertex> &vertices, vector<GLuint> &indices, vector<Texture> &textures)
{
	this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
	this->setupBuffers();
}

void Mesh::setupBuffers()
{
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

void Mesh::draw(Shader *shader)
{
	if(!textureSetupDone)
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
		textureSetupDone= true;
	}
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT,0);
	glBindVertexArray(0);


}
