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

	Point rotCenter(this->_wheelImg.getWidth(), this->_wheelImg.getHeight());
	rotCenter.x /= 2;
	rotCenter.y /= 2;
	this->_wheelImg.setRotationCenter(rotCenter);

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

void Wheel::startAnim()
{
	if (this->_isAnimActiv)
	{
		std::cerr << "ERROR -> Wheel anim is already active." << std::endl;
		return;
	}
	this->_isAnimActiv = true;
	std::cout << "Wheel anim started." << std::endl;
}

void Wheel::stopAnim()
{
	if (!this->_isAnimActiv)
	{
		std::cerr << "ERROR -> Wheel anim is already stoped." << std::endl;
		return;
	}
	this->_isAnimActiv = false;
	std::cout << "Wheel anim stoped." << std::endl;
}

void Wheel::process()
{
	if (!this->_isAnimActiv)
	{
		return;
	}
	this->_wheelImg.rotateRight(2);
}
