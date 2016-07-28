#include "HUD.h"
#include <Awesomium/BitmapSurface.h>
#include "Shader.h"
#include "ResourceManager.h"
using namespace Awesomium;
#include <iostream>
using namespace std;
void HUD::init()
{
	web_config.log_path = WSLit("awesomiumLog.log");
	web_config.log_level = kLogLevel_Normal;
	web_core = WebCore::Initialize(web_config);
	web_view = web_core->CreateWebView(800, 600);
	//WebURL url(WSLit("https://www.google.com"));
	WebURL url(WSLit("file:///home/danmaklen/Desktop/Projects/Work/Thesis/Tacticks/HUDAssets/test"));
	web_view->LoadURL(url);
	web_view->SetTransparent(true);
	while(web_view->IsLoading()) web_core->Update();
	sprite = new Sprite(ResourceManager::getShader("hudShader"));
}

void HUD::shutdown()
{
  web_view->Destroy();
  WebCore::Shutdown();
}


void HUD::update()
{
	web_core->Update();
	BitmapSurface* surface = (BitmapSurface*)web_view->surface();
	int w = surface->width();
	int h = surface->height();
	unsigned char *buffer = new unsigned char[w * h * 4];
	if (surface != 0)
	{
		surface->CopyTo(buffer, w * 4, 4, true, false);
		sprite->setTexture(w,h,buffer);
	}
	delete [] buffer;
}

void HUD::render()
{
  sprite->draw();
}
