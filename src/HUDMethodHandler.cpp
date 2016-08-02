#include "HUDMethodHandler.h"
#include <iostream>
using namespace std;
using namespace Awesomium;

void HUDMethodHandler::OnMethodCall (WebView* webView, unsigned int objID, const WebString& method, const Awesomium::JSArray& args){
	if(method == WSLit("ConsoleLog"))
		cout << args.At(0).ToString() << endl;
	else cout << "Unknown Method " << method << endl;
}

JSValue HUDMethodHandler::OnMethodCallWithReturnValue(WebView* webView, unsigned int objID, const WebString& method, const JSArray& args){
	cout << "Unknown Method " << method << endl;
	return JSValue();
}
