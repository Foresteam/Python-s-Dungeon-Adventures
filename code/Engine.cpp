#include "Engine.h"
#include <time.h>
#include <thread>

clock_t frameTimer;

Engine* Engine::_instance = nullptr;
std::list<KeyboardSubscriber> Engine::keyboardEvents = std::list<KeyboardSubscriber>();

Engine::Engine() {
	gameOver = false;
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

bool Engine::Render() {
	for (int i = 0; i < SCR_Y; i++)
		for (int j = 0; j < SCR_X; j++)
			renderWorld[j][i] = Representation();
	for (Entity* entity : entities) {
		auto RD = entity->GetRenderData();
		for (RenderData rd : RD) {
			// rd.pos = Vector::Normalized(rd.pos);
			renderWorld[rd.pos.x][rd.pos.y] = rd.rpr;
		}
	}
	system("clear");
	for (int i = 0; i < SCR_Y + 1; i++) {
		for (int j = 0; j < SCR_X + 1; j++) {
			if (j < SCR_X && i < SCR_Y)
				std::cout << renderWorld[j][i];
			else
				std::cout << Representation("#", Color::Modifier(Color::Code::FG_DEFAULT));
			if (j == SCR_X) {
				if (i == 10) {
					std::cout << Color::Modifier(Color::Code::FG_DEFAULT) << ' ';
					printf("Score: %i", score);
				}
				if (i == 11) {
					std::cout << Color::Modifier(Color::Code::FG_DEFAULT) << ' ';
					printf("Game over: %s", gameOver ? "yes" : "no");
				}
			}
		}
		std::cout << std::endl;
	}
	return gameOver;
}
bool Engine::Update() {
	if (double(std::clock() - frameTimer) / CLOCKS_PER_SEC < frameInterval)
		return false;
	frameTimer = std::clock();
	if (gameOver)
		return true;
	// std::this_thread::sleep_for(std::chrono::milliseconds(frameInterval));
	for (Spawner* spawner : spawners) {
		Entity* e = spawner->Spawn();
		if (e)
			RegisterEntity(e);
	}
	for (Entity* mover : entities)
		if (mover->GetFlags() & Entity::Flags::Movable) {
			dynamic_cast<IMovable*>(mover)->Move();
			Vector newPos = mover->GetPos();
			for (auto it = entities.rbegin(); it != entities.rend(); it++) {
				Entity* entity = *it;
				if (entity == mover) {
					if (dynamic_cast<IMovable*>(entity)->CheckSelfCollision() && entity->GetFlags() & Entity::Flags::Player)
						gameOver = true;
				}
				else
					if (entity->GetPos() == newPos && entity->GetFlags() & Entity::Flags::Interractable)
						dynamic_cast<IInterractable*>(entity)->Interract(mover);
			}
		}
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
	for (Spawner* s : spawners)
		s->Remove(entity);
	entities.remove(entity);
	// delete entity;
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