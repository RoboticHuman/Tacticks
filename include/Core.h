#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <vector>
#include "Camera.h"
#include "Timer.h"

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
	static const int screenWdith = 640;
	static const int screenHeight = 480;

	SDL_Window *mainwindow = nullptr;
	SDL_GLContext maincontext = NULL;
	bool exitFlag = false;
	std::vector<Model *> models;
	std::vector<Shader *> shader;
	Camera cam;
	Timer timer;

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
