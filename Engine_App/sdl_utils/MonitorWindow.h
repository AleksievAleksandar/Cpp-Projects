#ifndef MONITOR_WINDOW_H
#define MONITOR_WINDOW_H

//C system includes

//C++ system includes
#include <cstdint>
#include <string>

//Thitrd-party includes

//Own includes
#include "utils/drawing/Rectangle.h"
#include "config/MonitorWindowCfg.h"

//Forward Declarations
struct SDL_Window;
struct SDL_Surface;

class MonitorWindow
{
public:
	MonitorWindow() = default;
	~MonitorWindow();
	MonitorWindow(const MonitorWindow& other) = delete;
	MonitorWindow(MonitorWindow&& other) = delete;

	MonitorWindow& operator=(const MonitorWindow& other) = delete;
	MonitorWindow& operator=(MonitorWindow&& other) = delete;

	int32_t init(const MonitorWindowCfg& cfg);
	void deInit();
	void updateWindowSurface();
	SDL_Window* getWindow();

private:
	SDL_Window* _window = nullptr;
	Rectangle _windowRect = Rectangle::UNDEFINED;
};

#endif // !MONITOR_WINDOW_H
