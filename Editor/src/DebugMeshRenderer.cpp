#include "DebugMeshRenderer.h"

void DebugMeshRenderer::update()
{
    DebugFactory::update();
    const std::vector<std::weak_ptr<DebugMesh> >& debugMeshes=DebugFactory::getDebugMeshCacheReference();

    for (int i=0; i<debugMeshPtrs.size();) {
        if (debugMeshPtrs[i].expired()) {
            debugMeshPtrs.erase(debugMeshPtrs.begin()+i);
            debugMeshData.erase(debugMeshData.begin()+i);
            bDrawDebugMeshes.erase(bDrawDebugMeshes.begin()+i);
        }
        else {
            i++;
        }
    }

    for(int i=debugMeshPtrs.size() ; i<debugMeshes.size(); i++){
        debugMeshPtrs.push_back(debugMeshes[i]);

        debugMeshData.push_back(DebugMeshRenderData(debugMeshPtrs.back().lock()->vertices,debugMeshPtrs.back().lock()->indices));
        bDrawDebugMeshes.push_back(false);
    }
}

void DebugMeshRenderer::draw(){
    for(int i=0;i<bDrawDebugMeshes.size();i++)
    {
        if(bDrawDebugMeshes[i])
            debugMeshData[i].draw(debugMeshPtrs[i].lock()->getGlobalTransform());
    }
}
