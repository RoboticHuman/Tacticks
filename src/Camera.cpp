#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include "Camera.h"
using namespace glm;

void Camera::setup(float fov, float aspectRatio, vec3 position, vec3 at){
	this->fov = fov;
	this->aspectRatio = aspectRatio;
	this->near = 0.1;	//Fixed for now
	this->far = 1000.0;	//Fixed for now
	this->position = position;
	this->at = at;

	this->up = vec3(0.0, 0.0, 1.0);
	this->forward = normalize(at - position);
	this->right = normalize(cross(forward, up));

	this->rot = glm::quat(glm::vec3(0.0, 0.0, 0.0));
}
mat4 Camera::getViewMatrix() const{
	mat4 projection = perspective(fov, aspectRatio, near, far);
	mat4 transformation = lookAt(position, at, up);
	mat4 rotation = mat4_cast(rot);
	return projection * transformation;
}

void Camera::moveUp(float amount){
	position += amount * up;
	at += amount * up;
}
void Camera::moveForward(float amount){
	position += amount * forward;
	at += amount * forward;
}
void Camera::moveRight(float amount){
	position += amount * right;
	at += amount * right;
}

void Camera::lookUp(float theta){
	rot = rotate(rot, theta, right);
}
void Camera::lookRight(float theta){
	rot = rotate(rot, theta, up);
}
