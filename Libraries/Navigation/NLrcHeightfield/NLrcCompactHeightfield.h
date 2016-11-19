#include "Recast/Include/Recast.h"
#include "Tacticks/DebugFactory.h"
#include "NLrcHeightfield.h"
#include <limits>
#include <cmath>
#include <glm/vec3.hpp>
using namespace std;

#ifndef NLrcCompactHeightfield_h
#define NLrcCompactHeightfield_h

///  \addtogroup navlib
///  @{

///  @brief A wrapper for recast's compact heightfield that facilitates and manages its creation. For more information on compact heightfields see http://www.critterai.org/projects/nmgen_study/regiongen.html
class NLrcCompactHeightfield {

    void constructDebugMesh();

public:
    /// Actual data of the navigation library
    rcCompactHeightfield* data;
    std::shared_ptr<DebugMesh> debugMesh;
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
                       );

    ~NLrcCompactHeightfield();
};
/// @}


#endif
