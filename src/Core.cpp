#include "Core.h"
#include <string>
#include <cstdio>
using namespace std;

void Core::preLoop()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 1.0);

	shader.push_back(Shader("shaders/envCheck/VSTest.vs", "shaders/envCheck/FSTest.fs"));
}
void Core::render()
{
	shader[0].use();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Core::postLoop()
{
	shader.clear();
}

void Core::shutdown()
{
	SDL_GL_DeleteContext(maincontext);
	SDL_DestroyWindow(mainwindow);
	SDL_Quit();
}

bool Core::init()
{
	SDL_version SDL_cVer; //SDL version during compilation (Header version)
	SDL_version SDL_rVer; //SDL version during in runtime (Dll version)
	SDL_VERSION(&SDL_cVer);
	SDL_GetVersion(&SDL_rVer);

	if(SDL_Init(SDL_INIT_VIDEO| SDL_INIT_TIMER) != 0){
		printf("Error:: Unable to initialize SDL: %s\n", SDL_GetError());
		return false;
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	string SDL_err;
	mainwindow = SDL_CreateWindow("SDLTutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512, SDL_WINDOW_OPENGL);
	if(mainwindow == nullptr){
		printf("Error:: Unable to create SDL window: %s\n", SDL_GetError());
		SDL_Quit();
		return false;
	}
	if((SDL_err = SDL_GetError()) != ""){
		printf("Error:: SDL Error: %s\n", SDL_err.c_str());
		SDL_ClearError();
	}
    maincontext = SDL_GL_CreateContext(mainwindow);
	if((SDL_err = SDL_GetError()) != ""){
		printf("Error:: SDL Error: %s\n", SDL_err.c_str());
		SDL_ClearError();
	}

	SDL_GL_SetSwapInterval(1);

	if(SDL_cVer.major != SDL_rVer.major || SDL_cVer.minor != SDL_rVer.minor || SDL_cVer.patch != SDL_rVer.patch){
		printf("Warning:: SDL compiled version is different from the DLL.\n");
		printf("\tSDL compiled version: %d.%d.%d\n", SDL_cVer.major, SDL_cVer.minor, SDL_cVer.patch);
		printf("\tSDL runtime version:  %d.%d.%d\n", SDL_rVer.major, SDL_rVer.minor, SDL_rVer.patch);
	}

	GLenum glew_init = glewInit();
	if(glew_init != GLEW_OK){
		printf("Error:: Glew Init failed: %d: %s\n", glew_init, glewGetErrorString(glew_init));
		shutdown();
		return false;
	}
	return true;
}

void Core::start()
{
	SDL_Event event;
	preLoop();
	while(!exitFlag){
		while(SDL_PollEvent(&event)){	//Handeling events
			switch(event.type){
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_q:
						case SDLK_ESCAPE:
							exitFlag = true;
						break;
					}
				break;
				case SDL_QUIT:
					exitFlag = true;
				break;
			}

		}

		render();

		SDL_GL_SwapWindow(mainwindow);
	}
	postLoop();
}
