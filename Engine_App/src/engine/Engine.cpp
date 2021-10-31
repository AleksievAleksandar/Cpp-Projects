//Coresponding header
#include "engine/Engine.h"

//C system includes

//C++ system includes
#include <cstring>
#include <iostream>

//Thitrd-party includes

//Own includes
#include "utils/thread/ThreadUtils.h"
#include "utils/time/Time.h"
#include "engine/config/EngineConfig.h"
#include "manager_utils/managers/DrawMgr.h"
#include "sdl_utils/Texture.h"


int32_t Engine::init(const EngineConfig& cfg)
{
	if (EXIT_SUCCESS != this->_managerHandler.init(cfg.managerHandlerCfg))
	{
		std::cerr << "_managerHandler.init() failed." << std::endl;
		return EXIT_FAILURE;
	}

	if (EXIT_SUCCESS != this->_event.init())
	{
		std::cerr << "_event.init() failed." << std::endl;
		return EXIT_FAILURE;
	}

	if (EXIT_SUCCESS != this->_game.init(cfg.gameCfg))
	{
		std::cerr << "_game.init() failed." << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void Engine::deInit()
{
	this->_game.deInit();
	this->_event.deInit();
	this->_managerHandler.deInit();
}

void Engine::start()
{
	this->mainLoop();
}

void Engine::mainLoop()
{
	Time time;

	while (true)
	{
		time.getElapsed();
		if (this->processFrame())
		{
			break;
		}
		this->limitFPS(time.getElapsed().toMicroseconds());
	}
}

void Engine::drawFrame()
{
	gDrawMgr->clearScreen();

	this->_game.draw();

	gDrawMgr->finishFrame();
}

bool Engine::processFrame()
{
	while (this->_event.pollEvent())
	{
		if (this->_event.checkForExitRequest())
		{
			return true;
		}
		this->handleEvent();
	}

	this->drawFrame();

	return false;
}

void Engine::handleEvent()
{
	this->_game.handleEvent(this->_event);
}



void Engine::limitFPS(const int64_t elapsedTimeMicroSeconds) const
{
	constexpr auto maxFrames = 30;
	constexpr auto microSecondsInSecond = 1000000;
	constexpr auto microSecondsPerFrame = microSecondsInSecond / maxFrames;
	const int64_t sleepDurationMicroSeconds = microSecondsPerFrame - elapsedTimeMicroSeconds;

	if (sleepDurationMicroSeconds > 0)
	{
		Threading::sleepFor(sleepDurationMicroSeconds);
	}
}


