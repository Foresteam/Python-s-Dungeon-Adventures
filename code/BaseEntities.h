#pragma once
#include "AbstractionsUtils.h"
#include <list>

struct RenderData {
	Vector pos;
	Representation rpr;
	RenderData(Vector pos, Representation rpr) {
		this->pos = pos;
		this->rpr = rpr;
	}
};

class Entity {
private:
	Vector pos;

protected:
    unsigned int flags;
	Representation representation;
	Entity(Vector pos, Representation representation);
	Entity();

public:
	virtual ~Entity() = default;

	enum Flags {
        Solid = 1,
		Single = 2,
		Movable = 4,
		Interractable = 8,
		Player = 16,
		Growable = 32
    };

	Representation GetRepresentation();
	virtual std::list<RenderData> GetRenderData();
	virtual Vector GetPos();
	void _SetPos(Vector npos);
    unsigned int GetFlags();
	virtual bool IsSingle() { return false; }
};

// typedef void (*SetPosFunc)(Entity*, Vector);
class IMovable {
public:
	IMovable() = default;
	virtual void Move() = 0;
	virtual bool CheckSelfCollision() = 0;
};
// class SolidEntity {};

class IInterractable {
protected:
	IInterractable() = default;
public:
	virtual void Interract(Entity* interractor) = 0;
};

class IGrowable {
protected:
	IGrowable() = default;
public:
	virtual void Grow(unsigned int amount) = 0;
};