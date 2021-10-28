#ifndef INPUT_EVENT_H
#define INPUT_EVENT_H

//C system includes

//C++ system includes
#include <cstdint>

//Thitrd-party includes

//Own includes
#include "utils/drawing/Point.h"
#include "utils/input/EventDefines.h"

//Forward Declarations
union SDL_Event;

class InputEvent
{
public:
	int32_t init();
	void deInit();

	/* returns if OS event is pull*/
	bool pollEvent();
	bool checkForExitRequest() const;

	/* Holds event position on the screen */
	Point pos = Point::UNDEFINED;

	/* See EventDefines.h for more information */
	int32_t key = Keyboard::KEY_UNKNOWN;
	uint8_t mouseButton = Mouse::UNKNOWN;
	TouchEvent type = TouchEvent::UNKNOWN;

private:
	/** Holds the OS communication event system */
	SDL_Event* _sdlEvent = nullptr;

	void setEventTypeInternal();
};

#endif // !INPUT_EVENT_H

