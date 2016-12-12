#include <Recast.h>
#include <limits>
#include <cmath>
#include <Tacticks/DebugFactory.h>
#include <Tacticks/AbstractNavigation.h>


#ifndef NLrcPolyMesh_h
#define NLrcPolyMesh_h

///  \addtogroup navlib
///  @{

///  @brief A wrapper for recast's polymesh that facilitates and manages its creation. For more information on polymeshes see http://www.critterai.org/projects/nmgen_study/polygen.html
class NLrcPolyMesh : public AbstractNavigation{

    /// Actual data of the navigation library
    rcPolyMesh* data;
    std::shared_ptr<DebugMesh> debugMesh;
public:
    NLrcPolyMesh(const World* world);
    virtual ~NLrcPolyMesh();
    virtual bool init();
    virtual std::vector<PassObject*> getData(std::string dataName, std::vector<PassObject*> args);
    virtual std::vector<void*> getRawData();
    virtual void constructDebugMesh();
};
/// @}

#endif
