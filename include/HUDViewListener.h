#pragma once
#include <Awesomium/WebCore.h>
#include <iostream>
using namespace Awesomium;
class HUDViewListener  : public WebViewListener::View {
  virtual void OnAddConsoleMessage	(	Awesomium::WebView * 	caller,const Awesomium::WebString & 	message,int 	line_number,const Awesomium::WebString & 	source );
  virtual void 	OnChangeAddressBar (Awesomium::WebView *caller, const Awesomium::WebURL &url);
  virtual void OnChangeTitle (Awesomium::WebView *caller, const Awesomium::WebString &title);
  virtual void OnChangeTargetURL (Awesomium::WebView *caller, const Awesomium::WebURL &url);
  virtual void 	OnChangeTooltip (Awesomium::WebView *caller, const Awesomium::WebString &tooltip);
  virtual void OnChangeCursor (Awesomium::WebView *caller, Awesomium::Cursor cursor);
  virtual void 	OnChangeFocus (Awesomium::WebView *caller, Awesomium::FocusedElementType focused_type);
  virtual void 	OnShowCreatedWebView (Awesomium::WebView *caller, Awesomium::WebView *new_view, const Awesomium::WebURL &opener_url, const Awesomium::WebURL &target_url, const Awesomium::Rect &initial_pos, bool is_popup);

};
