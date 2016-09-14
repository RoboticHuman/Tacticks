#include "DetourNavMesh.h"
#include "DetourNavMeshBuilder.h"
#include <math.h>
#include <stdio.h>



class dtNavLib {
      //Clears m_pmesh and m_dmesh
      float m_cellSize;
      float m_cellHeight;
      float m_agentHeight;
      float m_cellSize;
      float m_cellHeight;
      float m_agentHeight;
      float m_agentRadius;
      float m_agentMaxClimb;
      void cleanup() {
          rcPolyMesh(m_pmesh);
          m_pmesh = 0;
          rcPolyMeshDetail(m_dmesh);
          m_dmesh = 0;
      }
public:

//Creating the NavMesh from the PolyMesh and the PolyMeshDetails
      dtNavMesh* createdtNacMesh (rcPolyMesh m_pmesh, rcPolyMeshDetail m_dmesh ){ //m_cfg should also be sent, where it's the place in the gui or the map itself where the mesh will be shown.

                  //Variables needed for the drCreateNavMeshParams
                  unsigned char* navData = 0;
                  int navDataSize = 0;
                  dtNavMeshCreateParams params;

                  //Initializing dtNavMeshCreateParams
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
              		params.walkableClimb = m_agentMaxClimb;
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
                  params.cs = 12;
                  params.cs = 6;
              		params.buildBvTree = true;

                  //Building navmesh
                  if (!dtCreateNavMeshData(&params, &navData, &navDataSize))
              		{
              			m_ctx->log(RC_LOG_ERROR, "Could not build Detour navmesh.");
              			return false;
              		}

                  //Allocating the navmesh
              		m_navMesh = dtAllocNavMesh();
              		if (!m_navMesh)
              		{
              			dtFree(navData);
              			m_ctx->log(RC_LOG_ERROR, "Could not create Detour navmesh");
              			return false;
              		}
                  else {
                      return m_navMesh;
                    }
                  //Testing
              /*		dtStatus status;
                  status = m_navMesh->init(navData, navDataSize, DT_TILE_FREE_DATA);
                  if (dtStatusFailed(status))
                  {
                    dtFree(navData);
                    m_ctx->log(RC_LOG_ERROR, "Could not init Detour navmesh");
                    return false;
                  }
              */

      }

// These variables are all user entered. This is just setting them up.
      void RecastUtilM::resetCommonSettings(  float cellSize,
                                              float cellHeight,
                                              float agentHeight,
                                              float agentRadius,
                                              float agentMaxClimb){
        m_cellSize = cellSize;
        m_cellHeight = cellHeight;
        m_agentHeight = agentHeight;
        m_agentRadius = agentRadius;
        m_agentMaxClimb = agentMaxClimb;


      }



}
