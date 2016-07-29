#pragma once
#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>
#include "Sprite.h"

class Shader;
class HUD{
	Awesomium::WebCore* web_core;
	Awesomium::WebConfig web_config;
	Awesomium::WebView* web_view;
	Sprite *sprite;
public:
	HUD()=default;
	~HUD()=default;
	void init();
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

	void keyDown(int);	//int for quick test
	void keyUp(int);	//int for quick test  
};
