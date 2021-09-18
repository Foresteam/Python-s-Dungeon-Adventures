#pragma once
#include <list>
#include "Engine.h"
#include "BaseEntities.h"

class Snake : public Entity, public IMovable, public IGrowable {
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
		void Die();
	};
	class BodyEntity : public Entity {
	public:
		BodyEntity(Vector pos);
		void Die();
	};

	HeadEntity* head;
	std::list<BodyEntity*> body;

public:
	std::shared_ptr<Vector> velocity;
	Snake(Vector pos);
	~Snake();
	void Move() override;
	bool CheckSelfCollision() override;
	void Die();
	void Grow(unsigned int amount) override;
	Vector GetPos() override;
	void Control(char code);
	std::list<RenderData> GetRenderData() override;
};