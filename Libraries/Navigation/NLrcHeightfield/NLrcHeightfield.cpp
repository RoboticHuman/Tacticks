#include "Recast/Include/Recast.h"
#include "Tacticks/DebugFactory.h"
#include <limits>
#include <cmath>
#include <cstring>
#include <memory>
template <typename> class NavLibContainer;

#pragma once

///  \addtogroup navlib
///  @{

///  @brief A wrapper for recast's heightfield that facilitates and manages its creation. For more information on heightfields see http://www.critterai.org/projects/nmgen_study/voxelization.html
class NLrcHeightfield {
    friend class NLrcCompactHeightfield;
    friend class NavLibContainer<NLrcHeightfield>;
    
private:
    // Stores parameters used to construct this wraper
    struct constructionParameters {
        float bmin[3]; float bmax[3]; int walkableHeight; int walkableClimb;
        float walkableSlopeAngle; float* verts; int nv; int* tris; int nt;
        float cs; float ch; int flagMergeThr;
    };
    
    std::shared_ptr<DebugMesh> debugMesh;
    constructionParameters inputData;
    
    void constructDebugMesh(){
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
                    debugMesh->drawCuboid(fx,origin[1]+spanList->smin*ch,fz,fx+cs,origin[1]+spanList->smax*ch,fz+cs,235,255,131);
                    spanList=spanList->next;
                }
            }
        }
    }
    
public:
    /// Actual data of the navigation library
    rcHeightfield* data;
    
    
    ///  @param[in]     bmin                The minimum bounds in world space. [(x, y, z)]
    ///  @param[in]     bmax                The maximum bounds in world space. [(x, y, z)]
    ///  @param[in]		walkableHeight      Minimum floor to 'ceiling' height that will still allow the floor area to
    ///                                         be considered walkable. [Limit: >= 3] [Units: vx]
    ///  @param[in]		walkableClimb       Maximum ledge height that is considered to still be traversable.
    ///                                         [Limit: >=0] [Units: vx]
    ///  @param[in]		walkableSlopeAngle	The maximum slope that is considered walkable.
    ///                                         [Limits: 0 <= value < 90] [Units: Degrees]
    ///  @param[in]		verts				The vertices. [(x, y, z) * @p nv]
    ///  @param[in]		nv					The number of vertices.
    ///  @param[in]		tris				The triangle vertex indices. [(vertA, vertB, vertC) * @p nt]
    ///  @param[in]		nt					The number of triangles.
    ///  @param[in]     cs                  The size of each cell. (On the xz-plane.)
    ///  @param[in]     ch                  The height of each cell. (The minimum increment along the y-axis.)
    ///  @param[in]		flagMergeThr        The merge theshold. [Limit: >= 0] [Units: vx]
    NLrcHeightfield(
                    const float* bmin, const float* bmax, const int walkableHeight, const int walkableClimb,
                    const float walkableSlopeAngle, const float* verts, const int nv, const int* tris, const int nt,
                    float cs, float ch, const int flagMergeThr
                    )
    {
        
        // Store parameters used to construct this wraper
        ////////////////////////////////////////////////////
        std::memcpy(inputData.bmin,bmin,sizeof inputData.bmin);
        std::memcpy(inputData.bmax,bmax,sizeof inputData.bmax);
        inputData.walkableHeight = walkableHeight;
        inputData.walkableClimb = walkableClimb;
        inputData.walkableSlopeAngle = walkableSlopeAngle;
        
        std::memcpy(inputData.verts,verts,sizeof (float) * nv);
        inputData.nv = nv;
        std::memcpy(inputData.tris,tris,sizeof (int) * nt);
        inputData.nt = nt;
        inputData.cs = cs;
        inputData.ch = ch;
        inputData.flagMergeThr = flagMergeThr;
        ////////////////////////////////////////////////////
        
        
        // Construct the actual rcHeightfield
        ////////////////////////////////////////////////////
        rcContext ctx;
        unsigned char* areas;
        
        data = rcAllocHeightfield();
        rcCalcGridSize(bmin, bmax, cs, &(data->width), &(data->height));
        
        if (!rcCreateHeightfield(&ctx, *data, data->width, data->height, bmin, bmax, cs,  ch))
            throw NLerror("Call to rcCreateHeightfield failed");
        
        rcMarkWalkableTriangles (&ctx, walkableSlopeAngle, verts, nv, tris, nt, areas);
        
        if (!rcRasterizeTriangles (&ctx, verts, nv, tris, areas, nt, *data, flagMergeThr))
            throw NLerror("Call to rcRasterizeTriangles failed");
        
        rcFilterLowHangingWalkableObstacles (&ctx, walkableClimb,*data);
        
        rcFilterLedgeSpans (&ctx, walkableHeight, walkableClimb, *data);
        
        rcFilterWalkableLowHeightSpans	(&ctx, walkableHeight, *data);
        ////////////////////////////////////////////////////
        
    };
    
    
    bool constructedWithSameParams(
                                   const float* bmin, const float* bmax, const int walkableHeight, const int walkableClimb,
                                   const float walkableSlopeAngle, const float* verts, const int nv, const int* tris, const int nt,
                                   float cs, float ch, const int flagMergeThr
                                   )
    {
        // return value, true if all values match the inputData
        bool ret = true;
        
        // Separate check for the size of the number of vertices and number of triangles
        // so that their comparisons don't go out of bound
        if (inputData.nv != nv || inputData.nt != nt)
            return false;
        
        // check if borders are the same
        for (int i=0; i<3; i++) {
            ret &= (std::abs(bmin[i] - inputData.bmin[i]) <= std::numeric_limits<float>::epsilon());
            ret &= (std::abs(bmax[i] - inputData.bmax[i]) <= std::numeric_limits<float>::epsilon());
        }
        // check if the vertices are the same
        for (int i=0; i<nv; i++)
            ret &= (std::abs(verts[i] - inputData.verts[i]) <= std::numeric_limits<float>::epsilon());
        // check if the triangles are the same
        ret &= !std::memcmp(inputData.tris, tris, sizeof(int)*nt);
        // check for the rest
        ret &= (std::abs(inputData.walkableSlopeAngle - walkableSlopeAngle) <= std::numeric_limits<float>::epsilon());
        ret &= (std::abs(inputData.cs - cs) <= std::numeric_limits<float>::epsilon());
        ret &= (std::abs(inputData.ch - ch) <= std::numeric_limits<float>::epsilon());
        ret &= (inputData.walkableHeight == walkableHeight);
        ret &= (inputData.walkableClimb == walkableClimb);
        ret &= (inputData.flagMergeThr == flagMergeThr);
        
        return ret;
    }
    
    ~NLrcHeightfield() {
        rcFreeHeightField(data);
    }
};
/// @}
