#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <vector>
#include <string>
#include <cmath>
#include "Camera.h"
#include "Timer.h"
#include "HUD.h"

class Shader;
class Model;

/**
 * @brief      This class is responsible for initializing the windowing system as well as handling input.
 */
class Core
{
	Core(const Core&) = delete;
	Core(Core&&) = delete;
private:
	int screenWidth ;
	int screenHeight ;
	float moveSpeed = 1.0f;
	float mouseSensitivity = 5.0f;
	bool shouldRotateView = false;
	glm::vec2 cameraAngle = glm::vec2(0,0);
	glm::vec2 origCameraAngle = glm::vec2(0,0);
	SDL_Window *mainwindow = nullptr;
	SDL_GLContext maincontext = NULL;
	bool exitFlag = false;
	std::vector<Model *> models;
	std::vector<Shader *> shader;
	Camera cam;
	Timer timer;
	HUD coreHUD;

	GLuint transformLocation;

	/**
	 * @brief      This functions is called exactly once just after initializing the window and right before the main loop.
	 */
	void preLoop();
	/**
	 * @brief      This function is called once per loop to render the scene on the the screen.
	 */
	void render();
	/**
	 * @brief      This function is called once right after exiting the main loop. It's main purpose is to deallocate and clean up things before the destruction of the window.
	 */
	void postLoop();
public:
	Core() = default;
	~Core() = default;
	/**
	 * @brief      Initialize the windowing system including SDL and necessary OpenGL setup
	 *
	 * @return     returns a boolean indicating whether it initialization was a success or a failure.
	 */
	bool init();
	/**
	 * @brief      This function is responsible for starting the event handling and drawing loop. The loop is controlled by a boolean called "exitFlag"
	 */
	void start();
	/**
	 * @brief      This function takes care of cleaning SDL related structures and quits SDL safely.
	 */
	void shutdown();

	void loadMesh(std::string, bool = false);
};
