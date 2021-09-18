#include "BaseEntities.h"

Entity::Entity(Vector pos, Representation representation) {
	this->representation = representation;
	this->pos = pos;
    flags = 0u;
}
Entity::Entity() : Entity::Entity(Vector(), Representation()) {}
Vector Entity::GetPos() { return pos; }
unsigned int Entity::GetFlags() { return flags; }
void Entity::_SetPos(Vector npos) { pos = npos; }
std::list<RenderData> Entity::GetRenderData() {
	auto l = std::list<RenderData>();
	l.push_back(RenderData(pos, representation));
	return l;
}
Representation Entity::GetRepresentation() {
	return representation;
}