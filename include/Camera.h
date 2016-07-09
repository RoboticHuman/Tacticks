#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <limits>

class Camera{
	float fov = 90.0;
	float aspectRatio = 1.0;
	float near = 0.1;
	float far = 100.;
	glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 at = glm::vec3(0.0, 0.0, 0.0);

	glm::vec3 up = glm::vec3(0.0, 1.0, 0.0);
	glm::vec3 forward = glm::vec3(0.0, 0.0, 1.0);
	glm::vec3 right = glm::vec3(1.0, 0.0, 0.0);

	void updateAxies();
public:
	Camera() = default;
	~Camera() = default;

	void setup(float, float, glm::vec3, glm::vec3);
	glm::mat4 getViewMatrix() const;
	glm::vec3 getCameraWorldPosition();
	void moveUp(float);
	void moveForward(float);
	void moveRight(float);
	void updateCameraAngle(float thetaX, float thetaY);

	void lookUp(float);
	void lookRight(float);
};
