#include "Recast/Include/Recast.h"
#include "Tacticks/DebugFactory.h"
#include <limits>
#include <cmath>
#include <cstring>
#include <memory>
#include <iostream>

#pragma once

///  \addtogroup navlib
///  @{

///  @brief A wrapper for recast's heightfield that facilitates and manages its creation. For more information on heightfields see http://www.critterai.org/projects/nmgen_study/voxelization.html
class NLrcHeightfield {
    friend class NLrcCompactHeightfield;
    int walkableHeight, walkableClimb;

    void constructDebugMesh();
public:
    /// Actual data of the navigation library
    rcHeightfield* data;
    std::shared_ptr<DebugMesh> debugMesh;

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
                    float cs, float ch, const int flagMergeThr = 1
                );
    ~NLrcHeightfield();
};

/// @}
