#include <cstdio>
#include <cstring>
#include <unistd.h>
#include "BehaviourModuleFactory.h"
#include "DummyBeh.h"
using namespace std;

//Behaviour Implementation
bool Behaviour::validity() const
{
	return name.size() != 0 && type != Type::Null;
}

//BehaviourModuleFactory Implementation:
const string BehaviourModuleFactory::libraryPath = "Behaviour/";

AbstractBehaviourModule* BehaviourModuleFactory::construct(std::string behName)
{
	//Checks if behaviour file exist and have read permission.
	if(access((libraryPath + behName + ".beh").c_str(), F_OK | R_OK) == -1) return nullptr;

	/*
		TODO: Read file content, build, link shared object, ... etc.
	*/

	return new Dummy();
}

Behaviour BehaviourModuleFactory::getMetaData(std::string behName)
{
	//Constructs an invalid Behaviour
	Behaviour ret; ret.type = Behaviour::Type::Null;

	char buf[1000];
	FILE* behFile;

	//Checks if behaviour file exist and have read permission.
	if((behFile = fopen((libraryPath + behName + ".beh").c_str(), "r")) == nullptr) return ret;

	//For now Assuming no whitespaces.

	//Name:
	fscanf(behFile, "%s\n", buf);
	ret.name = buf;

	//Type:
	fscanf(behFile, "%s\n", buf);
	if(strcmp(buf, "Milestone") == 0) ret.type = Behaviour::Type::Milestone;
	else if(strcmp(buf, "Force") == 0) ret.type = Behaviour::Type::Force;
	else ret.type = Behaviour::Type::Null;


	//Navigation Dependencies
	while(fscanf(behFile, "%[^;\n]%*[;\n]", buf) != EOF)
		ret.navDependencies.push_back(string(buf));
	return ret;
}
