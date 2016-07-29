#include "HUD.h"
#include <Awesomium/BitmapSurface.h>
#include "Shader.h"
#include "ResourceManager.h"
using namespace Awesomium;

void HUD::init()
{
	web_config.log_path = WSLit("awesomiumLog.log");
	web_config.log_level = kLogLevel_Normal;
	web_core = WebCore::Initialize(web_config);
	web_view = web_core->CreateWebView(800, 600);
	sprite = new Sprite(ResourceManager::getShader("hudShader"));


	WebURL url(WSLit("file:///home/danmaklen/Desktop/Projects/Work/Thesis/Tacticks/HUDAssets/test"));
	web_view->LoadURL(url);
	web_view->SetTransparent(true);
	web_view->Focus();

	while(web_view->IsLoading()) web_core->Update();
}

void HUD::shutdown()
{
	delete sprite;
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

void HUD::mouseMoveTo(int x, int y)
{
	web_view->InjectMouseMove(x, y);
}

void HUD::mouseLeftDown()
{
	web_view->InjectMouseDown(kMouseButton_Left);
}
void HUD::mouseRightDown()
{
	web_view->InjectMouseDown(kMouseButton_Right);
}
void HUD::mouseMiddleDown()
{
	web_view->InjectMouseDown(kMouseButton_Middle);
}

void HUD::mouseLeftUp()
{
	web_view->InjectMouseUp(kMouseButton_Left);
}
void HUD::mouseRightUp()
{
	web_view->InjectMouseUp(kMouseButton_Right);
}
void HUD::mouseMiddleUp()
{
	web_view->InjectMouseUp(kMouseButton_Middle);
}

#include <iostream>
using namespace std;

void HUD::keyDown(int key){
	WebKeyboardEvent event;
	event.type = WebKeyboardEvent::kTypeKeyDown;

	event.virtual_key_code = Awesomium::KeyCodes::AK_A;


	web_view->InjectKeyboardEvent(event);
	cout << "hmmmDown" << endl;

}

void HUD::keyUp(int key){
	WebKeyboardEvent event;
	event.type = WebKeyboardEvent::kTypeKeyUp;

	event.virtual_key_code = Awesomium::KeyCodes::AK_A;

	cout << "hmmmUp" << endl;
	web_view->InjectKeyboardEvent(event);
}
