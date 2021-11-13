//Coresponding header
#include "manager_utils/input/ButtonBase.h"

//C system includes

//C++ system includes
#include <iostream>

//Thitrd-party includes

//Own includes
#include "sdl_utils/InputEvent.h"

void ButtonBase::draw()
{
	Image::draw();
}

void ButtonBase::lockInput()
{
	this->_isInputUnlocked = false;
	Image::setFrame(ButtonStates::DISABLED);
}

void ButtonBase::unlockInput()
{
	this->_isInputUnlocked = true;
	Image::setFrame(ButtonStates::UNCLICKED);
}

bool ButtonBase::isInputUnlocked() const
{
	return this->_isInputUnlocked;
}

bool ButtonBase::containsEvent(const InputEvent& e)
{
	return Image::containsPoint(e.pos);
}
