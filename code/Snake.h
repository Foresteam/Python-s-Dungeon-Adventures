#pragma once
#include <list>
#include "Engine.h"
#include "BaseEntities.h"

class Snake : public Entity, public MovableEntity, public GrowableEntity {
private:
	enum Direction {
		INVALID = 0,
		LEFT = 'a',
		UP = 'w',
		RIGHT = 'd',
		DOWN = 's'
	};
	class HeadEntity : public Entity {
	public:
		HeadEntity(Vector pos);
		void UpdateDirection(Direction direction);
	};
	class BodyEntity : public Entity {
	public:
		BodyEntity(Vector pos);
	};

	HeadEntity* head;
	std::list<BodyEntity*> body;

public:
	std::shared_ptr<Vector> velocity;
	Snake(Vector pos);
	~Snake();
	void Move() override;
	void Grow(unsigned int amount) override;
	Vector GetPos() override;
	void Control(char code);
	std::list<RenderData> GetRenderData() override;
};