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

	glm::vec4 viewPort = glm::vec4(0.0, 0.0, 1.0, 1.0);

	void updateAxies();
public:
	Camera() = default;
	~Camera() = default;
	/**
	 * @brief		This functions sets up the initial camera position and settings.
	 */
	void setup(float, float, glm::vec3, glm::vec3, glm::vec2, glm::vec2);
	/**
	 *	@breif		Returns the View transformation materix.
	 */
	glm::mat4 getViewMatrix() const;
	/**
	 *	@breif		return the position parameter
	 */
	glm::vec3 getCameraWorldPosition();

	glm::vec3 screenToWorld(glm::vec3);

	/**
	 *	@breif		Moves the camera upwards.
	 */
	void moveUp(float);
	/**
	 *	@breif		Moves the camera forward
	 */
	void moveForward(float);
	/**
	 *	@breif		Moves the camera to the right
	 */
	void moveRight(float);
	/**
	 *	@breif		Updates the camera Angle
	 */
	void updateCameraAngle(float thetaX, float thetaY);

	/**
	 *	@breif		Rotates the camera vertically
	 */
	void lookUp(float);
	/**
	 *	@breif		Rotates the camera horizontally.
	 */
	void lookRight(float);
};
