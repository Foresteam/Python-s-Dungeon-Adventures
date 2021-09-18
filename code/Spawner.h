#pragma once
#include <list>
#include "BaseEntities.h"

class Spawner {
protected:
    Spawner() = default;
    void Add(Entity* e);
    std::list<Entity*> spawned;
public:
    void Remove(Entity* e);
    virtual Entity* Spawn() = 0;
};