#include "NLdtNavMesh.h"
#include <Recast.h>
#include <DetourNavMesh.h>
#include <DetourNavMeshBuilder.h>
#include <Tacticks/NavigationFactory.h>
#include <Tacticks/PassObjectFloat.h>
#include <Tacticks/PassObjectInt.h>
#include <Tacticks/PassObjectBool.h>
#include <iostream>
using namespace std;

NLdtNavMesh::NLdtNavMesh(const World* world) : AbstractNavigation(world){data = nullptr;}
NLdtNavMesh::~NLdtNavMesh(){if(data) dtFreeNavMesh(data);}
bool NLdtNavMesh::init()
{
    AbstractNavigation* polyMeshNav = NavigationFactory::getNav("NLrcPolyMesh").getNav();
    AbstractNavigation* polyMeshDetailNav = NavigationFactory::getNav("NLrcPolyMeshDetail").getNav();
    AbstractNavigation* heightFieldNav = NavigationFactory::getNav("NLrcHeightfield").getNav();
    rcPolyMesh* m_pmesh = static_cast<rcPolyMesh*>(polyMeshNav->getRawData()[0]);
    rcPolyMeshDetail* m_dmesh = static_cast<rcPolyMeshDetail*>(polyMeshDetailNav->getRawData()[0]);
    rcHeightfield* rcHeightfieldData = static_cast<rcHeightfield*>(heightFieldNav->getRawData()[0]);
    const float m_agentHeight = dynamic_cast<PassObjectFloat*>(args[0])->getValue();
    const float m_agentRadius = dynamic_cast<PassObjectFloat*>(args[1])->getValue();
    const float walkableClimb = dynamic_cast<PassObjectFloat*>(args[2])->getValue();

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
    //      params.offMeshConCount = m_geom->getOffMeshConnectionCount();
    params.walkableHeight = m_agentHeight;
    params.walkableRadius = m_agentRadius;
    params.walkableClimb = walkableClimb;
    params.offMeshConVerts = 0;
    params.offMeshConRad = 0;
    params.offMeshConDir = 0;
    params.offMeshConAreas = 0;
    params.offMeshConFlags = 0;
    params.offMeshConUserID = 0;
    params.offMeshConCount = 0;
    rcVcopy(params.bmin, m_pmesh->bmin);
    rcVcopy(params.bmax, m_pmesh->bmax);
    params.ch = rcHeightfieldData->ch;
    params.cs = rcHeightfieldData->cs;
    params.buildBvTree = true;
    ////////////////////////////////////////////////////
    
    //Building navmesh
    ////////////////////////////////////////////////////
    if (!dtCreateNavMeshData(&params, &navData, &navDataSize))
    {
        return false;
    }

    ////////////////////////////////////////////////////


    //Allocating the navmesh
    ////////////////////////////////////////////////////
    dtNavMesh* m_navMesh;
    m_navMesh = dtAllocNavMesh();
    if (!m_navMesh)
    {
        dtFree(navData);
        return false;
    }
    else {
        data = m_navMesh;
    }
    ////////////////////////////////////////////////////
    m_navMesh->init(navData,navDataSize,DT_TILE_FREE_DATA);

    constructDebugMesh();
    clearDirty();
    return true;
}

vector<PassObject*> NLdtNavMesh::getData(string, vector<PassObject*>){return {};}

vector<void*> NLdtNavMesh::getRawData()
{
	if(isDirty()){
		if(data) dtFreeNavMesh(data);
		data = nullptr;
		init();
	}
	return {data};
}




void NLdtNavMesh::constructDebugMesh()
{
    debugMesh = DebugFactory::createDebugMesh("dtNavMesh");

    for (int i = 0; i < data->getMaxTiles(); i++)
    {
        const dtNavMesh* temp = data;
        const dtMeshTile* tile = temp->getTile(i);
        if (!tile->header) continue;
        dtPolyRef base = data->getPolyRefBase(tile);


        for (int l = 0; l < tile->header->polyCount; l++)
        {
            const dtPoly* p = &tile->polys[l];
            if (p->getType() == DT_POLYTYPE_OFFMESH_CONNECTION) // Skip off-mesh links.
                continue;
            const dtPolyDetail* pd = &tile->detailMeshes[l];

            glm::vec3 color = glm::vec3((rand()%1000)/1000.0,(rand()%1000)/1000.0,(rand()%1000)/1000.0);

            for (int j = 0; j < pd->triCount; ++j)
            {
                const unsigned char* t = &tile->detailTris[(pd->triBase+j)*4];


                vector<glm::vec3> polygon;
                for (int k = 0; k < 3; ++k)
                {
                    if (t[k] < p->vertCount){
                        polygon.push_back(glm::vec3(tile->verts[p->verts[t[k]]*3], tile->verts[p->verts[t[k]]*3+1], tile->verts[p->verts[t[k]]*3+2]));
                    }
                    else {
                        polygon.push_back(glm::vec3(tile->detailVerts[(pd->vertBase+t[k]-p->vertCount)*3], 
                                tile->detailVerts[(pd->vertBase+t[k]-p->vertCount)*3+1], 
                                tile->detailVerts[(pd->vertBase+t[k]-p->vertCount)*3+2]));
                    }
                }
                debugMesh->drawConvexPolygon(polygon,color[0],color[1],color[2],1);
            }
        }
    }
}

extern "C"
AbstractNavigation* newNav(const World* world)
{
  return new NLdtNavMesh(world);
}

extern "C"
NavigationInfo declareDependencies()
{
  return {{"NLrcPolyMesh","NLrcPolyMeshDetail","NLrcHeightfield"}};
}
