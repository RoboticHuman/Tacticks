#pragma once
#include <Awesomium/WebCore.h>
#include <iostream>
using namespace Awesomium;
class HUDMenuHandler : public WebViewListener::Menu{
  virtual void OnShowPopupMenu(Awesomium::WebView* caller, const WebPopupMenuInfo& menuInfo);
  virtual void OnShowContextMenu(Awesomium::WebView *view,const Awesomium::WebContextMenuInfo &info);
private:
  /* data */
public:
  HUDMenuHandler ()= default;
  virtual ~HUDMenuHandler ()=default;
};
