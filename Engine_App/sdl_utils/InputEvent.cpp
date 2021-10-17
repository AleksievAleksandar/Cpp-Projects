//Coresponding header
#include "InputEvent.h"

//C system includes

//C++ system includes
#include <iostream>
#include <cstring>

//Thitrd-party includes
#include <SDL_events.h>

//Own includes

//Forward Declarations



int32_t InputEvent::init()
{
	this->_sdlEvent = new SDL_Event{};
	//memset(this->_sdlEvent, 0, sizeof(SDL_Event)); //set 0 for each bite
	if (this->_sdlEvent == nullptr)
	{
		std::cerr << "InputEvent::init() failed. Bad alloc for SDL_Event()." << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

void InputEvent::deInit()
{
	if (this->_sdlEvent != nullptr)
	{
		delete this->_sdlEvent;
		this->_sdlEvent = nullptr;
	}
}

bool InputEvent::pollEvent()
{
	if (0 == SDL_PollEvent(this->_sdlEvent))
	{
		// no events currently
		return false;
	}

	SDL_GetMouseState(&this->pos.x, &this->pos.y);
	this->setEventTypeInternal();

	return true;
}

bool InputEvent::checkForExitRequest() const
{
	return ((this->_sdlEvent->type == EventType::QUIT) || (this->type == TouchEvent::KEYBOARD_PRESS && this->key == Keyboard::KEY_ESCAPE));
}

void InputEvent::setEventTypeInternal() {
	switch (this->_sdlEvent->type) {
	case EventType::KEYBOARD_PRESS:
		this->key = this->_sdlEvent->key.keysym.sym;
		this->mouseButton = Mouse::UNKNOWN;
		this->type = TouchEvent::KEYBOARD_PRESS;
		break;

	case EventType::KEYBOARD_RELEASE:
		this->key = this->_sdlEvent->key.keysym.sym;
		this->mouseButton = Mouse::UNKNOWN;
		this->type = TouchEvent::KEYBOARD_RELEASE;
		break;

		//NOTE: the fall-through is intentional
	case EventType::MOUSE_PRESS:
		this->key = Keyboard::KEY_UNKNOWN;
		this->mouseButton = this->_sdlEvent->button.button;
		this->type = TouchEvent::TOUCH_PRESS;
		break;
	case EventType::FINGER_PRESS:
		this->key = Keyboard::KEY_UNKNOWN;
		this->mouseButton = Mouse::UNKNOWN;
		this->type = TouchEvent::TOUCH_PRESS;
		break;

	case EventType::MOUSE_RELEASE:
		this->key = Keyboard::KEY_UNKNOWN;
		this->mouseButton = this->_sdlEvent->button.button;
		this->type = TouchEvent::TOUCH_RELEASE;
		break;
	case EventType::FINGER_RELEASE:
		this->key = Keyboard::KEY_UNKNOWN;
		this->mouseButton = Mouse::UNKNOWN;
		this->type = TouchEvent::TOUCH_RELEASE;
		break;

		//X is pressed on the window (or CTRL-C signal is sent)
	case EventType::QUIT:
		this-> key = Keyboard::KEY_UNKNOWN;
		this-> mouseButton = Mouse::UNKNOWN;
		this-> type = TouchEvent::UNKNOWN;
		break;

	default:
		this->key = Keyboard::KEY_UNKNOWN;
		this->mouseButton = Mouse::UNKNOWN;
		this->type = TouchEvent::UNKNOWN;
		break;
	}
}

