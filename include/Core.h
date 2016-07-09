#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <vector>
#include "Camera.h"
#include "Timer.h"
#include <cmath>

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
	float mouseSensitivity = 1.0f;
	bool shouldRotateView = false;
	glm::vec2 mousePos = glm::vec2(0,0);
	glm::vec2 origMousePos = glm::vec2(0,0);
	glm::vec2 cameraAngle = glm::vec2(0,0);
	glm::vec2 origCameraAngle = glm::vec2(0,0);
	SDL_Window *mainwindow = nullptr;
	SDL_GLContext maincontext = NULL;
	bool exitFlag = false;
	std::vector<Model *> models;
	std::vector<Shader *> shader;
	Camera cam;
	Timer timer;

	GLuint transformLocation;

	void preLoop();
	void render();
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
};
