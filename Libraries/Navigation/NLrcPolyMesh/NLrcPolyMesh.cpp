#include "NLrcPolyMesh.h"
#include <Tacticks/NavigationFactory.h>
#include <Tacticks/PassObjectInt.h>
#include <Tacticks/PassObjectBool.h>
#include <limits>
#include <cmath>
#include <glm/vec3.hpp>
using namespace std;

NLrcPolyMesh::NLrcPolyMesh(const World* world) : AbstractNavigation(world){data = nullptr;}
NLrcPolyMesh::~NLrcPolyMesh(){if(data) rcFreePolyMesh(data);}

bool NLrcPolyMesh::init()
{
	const int nvp= dynamic_cast<PassObjectInt*>(args[0])->getValue();
    AbstractNavigation* contoursetNav = NavigationFactory::getNav("NLrcContourSet").getNav();
    rcContourSet* rcCompactHeightfieldData =  static_cast<rcContourSet*>(contoursetNav->getRawData()[0]);
    rcContext ctx;
    data = rcAllocPolyMesh();
    if (!rcBuildPolyMesh (&ctx,*rcCompactHeightfieldData, nvp, *data)) return false;
	return true;
}

vector<PassObject*> NLrcPolyMesh::getData(string, vector<PassObject*>){return {};}

vector<void*> NLrcPolyMesh::getRawData()
{
	if(isDirty()){
		if(data) rcFreePolyMesh(data);
		data = nullptr;
		init();
	}
	return {data};
}

void NLrcPolyMesh::constructDebugMesh()
{

}

extern "C"
AbstractNavigation* newNav(const World* world)
{
  return new NLrcPolyMesh(world);
}

extern "C"
NavigationInfo declareDependencies()
{
  return {{"NLrcContourSet"}};
}
