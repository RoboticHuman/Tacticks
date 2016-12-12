#pragma once
#include <vector>
#include "Model.h"
class World {
private:
    World () = default;
    ~World () = default;
    static World world;
    Model worldModel;
public:
    static World& getInstance();
    Model& getWorldModel();
    const Model& getWorldModel() const;
	std::vector<float> getVertices() const;
	std::vector<int> getIndices() const;
};
