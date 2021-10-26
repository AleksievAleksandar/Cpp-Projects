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

#include "sdl_utils/Texture.h"


int32_t Engine::init(const EngineConfig& cfg)
{
	if (EXIT_SUCCESS != this->_window.init(cfg.windowCfg))
	{
		std::cerr << "_window.init() failed." << std::endl;
		return EXIT_FAILURE;
	}

	if (EXIT_SUCCESS != this->_renderer.init(this->_window.getWindow()))
	{
		std::cerr << "_renderer.init() failed." << std::endl;
		return EXIT_FAILURE;
	}

	if (EXIT_SUCCESS != this->_imageContainer.init(cfg.imageContainerCfg))
	{
		std::cerr << "_imageContainer.init() failed." << std::endl;
		return EXIT_FAILURE;
	}

	if (EXIT_SUCCESS != this->_textContainer.init(cfg.textContainerCfg))
	{
		std::cerr << "_textContainer.init() failed." << std::endl;
		return EXIT_FAILURE;
	}

	if (EXIT_SUCCESS != this->_event.init())
	{
		std::cerr << "_event.init() failed." << std::endl;
		return EXIT_FAILURE;
	}

	if (EXIT_SUCCESS != this->_game.init(cfg.gameCfg, &(this->_imageContainer)))
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
	this->_textContainer.deInit();
	this->_imageContainer.deInit();
	this->_renderer.deInit();
	this->_window.deInit();
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
	this->_renderer.clearScreen();

	std::vector<DrawParams> images;
	this->_game.draw(images);

	SDL_Texture* texture = nullptr;
	for (const DrawParams& image : images)
	{
		texture = this->_imageContainer.getImageTexture(image.rsrcId);
		this->_renderer.renderTexture(texture, image);
	}

	this->_renderer.finishFrame();
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


