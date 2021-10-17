#ifndef ENGINE_H
#define ENGINE_H

//C system includes

//C++ system includes
#include <cstdint>

//Thitrd-party includes

//Own includes
#include "sdl_utils/MonitorWindow.h"
#include "sdl_utils/InputEvent.h"

//Forward Declarations
struct SDL_Surface;

class Engine
{
public:
	int32_t init();
	void deInit();
	void start();

private:
	void mainLoop();
	void drawFrame();
	bool processFrame();
	void handleEvent();

	int32_t loadResources();

	MonitorWindow _window;
	InputEvent _event;
	SDL_Surface* _screenSurface = nullptr;
	SDL_Surface* _image = nullptr;
};

#endif // !ENGINE_H

