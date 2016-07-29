#pragma once
#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>
#include "Sprite.h"
#include <SDL2/SDL.h>

class Shader;
class HUD{
	Awesomium::WebCore* web_core;
	Awesomium::WebConfig web_config;
	Awesomium::WebView* web_view;
	Awesomium::WebSession* web_session;
	Sprite *sprite;
public:
	HUD()=default;
	~HUD()=default;
	void init(int screenWidth, int screenHeight);
	void shutdown();
	void update();
	void render();

	//Input Injection
	void mouseMoveTo(int, int);

	void mouseLeftDown();
	void mouseRightDown();
	void mouseMiddleDown();

	void mouseLeftUp();
	void mouseRightUp();
	void mouseMiddleUp();

	void handleKeyPress(const SDL_Event &event);
	int getWebKeyFromSDLKey(SDL_Keycode key); //helper function for mapping between SDL and Awesomium key codes ;)
};
