#ifndef ENGINE_H
#define ENGINE_H

//C system includes

//C++ system includes
#include <cstdint>

//Thitrd-party includes

//Own includes
#include "game/Game.h"
#include "sdl_utils/InputEvent.h"
#include "manager_utils/managers/ManagerHandler.h"

//Forward Declarations
struct EngineConfig;


class Engine
{
public:
	int32_t init(const EngineConfig& cfg);
	void deInit();
	void start();

private:
	void mainLoop();
	void drawFrame();
	bool processFrame();
	void handleEvent();

	void limitFPS(const int64_t elapsedTimeMicroSeconds) const;

	InputEvent _event;
	Game _game;
	ManagerHandler _managerHandler;
};

#endif // !ENGINE_H

