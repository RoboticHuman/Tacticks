#include <Awesomium/STLHelpers.h>
#include <iostream>
#include "JSHandler.h"
#include "HUDEventHandler.h"
using namespace std;
using namespace Awesomium;

//JSMethodHandler
void HUDEventHandler::OnMethodCall(WebView* webView, unsigned int objID, const WebString& method, const JSArray& args){
	js_handler->callback(ToString(method), args);
}
JSValue HUDEventHandler::OnMethodCallWithReturnValue(WebView* webView, unsigned int objID, const WebString& method, const JSArray& args){
	cout << "Unknown Method " << method << endl;
	return JSValue();
}

//WebViewListener::Menu
void HUDEventHandler::OnShowPopupMenu(WebView* caller, const WebPopupMenuInfo& popupMenuInfo)
{
	auto items = popupMenuInfo.items;
	for(int i = 0; i < items.size(); i++) cout << ToString(items[i].label) << endl;
}
void HUDEventHandler::OnShowContextMenu(WebView* caller, const WebContextMenuInfo& contextMenuInfo)
{

}

//WebViewListener::View
void HUDEventHandler::OnAddConsoleMessage(WebView* caller, const WebString& message, int line_number, const WebString& source)
{
	cout << ToString(message) + "at line number: " + std::to_string(line_number) << endl;
}
void HUDEventHandler::OnChangeAddressBar(WebView* caller, const WebURL& url)
{

}
void HUDEventHandler::OnChangeTitle(WebView* caller, const WebString& title)
{

}
void HUDEventHandler::OnChangeTargetURL(WebView* caller, const WebURL& url)
{

}
void HUDEventHandler::OnChangeCursor(WebView* caller, Cursor cursor)
{

}
void HUDEventHandler::OnChangeTooltip(WebView* caller, const WebString& tooltip)
{

}
void HUDEventHandler::OnChangeFocus(WebView* caller, FocusedElementType focused_type)
{
	if(focused_type == kFocusedElementType_None) textInputFocused=false;
	else if(focused_type == kFocusedElementType_TextInput) textInputFocused=true;
}
void HUDEventHandler::OnShowCreatedWebView(WebView* caller, WebView* new_view, const WebURL& opener_url, const WebURL& target_url, const Rect& initial_pos, bool is_popup)
{

}

//
HUDEventHandler::HUDEventHandler(JSHandler* jsh)
{
	js_handler = jsh;
}
bool HUDEventHandler::isTextInputFocused()
{
	return textInputFocused;
}
