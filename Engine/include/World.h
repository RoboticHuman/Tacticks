#pragma once
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
};
