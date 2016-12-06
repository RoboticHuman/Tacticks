#include "World.h"
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
	auto& vert = worldModel.getMeshes()[0].getVertices(); //Hardcoding first mesh only for now.
	vector<float> ret(vert.size() * 3);
	for(int i = 0; i < vert.size(); i++){
		ret[3*i + 0] = vert[i].position.x;
		ret[3*i + 1] = vert[i].position.y;
		ret[3*i + 2] = vert[i].position.z;
	}
	return ret;
}
vector<int> World::getIndices() const
{
	auto& ind = worldModel.getMeshes()[0].getIndices(); //Hardcoding first mesh only for now.
	vector<int> ret(ind.size());
	for(int i = 0; i < ret.size(); i++)
		ret[i] = ind[i];
	return ret;
}
