#ifndef MONITOR_WINDOW_CFG_H
#define MONITOR_WINDOW_CFG_H

//C system includes

//C++ system includes
#include <cstdint>
#include <string>

//Thitrd-party includes
#include "utils/drawing/Point.h"
//Own includes

//Forward Declarations

enum WindownFlags
{
	WINDOW_SHOWN = 4, //SDL_WINDOW_SHOWN
	WINDOW_FULLSCREEN_DESKTOP = 4097 //SDL_WINDOW_FULLSCREEN_DESCTOP
};

struct MonitorWindowCfg
{
	std::string windowName;
	Point windowPos = Point::UNDEFINED;
	int32_t windowWidth = 0;
	int32_t windowHeight = 0;
	WindownFlags windowFlags = WINDOW_SHOWN;
};

#endif // !MONITOR_WINDOW_CFG_H
