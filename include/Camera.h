#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class Camera{
	float fov = 90.0;
	float aspectRatio = 1.0;
	float near = 0.1;
	float far = 100.;
	glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 at = glm::vec3(0.0, 0.0, 0.0);
public:
	Camera() = default;
	~Camera() = default;

	void setup(float, float, glm::vec3, glm::vec3);
	glm::mat4 getViewMatrix() const;
};
