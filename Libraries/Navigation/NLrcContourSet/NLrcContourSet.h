#include <Recast.h>
#include <limits>
#include <Tacticks/DebugFactory.h>
#include <Tacticks/AbstractNavigation.h>
#include <cmath>

#ifndef NLrcContourSet_h
#define NLrcContourSet_h

///  \addtogroup navlib
///  @{

///  @brief A wrapper for recast's contour set that facilitates and manages its creation. For more information on compact heightfields see http://www.critterai.org/projects/nmgen_study/contourgen.html
class NLrcContourSet : public AbstractNavigation{

    /// Actual data of the navigation library
    rcContourSet* data;
    std::shared_ptr<DebugMesh> debugMesh;
public:
    NLrcContourSet(const World* world);
    virtual ~NLrcContourSet();
    virtual bool init();
	virtual std::vector<PassObject*> getData(std::string dataName, std::vector<PassObject*> args);
	virtual std::vector<void*> getRawData();
	virtual void constructDebugMesh();
};
/// @}


#endif
