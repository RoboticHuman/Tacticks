#include "Mesh.h"
#include <algorithm>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
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
	Triangle(Vertex va, Vertex vb, Vertex vc)
	{
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
	bool getIntersect(vec3 start, vec3 end, float& t)
	{
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
	}
	void updateVertices(glm::mat4& transform)
	{
		a = vec3(transform* vec4(a,1.0) );
		b = vec3(transform* vec4(b,1.0) );
		c = vec3(transform*vec4(c,1.0) );
	}
};

Mesh::Mesh(vector<Vertex> &vertices, vector<uint32_t> &indices, vector<string> &textures)
{
	this->vertices = vertices;
    this->indices = indices;
    this->texturePaths = textures;
}

bool Mesh::raycast(const vec3& start, const vec3& end, float& tmin, glm::mat4& globalTransform){
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
