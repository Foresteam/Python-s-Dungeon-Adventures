#include "Engine.h"
#include <time.h>
#include <thread>

clock_t frameTimer;

Engine* Engine::_instance = nullptr;
std::list<KeyboardSubscriber> Engine::keyboardEvents = std::list<KeyboardSubscriber>();

Engine::Engine() {
	gameOver = true;
	score = 0;
	keyboardEvents.clear();
	spawners.clear();
	entities.clear();
}
Engine::~Engine() {
	for (Entity* e : entities)
		delete e;
	for (Spawner* s : spawners)
		delete s;
}
Engine* Engine::GetInstance() {
	if (!_instance)
		_instance = new Engine();
	return _instance;
}
void Engine::Dispose() { delete _instance; }

void Engine::Render() {
	for (int i = 0; i < SCR_Y; i++)
		for (int j = 0; j < SCR_X; j++)
			renderWorld[j][i] = Representation();
	for (Entity* entity : entities) {
		auto RD = entity->GetRenderData();
		for (RenderData rd : RD) {
			rd.pos = Vector::Normalized(rd.pos);
			renderWorld[rd.pos.x][rd.pos.y] = rd.rpr;
		}
	}
	system("clear");
	for (int i = 0; i < SCR_Y; i++) {
		for (int j = 0; j < SCR_X; j++)
			std::cout << renderWorld[j][i];
		std::cout << std::endl;
	}
}
bool Engine::Update() {
	if (double(std::clock() - frameTimer) / CLOCKS_PER_SEC < frameInterval)
		return false;
	frameTimer = std::clock();
	// std::this_thread::sleep_for(std::chrono::milliseconds(frameInterval));
	for (Spawner* spawner : spawners) {
		Entity* e = spawner->Spawn();
		if (e)
			RegisterEntity(e);
	}
	for (Entity* entity : entities)
		if (entity->GetFlags() & Entity::Flags::Movable)
			dynamic_cast<MovableEntity*>(entity)->Move();
	return true;
}
void Engine::SubscribeKeyboardEvent(KeyboardSubscriber sub) {
	keyboardEvents.push_back(sub);
}
void Engine::KeyboardThread(std::shared_ptr<bool> finished) {
	while (true) {
		char c = getch();
		for (KeyboardSubscriber sub : keyboardEvents)
			sub(c);
		if (c == 'e') {
			*finished = true;
			return;
		}
	}
}

void Engine::RegisterSpawner(Spawner* spawner) {
	spawners.push_back(spawner);
}
void Engine::RegisterEntity(Entity* entity) {
	entities.push_back(entity);
}
void Engine::RemoveEntity(Entity* entity) {
	entities.remove(entity);
	for (Spawner* s : spawners)
		s->Remove(entity);
	delete entity;
}
void Engine::SetSpeed(double speed) {
	frameInterval = 1. / speed;
}
void Engine::SetEntityPos(Entity* entity, Vector pos) {
	entity->_SetPos(pos);
}

void Engine::AddScore(unsigned int amount) {
	score += amount;
}
void Engine::ResetScore() {
	score = 0;
}
void Engine::GameOver() {
	gameOver = true;
}