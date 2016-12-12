#pragma once
#include <Recast.h>
#include <Tacticks/DebugFactory.h>
#include <Tacticks/AbstractNavigation.h>

///  \addtogroup navlib
///  @{

///  @brief A wrapper for recast's compact heightfield that facilitates and manages its creation. For more information on compact heightfields see http://www.critterai.org/projects/nmgen_study/regiongen.html
class NLrcCompactHeightfield : public AbstractNavigation{

	/// Actual data of the navigation library
	rcCompactHeightfield* data;
	std::shared_ptr<DebugMesh> debugMesh;
public:
    NLrcCompactHeightfield(const World* world);
    virtual ~NLrcCompactHeightfield();
	virtual bool init();
	virtual std::vector<PassObject*> getData(std::string dataName, std::vector<PassObject*> args);
	virtual std::vector<void*> getRawData();
	virtual void constructDebugMesh();
};
/// @}
