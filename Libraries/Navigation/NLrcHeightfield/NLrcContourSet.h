#include "Recast/Include/Recast.h"
#include "NLrcCompactHeightfield.h"
#include "Tacticks/DebugFactory.h"
#include <limits>
#include <cmath>

#ifndef NLrcContourSet_h
#define NLrcContourSet_h

///  \addtogroup navlib
///  @{

///  @brief A wrapper for recast's contour set that facilitates and manages its creation. For more information on compact heightfields see http://www.critterai.org/projects/nmgen_study/contourgen.html
class NLrcContourSet {

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
               );

    ~NLrcContourSet();
};
/// @}


#endif
