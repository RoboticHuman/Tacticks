#include "JSHandler.h"
#include "Core.h"
using namespace Awesomium;
using namespace std;
#include <iostream>

Core* JSHandler::coreInstance;

void JSHandler::init(JSObject mainObj)
{
	mainObject = mainObj;
	trie.push_back(trieNode());

	registerCallback("loadMesh", &JSHandler::loadMesh);
	registerCallback("togglePlacingAgents", &JSHandler::togglePlacingAgents);
	registerCallback("getDefaultPath", &JSHandler::getDefaultPath);
	registerCallback("getAttrforAgent", &JSHandler::getAttrforAgent);
  registerCallback("loadBehaviorModules", NULL);
}
void JSHandler::shutdown()
{
	trie.clear();
}

void JSHandler::registerCallback(string methodName, void(JSHandler::* funcPtr)(JSArray))
{
	const char* s = methodName.c_str();
	int ind;
	for(ind = 0; *s; ind = trie[ind].edge[*s++])
		if(trie[ind].edge[*s] == -1){
			trie[ind].edge[*s] = trie.size();
			trie.push_back(trieNode());
		}
	if(trie[ind].funcPtr != nullptr) cout << "Unable to register method " << methodName << ". Method name already registered." << endl;
	else
	{
		mainObject.SetCustomMethod(WSLit(methodName.c_str()), false);
		trie[ind].funcPtr = funcPtr;
	}
}
void JSHandler::registerCallback(string methodName, JSValue(JSHandler::* funcPtr)(JSArray))
{
	const char* s = methodName.c_str();
	int ind;
	for(ind = 0; *s; ind = trie[ind].edge[*s++])
		if(trie[ind].edge[*s] == -1){
			trie[ind].edge[*s] = trie.size();
			trie.push_back(trieNode());
		}
	if(trie[ind].funcPtrWithReturn != nullptr) cout << "Unable to register method " << methodName << ". Method name already registered." << endl;
	else
	{
		mainObject.SetCustomMethod(WSLit(methodName.c_str()), true);
		trie[ind].funcPtrWithReturn = funcPtr;
	}
}
void JSHandler::callback(string methodName, JSArray args)
{
	const char* s = methodName.c_str();
	int ind;
	for(ind = 0; *s; ind = trie[ind].edge[*s++])
		if(trie[ind].edge[*s] == -1){
			cout << "Unable to call method " << methodName << ". Method may not be registered" << endl;
			return;
		}
	if(trie[ind].funcPtr == nullptr) cout << "Unable to call method " << methodName << ". Method may not be registered" << endl;
	else (this->*trie[ind].funcPtr)(args);
}
JSValue JSHandler::callbackWithReturn(string methodName, JSArray args)
{
	const char* s = methodName.c_str();
	int ind;
	for(ind = 0; *s; ind = trie[ind].edge[*s++])
		if(trie[ind].edge[*s] == -1){
			cout << "Unable to call method " << methodName << ". Method may not be registered" << endl;
			return JSValue();
		}
	if(trie[ind].funcPtrWithReturn == nullptr) cout << "Unable to call method " << methodName << ". Method may not be registered" << endl;
	else return (this->*trie[ind].funcPtrWithReturn)(args);
	return JSValue();
}

//Callbacks
void JSHandler::loadMesh(JSArray args)
{
	coreInstance->loadMesh(ToString(args.At(0).ToString()).c_str(), true);
}
void JSHandler::togglePlacingAgents(JSArray args)
{
	coreInstance->setplaceAgents(args.At(0).ToBoolean());
}

void JSHandler::addForcetoPipeline(JSHandler args){
	coreInstance->addForcetoPipeline(args.At(0).ToString());
}
void JSHandler::addMilestonetoPipeline(JSHandler args){
	coreInstance->addMilestonetoPipeline(args.At(0).ToString());
}

void JSHandler::getAttrforAgent(JSArray args)
{
	coreInstance->getagentAttrbyID(args.At(0).ToInteger());
}

void JSHandler::loadBehaviorModules(){
		coreInstance->loadBehaviorModules();
}

void JSHandler::addNewBehaviorModule(string elementText, string type){
	JSArray args;
	args.Push(WSLit(elementText.c_str()));
	args.Push(WSLit(type.c_str()));
	mainObject.Invoke(WSLit("addNewBehaviorModule"), args);
}
void JSHandler::addAgent(int agentID){
	JSArray args;
	std::string agent = std::to_string(agentID);
	args.Push(WSLit(agent.c_str()));
	mainObject.Invoke(WSLit("addAgent"), args);
}

void JSHandler::addCheckbox(string elementText){
	JSArray args;
	args.Push(WSLit(elementText.c_str()));
	mainObject.Invoke(WSLit("addcheckbox"), args);
}
void JSHandler::addInt(string elementText){
	JSArray args;
	args.Push(WSLit(elementText.c_str()));
	mainObject.Invoke(WSLit("addint"), args);
}

void JSHandler::addFloat(string elementText){
	JSArray args;
	args.Push(WSLit(elementText.c_str()));
	mainObject.Invoke(WSLit("addfloat"), args);
}

void JSHandler::addDropbox(string elementText){
	JSArray args;
	args.Push(WSLit(elementText.c_str()));
	mainObject.Invoke(WSLit("adddropbox"), args);
}

JSValue JSHandler::getDefaultPath(JSArray args)
{
	return JSValue(WSLit("EditorAssets/models/Small Tropical Island/Small Tropical Island.obj"));
}

void JSHandler::JSCallExamples(string str){	//P.S. This calls a function "setTextboxValue" with 1 string argument P.S. Not intended to be called just there for reference
	JSArray args;
	args.Push(WSLit(str.c_str()));
	mainObject.Invoke(WSLit("setTextboxValue"), args);
}
