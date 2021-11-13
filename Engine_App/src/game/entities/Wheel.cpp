//Coresponding header
#include "game/entities/Wheel.h"

//C system includes

//C++ system includes
#include <iostream>

//Thitrd-party includes

//Own includes
#include "sdl_utils/InputEvent.h"


Wheel::~Wheel()
{
	if (this->isActiveTimerId(this->_rotAnimTimerId))
	{
		this->stopTimer(this->_rotAnimTimerId);
		this->stopTimer(this->_scaleAnimTimerId);
	}
}

int32_t Wheel::init(const int32_t wheelRsrcId, int32_t rotAnimTimerId, int32_t scaleAnimTimerId)
{
	this->_wheelImg.create(wheelRsrcId);


	Point rotCenter(this->_wheelImg.getWidth(), this->_wheelImg.getHeight());
	rotCenter.x /= 2;
	rotCenter.y /= 2;
	this->_wheelImg.setRotationCenter(rotCenter);

	this->_rotAnimTimerId = rotAnimTimerId;
	this->_scaleAnimTimerId = scaleAnimTimerId;

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

	this->startTimer(20, this->_rotAnimTimerId, TimerType::PULSE);
	this->startTimer(100, this->_scaleAnimTimerId, TimerType::PULSE);
}

void Wheel::stopAnim()
{
	if (!this->_isAnimActiv)
	{
		std::cerr << "ERROR -> Wheel anim is already stoped." << std::endl;
		return;
	}
	this->_isAnimActiv = false;
	this->stopTimer(this->_rotAnimTimerId);
	this->stopTimer(this->_scaleAnimTimerId);
}

void Wheel::processRotAnim()
{
	this->_wheelImg.rotateRight(2);
}

void Wheel::processScaleAnim()
{
	//this->_wheelImg.rotateRight(2);
	--this->_scaleSteps;

	if (0 == this->_scaleSteps)
	{
		this->_isShrinking = !this->_isShrinking;
		this->_scaleSteps = 50;
	}

	if (this->_isShrinking)
	{
		this->_wheelImg.setWidth(this->_wheelImg.getWidth() - 5);
		this->_wheelImg.setHeight(this->_wheelImg.getHeight() - 5);
	}
	else
	{
		this->_wheelImg.setWidth(this->_wheelImg.getWidth() + 5);
		this->_wheelImg.setHeight(this->_wheelImg.getHeight() + 5);
	}
}

void Wheel::onTimeout(int32_t timerId)
{
	if (timerId == this->_rotAnimTimerId)
	{
		this->processRotAnim();
	}
	else if (timerId == this->_scaleAnimTimerId)
	{
		this->processScaleAnim();
	}
	else
	{
		std::cerr << "ERROR -> Received unsupported timerId: " << timerId << std::endl;
	}
}
