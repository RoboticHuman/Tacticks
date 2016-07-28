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
  WebURL url(WSLit("https://www.google.com"));
  web_view->LoadURL(url);
  while(web_view->IsLoading())
  //WTF IS THIS LINE BELOW THIS COMMENT!!!!
  //web_view->SetTransparent(true);
  web_core->Update();
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
    surface->CopyTo(buffer, w * 4, 4, false, false);
    sprite->setTexture(w,h,buffer);
  }

  delete []buffer;
}

void HUD::render()
{
  sprite->draw();
}
