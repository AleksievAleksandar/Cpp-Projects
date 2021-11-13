//Coresponding header
#include "game/Game.h"

//C system includes

//C++ system includes
#include <iostream>

//Thitrd-party includes

//Own includes
#include "sdl_utils/InputEvent.h"


int32_t Game::init(const GameCfg& cfg)
{
	if (EXIT_SUCCESS != this->_hero.init(cfg.runningGirlRsrcId))
	{
		std::cerr << "ERROR -> _hero.init() failed() for RsrcId: " << cfg.runningGirlRsrcId << std::endl;
		return EXIT_FAILURE;
	}

	if (EXIT_SUCCESS != this->_wheel.init(cfg.wheelRsrcId))
	{
		std::cerr << "ERROR -> _wheel.init() failed() for RsrcId: " << cfg.wheelRsrcId << std::endl;
		return EXIT_FAILURE;
	}

	const int32_t buttonsRsrcIds[WHEEL_BTNS_CNT] = { cfg.startButtonRsrcId,
													 cfg.stopButtonRsrcId };

	const Point buttonsStartPos[WHEEL_BTNS_CNT] = { Point(650, 100),
													Point(830, 100) };

	for (int32_t i = 0; i < WHEEL_BTNS_CNT; ++i)
	{
		if (EXIT_SUCCESS != this->_wheelBtns[i].init(this, i))
		{
			std::cerr << "ERROR -> _wheelBtns[].init() failed() for RsrcId: " << i << " failed." << std::endl;
			return EXIT_FAILURE;
		}

		this->_wheelBtns[i].create(buttonsRsrcIds[i], buttonsStartPos[i]);
	}

	this->_blackBgrImg.create(cfg.blackBgrRsrcId);
	this->_blackBgrImg.activateAlphaModulation();
	this->_blackBgrImg.setOpacity(ZERO_OPACITY);

	this->_wheelBtns[WHEEL_STOP_BTN_IDX].lockInput();

	return EXIT_SUCCESS;
}

void Game::deInit()
{
	this->_hero.deInit();
}

void Game::draw()
{
	this->_wheel.draw();
	this->_hero.draw();

	for (int32_t i = 0; i < WHEEL_BTNS_CNT; ++i)
	{
		this->_wheelBtns[i].draw();
	}

	this->_blackBgrImg.draw();
}

void Game::handleEvent(const InputEvent& event)
{
	for (int32_t i = 0; i < WHEEL_BTNS_CNT; ++i)
	{
		if (this->_wheelBtns[i].isInputUnlocked() && this->_wheelBtns[i].containsEvent(event))
		{
			this->_wheelBtns[i].handleEvent(event);
			return;
		}
		
	}

	this->_hero.handleEvent(event);
	this->_wheel.handleEvent(event);

	if (event.type == TouchEvent::KEYBOARD_PRESS)
	{
		if (event.key == Keyboard::KEY_NUMPAD_PLUS)
		{
			this->_blackBgrImg.setOpacity(this->_blackBgrImg.getOpacity() + 5);
		}
		else if (event.key == Keyboard::KEY_NUMPAD_MINUS)
		{
			this->_blackBgrImg.setOpacity(this->_blackBgrImg.getOpacity() - 5);
		}
	}
}

void Game::process()
{
	this->_wheel.process();
}

void Game::onButtonPressed(int32_t buttonId)
{
	switch (buttonId)
	{
	case WHEEL_START_BTN_IDX:
		this->_wheelBtns[WHEEL_START_BTN_IDX].lockInput();
		this->_wheelBtns[WHEEL_STOP_BTN_IDX].unlockInput();
		this->_wheel.startAnim();
		break;

	case WHEEL_STOP_BTN_IDX:
		this->_wheelBtns[WHEEL_START_BTN_IDX].unlockInput();
		this->_wheelBtns[WHEEL_STOP_BTN_IDX].lockInput();
		this->_wheel.stopAnim();
		break;

	default:
		std::cerr << "ERROR -> Received unsuported buttonId: " << buttonId << std::endl;
		break;
	}
}

