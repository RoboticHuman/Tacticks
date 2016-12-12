#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <limits>
/**
 * @brief      Camera class responsible for creating the basic transformations like moving and rotating the camera in the scene.
 */
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
	 * 
	 * @param[in] fov The field of view of the camera, default is 90 degrees.
	 * @param[in] aspectRatio The aspect ratio as a fraction of screenWidth/screenHeight.
	 * @param[in] position The position of the camera in the scene.
	 * @param[in] at The current location in the world the camera is looking at.
	 * @param[in] windowXY The default starting position of the corner of the screen.
	 * @param[in] windowWH The width and height of the screen.
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
	/**
	 * @brief      Retrieve world location from a given window coordinate. (Uses Raycasting)
	 *
	 * @param[in]  windowCoordinate  The location of the mouse click and a depth value, all in a vec3 structure.
	 *
	 * @return     The world location corresponding to a ray casted from the camera position to the triangles of the world.
	 */
	glm::vec3 screenToWorld(glm::vec3);

	/**
	 * @brief      Moves the camera upwards.
	 *
	 * @param[in]  val  moves the camera upwards by a certain amount in the Y axis.
	 */
	void moveUp(float);
	/**
	 * @brief      Moves the camera forward
	 *
	 * @param[in]  val  amount to move with.
	 */
	void moveForward(float);
	/**
	 *	@breif		Moves the camera to the right
	 */
	void moveRight(float);
	/**
	 * @brief      Updates the camera angle
	 *
	 * @param[in]  thetaX  The theta x to rotate about the X axis
	 * @param[in]  thetaY  The theta y to rotate about the Y axis
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
