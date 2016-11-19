#include "DebugFactory.h"
#include <vector>
#include <utility>
#include <memory>
using namespace std;

glm::mat4 DebugFactory::identity(1.0);
std::vector <std::pair <std::string, std::weak_ptr<DebugMesh> > > DebugFactory::debugMeshCache;

shared_ptr<DebugMesh> DebugFactory::createDebugMesh(const string& meshName, glm::mat4& parentTransform)
{
    shared_ptr<DebugMesh> ret = make_shared<DebugMesh>(parentTransform);

    debugMeshCache.push_back(pair<string, weak_ptr<DebugMesh> > (meshName, ret));

    return ret;
}


void DebugFactory::update()
{
    // Check if any of the Debug Meshes stored have been deleted
    for (int i=0; i<debugMeshCache.size();){
        if (!debugMeshCache[i].second.expired())
            i++;
        else {
            std::iter_swap(debugMeshCache.begin()+i, debugMeshCache.end() - 1);
            debugMeshCache.pop_back();
        }
    }
}

const std::vector<std::pair<string, std::weak_ptr<DebugMesh> > >& DebugFactory::getDebugMeshCacheReference()
{
    return debugMeshCache;
}
