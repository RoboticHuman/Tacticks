#pragma once
#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>
#include <SDL2/SDL.h>
#include <string>
#include "Sprite.h"

class Shader;
class HUDEventHandler;
class JSHandler;
/**
 * @brief      Class for hud with Awesomium support. Capturing hud inputs, updating and rendering of it happens here.
 */
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
	/**
	 * @brief      An initialization function that loads the necessary structures and makes connections with Awesomium.
	 *
	 * The HTML file needed by the HUD is loaded. A web session is created and a web view is linked to it and event handlers are linked.
	 * @param[in]  screenWidth   The screen width
	 * @param[in]  screenHeight  The screen height
	 */
	void init(int screenWidth, int screenHeight);
	/**
	 * @brief      Releases Awesomium datastructures and extra structures related to event handling
	 */
	void shutdown();
	/**
	 * @brief      Updating of the HUD based on retrieving the current look of the webview in the form of a texture from Awesomium and writing that texture to an OpenGL buffer.
	 */
	void update();
	/**
	 * @brief      Draws the sprite on which the texture of the HUD is loaded.
	 */
	void render();
	/**
	 * @brief      A function that captures SDL events and extracts mouse and keyboard events from them and handles them separately with Awesomium.
	 *
	 * @param[in]  event  The SDL event that has the keyboard and mouse events to use in updating the HUD.
	 */
	void injectEvent(const SDL_Event&);
	/**
	 * @brief      A function that decides whether or not motion in the editor should be allowed based on focus changes in the webview
	 *
	 * @return     Whether motion in the editor should be allowed or not.
	 */
	bool shouldCoreMove() const;
	void addAgenthud(int);
	void addBoolhud(std::string);
	void addInthud(std::string);
	void addFloathud(std::string);
	void addDropdownhud(std::string);
	void addNewForce(std::string);
	void addNewMilestone(std::string);
};
