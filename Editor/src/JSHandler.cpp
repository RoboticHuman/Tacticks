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
	registerCallback("toggleDebugNavMesh", &JSHandler::toggleDebugNavMesh);
	registerCallback("getDefaultPath", &JSHandler::getDefaultPath);
	registerCallback("getAttrforAgent", &JSHandler::getAttrforAgent);
  	registerCallback("loadBehaviorModules", &JSHandler::loadBehaviorModules);
	registerCallback("addFtoPipeline", &JSHandler::addFtoPipeline);
	registerCallback("addMtoPipeline", &JSHandler::addMtoPipeline);
	registerCallback("toggleSimulationState", &JSHandler::toggleSimulationState);


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
	coreInstance->renderDebugMesh();
}

void JSHandler::toggleSimulationState(JSArray args){
	coreInstance->simulateAgents(args.At(0).ToBoolean());
}
void JSHandler::togglePlacingAgents(JSArray args)
{
	coreInstance->setplaceAgents(args.At(0).ToBoolean());
}

void JSHandler::toggleDebugNavMesh(JSArray args)
{
	coreInstance->toggleDNavMesh(args.At(0).ToInteger());
}
void JSHandler::addFtoPipeline(JSArray args){
	//coreInstance->addFtoPipeline(Awesomium::ToString(args.At(0).ToString()));
}
void JSHandler::addMtoPipeline(JSArray args){
	coreInstance->addMtoPipeline(Awesomium::ToString(args.At(0).ToString()));
}
void JSHandler::getAttrforAgent(JSArray args)
{
	coreInstance->getagentAttrbyID(args.At(0).ToInteger());
}
void JSHandler::loadBehaviorModules(JSArray args){
	coreInstance->loadBehaviorModules();
}

void JSHandler::addNewForce(string forceName){
	JSArray args;
	args.Push(WSLit(forceName.c_str()));
	mainObject.Invoke(WSLit("addNewForce"), args);
}
void JSHandler::addNewMilestone(string milestoneName){
	JSArray args;
	args.Push(WSLit(milestoneName.c_str()));
	mainObject.Invoke(WSLit("addNewMilestone"), args);
}

void JSHandler::addDebugMesh(string debugMeshName){
	JSArray args;
	args.Push(WSLit(debugMeshName.c_str()));
	mainObject.Invoke(WSLit("addDebugMesh"), args);
}
void JSHandler::addAgent(int agentID){
	JSArray args;
	std::string agent = std::to_string(agentID);
	args.Push(WSLit(agent.c_str()));
	mainObject.Invoke(WSLit("addAgent"), args);
}

void JSHandler::addAttrtoHud(string elementText){
	JSArray args;
	args.Push(WSLit(elementText.c_str()));
	mainObject.Invoke(WSLit("addAttrtoHud"), args);
}
JSValue JSHandler::getDefaultPath(JSArray args)
{
	return JSValue(WSLit("EditorAssets/models/old fashion town/old town block.obj"));
}
void JSHandler::JSCallExamples(string str){	//P.S. This calls a function "setTextboxValue" with 1 string argument P.S. Not intended to be called just there for reference
	JSArray args;
	args.Push(WSLit(str.c_str()));
	mainObject.Invoke(WSLit("setTextboxValue"), args);
}
