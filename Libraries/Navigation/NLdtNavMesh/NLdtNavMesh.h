#include <Recast.h>
#include <DetourNavMesh.h>
#include <DetourNavMeshBuilder.h>
#include <Tacticks/DebugFactory.h>
#include <Tacticks/AbstractNavigation.h>

#include <math.h>
#include <stdio.h>
#include <cstring>

///  \addtogroup navlib
///  @{

///  @brief A wrapper for detour that create the constructed polymesh from the outputs of recast.
class NLdtNavMesh : public AbstractNavigation{
      /// Actual data of the navigation library
      dtNavMesh* data;
public:
    NLdtNavMesh(const World* world);
    virtual ~NLdtNavMesh();
	virtual bool init();
	virtual std::vector<PassObject*> getData(std::string dataName, std::vector<PassObject*> args);
	virtual std::vector<void*> getRawData();
	virtual void constructDebugMesh();
};
