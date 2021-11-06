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

	this->_mousePosText.create("_", cfg.textFontId, Colors::RED);
	this->_mousePosText.hide();

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
	this->_mousePosText.draw();
}

void Game::handleEvent(const InputEvent& event)
{
	this->_hero.handleEvent(event);
	this->_wheel.handleEvent(event);

	if (event.type == TouchEvent::KEYBOARD_PRESS)
	{
		if (event.key == Keyboard::KEY_A)
		{
			this->_mousePosText.rotateRight(30);
		}
	}

	this->setMousePosText(event.pos);
}

void Game::setMousePosText(const Point& mousePos)
{
	this->_mousePosText.show();
	this->_mousePosText.setPossition(mousePos);

	std::string textContetnt = "X: ";
	textContetnt.append(std::to_string(mousePos.x))
		        .append(", Y: ")
		        .append(std::to_string(mousePos.y));
	this->_mousePosText.setText(textContetnt);
}
