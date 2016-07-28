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
};
