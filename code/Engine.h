#pragma once
#include <iostream>
#include <list>
#include <memory>
#include <functional>
#include "AbstractionsUtils.h"
#include "BaseEntities.h"
#include "Spawner.h"

typedef std::function<void(char)> KeyboardSubscriber;

class Engine {
private:
	Representation renderWorld[SCR_X][SCR_Y];
	double frameInterval;
	static Engine* _instance;
	Engine();
	~Engine();

	static std::list<KeyboardSubscriber> keyboardEvents;
	std::list<Spawner*> spawners;
	std::list<Entity*> entities;
	bool gameOver;
	unsigned int score;
public:
	Engine(Engine& other) = delete;
	void operator=(const Engine&) = delete;
	static Engine* GetInstance();
	static void Dispose();

	bool Render();
	bool Update();
	static void SubscribeKeyboardEvent(KeyboardSubscriber sub);
	static void KeyboardThread(std::shared_ptr<bool> finished);

	void RegisterSpawner(Spawner* spawner);
	void RegisterEntity(Entity* entity);
	void RemoveEntity(Entity* entity);
	void SetSpeed(double speed);
	void SetEntityPos(Entity* entity, Vector pos);

	void AddScore(unsigned int amount);
	void ResetScore();
	void GameOver();
	// void RestartGame();
};