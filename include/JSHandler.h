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
	};
	std::vector<trieNode> trie;
public:
	JSHandler() = default;
	~JSHandler() = default;

	void init(Awesomium::JSObject);
	void shutdown();

	void registerCallback(std::string, void(JSHandler::*)(Awesomium::JSArray)); //Assuming all functions doesn't return types for now.
	void callback(std::string, Awesomium::JSArray);	//Callback from JS

public:	//static class instances Exists only until we remove the hardcoding
	static Core *coreInstance;

private:	//callbacks
	void loadMesh(Awesomium::JSArray);

public:		//JS Method Calls
	void JSCallExamples(std::string);
};
