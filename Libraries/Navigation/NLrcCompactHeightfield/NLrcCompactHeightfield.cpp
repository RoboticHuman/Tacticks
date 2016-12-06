#include "NLrcCompactHeightfield.h"
#include <Tacticks/NavigationFactory.h>
#include <Tacticks/PassObjectInt.h>
#include <Tacticks/PassObjectBool.h>
#include <limits>
#include <cmath>
#include <glm/vec3.hpp>
using namespace std;

class rcHeightfield;

NLrcCompactHeightfield::NLrcCompactHeightfield(const World* world) : AbstractNavigation(world){}
NLrcCompactHeightfield::~NLrcCompactHeightfield(){rcFreeCompactHeightfield(data);}

bool NLrcCompactHeightfield::init()
{
	//Parsing args
	int radius = dynamic_cast<PassObjectInt*>(args[0])->getValue();
	int borderSize = dynamic_cast<PassObjectInt*>(args[1])->getValue();
	int minRegionArea = dynamic_cast<PassObjectInt*>(args[2])->getValue();
    int mergeRegionArea = dynamic_cast<PassObjectInt*>(args[3])->getValue();
	bool useMonotone = dynamic_cast<PassObjectBool*>(args[4])->getValue();

	AbstractNavigation* hieghtFieldNav = NavigationFactory::getNav("NLrcHeightfield").getNav();
	rcHeightfield* heightField = static_cast<rcHeightfield*>(hieghtFieldNav->getRawData()[0]);
	int walkableHeight = dynamic_cast<PassObjectInt*>(hieghtFieldNav->getData("walkableHeight", {})[0])->getValue();
	int walkableClimb = dynamic_cast<PassObjectInt*>(hieghtFieldNav->getData("walkableClimb", {})[0])->getValue();


	rcContext ctx;
	data = rcAllocCompactHeightfield();

	if(!rcBuildCompactHeightfield(&ctx, walkableHeight, walkableClimb, *heightField, *data)) return false;
	if(!rcErodeWalkableArea (&ctx, radius, *data)) return false;
	if(!rcBuildDistanceField (&ctx, *data)) return false;
	if(useMonotone){
		if(!rcBuildRegionsMonotone (&ctx,*data, borderSize, minRegionArea, mergeRegionArea)) return false;
	}
	else{
		if (!rcBuildRegions (&ctx, *data, borderSize, minRegionArea, mergeRegionArea)) return false;
	}

	constructDebugMesh();
}
vector<PassObject*> NLrcCompactHeightfield::getData(string, vector<PassObject*>){}
vector<void*> NLrcCompactHeightfield::getRawData()
{
	return {data};
}
void NLrcCompactHeightfield::constructDebugMesh()
{
	debugMesh = DebugFactory::createDebugMesh("compactHeightfield");
    const float* origin = data->bmin;
    const float cs = data->cs;
    const float ch = data->ch;

    vector<float> color[3] {vector<float>(data->maxRegions),
                            vector<float>(data->maxRegions),
                            vector<float>(data->maxRegions)};

    for (int i=0; i<color[0].size(); i++) {
        color[0][i] = (rand()%1000)/1000.0;
        color[1][i] = (rand()%1000)/1000.0;
        color[2][i] = (rand()%1000)/1000.0;
    }

	for (int y = 0; y < data->height; ++y)
	{
		for (int x = 0; x < data->width; ++x)
		{
			const float fx = origin[0] + x*cs;
			const float fz = origin[2] + y*cs;
			const rcCompactCell& c = data->cells[x+y*data->width];

			for (unsigned i = c.index, ni = c.index+c.count; i < ni; ++i)
			{
				const rcCompactSpan& s = data->spans[i];
				const float fy = origin[1] + (s.y)*ch;

                vector<glm::vec3> grid(4);

                grid[0] = glm::vec3(fx,fy,fz);
                grid[1] = glm::vec3(fx,fy,fz+cs);
                grid[2] = glm::vec3(fx+cs,fy,fz+cs);
                grid[3] = glm::vec3(fx+cs,fy,fz);
                if (s.reg){
                    debugMesh->drawConvexPolygon(grid,color[0][s.reg],
                                                    color[1][s.reg],
                                                    color[2][s.reg],1);
                }
                else {
                    debugMesh->drawConvexPolygon(grid,0,0,0,1);
                }


			}
		}
	}
}

extern "C"
AbstractNavigation* newNav(const World* world)
{
  return new NLrcCompactHeightfield(world);
}

extern "C"
NavigationInfo declareDependencies()
{
  return {{"NLrcHeightfield"}};
}
