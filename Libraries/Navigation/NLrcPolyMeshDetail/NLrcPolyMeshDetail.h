#include <Recast.h>
#include <limits>
#include <cmath>
#include <Tacticks/DebugFactory.h>
#include <Tacticks/AbstractNavigation.h>

#ifndef NLrcPolyMeshDetail_h
#define NLrcPolyMeshDetail_h

///  \addtogroup navlib
///  @{

///  @brief A wrapper for recast's detailed polymesh that facilitates and manages its creation. For more information on polymeshes see http://www.critterai.org/projects/nmgen_study/detailgen.html
class NLrcPolyMeshDetail : public AbstractNavigation{

    /// Actual data of the navigation library
    rcPolyMeshDetail* data;
    std::shared_ptr<DebugMesh> debugMesh;
    
public:
    NLrcPolyMeshDetail(const World* world);
    virtual ~NLrcPolyMeshDetail();
    virtual bool init();
    virtual std::vector<PassObject*> getData(std::string dataName, std::vector<PassObject*> args);
    virtual std::vector<void*> getRawData();
    virtual void constructDebugMesh();
};
/// @}

#endif
