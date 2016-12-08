#include "NLrcPolyMeshDetail.h"
#include <Tacticks/NavigationFactory.h>
#include <Tacticks/PassObjectFloat.h>
#include <Tacticks/PassObjectBool.h>
#include <limits>
#include <cmath>
#include <glm/vec3.hpp>
using namespace std;
NLrcPolyMeshDetail::NLrcPolyMeshDetail(const World* world) : AbstractNavigation(world){data = nullptr;}
NLrcPolyMeshDetail::~NLrcPolyMeshDetail(){if(data) rcPolyMeshDetail(data);}

bool NLrcPolyMeshDetail::init()
{
    const float sampleDist = dynamic_cast<PassObjectFloat*>(args[0])->getValue();
    const float sampleMaxError = dynamic_cast<PassObjectFloat*>(args[1])->getValue();
    AbstractNavigation* compactHeigtfieldNav = NavigationFactory::getNav("NLrcCompactHeightfield").getNav();
    AbstractNavigation* polyMeshNav = NavigationFactory::getNav("NLrcPolyMesh").getNav();
    rcCompactHeightfield* compactHeightfieldData = static_cast<rcCompactHeightfield*>(compactHeigtfieldNav->getRawData()[0]);
    rcPolyMesh* polyMeshData = static_cast<rcPolyMesh*>(polyMeshNav->getRawData()[0]);
    rcContext ctx;
    data = rcAllocPolyMeshDetail();
    if (!rcBuildPolyMeshDetail	(&ctx, *polyMeshData, *compactHeightfieldData,sampleDist,sampleMaxError,*data)) return false;
	constructDebugMesh();
	return true;
}

vector<PassObject*> NLrcPolyMeshDetail::getData(string, vector<PassObject*>){return {};}

vector<void*> NLrcPolyMeshDetail::getRawData()
{
	if(isDirty()){
		if(data) rcFreePolyMeshDetail(data);
		data = nullptr;
		init();
	}
	return {data};
}

void NLrcPolyMeshDetail::constructDebugMesh()
{
	debugMesh = DebugFactory::createDebugMesh("polymeshdetail");
    AbstractNavigation* polyMeshNav = NavigationFactory::getNav("NLrcPolyMesh").getNav();
	for (int i = 0; i < data->nmeshes; ++i)
	{
		const unsigned int* m = &data->meshes[i*4];
		const unsigned int bverts = m[0];
		const unsigned int btris = m[2];
		const int ntris = (int)m[3];
		const float* verts = &data->verts[bverts*3];
		const unsigned char* tris = &data->tris[btris*4];
        vector<glm::vec3> poly;
		for (int j = 0; j < ntris; ++j)
		{
            poly.push_back(glm::vec3(verts[tris[j*4+0]*3],verts[tris[j*4+1]*3],verts[tris[j*4+2]*3]));

		}
        debugMesh->drawConvexPolygon(poly,(rand()%1000)/1000.0,(rand()%1000)/1000.0,(rand()%1000)/1000.0,1.0);
        //triangle.clear();
	}
}

extern "C"
AbstractNavigation* newNav(const World* world)
{
  return new NLrcPolyMeshDetail(world);
}

extern "C"
NavigationInfo declareDependencies()
{
  return {{"NLrcCompactHeightfield","NLrcPolyMesh"}};
}
