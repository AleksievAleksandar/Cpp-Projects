//Coresponding header
#include "game/entities/Wheel.h"

//C system includes

//C++ system includes
#include <iostream>

//Thitrd-party includes

//Own includes
#include "sdl_utils/InputEvent.h"


int32_t Wheel::init(const int32_t wheelRsrcId)
{
	this->_wheelImg.create(wheelRsrcId);
	return EXIT_SUCCESS;
}

void Wheel::draw()
{
	this->_wheelImg.draw();
}

void Wheel::handleEvent(const InputEvent& event)
{
	if (TouchEvent::KEYBOARD_PRESS != event.type)
	{
		return;
	}

	switch (event.key)
	{
	case Keyboard::KEY_P:
		this->_wheelImg.rotateRight(20);
		break;

	case Keyboard::KEY_O:
		this->_wheelImg.rotateLeft(20);
		break;

	case Keyboard::KEY_K:
		this->_wheelImg.setRotationCenter(Point::ZERO);
		break;

	case Keyboard::KEY_L:
	{
		Point rotCenter(this->_wheelImg.getWidth(), this->_wheelImg.getHeight());
		rotCenter.x /= 2;
		rotCenter.y /= 2;
		this->_wheelImg.setRotationCenter(rotCenter);
		break;
	}

	default:
		break;
	}
}
