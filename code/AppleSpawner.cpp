#include "AppleSpawner.h"
#include "Apple.h"
#include "Engine.h"

AppleSpawner::AppleSpawner() {
    ticks = 0;
}
Entity* AppleSpawner::Spawn() {
    if (ticks < ticksToSpawn) {
        ticks++;
        return nullptr;
    }
    ticks = 0;

    Apple* apple = new Apple();
    Add(apple);
    return apple;
}