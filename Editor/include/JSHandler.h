#pragma once
#include <Awesomium/WebCore.h>
#include <string>
#include <vector>

class Core;

class JSHandler{
	Awesomium::JSObject mainObject;
private:
	struct trieNode{
		std::vector<int> edge = std::vector<int>(128, -1);
		void(JSHandler::*funcPtr)(Awesomium::JSArray) = nullptr;
		Awesomium::JSValue(JSHandler::*funcPtrWithReturn)(Awesomium::JSArray) = nullptr;
	};
	std::vector<trieNode> trie;
public:
	JSHandler() = default;
	~JSHandler() = default;

	void init(Awesomium::JSObject);
	void shutdown();

	void registerCallback(std::string, void(JSHandler::*)(Awesomium::JSArray));
	void registerCallback(std::string, Awesomium::JSValue(JSHandler::*)(Awesomium::JSArray));
	void callback(std::string, Awesomium::JSArray);
	Awesomium::JSValue callbackWithReturn(std::string, Awesomium::JSArray);

public:	//static class instances Exists only until we remove the hardcoding
	static Core *coreInstance;

private:	//callbacks
	void loadMesh(Awesomium::JSArray);
	Awesomium::JSValue getDefaultPath(Awesomium::JSArray);
public:		//JS Method Calls
	void JSCallExamples(std::string);
};
