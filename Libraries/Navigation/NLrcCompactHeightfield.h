#include "Recast/Include/Recast.h"
#include "NLrcHeightfield.h"
#include "NLerror.h"
#include <limits>
#include <cmath>
template <typename> class NavLibContainer;

#ifndef NLrcCompactHeightfield_h
#define NLrcCompactHeightfield_h

///  \addtogroup navlib
///  @{

///  @brief A wrapper for recast's compact heightfield that facilitates and manages its creation. For more information on compact heightfields see http://www.critterai.org/projects/nmgen_study/regiongen.html
class NLrcCompactHeightfield {
    friend class NavLibContainer<NLrcCompactHeightfield>;
    
private:
    // Stores the parameters used to construct this wraper
    struct constructionParameters {
        std::shared_ptr<NLrcHeightfield> heightField;
        int borderSize; int minRegionArea; int mergeRegionArea; int radius; bool useMonotone;
    };
    
    constructionParameters inputData;
    
public:
    /// Actual data of the navigation library
    rcCompactHeightfield* data;
    
protected:
    
    ///  @brief         Constructs the NLrcCompactHeightfield from a given NLrcHeightfield
    ///  @param[in]     heightField         An NLrcHeightfield ptr obtained using the NavLibContainer
    ///  @param[in]		radius              The radius of erosion. Basically any spans that are closer to a boundary or obstruction
    ///                                         than the specified radius are marked as unwalkable. [Limits: 0 < value < 255] [Units: vx].
    ///  @param[in]		borderSize          The size of the non-navigable border around the heightfield.
    ///                                         [Limit: >=0] [Units: vx]
    ///  @param[in]		minRegionArea       The minimum number of cells allowed to form isolated island areas.
    ///                                         [Limit: >=0] [Units: vx].
    ///  @param[in]		mergeRegionArea		Any regions with a span count smaller than this value will, if possible,
    ///                                         be merged with larger regions. [Limit: >=0] [Units: vx]
    ///  @param[in]		useMonotone         Optional parameter. Tells the wrapper to use rcBuildRegionsMonotone instead of the normal
    ///                                         rcBuildRegions. See Recast's official documentation for more details [Default: False]
    NLrcCompactHeightfield(
                           std::shared_ptr<NLrcHeightfield> heightField, const int radius,
                           const int borderSize, const int minRegionArea,
                           const int mergeRegionArea, const bool useMonotone=false
                           )
    {
        // Store parameters used to construct this wraper
        ////////////////////////////////////////////////////
        inputData.heightField = heightField;
        inputData.borderSize = borderSize;
        inputData.minRegionArea = minRegionArea;
        inputData.mergeRegionArea = mergeRegionArea;
        inputData.radius = radius;
        inputData.useMonotone = useMonotone;
        ////////////////////////////////////////////////////
        
        
        // Construct the actual rcHeightfield
        ////////////////////////////////////////////////////
        rcContext ctx;
        data = rcAllocCompactHeightfield();
        
        if (!rcBuildCompactHeightfield	(&ctx, heightField->inputData.walkableHeight, heightField->inputData.walkableClimb, *(heightField->data), *data))
            throw NLerror("Call to rcBuildCompactHeightfield failed");
        if (!rcErodeWalkableArea	(&ctx,radius,*data))
            throw NLerror("Call to rcErodeWalkableArea failed");
        if (!rcBuildDistanceField	(&ctx,*data))
            throw NLerror("Call to rcBuildDistanceField failed");
        if (useMonotone) {
            if (!rcBuildRegionsMonotone	(&ctx,*data,borderSize,minRegionArea,mergeRegionArea))
                throw NLerror("Call to rcBuildRegionsMonotone failed");
        }
        else
            if (!rcBuildRegions	(&ctx,*data,borderSize,minRegionArea,mergeRegionArea))
                throw NLerror("Call to rcBuildRegions failed");
        ////////////////////////////////////////////////////
    };
    
    
    bool constructedWithSameParams(
                                   std::shared_ptr<NLrcHeightfield> heightField,
                                   const int borderSize, const int minRegionArea,
                                   const int mergeRegionArea, const int radius, const bool useMonotone=false
                                   )
    {
        // return value, true if all values match the inputData
        bool ret = true;
        ret &= (inputData.heightField == heightField);
        ret &= (inputData.borderSize == borderSize);
        ret &= (inputData.minRegionArea == minRegionArea);
        ret &= (inputData.mergeRegionArea == mergeRegionArea);
        ret &= (inputData.radius == radius);
        ret &= (inputData.useMonotone == useMonotone);
        return ret;
    }
    
    ~NLrcCompactHeightfield() {
        rcFreeCompactHeightfield(data);
    }
};
/// @}


#endif

/*

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
///  @param[in]		radius              The radius of erosion. Basically any spans that are closer to a boundary or obstruction
///                                         than the specified radius are marked as unwalkable. [Limits: 0 < value < 255] [Units: vx].
///  @param[in]		borderSize          The size of the non-navigable border around the heightfield.
///                                         [Limit: >=0] [Units: vx]
///  @param[in]		minRegionArea       The minimum number of cells allowed to form isolated island areas.
///                                         [Limit: >=0] [Units: vx].
///  @param[in]		mergeRegionArea		Any regions with a span count smaller than this value will, if possible,
///                                         be merged with larger regions. [Limit: >=0] [Units: vx]

///  @param[in]		useMonotone         Optional parameter. Tells the wrapper to use rcBuildRegionsMonotone instead of the normal
///                                         rcBuildRegions. See Recast's official documentation for more details [Default: False]
NLrcCompactHeightfield(
                       const float* bmin, const float* bmax, const int walkableHeight, const int walkableClimb,
                       const float walkableSlopeAngle, const float* verts, const int nv, const int* tris, const int nt,
                       float cs, float ch, const int flagMergeThr, const int radius, const int borderSize, const int minRegionArea,
                       const int mergeRegionArea, const bool useMonotone=false
                       )
{
    // Store parameters used to construct this wraper
    ////////////////////////////////////////////////////
    inputData.heightField = NavLibContainer<NLrcHeightfield>::getNavigationLibrary(bmin,bmax,walkableHeight,walkableClimb, walkableSlopeAngle,verts,nv,tris,nt,cs,ch,flagMergeThr);
    inputData.borderSize = borderSize;
    inputData.minRegionArea = minRegionArea;
    inputData.mergeRegionArea = mergeRegionArea;
    inputData.radius = radius;
    inputData.useMonotone = useMonotone;
    ////////////////////////////////////////////////////
    
    
    // Construct the actual rcHeightfield
    ////////////////////////////////////////////////////
    rcContext ctx;
    data = rcAllocCompactHeightfield();
    
    if (!rcBuildCompactHeightfield	(&ctx, walkableHeight, walkableClimb, *(inputData.heightField->data), *data))
        throw NLerror("Call to rcBuildCompactHeightfield failed");
    if (!rcErodeWalkableArea	(&ctx,radius,*data))
        throw NLerror("Call to rcErodeWalkableArea failed");
    if (!rcBuildDistanceField	(&ctx,*data))
        throw NLerror("Call to rcBuildDistanceField failed");
    
    if (useMonotone){
        if (!rcBuildRegionsMonotone	(&ctx,*data,borderSize,minRegionArea,mergeRegionArea))
            throw NLerror("Call to rcBuildRegionsMonotone failed");
    }
    else
        if (!rcBuildRegions	(&ctx,*data,borderSize,minRegionArea,mergeRegionArea))
            throw NLerror("Call to rcBuildRegions failed");
    ////////////////////////////////////////////////////
};
 
 
 
 
 bool constructedWithSameParams(
 const float* bmin, const float* bmax, const int walkableHeight, const int walkableClimb,
 const float walkableSlopeAngle, const float* verts, const int nv, const int* tris, const int nt,
 float cs, float ch, const int flagMergeThr, const int borderSize, const int minRegionArea,
 const int mergeRegionArea,const int radius, const bool useMonotone=false
 )
 {
 // return value, true if all values match the inputData
 bool ret = true;
 ret &= inputData.heightField->constructedWithSameParams(bmin,bmax,walkableHeight,walkableClimb, walkableSlopeAngle,verts,nv,tris,nt,cs,ch,flagMergeThr);
 ret &= (inputData.borderSize == borderSize);
 ret &= (inputData.minRegionArea == minRegionArea);
 ret &= (inputData.mergeRegionArea == mergeRegionArea);
 ret &= (inputData.radius == radius);
 ret &= (inputData.useMonotone == useMonotone);
 return ret;
 }
*/




