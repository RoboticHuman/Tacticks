#include "BehaviourModuleFactory.h"
#include <dirent.h>
#include <sys/stat.h>
using namespace std;

const string BehaviourModuleFactory::libraryPath = "Libraries/Behaviour/";

Behaviour BehaviourModuleFactory::getBeh(std::string behName, bool Force_Milestone)
{
	string flag = (Force_Milestone ? "f" : "m");
	return Behaviour(behName.c_str(), (libraryPath + flag + behName + "/" + behName + ".so").c_str());
}
pair<vector<string>, vector<string>> BehaviourModuleFactory::getBehList()
{
	pair<vector<string>, vector<string>> ret;
	vector<string>& forces = ret.first;
	vector<string>& milestones = ret.second;

	DIR* behLibrary = opendir(libraryPath.c_str());
	dirent* beh;
	while(beh = readdir(behLibrary)){
		struct stat s;
		if(stat((libraryPath + "/" + string(beh->d_name)).c_str(), &s) || ~s.st_mode & S_IFDIR) continue;	//Skipping non-folders
		if(beh->d_name[0] == 'f' || beh->d_name[0] == 'F') forces.push_back(string(beh->d_name + 1));
		if(beh->d_name[0] == 'm' || beh->d_name[0] == 'M') milestones.push_back(string(beh->d_name + 1));
	}

	return ret;
}
