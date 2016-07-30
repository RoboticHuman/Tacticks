#include <string>
#include <cstdio>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec3.hpp>
#include "Core.h"
#include "Model.h"
#include "Shader.h"
#include "Model.h"
#include "Globals.h"
#include "ResourceManager.h"

using namespace std;
using namespace glm;

void Core::preLoop()
{
	glEnable(GL_CULL_FACE);
	glEnable (GL_BLEND);
	glClearColor(0, 0, 0, 1.0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//shader.push_back(new Shader("shaders/envCheck/VSTest.vs", "shaders/envCheck/FSTest.fs"));
	models.push_back(new Model("models/envCheck/Crate1.obj"));
	cam.setup(45, 1.0*screenWidth/screenHeight, vec3(0.0, 0.0, 1.0), vec3(0.0, 0.0, 0.0));
	transformLocation = ResourceManager::getShader("meshShader")->getUniformLocation("transform");


}
void Core::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	ResourceManager::getShader("meshShader")->use();
	models[0]->draw(ResourceManager::getShader("meshShader"));

	glDisable(GL_DEPTH_TEST);
	coreHUD.render();
}
void Core::postLoop()
{
	//for(Shader *s : shader) delete s;
	for(Model *m : models) delete m;
}

void Core::shutdown()
{
	coreHUD.shutdown();
	ResourceManager::cleanup();
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

	//hides cursor and allow only for relative motion
	//SDL_SetRelativeMouseMode(SDL_TRUE);

	// 4x MSAA.
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);

	screenWidth = std::min(displayMode.w, (int)(displayMode.h * 16.0f/9.0f)) - 80;
	screenHeight = displayMode.h - 80;

	string SDL_err;
	mainwindow = SDL_CreateWindow("Tacticks Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL);
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

	ResourceManager::loadShader("shaders/envCheck/VSTest.vs", "shaders/envCheck/FSTest.fs","meshShader");
	ResourceManager::loadShader("shaders/VSHUD.vs", "shaders/FSHUD.fs","hudShader");
	coreHUD.init(screenWidth,screenHeight);

	return true;

}

void Core::start()
{
	SDL_Event event;
	preLoop();

	while(!exitFlag){
		const double MIN_FRAME_TIME = 1.0f / 40.0f;
		cameraAngle = vec2(0,0);
		double dt = timer.GetDelta();
		if ( dt < MIN_FRAME_TIME){
			int ms = (int)((MIN_FRAME_TIME - dt) * 1000.0f);
			if (ms > 10) ms = 10;
			if (ms >= 0) SDL_Delay(ms);
		}

		while(SDL_PollEvent(&event)){	//Handeling events
			coreHUD.injectEvent(event);
			switch(event.type){
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE:
							exitFlag = true;
						break;
					}
				break;
				case SDL_QUIT:
					exitFlag = true;
				break;
				case SDL_MOUSEBUTTONDOWN:
					switch(event.button.button){
						case SDL_BUTTON_RIGHT:
							shouldRotateView = true;
							origCameraAngle=cameraAngle;
							origMousePos = mousePos;
						break;
					}
				break;
				case SDL_MOUSEWHEEL:
					if(shouldRotateView)
					{
						const float mouseSen = mouseSensitivity;
						if (event.wheel.y > 0) mouseSensitivity = glm::clamp(mouseSen + 1.f,1.f,10.f);
						else mouseSensitivity = glm::clamp(mouseSen-1.f,1.f,10.f);
					}
				break;
				case SDL_MOUSEBUTTONUP:
					switch(event.button.button){
						case SDL_BUTTON_RIGHT:
							shouldRotateView = false;
						break;
					}
				break;
				case SDL_MOUSEMOTION:
					/* //TODO: try to have the rotation based on an angle from mouse movement instead of relative motion.
					int sdlMousex,sdlMousey;
					SDL_GetMouseState(&sdlMousex,&sdlMousey);
					mousePos.x = sdlMousex;
					mousePos.y = screenHeight-1 - sdlMousey;
					*/
					if(shouldRotateView)
					{
						cameraAngle.x = -(float)event.motion.yrel * mouseSensitivity;
						cameraAngle.y = (float)event.motion.xrel * mouseSensitivity ;
					}
				break;
			}
		}
		const Uint8 *keyState = SDL_GetKeyboardState(nullptr);

		if(keyState[SDL_SCANCODE_T]) cam.moveUp(moveSpeed * dt);
		if(keyState[SDL_SCANCODE_G]) cam.moveUp(-moveSpeed * dt);
		if(keyState[SDL_SCANCODE_W]) cam.moveForward(moveSpeed * dt);
		if(keyState[SDL_SCANCODE_S]) cam.moveForward(-moveSpeed * dt);
		if(keyState[SDL_SCANCODE_D]) cam.moveRight(moveSpeed * dt);
		if(keyState[SDL_SCANCODE_A]) cam.moveRight(-moveSpeed * dt);
		if(keyState[SDL_SCANCODE_LSHIFT]) moveSpeed = 5.f; else moveSpeed=1.0f;
		cam.updateCameraAngle(glm::radians(cameraAngle.y)* dt , glm::radians(cameraAngle.x) * dt);

		coreHUD.update();

		//need to use the shader before the operation after it, TODO: need to fix this crap...
		ResourceManager::getShader("meshShader")->use();
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, value_ptr(cam.getViewMatrix()));

		render();

		SDL_GL_SwapWindow(mainwindow);
	}
	postLoop();
}
