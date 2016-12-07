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
	constructDebugMesh();
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

	for (int i = 0; i < data->npolys; ++i)
	{
		const unsigned short* p = &data->polys[i*nvp*2];

		vector<float> color;
		if (data->areas[i] == RC_WALKABLE_AREA)
			color = vector<float>{0,192,255,64};
		else if (data->areas[i] == RC_NULL_AREA)
			color = vector<float>{0,0,0,64};
		//else
			//color = duIntToCol(data->areas[i], 255);

		unsigned short vi[3];
		for (int j = 2; j < nvp; ++j)
		{
			vector<glm::vec3> triangle;
			if (p[j] == RC_MESH_NULL_IDX) break;
			vi[0] = p[0];
			vi[1] = p[j-1];
			vi[2] = p[j];
			for (int k = 0; k < 3; ++k)
			{
				const unsigned short* v = &data->verts[vi[k]*3];
				const float x = orig[0] + v[0]*cs;
				const float y = orig[1] + (v[1]+1)*ch;
				const float z = orig[2] + v[2]*cs;
				triangle.push_back(glm::vec3(x,y,z));
			}
			debugMesh->drawConvexPolygon(triangle,color[0],
											color[1],
											color[2],color[3]);
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
