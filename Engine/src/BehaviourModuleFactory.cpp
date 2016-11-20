#include "BehaviourModuleFactory.h"
using namespace std;

const string BehaviourModuleFactory::libraryPath = "Libraries/Behaviour/";

Behaviour BehaviourModuleFactory::newBeh(std::string behName)
{
	return Behaviour(behName.c_str(), (libraryPath + behName + "/" + behName + ".so").c_str());
}
