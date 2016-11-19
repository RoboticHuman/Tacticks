#include "Recast/Include/Recast.h"
#include "NLrcCompactHeightfield.h"
#include "NLrcContourSet.h"
#include "Tacticks/DebugFactory.h"
#include <limits>
#include <cmath>


NLrcContourSet::NLrcContourSet(
               std::shared_ptr<NLrcCompactHeightfield> compactHeightField,
               const float maxError, const int maxEdgeLen, const int buildFlags
              )
{
    // Construct the actual rcHeightfield
    ////////////////////////////////////////////////////
    rcContext ctx;
    data = rcAllocContourSet();

    if (!rcBuildContours	(&ctx, *(compactHeightField->data), maxError, maxEdgeLen, *data, buildFlags))
        ;//throw NLerror("Call to rcBuildContours failed");
    ////////////////////////////////////////////////////
};

NLrcContourSet::~NLrcContourSet() {
    rcFreeContourSet(data);
}
