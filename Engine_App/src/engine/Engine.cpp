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
	gDrawMgr = new DrawMgr();
	if (gDrawMgr == nullptr)
	{
		std::cerr << "ERROR -> gDrawMgr failed with bad alloc." << std::endl;
		return EXIT_FAILURE;
	}

	if (EXIT_SUCCESS != gDrawMgr->init(cfg.drawMgrCfg))
	{
		std::cerr << "gDrawMgr->init() failed." << std::endl;
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

	if (EXIT_SUCCESS != this->_game.init(cfg.gameCfg, &(this->_imageContainer), &(this->_textContainer)))
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

	gDrawMgr->deInit();
	delete gDrawMgr;
	gDrawMgr = nullptr;
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


	std::vector<DrawParams> images;
	this->_game.draw(images);

	SDL_Texture* texture = nullptr;
	for (const DrawParams& image : images)
	{
		switch (image.widgetType)
		{
		case WidgetType::IMAGE:
			texture = this->_imageContainer.getImageTexture(image.rsrcId);
			break;

		case WidgetType::TEXT:
			texture = this->_textContainer.getTextTexture(image.textId);
			break;

		default:
			std::cerr << "ERROR -> received unsupported WidgetType"
				<< static_cast<int32_t>(image.widgetType)
				<< " for rsrcId: " << image.rsrcId
				<< std::endl;
			break;
		}
		
		gDrawMgr->addDrawCmd(image, texture);
	}
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


