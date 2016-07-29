#include "HUD.h"
#include <Awesomium/BitmapSurface.h>
#include "Shader.h"
#include "ResourceManager.h"
#include "HUDDataSource.h"
#include <iostream>
using namespace std;
using namespace Awesomium;

void HUD::init(int screenWidth, int screenHeight)
{
	web_config.log_path = WSLit("awesomiumLog.log");
	web_config.log_level = kLogLevel_Normal;
	web_core = WebCore::Initialize(web_config);
  web_session = web_core->CreateWebSession(WebString(WSLit("")),WebPreferences());
  DataSource* data_source = new HUDDataSource();
  web_session->AddDataSource(WSLit("Tacticks"), data_source);
	web_view = web_core->CreateWebView(screenWidth, screenHeight,web_session,kWebViewType_Offscreen);
	sprite = new Sprite(ResourceManager::getShader("hudShader"),screenWidth,screenHeight);
	WebURL url(WSLit("asset://Tacticks/HUDAssets/test"));
	web_view->LoadURL(url);
	web_view->SetTransparent(true);
	web_view->Focus();
	while(web_view->IsLoading()) web_core->Update();
}

void HUD::shutdown()
{
	delete sprite;
	web_view->Destroy();
  web_session->Release();
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

void HUD::handleKeyPress(const SDL_Event &event)
{
  if (!(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP))
    return;

  Awesomium::WebKeyboardEvent keyEvent;

  keyEvent.type = event.type == SDL_KEYDOWN?
                  Awesomium::WebKeyboardEvent::kTypeKeyDown :
                  Awesomium::WebKeyboardEvent::kTypeKeyUp;
  char* buf = new char[20];
  keyEvent.virtual_key_code = getWebKeyFromSDLKey(event.key.keysym.sym);
  cout<<keyEvent.virtual_key_code<<endl;
  Awesomium::GetKeyIdentifierFromVirtualKeyCode(keyEvent.virtual_key_code,
      &buf);
  strcpy(keyEvent.key_identifier, buf);
  delete[] buf;

  keyEvent.modifiers = 0;

  keyEvent.native_key_code = event.key.keysym.scancode;
  if (event.type == SDL_KEYUP) {
    web_view->InjectKeyboardEvent(keyEvent);
  } else {
    unsigned int chr;
    chr = keyEvent.virtual_key_code;

    keyEvent.text[0] = chr;
    keyEvent.unmodified_text[0] = chr;

    web_view->InjectKeyboardEvent(keyEvent);

    if (chr) {
      keyEvent.type = Awesomium::WebKeyboardEvent::kTypeChar;
      keyEvent.virtual_key_code = chr;
      keyEvent.native_key_code = chr;
      web_view->InjectKeyboardEvent(keyEvent);
    }
  }
}

#define mapKey(a, b) case SDLK_##a: return Awesomium::KeyCodes::AK_##b;

/// Get an Awesomium KeyCode from an SDLKey Code
int HUD::getWebKeyFromSDLKey(SDL_Keycode key) {
  switch (key) {
    mapKey(BACKSPACE, BACK)
    mapKey(TAB, TAB)
    mapKey(CLEAR, CLEAR)
    mapKey(RETURN, RETURN)
    mapKey(PAUSE, PAUSE)
    mapKey(ESCAPE, ESCAPE)
    mapKey(SPACE, SPACE)
    mapKey(a, A)
    mapKey(b, B)
    mapKey(c, C)
    mapKey(d, D)
    mapKey(e, E)
    mapKey(f, F)
    mapKey(g, G)
    mapKey(h, H)
    mapKey(i, I)
    mapKey(j, J)
    mapKey(k, K)
    mapKey(l, L)
    mapKey(m, M)
    mapKey(n, N)
    mapKey(o, O)
    mapKey(p, P)
    mapKey(q, Q)
    mapKey(r, R)
    mapKey(s, S)
    mapKey(t, T)
    mapKey(u, U)
    mapKey(v, V)
    mapKey(w, W)
    mapKey(x, X)
    mapKey(y, Y)
    mapKey(z, Z)
    mapKey(0, 0)
    mapKey(1, 1)
    mapKey(2, 2)
    mapKey(3, 3)
    mapKey(4, 4)
    mapKey(5, 5)
    mapKey(6, 6)
    mapKey(7, 7)
    mapKey(8, 8)
    mapKey(9, 9)
  default:
    return Awesomium::KeyCodes::AK_UNKNOWN;
  }
}
