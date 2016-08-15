#pragma once
#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>
#include <SDL2/SDL.h>
#include <string>
#include "Sprite.h"

class Shader;
class HUDEventHandler;
class JSHandler;

class HUD{
	Awesomium::WebCore* web_core;
	Awesomium::WebConfig web_config;
	Awesomium::WebView* web_view;
	Awesomium::WebSession* web_session;
	Awesomium::DataSource* data_source;
	HUDEventHandler* event_handler;
	JSHandler* js_handler;
	Sprite *sprite;

	//ConversionFunctions
	static Awesomium::MouseButton SDLToAwesomium(Uint8);
	static int SDLToAwesomium(SDL_Keycode);
	static bool isCharTypeKey(const SDL_Keysym&);
	static char applyModifiers(int, int);
	static Awesomium::WebKeyboardEvent SDLToAwesomium(SDL_KeyboardEvent, bool = false);
public:
	HUD() = default;
	~HUD() = default;

	void init(int screenWidth, int screenHeight);
	void shutdown();
	void update();
	void render();

	void injectEvent(const SDL_Event&);

	bool shouldCoreMove() const;
};
