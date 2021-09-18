#pragma once
#include "BaseEntities.h"

class Apple : public Entity, public InteractableEntity {
public:
    Apple();
    void Interract(Entity* interractor) override;
};