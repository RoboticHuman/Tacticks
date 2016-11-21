#include "DebugFactory.h"
#include <vector>
#include <utility>
#include <memory>
using namespace std;

glm::mat4 DebugFactory::identity(1.0);
std::vector <std::weak_ptr<DebugMesh> > DebugFactory::debugMeshCache;

shared_ptr<DebugMesh> DebugFactory::createDebugMesh(const string& meshName, glm::mat4& parentTransform)
{
    shared_ptr<DebugMesh> ret = make_shared<DebugMesh>(parentTransform);
    ret->name = meshName;

    debugMeshCache.push_back(weak_ptr<DebugMesh> (ret));

    return ret;
}


void DebugFactory::update()
{
    // Check if any of the Debug Meshes stored have been deleted
    for (int i=0; i<debugMeshCache.size();) {
        if (!debugMeshCache[i].expired())
            i++;
        else
            debugMeshCache.erase(debugMeshCache.begin()+i);
    }
}

const std::vector<std::weak_ptr<DebugMesh> >& DebugFactory::getDebugMeshCacheReference()
{
    return debugMeshCache;
}
