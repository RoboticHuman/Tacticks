#include "HUDViewListener.h"
#include <Awesomium/STLHelpers.h>
void HUDViewListener::OnAddConsoleMessage	(	Awesomium::WebView * 	caller,const Awesomium::WebString & 	message,int 	line_number,const Awesomium::WebString & 	source )
{
  std::cout<<ToString(message)+"at line number: "+std::to_string(line_number)<<std::endl;
}
void 	HUDViewListener::OnChangeAddressBar (Awesomium::WebView *caller, const Awesomium::WebURL &url)
{

}

bool HUDViewListener::isTextInputFocused()
{
  return textInputFocused;
}

void HUDViewListener::OnChangeTitle (Awesomium::WebView *caller, const Awesomium::WebString &title)
{

}
void HUDViewListener::OnChangeTargetURL (Awesomium::WebView *caller, const Awesomium::WebURL &url)
{

}

void HUDViewListener::OnChangeCursor (Awesomium::WebView *caller, Awesomium::Cursor cursor)
{

}

void 	HUDViewListener::OnChangeTooltip (Awesomium::WebView *caller, const Awesomium::WebString &tooltip)
{

}

void 	HUDViewListener::OnChangeFocus (Awesomium::WebView *caller, Awesomium::FocusedElementType focused_type)
{
  if(focused_type== kFocusedElementType_None) textInputFocused=false; else if(focused_type==kFocusedElementType_TextInput)textInputFocused=true;
}
void 	HUDViewListener::OnShowCreatedWebView (Awesomium::WebView *caller, Awesomium::WebView *new_view, const Awesomium::WebURL &opener_url, const Awesomium::WebURL &target_url, const Awesomium::Rect &initial_pos, bool is_popup)
{

}
