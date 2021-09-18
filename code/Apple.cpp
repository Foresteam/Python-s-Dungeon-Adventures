#include "Apple.h"
#include "Engine.h"

Apple::Apple() : Entity(Vector::Random(), Representation("■", Color::Modifier(Color::Code::FG_RED))) {

}
void Apple::Interract(Entity* interractor) {
    Engine* engine = Engine::GetInstance();

    if (interractor->GetFlags() & Growable)
        dynamic_cast<IGrowable*>(interractor)->Grow(1);

    engine->AddScore(1);
    engine->RemoveEntity(this);
}