#include "HUD.h"
#include <Awesomium/BitmapSurface.h>
#include "Shader.h"
#include "ResourceManager.h"
#include "HUDDataSource.h"
#include "HUDMethodHandler.h"
#include <iostream>
using namespace std;
using namespace Awesomium;

#define mapKey(a, b)	case SDLK_##a:		return Awesomium::KeyCodes::AK_##b
#define mapButton(a, b)	case SDL_BUTTON_##a:return Awesomium::MouseButton::kMouseButton_##b
#define mapChar(a, b) 	case a: return b;

MouseButton HUD::SDLToAwesomium(Uint8 button)
{
	switch(button)
	{
		mapButton(LEFT, Left);
		mapButton(MIDDLE, Middle);
		mapButton(RIGHT, Right);
	}
}
int HUD::SDLToAwesomium(SDL_Keycode key)
{
	switch(key)
	{
		mapKey(BACKSPACE, BACK);
	    mapKey(TAB, TAB);
	    mapKey(CLEAR, CLEAR);
	    mapKey(RETURN, RETURN);
	    mapKey(PAUSE, PAUSE);
	    mapKey(ESCAPE, ESCAPE);
	    mapKey(SPACE, SPACE);
	    mapKey(EXCLAIM, 1);
	    mapKey(QUOTEDBL, 2);
	    mapKey(HASH, 3);
	    mapKey(DOLLAR, 4);
	    mapKey(AMPERSAND, 7);
	    mapKey(QUOTE, OEM_7);
	    mapKey(LEFTPAREN, 9);
	    mapKey(RIGHTPAREN, 0);
	    mapKey(ASTERISK, 8);
	    mapKey(PLUS, OEM_PLUS);
	    mapKey(COMMA, OEM_COMMA);
	    mapKey(MINUS, OEM_MINUS);
	    mapKey(PERIOD, OEM_PERIOD);
	    mapKey(SLASH, OEM_2);
	    mapKey(0, 0);
	    mapKey(1, 1);
	    mapKey(2, 2);
	    mapKey(3, 3);
	    mapKey(4, 4);
	    mapKey(5, 5);
	    mapKey(6, 6);
	    mapKey(7, 7);
	    mapKey(8, 8);
	    mapKey(9, 9);
	    mapKey(COLON, OEM_1);
	    mapKey(SEMICOLON, OEM_1);
	    mapKey(LESS, OEM_COMMA);
	    mapKey(EQUALS, OEM_PLUS);
	    mapKey(GREATER, OEM_PERIOD);
	    mapKey(QUESTION, OEM_2);
	    mapKey(AT, 2);
	    mapKey(LEFTBRACKET, OEM_4);
	    mapKey(BACKSLASH, OEM_5);
	    mapKey(RIGHTBRACKET, OEM_6);
	    mapKey(CARET, 6);
	    mapKey(UNDERSCORE, OEM_MINUS);
	    mapKey(BACKQUOTE, OEM_3);
	    mapKey(a, A);
	    mapKey(b, B);
	    mapKey(c, C);
	    mapKey(d, D);
	    mapKey(e, E);
	    mapKey(f, F);
	    mapKey(g, G);
	    mapKey(h, H);
	    mapKey(i, I);
	    mapKey(j, J);
	    mapKey(k, K);
	    mapKey(l, L);
	    mapKey(m, M);
	    mapKey(n, N);
	    mapKey(o, O);
	    mapKey(p, P);
	    mapKey(q, Q);
	    mapKey(r, R);
	    mapKey(s, S);
	    mapKey(t, T);
	    mapKey(u, U);
	    mapKey(v, V);
	    mapKey(w, W);
	    mapKey(x, X);
	    mapKey(y, Y);
	    mapKey(z, Z);
	    mapKey(DELETE, DELETE);
	    mapKey(KP_0, NUMPAD0);
	    mapKey(KP_1, NUMPAD1);
	    mapKey(KP_2, NUMPAD2);
	    mapKey(KP_3, NUMPAD3);
	    mapKey(KP_4, NUMPAD4);
	    mapKey(KP_5, NUMPAD5);
	    mapKey(KP_6, NUMPAD6);
	    mapKey(KP_7, NUMPAD7);
	    mapKey(KP_8, NUMPAD8);
	    mapKey(KP_9, NUMPAD9);
	    mapKey(KP_PERIOD, DECIMAL);
	    mapKey(KP_DIVIDE, DIVIDE);
	    mapKey(KP_MULTIPLY, MULTIPLY);
	    mapKey(KP_MINUS, SUBTRACT);
	    mapKey(KP_PLUS, ADD);
	    mapKey(KP_ENTER, SEPARATOR);
	    mapKey(KP_EQUALS, UNKNOWN);
	    mapKey(UP, UP);
	    mapKey(DOWN, DOWN);
	    mapKey(RIGHT, RIGHT);
	    mapKey(LEFT, LEFT);
	    mapKey(INSERT, INSERT);
	    mapKey(HOME, HOME);
	    mapKey(END, END);
	    mapKey(PAGEUP, PRIOR);
	    mapKey(PAGEDOWN, NEXT);
	    mapKey(F1, F1);
	    mapKey(F2, F2);
	    mapKey(F3, F3);
	    mapKey(F4, F4);
	    mapKey(F5, F5);
	    mapKey(F6, F6);
	    mapKey(F7, F7);
	    mapKey(F8, F8);
	    mapKey(F9, F9);
	    mapKey(F10, F10);
	    mapKey(F11, F11);
	    mapKey(F12, F12);
	    mapKey(F13, F13);
	    mapKey(F14, F14);
	    mapKey(F15, F15);
	    mapKey(NUMLOCKCLEAR, NUMLOCK);
	    mapKey(CAPSLOCK, CAPITAL);
	    mapKey(SCROLLLOCK, SCROLL);
	    mapKey(RSHIFT, RSHIFT);
	    mapKey(LSHIFT, LSHIFT);
	    mapKey(RCTRL, RCONTROL);
	    mapKey(LCTRL, LCONTROL);
	    mapKey(RALT, RMENU);
	    mapKey(LALT, LMENU);
	    mapKey(MODE, MODECHANGE);
	    mapKey(HELP, HELP);
	    mapKey(PRINTSCREEN, SNAPSHOT);
	    mapKey(SYSREQ, EXECUTE);
		default:
			return Awesomium::KeyCodes::AK_UNKNOWN;
    }
}
bool HUD::isCharTypeKey(const SDL_Keysym& key)
{
	//TODO: Add support for numpad
	bool ret = (key.sym & 0x40000000) == 0;
	if(key.sym == SDLK_ESCAPE || key.sym == SDLK_UNKNOWN) ret = false;
	ret	|=	key.sym == SDLK_KP_PERIOD
		|	key.sym == SDLK_KP_ENTER
		|	key.sym == SDLK_KP_PLUS
		|	key.sym == SDLK_KP_MINUS
		|	key.sym == SDLK_KP_MULTIPLY
		|	key.sym == SDLK_KP_DIVIDE
		;
	if((key.mod & KMOD_NUM) && !(key.mod & KMOD_LSHIFT) && !(key.mod & KMOD_RSHIFT)){
		ret |=	key.sym == SDLK_KP_1
			|	key.sym == SDLK_KP_2
			|	key.sym == SDLK_KP_3
			|	key.sym == SDLK_KP_4
			|	key.sym == SDLK_KP_5
			|	key.sym == SDLK_KP_6
			|	key.sym == SDLK_KP_7
			|	key.sym == SDLK_KP_8
			|	key.sym == SDLK_KP_9
			|	key.sym == SDLK_KP_0
			;
	}
	return ret;
}
char HUD::applyModifiers(int chr, int modifiers)
{
	if(modifiers & WebKeyboardEvent::kModShiftKey) switch(chr){
		case 'a': case 'b': case 'c': case 'd': case 'e':
		case 'f': case 'g': case 'h': case 'i': case 'j':
		case 'k': case 'l': case 'm': case 'n': case 'o':
		case 'p': case 'q': case 'r': case 's': case 't':
		case 'u': case 'v': case 'w': case 'x': case 'y':
		case 'z': return chr + 'A' - 'a';

		case 'A': case 'B': case 'C': case 'D': case 'E':
		case 'F': case 'G': case 'H': case 'I': case 'J':
		case 'K': case 'L': case 'M': case 'N': case 'O':
		case 'P': case 'Q': case 'R': case 'S': case 'T':
		case 'U': case 'V': case 'W': case 'X': case 'Y':
		case 'Z': return chr + 'a' - 'A';

		mapChar('1', '!');
		mapChar('2', '@');
		mapChar('3', '#');
		mapChar('4', '$');
		mapChar('5', '%');
		mapChar('6', '^');
		mapChar('7', '&');
		mapChar('8', '*');
		mapChar('9', '(');
		mapChar('0', ')');

		mapChar('`', ')');
		mapChar('-', '_');
		mapChar('=', '+');
		mapChar('[', '{');
		mapChar(']', '}');
		mapChar(';', ':');
		mapChar('\'', '"');
		mapChar(',', '<');
		mapChar('.', '>');
		mapChar('/', '?');
		mapChar('\\', '|');
	}
	if(modifiers & WebKeyboardEvent::kModIsKeypad){
		switch(chr){
			mapChar(SDLK_KP_1, '1');
			mapChar(SDLK_KP_2, '2');
			mapChar(SDLK_KP_3, '3');
			mapChar(SDLK_KP_4, '4');
			mapChar(SDLK_KP_5, '5');
			mapChar(SDLK_KP_6, '6');
			mapChar(SDLK_KP_7, '7');
			mapChar(SDLK_KP_8, '8');
			mapChar(SDLK_KP_9, '9');
			mapChar(SDLK_KP_0, '0');
		}
	}

	//On all Modifiers
	switch(chr){
		mapChar(SDLK_KP_PERIOD, '.');
		mapChar(SDLK_KP_ENTER, '\r');
		mapChar(SDLK_KP_PLUS, '+');
		mapChar(SDLK_KP_MINUS, '-');
		mapChar(SDLK_KP_MULTIPLY, '*');
		mapChar(SDLK_KP_DIVIDE, '/');
	}
	return chr;
}
WebKeyboardEvent HUD::SDLToAwesomium(SDL_KeyboardEvent event, bool forceCharType)
{
	WebKeyboardEvent retEvent;

		 if(forceCharType)				retEvent.type = WebKeyboardEvent::kTypeChar;
	else if(event.type == SDL_KEYDOWN)	retEvent.type = WebKeyboardEvent::kTypeKeyDown;
	else if(event.type == SDL_KEYUP) 	retEvent.type = WebKeyboardEvent::kTypeKeyUp;

	retEvent.virtual_key_code = SDLToAwesomium(event.keysym.sym);
	retEvent.native_key_code = event.keysym.scancode;

	char* buf = retEvent.key_identifier;
	GetKeyIdentifierFromVirtualKeyCode(retEvent.virtual_key_code, &buf);

	retEvent.modifiers = 0;	//TODO: Yet to be implemented
	if(event.keysym.mod & KMOD_LALT   || event.keysym.mod & KMOD_RALT)	 retEvent.modifiers |= WebKeyboardEvent::kModAltKey;
    if(event.keysym.mod & KMOD_LCTRL  || event.keysym.mod & KMOD_RCTRL)	 retEvent.modifiers |= WebKeyboardEvent::kModControlKey;
    if(event.keysym.mod & KMOD_LSHIFT || event.keysym.mod & KMOD_RSHIFT) retEvent.modifiers |= WebKeyboardEvent::kModShiftKey;
    if(event.keysym.mod & KMOD_NUM)										 retEvent.modifiers |= WebKeyboardEvent::kModIsKeypad;

	int chr = event.keysym.sym;
	retEvent.text[0] = applyModifiers(chr, retEvent.modifiers);
	retEvent.unmodified_text[0] = chr;

	return retEvent;
}

void HUD::init(int screenWidth, int screenHeight)
{
	WebURL url(WSLit("asset://Tacticks/HUDAssets/test"));
	sprite = new Sprite(ResourceManager::getShader("hudShader"),screenWidth,screenHeight);
	data_source = new HUDDataSource();
	method_handler = new HUDMethodHandler();

	web_config.log_path = WSLit("awesomiumLog.log");
	web_config.log_level = kLogLevel_Normal;
	web_core = WebCore::Initialize(web_config);
	web_session = web_core->CreateWebSession(WebString(WSLit("")),WebPreferences());
	web_session->AddDataSource(WSLit("Tacticks"), data_source);

	web_view = web_core->CreateWebView(screenWidth, screenHeight,web_session,kWebViewType_Offscreen);
	web_view->SetTransparent(true);
	web_view->set_js_method_handler(method_handler);
	
	mainObject = web_view->ExecuteJavascriptWithResult(WSLit("window"), WSLit("")).ToObject();
	mainObject.SetCustomMethod(WSLit("ConsoleLog"), false);

	web_view->LoadURL(url);
	web_view->Focus();
	while(web_view->IsLoading()) web_core->Update();

}

void HUD::shutdown()
{
	web_view->Destroy();
	web_session->Release();
	WebCore::Shutdown();
	delete method_handler;
	delete data_source;
	delete sprite;
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

void HUD::injectEvent(const SDL_Event& event)
{
	switch(event.type){
		//Mouse Events
		case SDL_MOUSEMOTION:		web_view->InjectMouseMove(event.motion.x, event.motion.y);		break;
		case SDL_MOUSEBUTTONDOWN:	web_view->InjectMouseDown(SDLToAwesomium(event.button.button));	break;
		case SDL_MOUSEBUTTONUP:		web_view->InjectMouseUp(SDLToAwesomium(event.button.button));	break;
		case SDL_MOUSEWHEEL:		break;

		//Keyboard Events
		case SDL_KEYUP:				web_view->InjectKeyboardEvent(SDLToAwesomium(event.key));		break;
		case SDL_KEYDOWN:
			web_view->InjectKeyboardEvent(SDLToAwesomium(event.key));
			if(isCharTypeKey(event.key.keysym)) web_view->InjectKeyboardEvent(SDLToAwesomium(event.key, true));
		break;
	}
}

void HUD::setTextboxValue(string str)
{
	JSValue window = web_view->ExecuteJavascriptWithResult(WSLit("window"), WSLit(""));
	if (window.IsObject()) {
		JSArray args;
		args.Push(WSLit(str.c_str()));
		window.ToObject().Invoke(WSLit("setTextboxValue"), args);
	}
}
