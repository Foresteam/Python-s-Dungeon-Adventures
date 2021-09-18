#pragma once
#include <time.h>
#include "Spawner.h"

class AppleSpawner : public Spawner {
private:
    int ticks;
    const int ticksToSpawn = 10;

public:
    AppleSpawner();
    Entity* Spawn() override;
};