#include "Recast/Include/Recast.h"
#include "NLrcPolyMesh.h"
#include "NLrcCompactHeightfield.h"
#include "NLerror.h"
#include <limits>
#include <cmath>
template <typename> class NavLibContainer;


#ifndef NLrcPolyMeshDetail_h
#define NLrcPolyMeshDetail_h

///  \addtogroup navlib
///  @{

///  @brief A wrapper for recast's detailed polymesh that facilitates and manages its creation. For more information on polymeshes see http://www.critterai.org/projects/nmgen_study/detailgen.html
class NLrcPolyMeshDetail {
    friend class NavLibContainer<NLrcPolyMeshDetail>;
    
private:
    // Stores the parameters used to construct this wraper
    struct constructionParameters {
        std::shared_ptr<NLrcCompactHeightfield> compactHeightField;
        std::shared_ptr<NLrcPolyMesh> polyMesh;
        float sampleDist; float sampleMaxError;
    };
    
    constructionParameters inputData;
    
public:
    /// Actual data of the navigation library
    rcPolyMeshDetail* data;
    
protected:
    
    ///  @brief         Constructs an NLrcPolyMesh from a given NLrcPolyMesh and NLrcContourSet
    ///  @param[in]     compactHeightField      An NLrcCompactHeightfield ptr obtained using the NavLibContainer
    ///  @param[in]     polyMesh                An NLrcPolyMesh ptr obtained using the NavLibContainer
    ///  @param[in]		sampleDist              Sets the distance to use when samping the heightfield. [Limit: >=0] [Units: wu]
    ///  @param[in]		sampleMaxError          The maximum distance the detail mesh surface should deviate from
    ///                                             heightfield data. [Limit: >=0] [Units: wu]
    NLrcPolyMeshDetail(
                       std::shared_ptr<NLrcCompactHeightfield> compactHeightField,
                       std::shared_ptr<NLrcPolyMesh> polyMesh,
                       const float 	sampleDist,
                       const float 	sampleMaxError
                      )
    {
        // Store parameters used to construct this wraper
        ////////////////////////////////////////////////////
        inputData.compactHeightField = compactHeightField;
        inputData.polyMesh = polyMesh;
        inputData.sampleDist = sampleDist;
        inputData.sampleMaxError = sampleMaxError;
        ////////////////////////////////////////////////////
        
        // Construct the actual rcHeightfield
        ////////////////////////////////////////////////////
        rcContext ctx;
        data = rcAllocPolyMeshDetail();
        
        if (!rcBuildPolyMeshDetail	(&ctx, *(inputData.polyMesh->data), *(inputData.compactHeightField->data),sampleDist,sampleMaxError,*data))
            throw NLerror("Call to rcBuildPolyMeshDetail failed");
        ////////////////////////////////////////////////////
    };
    
    
    bool constructedWithSameParams(
                                   std::shared_ptr<NLrcCompactHeightfield> compactHeightField,
                                   std::shared_ptr<NLrcPolyMesh> polyMesh,
                                   const float 	sampleDist,
                                   const float 	sampleMaxError
                                   )
    {
        // return value, true if all values match the inputData
        bool ret = true;
        ret &= (inputData.compactHeightField == compactHeightField);
        ret &= (inputData.polyMesh == polyMesh);
        ret &= (std::abs(inputData.sampleDist - sampleDist) <= std::numeric_limits<float>::epsilon());
        ret &= (std::abs(inputData.sampleMaxError - sampleMaxError) <= std::numeric_limits<float>::epsilon());
        
        return ret;
    }
    
    ~NLrcPolyMeshDetail() {
        rcFreePolyMeshDetail(data);
    }
};
/// @}

#endif