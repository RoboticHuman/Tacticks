#include <vector>
#include <memory>
#include <string>
#include <utility>
#include "DebugMesh.h"

#pragma once


class DebugFactory
{
    static std::vector <std::pair <string, std::weak_ptr<DebugMesh> > > debugMeshCache;
    static glm::mat4 identity;

public:

    static std::shared_ptr<DebugMesh> createDebugMesh(const std::string& meshName, glm::mat4& parentTransform = identity);
    static void update();
    static const std::vector<std::pair<string, std::weak_ptr<DebugMesh> > >& getDebugMeshCacheReference();
};
