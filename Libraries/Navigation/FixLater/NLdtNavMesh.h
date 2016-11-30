#include "Detour/Include/DetourNavMesh.h"
#include "Detour/Include/DetourNavMeshBuilder.h"
#include "NLrcPolyMesh.h"
#include "NLrcPolyMeshDetail.h"
#include "NLrcHeightfield.h"

#include <math.h>
#include <stdio.h>
template <typename> class NavLibContainer;

///  \addtogroup navlib
///  @{

///  @brief A wrapper for detour that create the constructed polymesh from the outputs of recast.
class NLDetour {
    friend class NLrcHeightfield;
    friend class NavLibContainer<NLDetour>;

private:
      // Stores parameters used to construct this wraper
      struct constructionParameters {
          NLrcPolyMesh m_pmesh;
          NLrcPolyMeshDetail m_dmesh;
          NLrcHeightfield cell_details;
          const float agentHeight;
          const float agentRadius;
      };
      constructionParameters inputData;

      //clears PolyMesh and the PolyMeshDetails
      void cleanup() {
          NLrcPolyMesh(m_pmesh);
          m_pmesh = 0;
          NLrcPolyMeshDetail(m_dmesh);
          m_dmesh = 0;
      }

public:
    /// Actual data of the navigation library
    dtNavMesh* data;

protected:

  ///  @param[in] m_pmesh   The PolyMesh object created through recast
  ///  @param[in] m_demesh  The PolyMeshDetails object creared through recast, which contains all extra details about the PolyMesh
  ///  @param[in] cell_details  The NLrcHeightfield object containing the cell size, cell height, and the walkable climb required by detour to create the mesh
  ///  @param[in] agentHeight The height of every agentHeight
  ///  @param[in] agentRadius  the radius of the circle that fully surrounds every agent.

//Creating the NavMesh from the PolyMesh and the PolyMeshDetails
NLDetour (NLrcPolyMesh m_pmesh, NLrcPolyMeshDetail m_dmesh, NLrcHeightfield cell_details, const float m_agentHeight, const float m_agentRadius ){

                  // Store parameters used to construct this wraper
                  ////////////////////////////////////////////////////
                  memcpy(inputData.m_pmesh,m_pmesh,sizeof inputData.m_pmesh);
                  memcpy(inputData.m_dmesh,m_dmesh,sizeof inputData.m_dmesh);
                  memcpy(inputData.cell_details,cell_details,sizeof inputData.cell_details);
                  inputData.m_agentHeight = m_agentHeight;
                  inputData.m_agentRadius = m_agentRadius;
                  ////////////////////////////////////////////////////

                  //Variables needed for the drCreateNavMeshParams
                  unsigned char* navData = 0;
                  int navDataSize = 0;
                  dtNavMeshCreateParams params;

                  //Initializing dtNavMeshCreateParams
                  ////////////////////////////////////////////////////
                  memset(&params, 0, sizeof(params));
              		params.verts = m_pmesh->verts;
              		params.vertCount = m_pmesh->nverts;
              		params.polys = m_pmesh->polys;
              		params.polyAreas = m_pmesh->areas;
              		params.polyFlags = m_pmesh->flags;
              		params.polyCount = m_pmesh->npolys;
              		params.nvp = m_pmesh->nvp;
              		params.detailMeshes = m_dmesh->meshes;
              		params.detailVerts = m_dmesh->verts;
              		params.detailVertsCount = m_dmesh->nverts;
              		params.detailTris = m_dmesh->tris;
              		params.detailTriCount = m_dmesh->ntris;
                  //OFF MESH CONNECTIONS: This is a feature of Detour Crowds, but it must be set up in params, and this it is Initialized here as zeros.
            //  		params.offMeshConVerts = m_geom->getOffMeshConnectionVerts();
            //  		params.offMeshConRad = m_geom->getOffMeshConnectionRads();
            //  		params.offMeshConDir = m_geom->getOffMeshConnectionDirs();
            //  		params.offMeshConAreas = m_geom->getOffMeshConnectionAreas();
            //  		params.offMeshConFlags = m_geom->getOffMeshConnectionFlags();
            //  		params.offMeshConUserID = m_geom->getOffMeshConnectionId();
              		params.offMeshConCount = m_geom->getOffMeshConnectionCount();
              		params.walkableHeight = m_agentHeight;
              		params.walkableRadius = m_agentRadius;
              	  params.walkableClimb = cell_details.inputData.walkableClimb;
                  params.offMeshConVerts = 0;
            	    params.offMeshConRad = 0;
            	    params.offMeshConDir = 0;
            		  params.offMeshConAreas = 0;
            		  params.offMeshConFlags = 0;
           		    params.offMeshConUserID = 0;
           		    params.offMeshConCount = 0;
              		rcVcopy(params.bmin, m_pmesh->bmin);
              		rcVcopy(params.bmax, m_pmesh->bmax);
            //  		params.cs = m_cfg.cs;
            //  		params.ch = m_cfg.ch;
                  params.ch = cell_details.inputData.ch;
                  params.cs = cell_details.inputData.cs;
              		params.buildBvTree = true;
                  ////////////////////////////////////////////////////

                  //Building navmesh
                  ////////////////////////////////////////////////////
                  if (!dtCreateNavMeshData(&params, &navData, &navDataSize))
              		{
              			m_ctx->log(RC_LOG_ERROR, "Could not build Detour navmesh.");
              			return false;
              		}
                  ////////////////////////////////////////////////////

                  //Allocating the navmesh
                  ////////////////////////////////////////////////////
              		m_navMesh = dtAllocNavMesh();
              		if (!m_navMesh)
              		{
              			dtFree(navData);
              			m_ctx->log(RC_LOG_ERROR, "Could not create Detour navmesh");
              			return false;
              		}
                  else {
                      data = m_navMesh;
                  }
                  ////////////////////////////////////////////////////


      }
      //For NavLibContainer
      ////////////////////////////////////////////////////
      bool constructedWithSameParams((NLrcPolyMesh m_pmesh, NLrcPolyMeshDetail m_dmesh, NLrcHeightfield cell_details, const float m_agentHeight, const float m_agentRadius ){
        // return value, true if all values match the inputData
        bool ret = true;
        ret &= !memcmp(inputData.m_pmesh, m_pmesh, sizeof(int)*m_pmesh);
        ret &= !memcmp(inputData.m_dmesh, m_dmesh, sizeof(int)*m_dmesh);
        ret &= !memcmp(inputData.cell_details, cell_details, sizeof(int)*cell_details);
        ret &= (inputData.m_agentHeight == m_agentHeight);
        ret &= (inputData.m_agentRadius == m_agentRadius);

        return ret;
      }

      //Deconstructing and cleanup
      ////////////////////////////////////////////////////
      ~NLDetour()  {
        cleanup();
        dtFreeNacMesh(data);
      }
      ////////////////////////////////////////////////////

}
