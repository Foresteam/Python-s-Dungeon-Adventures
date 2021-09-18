#pragma once
#include "BaseEntities.h"

class Apple : public Entity, public IInterractable {
public:
    Apple();
    void Interract(Entity* interractor) override;
};