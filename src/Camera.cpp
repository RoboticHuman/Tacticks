#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
using namespace glm;

void Camera::setup(float fov, float aspectRatio, vec3 position, vec3 at){
	this->fov = fov;
	this->aspectRatio = aspectRatio;
	this->near = 0.1;	//Fixed for now
	this->far = 1000.0;	//Fixed for now
	this->position = position;
	this->at = at;
}
mat4 Camera::getViewMatrix() const{
	mat4 proj = perspective(fov, aspectRatio, near, far);
	mat4 trans = lookAt(position, at, vec3(0.0, 0.0, 1.0));
	return proj * trans;
}
