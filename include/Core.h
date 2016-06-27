#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <vector>
#include "Shader.h"
#include "Model.h"
#include <chrono>
using namespace std::chrono;

class Timer{
    public:
        Timer():timePrev( high_resolution_clock::now()){
        }
        double GetDelta(){
            auto timeCurrent = high_resolution_clock::now();
            duration< double > delta( timeCurrent - timePrev );
            timePrev = high_resolution_clock::now();
            return delta.count();
        }
    private:
        time_point< high_resolution_clock > timePrev;
};


/**
 * @brief      This class is responsible for initializing the windowing system as well as handling input.
 */
class Core
{
	Core(const Core&) = delete;
	Core(Core&&) = delete;
private:
	SDL_Window *mainwindow = nullptr;
	SDL_GLContext maincontext = NULL;
	bool exitFlag = false;
	vector<Model *> models;
	std::vector<Shader *> shader;
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
