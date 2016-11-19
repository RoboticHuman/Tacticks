#include "Recast/Include/Recast.h"
#include "Tacticks/DebugFactory.h"
#include "NLrcHeightfield.h"
#include <limits>
#include <cmath>
#include <cstring>
#include <memory>
#include <iostream>
using namespace std;



void NLrcHeightfield::constructDebugMesh(){
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

NLrcHeightfield::NLrcHeightfield(
                const float* bmin, const float* bmax, const int walkableHeight, const int walkableClimb,
                const float walkableSlopeAngle, const float* verts, const int nv, const int* tris, const int nt,
                float cs, float ch, const int flagMergeThr
            ) : walkableHeight(walkableHeight), walkableClimb(walkableClimb)
{


    // Construct the actual rcHeightfield
    ////////////////////////////////////////////////////
    rcContext ctx;
    unsigned char* areas = new unsigned char[nt*10];

    data = rcAllocHeightfield();
    rcCalcGridSize(bmin, bmax, cs, &(data->width), &(data->height));

    if (!rcCreateHeightfield(&ctx, *data, data->width, data->height, bmin, bmax, cs,  ch))
        ;//throw NLerror("Call to rcCreateHeightfield failed");

    rcMarkWalkableTriangles (&ctx, walkableSlopeAngle, verts, nv, tris, nt, areas);

    if (!rcRasterizeTriangles (&ctx, verts, nv, tris, areas, nt, *data, flagMergeThr))
        ;//throw NLerror("Call to rcRasterizeTriangles failed");

    rcFilterLowHangingWalkableObstacles (&ctx, walkableClimb,*data);

    rcFilterLedgeSpans (&ctx, walkableHeight, walkableClimb, *data);

    rcFilterWalkableLowHeightSpans	(&ctx, walkableHeight, *data);
    ////////////////////////////////////////////////////

    constructDebugMesh();

};

 NLrcHeightfield::~NLrcHeightfield() {
    rcFreeHeightField(data);
}
