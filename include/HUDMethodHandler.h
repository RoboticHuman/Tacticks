#pragma once
#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>

class HUDMethodHandler : public Awesomium::JSMethodHandler
{

public:
	void OnMethodCall (Awesomium::WebView*, unsigned int, const Awesomium::WebString&, const Awesomium::JSArray&);
	Awesomium::JSValue OnMethodCallWithReturnValue(Awesomium::WebView*, unsigned int, const Awesomium::WebString&, const Awesomium::JSArray&);
};
