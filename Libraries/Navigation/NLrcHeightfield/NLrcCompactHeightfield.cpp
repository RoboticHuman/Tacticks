#include "Recast/Include/Recast.h"
#include "Tacticks/DebugFactory.h"
#include "NLrcHeightfield.h"
#include "NLrcCompactHeightfield.h"
#include <limits>
#include <cmath>
#include <glm/vec3.hpp>
using namespace std;

void NLrcCompactHeightfield::constructDebugMesh(){
    debugMesh=DebugFactory::createDebugMesh("compactHeightfield");
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

NLrcCompactHeightfield::NLrcCompactHeightfield(
                       std::shared_ptr<NLrcHeightfield> heightField, const int radius,
                       const int borderSize, const int minRegionArea,
                       const int mergeRegionArea, const bool useMonotone
                       )
{
    // Construct the actual rcHeightfield
    ////////////////////////////////////////////////////
    rcContext ctx;

    data = rcAllocCompactHeightfield();

    if (!rcBuildCompactHeightfield	(&ctx, heightField->walkableHeight, heightField->walkableClimb, *(heightField->data), *data))
        ;//hrow NLerror("Call to rcBuildCompactHeightfield failed");
    if (!rcErodeWalkableArea	(&ctx,radius,*data))
        ;//throw NLerror("Call to rcErodeWalkableArea failed");
    if (!rcBuildDistanceField	(&ctx,*data))
        ;//throw NLerror("Call to rcBuildDistanceField failed");
    if (useMonotone) {
        if (!rcBuildRegionsMonotone	(&ctx,*data,borderSize,minRegionArea,mergeRegionArea))
            ;//throw NLerror("Call to rcBuildRegionsMonotone failed");
    }
    else
        if (!rcBuildRegions	(&ctx,*data,borderSize,minRegionArea,mergeRegionArea))
            ;//throw NLerror("Call to rcBuildRegions failed");
    constructDebugMesh();
    ////////////////////////////////////////////////////
};

NLrcCompactHeightfield::~NLrcCompactHeightfield() {
    rcFreeCompactHeightfield(data);
}
