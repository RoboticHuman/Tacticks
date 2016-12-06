#include <cstdio>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/vec3.hpp>
#include "Core.h"
#include "Shader.h"
#include "DrawableModel.h"
#include "ResourceManager.h"
#include "Tacticks/BehaviourPipeline.h"
#include "Tacticks/BehaviourModuleFactory.h"
#include "Tacticks/AttributeFactory.h"
#include "Tacticks/AgentAttributeBool.h"
#include "Tacticks/AgentAttributeEnum.h"
#include "Tacticks/AgentAttributeFloat.h"
#include "Tacticks/AgentAttributeInt.h"
#include "Tacticks/AgentAttributeVec3.h"

using namespace std;
using namespace glm;

void Core::loadMesh(string fpath, bool resetCam){
	pipeline.constructWorld(fpath);
	if(drawableModel) {delete drawableModel; drawableModel=nullptr;}
	if(!drawableModel){
		drawableModel = new DrawableModel(&pipeline.getWorldInstance().getWorldModel());
	}

	if(resetCam) cam.setup(45, 1.0*screenWidth/screenHeight, vec3(0.0, 0.0, 1.0), vec3(0.0, 0.0, 0.0), vec2(0.0, 0.0), vec2(screenWidth, screenHeight));
}

void Core::preLoop()
{
	glEnable(GL_CULL_FACE);
	glEnable (GL_BLEND);
	glClearColor(0, 0, 0, 1.0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	cam.setup(45, 1.0*screenWidth/screenHeight, vec3(0.0, 0.0, 1.0), vec3(0.0, 0.0, 0.0), vec2(0.0, 0.0), vec2(screenWidth, screenHeight));
	transformLocation = ResourceManager::getShader("meshShader")->getUniformLocation("transform");
}
void Core::render()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	ResourceManager::getShader("meshShader")->use();
	if(drawableModel)drawableModel->draw(ResourceManager::getShader("meshShader"));

	ResourceManager::getShader("meshShader")->use();
	for(auto& drawableAgent : drawableAgents) {drawableAgent.getAgentDrawableModel().draw(ResourceManager::getShader("meshShader"));}

	glDisable(GL_DEPTH_TEST);
	coreHUD.render();
}
void Core::postLoop()
{
	delete drawableModel;
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
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

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

	ResourceManager::loadShader("EditorAssets/shaders/VS.vs", "EditorAssets/shaders/FS.fs","meshShader");
	ResourceManager::loadShader("EditorAssets/shaders/VSHUD.vs", "EditorAssets/shaders/FSHUD.fs","hudShader");
	coreHUD.init(screenWidth,screenHeight);

	return true;
}

void Core::start()
{
	SDL_Event event;
	preLoop();
	int textBoxValue = 0;
	while(!exitFlag){
		const double MIN_FRAME_TIME = 1.0f / 40.0f;
		cameraAngle = vec2(0,0);
		double dt = timer.GetDelta();
		if(dt < MIN_FRAME_TIME){
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
						break;
						case SDL_BUTTON_LEFT:
							vec3 ray[2];
							ray[0] = cam.screenToWorld(vec3(event.button.x, screenHeight - event.button.y, 0.0));
							ray[1] = cam.screenToWorld(vec3(event.button.x, screenHeight - event.button.y, 1.0));
							vec3 pos;
							float NEEDS_TO_BE_FIXED_AND_DONE_PROPERLY_TMIN = 1.0f;
							if(placeAgents)
							{
								if(drawableModel&&drawableModel->raycast(ray[0], ray[1], pos, NEEDS_TO_BE_FIXED_AND_DONE_PROPERLY_TMIN)){
									int agentID = pipeline.addAgent();
									coreHUD.addAgenthud(agentID);
									drawableAgents.push_back(DrawableAgent("EditorAssets/models/AgentCylinder.obj",agentID));
									drawableAgents.back().getAgentModel().setPosition(pos);
								}
							}
							else
							{
								for(auto& drawableAgent : drawableAgents){
									if(drawableAgent.getAgentModel().raycast(ray[0],ray[1],pos,NEEDS_TO_BE_FIXED_AND_DONE_PROPERLY_TMIN)) cout<<drawableAgent.getAgentID()<<endl;
								}
							}
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
					if(shouldRotateView)
					{
						cameraAngle.x = -(float)event.motion.yrel * mouseSensitivity * 10;
						cameraAngle.y = (float)event.motion.xrel * mouseSensitivity * 10;
					}
				break;
			}
		}

		if(coreHUD.shouldCoreMove())
		{
			const Uint8 *keyState = SDL_GetKeyboardState(nullptr);

			if(keyState[SDL_SCANCODE_T]) cam.moveUp(moveSpeed * dt);
			if(keyState[SDL_SCANCODE_G]) cam.moveUp(-moveSpeed * dt);
			if(keyState[SDL_SCANCODE_W]) cam.moveForward(moveSpeed * dt);
			if(keyState[SDL_SCANCODE_S]) cam.moveForward(-moveSpeed * dt);
			if(keyState[SDL_SCANCODE_D]) cam.moveRight(moveSpeed * dt);
			if(keyState[SDL_SCANCODE_A]) cam.moveRight(-moveSpeed * dt);
			if(keyState[SDL_SCANCODE_LSHIFT]) moveSpeed = 50.f; else moveSpeed=10.0f;
			cam.updateCameraAngle(glm::radians(cameraAngle.y)* dt , glm::radians(cameraAngle.x) * dt);
		}
		coreHUD.update();

		//need to use the shader before the operation after it, TODO: need to fix this crap...
		ResourceManager::getShader("meshShader")->use();
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, value_ptr(cam.getViewMatrix()));

		render();

		SDL_GL_SwapWindow(mainwindow);
	}
	postLoop();
}
void Core::setplaceAgents(bool placeAgentsFlag){
	placeAgents = placeAgentsFlag;
}
void Core::getagentAttrbyID(int agentID)
{
	Agent* currentagent = pipeline.getAgentByID(agentID);
	std::map<std::string,AgentAttribute*> agentAttributes;
	agentAttributes = currentagent->getAllAttributes();
	string elementText;
	typedef std::map<std::string,AgentAttribute*>::iterator iter;
	for(iter iterator = agentAttributes.begin(); iterator != agentAttributes.end(); iterator++) {
			string name = iterator->first;
			AgentAttribute* agentattr = iterator->second;
			if (dynamic_cast<const AgentAttributeBool*>(agentattr)) {
					const AgentAttributeBool* temp = dynamic_cast<const AgentAttributeBool*>(agentattr);
					elementText = "<input type =\"checkbox name=\"";
					elementText.append(temp->getName());
					elementText.append("value=");
					if (temp->getValue()){
							elementText.append("true  checked> ");}
					else{
							elementText.append("false>");}
					elementText.append(temp->getName());
					elementText.append("<br>");
					coreHUD.addBoolhud(elementText);
			}
			else if (dynamic_cast<const AgentAttributeEnum*>(agentattr)) {
					const AgentAttributeEnum* temp = dynamic_cast<const AgentAttributeEnum*>(agentattr);
					elementText = "<div class=\"dropdown\"> <button onclick=\"onDropDownClick()\" class=\"dropbtn\">Options</button> <div id=\"optionsDropDown\" class=\"dropdown-content\">";
					vector<string> possibleValues = temp->getPossibleValues();
					for (int i = 0; i < possibleValues.size(); i++){
						elementText.append("<a>");
						elementText.append(possibleValues.at(i));
						elementText.append("</a>");
					}
					coreHUD.addDropdownhud(elementText);
			}
			else if (dynamic_cast<const AgentAttributeFloat*>(agentattr)) {\
					const AgentAttributeFloat* temp = dynamic_cast<const AgentAttributeFloat*>(agentattr);\
					elementText = temp->getName();
					elementText.append("<input type=\"number\" step=\"0.1\" onkeypress=\"return isFloat(event)\" value=");
					elementText.append(to_string(temp->getValue()));
					elementText.append("\" min=\"");
					elementText.append(to_string(temp->getMinValue()));
					elementText.append("\" max=\"");
					elementText.append(to_string(temp->getMaxValue()));
					elementText.append("\" />");
					coreHUD.addFloathud(elementText);
			}
			else if (dynamic_cast<const AgentAttributeInt*>(agentattr)) {
					const AgentAttributeInt* temp = dynamic_cast<const AgentAttributeInt*>(agentattr);
					elementText = temp->getName();
					elementText.append("<input type=\"number\" step=\"1\" onkeypress=\"return isInt(event)\" value=");
					elementText.append(to_string(temp->getValue()));
					elementText.append("\" min=\"");
					elementText.append(to_string(temp->getMinValue()));
					elementText.append("\" max=\"");
					elementText.append(to_string(temp->getMaxValue()));
					elementText.append("\" />");
				//	attributeToDraw = new AgentAttributeInt(temp->getValue(),
				//						temp->getMinValue(),temp->getMaxValue(), temp->getName());
					coreHUD.addInthud(elementText);
			}
	    // iterator->first = key
	    // iterator->second = value
	    // Repeat if you also want to iterate through the second map.
	}
}

void Core::loadBehaviorModules(){
	auto behlist = BehaviorModuleFactory::getBehList();
	for(std::string force: behlist.first){
		coreHUD.addNewForce(force);
	}
	for(std::string milestone:behlist.second){
		coreHUD.addNewMilestone(milestone);
	}
}

void Core::addFtoPipeline(std::string Force){
	pipeline.addForcesModule(Force);
}
void Core::addMtoPipeline(std::string Milestone){
	pipeline.addMilestonesModule(Milestone);
}
