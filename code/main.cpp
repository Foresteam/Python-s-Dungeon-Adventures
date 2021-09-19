#include <cstdlib>
#include <iostream>
#include <list>
#include <thread>
#include "AbstractionsUtils.h"
#include "BaseEntities.h"
#include "Engine.h"
#include "Snake.h"
#include "AppleSpawner.h"
using namespace std;

int main(int argc, char* argv[]) {
	Engine* engine = Engine::GetInstance();
	engine->SetSpeed(5);

	Snake* snake = new Snake(Vector());
	engine->RegisterEntity(dynamic_cast<Entity*>(snake));
	engine->SubscribeKeyboardEvent([snake](char c) { snake->Control(c); });
	engine->RegisterSpawner(new AppleSpawner());

	shared_ptr<bool> gameExit = make_shared<bool>(new bool());
	*gameExit = false;
	thread keyboardThread(Engine::KeyboardThread, gameExit);
	while (true) { // main cycle
		if (!engine->Update())
			continue;
		if (engine->Render())
			break;
		if (*gameExit)
			break;
	}

	keyboardThread.join();
	Engine::Dispose();
	return 0;
}