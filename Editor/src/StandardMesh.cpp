#include "StandardMesh.h"
#include "Shader.h"
#include <algorithm>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <ResourceManager.h>
#define GLM_SWIZZLE_XYZW
#include <glm/glm.hpp>
using namespace glm;
using namespace std;

/**
 * @brief      Class for triangle data structure.
 */
class Triangle{
private:
	vec3 a, b, c;
	vec3 ab, ac;
	vec3 norm;
public:
	Triangle(Vertex va, Vertex vb, Vertex vc){
		a = va.position;
		b = vb.position;
		c = vc.position;

		ab = b - a;
		ac = c - a;

		norm = cross(ab, ac);
	}
	/**
	 * @brief      Gets the intersect location along the ray
	 *
	 * @param[in]  start  The start
	 * @param[in]  end    The end
	 * @param      t      the scaling factor based on the distance of the hit point along the ray direction from the start of the ray.
	 *
	 * @return     Whether an intersection/hit was captured or not.
	 */
	bool getIntersect(vec3 start, vec3 end, float& t){
		vec3 ray = start - end;
		float d = dot(ray, norm);
		if(d <= 0) return false;

		vec3 as = start - a;
		t = dot(as, norm);
		if(t < 0) return false;
		if(t > d) return false;

		vec3 e = cross(ray, as);
		float v = dot(ac, e);
		if(v < 0 || v > d) return false;
		float w = -dot(ab, e);
		if(w < 0 || v + w > d) return false;

		t /= d;
		return true;
/*
		vec3 ray = end - start;
		float d = dot(ray, norm);
		if(d >= 0) return false;
		vec3 as = start - a;
		t = dot(as, norm);
		if(t < 0 || t > d) return false;
		vec3 e = cross(as, ray);
		float v = dot(ac, e);
		if(v < 0 || v > d) return false;
		float w = -dot(ab, e);
		if(w < 0 || v + w > d) return false;
		t /= d;
		return true;
*/
	}
	void updateVertices(glm::mat4& transform)
	{
		a = vec3(transform* vec4(a,1.0) );
		b = vec3(transform* vec4(b,1.0) );
		c = vec3(transform*vec4(c,1.0) );
	}
};

StandardMesh::StandardMesh(vector<Vertex> &vertices, vector<GLuint> &indices, vector<Texture> &textures, glm::mat4& parentTransform):globalTransform(parentTransform)
{
	this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
	this->setupBuffers();
}

void StandardMesh::setupBuffers()
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

void StandardMesh::draw(Shader *shader)
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

	GLuint transformLocation = ResourceManager::getShader("meshShader")->getUniformLocation("meshTransform");
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, value_ptr(globalTransform));
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT,0);
	glBindVertexArray(0);
}

bool StandardMesh::raycast(const vec3& start, const vec3& end, float& tmin){
	tmin = 1.0;
	float t;
	bool hit = false;
	for(int i = 2; i < indices.size(); i+=3){
		Triangle tri(vertices[indices[i-2]], vertices[indices[i-1]], vertices[indices[i]]);
		tri.updateVertices(globalTransform);
		if(tri.getIntersect(start, end, t)){
			cout<<t<<endl;
			tmin = std::min(tmin, t);
			hit = true;
		}
	}
	return hit;
}
