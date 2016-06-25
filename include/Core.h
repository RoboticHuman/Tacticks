#pragma once
#include <cstdio>
#include <SDL2/SDL.h>
#include <GL/glew.h>
/**
 * @brief      This class is responsible for initializing the windowing system as well as handling input.
 */
class Core
{
	Core(const Core&) = delete;
	Core(Core&&) = delete;
private:
	SDL_Window *mainwindow; 
	SDL_GLContext maincontext;
	SDL_Event event;
	bool exitFlag = false;
public:
	Core(){};
	~Core();
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