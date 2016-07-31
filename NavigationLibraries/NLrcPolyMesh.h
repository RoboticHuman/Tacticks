#include "Recast/Include/Recast.h"
#include "NLrcContourSet.h"
#include "NLerror.h"
#include <limits>
#include <cmath>
template <typename> class NavLibContainer;


#ifndef NLrcPolyMesh_h
#define NLrcPolyMesh_h

///  \addtogroup navlib
///  @{

///  @brief A wrapper for recast's polymesh that facilitates and manages its creation. For more information on polymeshes see http://www.critterai.org/projects/nmgen_study/polygen.html
class NLrcPolyMesh {
    friend class NavLibContainer<NLrcPolyMesh>;
    
private:
    // Stores the parameters used to construct this wraper
    struct constructionParameters {
        std::shared_ptr<NLrcContourSet> contourSet;
        int nvp;
    };
    
    constructionParameters inputData;
    
public:
    /// Actual data of the navigation library
    rcPolyMesh* data;
    
protected:
    
    ///  @brief         Constructs an NLrcPolyMesh from a given NLrcCompactHeightfield
    ///  @param[in]     contourSet      An NLrcContourSet ptr obtained using the NavLibContainer
    ///  @param[in]		nvp		The maximum number of vertices allowed for polygons generated during the
    ///  						contour to polygon conversion process. [Limit: >= 3]
    NLrcPolyMesh(
                   std::shared_ptr<NLrcContourSet> contourSet,
                   const int nvp
                   )
    {
        // Store parameters used to construct this wraper
        ////////////////////////////////////////////////////
        inputData.contourSet = contourSet;
        inputData.nvp = nvp;
        ////////////////////////////////////////////////////
        
        // Construct the actual rcHeightfield
        ////////////////////////////////////////////////////
        rcContext ctx;
        data = rcAllocPolyMesh();
        
        if (!rcBuildPolyMesh (&ctx,*(contourSet->data), nvp, *data))
            throw NLerror("Call to rcBuildPolyMesh failed");
        ////////////////////////////////////////////////////
    };
    
    
    bool constructedWithSameParams(
                                   std::shared_ptr<NLrcContourSet> contourSet,
                                   const int nvp
                                   )
    {
        // return value, true if all values match the inputData
        bool ret = true;
        ret &= (inputData.contourSet == contourSet);
        ret &= (inputData.nvp == nvp);
        return ret;
    }
    
    ~NLrcPolyMesh() {
        rcFreePolyMesh(data);
    }
};
/// @}

#endif