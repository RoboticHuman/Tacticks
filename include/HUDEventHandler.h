#pragma once
#include <Awesomium/WebCore.h>

class HUDEventHandler : public Awesomium::JSMethodHandler, public Awesomium::WebViewListener::Menu, public Awesomium::WebViewListener::View
{
//JSMethodHandler
	void OnMethodCall (Awesomium::WebView*, unsigned int, const Awesomium::WebString&, const Awesomium::JSArray&);
	Awesomium::JSValue OnMethodCallWithReturnValue(Awesomium::WebView*, unsigned int, const Awesomium::WebString&, const Awesomium::JSArray&);

//WebViewListener::Menu
	void OnShowPopupMenu(Awesomium::WebView*, const Awesomium::WebPopupMenuInfo&);
	void OnShowContextMenu(Awesomium::WebView*, const Awesomium::WebContextMenuInfo&);

//WebViewListener::View
	void OnAddConsoleMessage(Awesomium::WebView*, const Awesomium::WebString&, int, const Awesomium::WebString&);
	void OnChangeAddressBar(Awesomium::WebView*, const Awesomium::WebURL&);
	void OnChangeTitle(Awesomium::WebView*, const Awesomium::WebString&);
	void OnChangeTargetURL(Awesomium::WebView*, const Awesomium::WebURL&);
	void OnChangeTooltip(Awesomium::WebView*, const Awesomium::WebString&);
	void OnChangeCursor(Awesomium::WebView*, Awesomium::Cursor);
	void OnChangeFocus(Awesomium::WebView*, Awesomium::FocusedElementType);
	void OnShowCreatedWebView (Awesomium::WebView*, Awesomium::WebView*, const Awesomium::WebURL&, const Awesomium::WebURL&, const Awesomium::Rect&, bool);

private:
	bool textInputFocused = false;
public:
	bool isTextInputFocused();
};
