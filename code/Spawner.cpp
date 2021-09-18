#include "Spawner.h"

void Spawner::Add(Entity* e) {
    spawned.push_back(e);
    for (auto it = spawned.rbegin(); it != spawned.rend(); it++)
        if (!*it)
            spawned.erase(it.base());
}
void Spawner::Remove(Entity* e) {
    spawned.remove(e);
}