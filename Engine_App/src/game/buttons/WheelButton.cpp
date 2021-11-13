//Coresponding header
#include "game/buttons/WheelButton.h"

//C system includes

//C++ system includes
#include <iostream>

//Thitrd-party includes

//Own includes
#include "sdl_utils/InputEvent.h"
#include "game/proxies/GameProxy.h"

int32_t WheelButton::init(GameProxy* gameProxy, int32_t buttonId)
{
	if (gameProxy == nullptr)
	{
		std::cerr << "ERROR -> nullptr provided for gameProxy. Button ID " << buttonId << std::endl;
		return EXIT_FAILURE;
	}

	this->_gameProxy = gameProxy;
	this->_buttonId = buttonId;

	return EXIT_SUCCESS;
}

void WheelButton::handleEvent(const InputEvent& e)
{
	if (e.type == TouchEvent::TOUCH_PRESS)
	{
		this->setFrame(ButtonStates::CLICKED);
	}
	else if (e.type == TouchEvent::TOUCH_RELEASE)
	{
		this->setFrame(ButtonStates::UNCLICKED);
		this->_gameProxy->onButtonPressed(this->_buttonId);
	}
}
