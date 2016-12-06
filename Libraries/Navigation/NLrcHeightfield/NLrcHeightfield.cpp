#include "NLrcHeightfield.h"
#include <Tacticks/NavigationFactory.h>
#include <Tacticks/PassObjectInt.h>
#include <Tacticks/PassObjectVec3.h>
#include <Tacticks/PassObjectFloat.h>
#include <Tacticks/World.h>
#include <limits>
#include <cmath>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;
using namespace glm;

NLrcHeightfield::NLrcHeightfield(const World* world) : AbstractNavigation(world){}
NLrcHeightfield::~NLrcHeightfield(){rcFreeHeightField(data);}

bool NLrcHeightfield::init()
{
	//Parsing args
	const float* bmin = value_ptr(dynamic_cast<PassObjectVec3*>(args[0])->getValue());
	const float* bmax = value_ptr(dynamic_cast<PassObjectVec3*>(args[1])->getValue());
	walkableHeight = dynamic_cast<PassObjectInt*>(args[2])->getValue();
	walkableClimb = dynamic_cast<PassObjectInt*>(args[3])->getValue();
	float walkableSlopeAngle = dynamic_cast<PassObjectFloat*>(args[4])->getValue();
	float cs = dynamic_cast<PassObjectFloat*>(args[5])->getValue();
	float ch = dynamic_cast<PassObjectFloat*>(args[6])->getValue();
	int flagMergeThr = dynamic_cast<PassObjectInt*>(args[7])->getValue();


	const vector<float>& verts = world->getVertices();
	const vector<int>& tris = world->getIndices();
	int nv = verts.size() / 3;
	int nt = tris.size() / 3;

	rcContext ctx;
	unsigned char* areas = new unsigned char[nt*10];

	data = rcAllocHeightfield();
    rcCalcGridSize(bmin, bmax, cs, &(data->width), &(data->height));

    if(!rcCreateHeightfield(&ctx, *data, data->width, data->height, bmin, bmax, cs,  ch)) return false;
    rcMarkWalkableTriangles(&ctx, walkableSlopeAngle, &verts[0], nv, &tris[0], nt, areas);
    if(!rcRasterizeTriangles(&ctx, &verts[0], nv, &tris[0], areas, nt, *data, flagMergeThr)) return false;
    rcFilterLowHangingWalkableObstacles(&ctx, walkableClimb,*data);
    rcFilterLedgeSpans(&ctx, walkableHeight, walkableClimb, *data);
    rcFilterWalkableLowHeightSpans(&ctx, walkableHeight, *data);

    constructDebugMesh();
}
vector<PassObject*> NLrcHeightfield::getData(string dataName, vector<PassObject*> args)
{
	if(dataName == "walkableHeight" && args.size() == 0) return {new PassObjectInt(walkableHeight, "walkableHeight")};
	if(dataName == "walkableClimb" && args.size() == 0) return {new PassObjectInt(walkableClimb, "walkableClimb")};
	return {};
}
vector<void*> NLrcHeightfield::getRawData()
{
	return {data};
}
void NLrcHeightfield::constructDebugMesh()
{
	debugMesh=DebugFactory::createDebugMesh("heightfield");
    const float* origin = data->bmin;
    const float cs = data->cs;
    const float ch = data->ch;

    const int gridWidth = data->width;
    const int gridHeight = data->height;

    for(int z=0;z<gridHeight;z++)
    {
        for(int x=0;x<gridWidth;x++)
        {
            float fx = origin[0] + x*cs;
            float fz = origin[2] + z*cs;
            const rcSpan* spanList = data->spans[x+z*gridWidth];
            while(spanList)
            {
                debugMesh->drawCuboid(fx,origin[1]+spanList->smin*ch,fz,fx+cs,origin[1]+spanList->smax*ch,fz+cs,(rand()%255)/255.0,(rand()%255)/255.0,(rand()%255)/255.0);
                spanList=spanList->next;
            }
        }
    }
}

extern "C"
AbstractNavigation* newNav(const World* world)
{
  return new NLrcHeightfield(world);
}

extern "C"
NavigationInfo declareDependencies()
{
  return {{}};
}
