#include "Snake.h"
#include <mutex>
#include <thread>

std::mutex mu;

Snake::HeadEntity::HeadEntity(Vector pos) : Entity(pos, Representation("■", Color::Modifier(Color::Code::FG_CYAN))) {}
void Snake::HeadEntity::UpdateDirection(Direction direction) {
	switch (direction) {
		case LEFT:
			representation = Representation("◀", Color::Modifier(Color::Code::FG_CYAN));
			break;
		case UP:
			representation = Representation("▲", Color::Modifier(Color::Code::FG_CYAN));
			break;
		case RIGHT:
			representation = Representation("▶", Color::Modifier(Color::Code::FG_CYAN));
			break;
		case DOWN:
			representation = Representation("▼", Color::Modifier(Color::Code::FG_CYAN));
			break;
	}
}
void Snake::HeadEntity::Die() {
	representation = Representation("X", Color::Modifier(Color::Code::FG_CYAN));
}

Snake::BodyEntity::BodyEntity(Vector pos) : Entity(pos, Representation("■", Color::Modifier(Color::Code::FG_BLUE))) {}
void Snake::BodyEntity::Die() {
	representation = Representation("X", Color::Modifier(Color::Code::FG_BLUE));
}

Snake::Snake(Vector pos) : Entity() {
	flags |= Player;
	flags |= Movable;
	flags |= Growable;
	head = new HeadEntity(pos);
	velocity = std::make_shared<Vector>(Vector(0, 1));
	head->UpdateDirection(DOWN);
	body = std::list<BodyEntity*>();
	// for (int i = 0; i < 5; i++)
	// 	body.push_back(new BodyEntity(pos));
}
Snake::~Snake() {
	delete head;
	for (Entity* e : body)
		delete e;
}
void Snake::Move() {
	Engine* engine = Engine::GetInstance();
	Vector prevPos = head->GetPos();
	engine->SetEntityPos(head, head->GetPos() + *velocity);
	for (BodyEntity* be : body) {
		Vector _prevPos = prevPos;
		prevPos = be->GetPos();
		engine->SetEntityPos(be, _prevPos);
	}
}
bool Snake::CheckSelfCollision() {
	for (BodyEntity* be : body)
		if (be->GetPos() == head->GetPos()) {
			Die();
			return true;
		}
	return false;
}
void Snake::Die() {
	head->Die();
	for (BodyEntity* be : body)
		be->Die();
}
void Snake::Grow(unsigned int amount) {
	for (unsigned int i = 0; i < amount; i++)
		body.push_back(new BodyEntity(body.size() > 0 ? body.back()->GetPos() : head->GetPos()));
}
Vector Snake::GetPos() {
	return head->GetPos();
}
void Snake::Control(char code) {
	mu.lock();
	switch (code) {
		case Direction::LEFT:
			*velocity = Vector(-1, 0);
			head->UpdateDirection((Direction)code);
			break;
		case Direction::UP:
			*velocity = Vector(0, -1);
			head->UpdateDirection((Direction)code);
			break;
		case Direction::RIGHT:
			*velocity = Vector(1, 0);
			head->UpdateDirection((Direction)code);
			break;
		case Direction::DOWN:
			*velocity = Vector(0, 1);
			head->UpdateDirection((Direction)code);
			break;
	}
	mu.unlock();
}
std::list<RenderData> Snake::GetRenderData() {
	auto rd = std::list<RenderData>();
	for (auto e : body)
		rd.push_back(RenderData(e->GetPos(), e->GetRepresentation()));
	rd.push_back(RenderData(head->GetPos(), head->GetRepresentation()));
	return rd;
}