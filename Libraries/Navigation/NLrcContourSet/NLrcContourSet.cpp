#include "NLrcContourSet.h"
#include <Tacticks/NavigationFactory.h>
#include <Tacticks/PassObjectInt.h>
#include <Tacticks/PassObjectFloat.h>
#include <Tacticks/PassObjectBool.h>
#include <limits>
#include <cmath>
#include <glm/vec3.hpp>
using namespace std;

NLrcContourSet::NLrcContourSet(const World* world) : AbstractNavigation(world){data = nullptr;}
NLrcContourSet::~NLrcContourSet(){if(data) rcFreeContourSet(data);}

bool NLrcContourSet::init()
{
	const float maxError= dynamic_cast<PassObjectFloat*>(args[0])->getValue();
    const int maxEdgeLen= dynamic_cast<PassObjectInt*>(args[1])->getValue();
    const int buildFlags= dynamic_cast<PassObjectInt*>(args[2])->getValue();
    AbstractNavigation* compactHeightfieldNav = NavigationFactory::getNav("NLrcCompactHeightfield").getNav();
    rcCompactHeightfield* rcCompactHeightfieldData =  static_cast<rcCompactHeightfield*>(compactHeightfieldNav->getRawData()[0]);
    rcContext ctx;
    data = rcAllocContourSet();
    if (!rcBuildContours	(&ctx, *rcCompactHeightfieldData, maxError, maxEdgeLen, *data, buildFlags)) return false;
	return true;
}

vector<PassObject*> NLrcContourSet::getData(string, vector<PassObject*>){return {};}

vector<void*> NLrcContourSet::getRawData()
{
	if(isDirty()){
		if(data) rcFreeContourSet(data);
		data = nullptr;
		init();
	}
	return {data};
}

void NLrcContourSet::constructDebugMesh()
{

}

extern "C"
AbstractNavigation* newNav(const World* world)
{
  return new NLrcContourSet(world);
}

extern "C"
NavigationInfo declareDependencies()
{
  return {{"NLrcCompactHeightfield"}};
}
