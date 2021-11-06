//Coresponding header
#include "game/entities/Hero.h"

//C system includes

//C++ system includes
#include <iostream>

//Thitrd-party includes

//Own includes
#include "sdl_utils/InputEvent.h"

int32_t Hero::init(const int32_t heroRsrcId)
{
	this->_heroImg.create(heroRsrcId);
	return EXIT_SUCCESS;
}

void Hero::deInit()
{
}

void Hero::draw()
{
	this->_heroImg.draw();
}

void Hero::handleEvent(const InputEvent& event)
{
	if (TouchEvent::KEYBOARD_PRESS != event.type)
	{
		return;
	}

	switch (event.key)
	{
	case Keyboard::KEY_RIGHT:
		this->_heroImg.setFlipType(WidgetFlip::NONE);
		this->_heroImg.setNextFrame();
		this->_heroImg.moveRight(8);
		break;

	case Keyboard::KEY_LEFT:
		this->_heroImg.setFlipType(WidgetFlip::HORIZONTAL);
		this->_heroImg.setNextFrame();
		this->_heroImg.moveLeft(8);
		break;

	case Keyboard::KEY_DOWN:
		this->_heroImg.setPrevFrame();
		this->_heroImg.moveDown(8);
		break;

	case Keyboard::KEY_UP:
		this->_heroImg.setPrevFrame();
		this->_heroImg.moveUp(8);
		break;

	default:
		break;
	}
}
