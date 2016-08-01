#pragma once
#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>
#include "Sprite.h"
#include <SDL2/SDL.h>
#include <string>

class Shader;
class HUD{
	Awesomium::WebCore* web_core;
	Awesomium::WebConfig web_config;
	Awesomium::WebView* web_view;
	Awesomium::WebSession* web_session;
	Sprite *sprite;

	//ConversionFunctions
	static Awesomium::MouseButton SDLToAwesomium(Uint8);
	static int SDLToAwesomium(SDL_Keycode);
	static bool isCharTypeKey(const SDL_Keysym&);
	static char applyModifiers(int, int);
	static Awesomium::WebKeyboardEvent SDLToAwesomium(SDL_KeyboardEvent, bool = false);

public:
	HUD()=default;
	~HUD()=default;
	void init(int screenWidth, int screenHeight);
	void shutdown();
	void update();
	void render();

	//Input Injection
	void injectEvent(const SDL_Event&);

	void handleKeyPress(const SDL_Event &event);
	int getWebKeyFromSDLKey(SDL_Keycode key); //helper function for mapping between SDL and Awesomium key codes ;)

	void setTextboxValue(std::string);
};
