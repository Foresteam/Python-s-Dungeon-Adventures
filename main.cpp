#include <cstdlib>
#include <iostream>
#include <list>
#include<thread>
// #include "/usr/include/ois/OIS.h" // #include <OIS.h>
#include "code/AbstractionsUtils.h"
#include "code/BaseEntities.h"
#include "code/Engine.h"
#include "code/Snake.h"
using namespace std;

int main(int argc, char* argv[]) {
	Engine* engine = Engine::GetInstance();
	engine->SetSpeed(10);

	Snake* snake = new Snake(Vector());
	engine->RegisterEntity(dynamic_cast<Entity*>(snake));
	engine->SubscribeKeyboardEvent([snake](char c) { snake->Control(c); });

	shared_ptr<bool> gameExit = make_shared<bool>(new bool());
	*gameExit = false;
	thread keyboardThread(Engine::KeyboardThread, gameExit);
	while (true) { // main cycle
		if (!engine->Update())
			continue;
		engine->Render();
		if (*gameExit)
			break;
	}

	keyboardThread.join();
	Engine::Dispose();
	return 0;
}