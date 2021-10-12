#ifndef MONITOR_WINDOW_H
#define MONITOR_WINDOW_H

//C system includes

//C++ system includes
#include <cstdint>
#include <string>

//Thitrd-party includes

//Own includes
#include "../utils/drawing/Rectangle.h"

//Forward Declarations
struct SDL_Window;

struct MonitorWindowCfg
{
	std::string windowName = "Hello, World!";
	int32_t windowX;
	int32_t windowY;
	int32_t windowWidth;
	int32_t windowHeight;
	uint32_t windowFlags;
};

class MonitorWindow
{
public:
	MonitorWindow() = default;

	MonitorWindow(const MonitorWindow& other) = delete;
	MonitorWindow(MonitorWindow&& other) = delete;

	MonitorWindow& operator=(const MonitorWindow& other) = delete;
	MonitorWindow& operator=(MonitorWindow&& other) = delete;

	int32_t init(const MonitorWindowCfg& cfg);
	void deinit();

private:
	SDL_Window* _window;
	Rectangle _windowRect;
};

#endif // !MONITOR_WINDOW_H
