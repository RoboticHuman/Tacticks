#pragma once
#include <Recast.h>
#include <Tacticks/DebugFactory.h>
#include <Tacticks/AbstractNavigation.h>

///  \addtogroup navlib
///  @{

///  @brief A wrapper for recast's compact heightfield that facilitates and manages its creation. For more information on compact heightfields see http://www.critterai.org/projects/nmgen_study/regiongen.html
class NLrcHeightfield : public AbstractNavigation{
	/// Actual data of the navigation library
	int walkableHeight, walkableClimb;
	rcHeightfield* data;
	std::shared_ptr<DebugMesh> debugMesh;
public:
    NLrcHeightfield(const World* world);
    virtual ~NLrcHeightfield();
	virtual bool init();
	virtual std::vector<PassObject*> getData(std::string dataName, std::vector<PassObject*> args);
	virtual std::vector<void*> getRawData();
	virtual void constructDebugMesh();
};
/// @}
