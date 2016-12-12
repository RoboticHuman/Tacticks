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
    rcContourSet* rcContourData =  static_cast<rcContourSet*>(contoursetNav->getRawData()[0]);
    rcContext ctx;
    data = rcAllocPolyMesh();
    if (!rcBuildPolyMesh (&ctx,*rcContourData, nvp, *data))
    	return false;
	constructDebugMesh();
	clearDirty();
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
	debugMesh = DebugFactory::createDebugMesh("polymesh");
	const int nvp = data->nvp;
	const float cs = data->cs;
	const float ch = data->ch;
	const float* orig = data->bmin;

	vector<float> color[3] {vector<float>(data->maxpolys),
                vector<float>(data->maxpolys),
                vector<float>(data->maxpolys)};

    for (int i=0; i<color[0].size(); i++) {
        color[0][i] = (rand()%1000)/1000.0;
        color[1][i] = (rand()%1000)/1000.0;
        color[2][i] = (rand()%1000)/1000.0;
    }

	for (int i = 0; i < data->npolys; ++i)
	{
		const unsigned short* p = &data->polys[i*nvp*2];

		vector<glm::vec3> poly;
		for (int j = 0; j < nvp && p[j] != RC_MESH_NULL_IDX; j++)
		{
			const unsigned short* v = &(data->verts[p[j]*3]);

			const float x = orig[0] + v[0]*cs;
			const float y = orig[1] + (v[1]+1)*ch;
			const float z = orig[2] + v[2]*cs;

			poly.push_back(glm::vec3(x,y,z));
		}
		if (data->areas[i] == RC_WALKABLE_AREA) {
			debugMesh->drawConvexPolygon(poly,color[0][data->regs[i]],
										color[1][data->regs[i]],
										color[2][data->regs[i]],1);
		}
		else if (data->areas[i] == RC_NULL_AREA) {
			debugMesh->drawConvexPolygon(poly,0,0,0,1);
		}

	}
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
