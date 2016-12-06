#include "World.h"

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
