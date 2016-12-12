#include "Recast/Include/Recast.h"
#include "NLrcCompactHeightfield.h"
#include "NLerror.h"
#include <limits>
#include <cmath>
template <typename> class NavLibContainer;

#ifndef NLrcContourSet_h
#define NLrcContourSet_h

///  \addtogroup navlib
///  @{

///  @brief A wrapper for recast's contour set that facilitates and manages its creation. For more information on compact heightfields see http://www.critterai.org/projects/nmgen_study/contourgen.html
class NLrcContourSet {
    friend class NavLibContainer<NLrcContourSet>;
    
private:
    // Stores the parameters used to construct this wraper
    struct constructionParameters {
        std::shared_ptr<NLrcCompactHeightfield> compactHeightField;
        float maxError; int maxEdgeLen; int buildFlags;
    };
    
    constructionParameters inputData;
    
public:
    /// Actual data of the navigation library
    rcContourSet* data;
    
protected:
    
    ///  @brief         Constructs the NLrcContourSet from a given NLrcCompactHeightfield
    ///  @param[in]     compactHeightField      An NLrcCompactHeightfield ptr obtained using the NavLibContainer
    ///  @param[in]		maxError	The maximum distance a simplfied contour's border edges should deviate
    ///                                 the original raw contour. [Limit: >=0] [Units: wu]
    ///  @param[in]		maxEdgeLen	The maximum allowed length for contour edges along the border of the mesh.
    ///                                 [Limit: >=0] [Units: vx]
    ///  @param[in]		buildFlags	The build flags. See recast's documentation on "rcBuildContoursFlags" here
    ///                                 http://www.stevefsp.org/projects/rcndoc/prod/Recast_8h.html#a63345b5052e97366027aa92b54c7786f
    NLrcContourSet(
                   std::shared_ptr<NLrcCompactHeightfield> compactHeightField,
                   const float maxError, const int maxEdgeLen, const int buildFlags
                  )
    {
        // Store parameters used to construct this wraper
        ////////////////////////////////////////////////////
        inputData.compactHeightField = compactHeightField;
        inputData.maxError = maxError;
        inputData.maxEdgeLen = maxEdgeLen;
        inputData.buildFlags = buildFlags;
        ////////////////////////////////////////////////////
        
        // Construct the actual rcHeightfield
        ////////////////////////////////////////////////////
        rcContext ctx;
        data = rcAllocContourSet();
        
        if (!rcBuildContours	(&ctx, *(compactHeightField->data), maxError, maxEdgeLen, *data, buildFlags))
            throw NLerror("Call to rcBuildContours failed");
        ////////////////////////////////////////////////////
    };
    
    
    bool constructedWithSameParams(
                                   std::shared_ptr<NLrcCompactHeightfield> compactHeightField,
                                   const float maxError, const int maxEdgeLen, const int buildFlags
                                   )
    {
        // return value, true if all values match the inputData
        bool ret = true;
        ret &= (inputData.compactHeightField == compactHeightField);
        ret &= (std::abs(inputData.maxError - maxError) <= std::numeric_limits<float>::epsilon());
        ret &= (inputData.maxEdgeLen == maxEdgeLen);
        ret &= (inputData.buildFlags == buildFlags);
        return ret;
    }
    
    ~NLrcContourSet() {
        rcFreeContourSet(data);
    }
};
/// @}


#endif







