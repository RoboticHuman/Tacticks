#include "World.h"
#include <queue>
using namespace std;

World World::world;

World& World::getInstance()
{
    return world;
}

Model& World::getWorldModel()
{
    return worldModel;
}

const Model& World::getWorldModel() const
{
    return worldModel;
}
vector<float> World::getVertices() const
{
    queue<const Model*> Q;
    Q.push(&worldModel);
    vector<float> ret;
    while(Q.size()){
        const Model* cur = Q.front(); Q.pop();
        if(cur == nullptr) continue;
        for(const Mesh& mesh : cur->getMeshes())
            for(const Vertex& v : mesh.getVertices()){
                ret.push_back(v.position.x);
                ret.push_back(v.position.y);
                ret.push_back(v.position.z);
            }

        for(const Model& model : cur->getModels())
            Q.push(&model);
    }
	return ret;
}
vector<int> World::getIndices() const
{
    queue<const Model*> Q;
    Q.push(&worldModel);
    vector<int> ret;
    int total=0;
    while(Q.size()){
        const Model* cur = Q.front(); Q.pop();
        if(cur == nullptr) continue;
        for(const Mesh& mesh : cur->getMeshes()){
            for(uint32_t ind : mesh.getIndices())
                ret.push_back(ind);
            }
        for(const Model& model : cur->getModels())
            Q.push(&model);
    }
	return ret;
}
