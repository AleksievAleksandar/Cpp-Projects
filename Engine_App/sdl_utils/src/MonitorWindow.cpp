//Coresponding header
#include "sdl_utils/MonitorWindow.h"

//C system includes

//C++ system includes
#include <iostream>

//Thitrd-party includes
#include <SDL_video.h>

//Own includes

//Forward Declarations


MonitorWindow::~MonitorWindow()
{
    this->deInit();
}

int32_t MonitorWindow::init(const MonitorWindowCfg& cfg)
{
    Point finalPos;
    if (cfg.windowPos == Point::UNDEFINED)
    {
        finalPos.x = SDL_WINDOWPOS_UNDEFINED;
        finalPos.y = SDL_WINDOWPOS_UNDEFINED;
    }
    else
    {
        finalPos = cfg.windowPos;
    }

    this->_window = SDL_CreateWindow(cfg.windowName.c_str(), finalPos.x, finalPos.y, cfg.windowWidth, cfg.windowHeight, cfg.windowFlags);
    if (nullptr == this->_window)
    {
        std::cerr << "SDL_CreateWindow() failed. Reason: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

	return EXIT_SUCCESS;;
}

void MonitorWindow::deInit()
{
    if (this->_window != nullptr)
    {
        SDL_DestroyWindow(this->_window);
        this->_window = nullptr;
    }
}

void MonitorWindow::updateWindowSurface()
{
    if (EXIT_SUCCESS != SDL_UpdateWindowSurface(this->_window))
    {
        std::cerr << "SDL_UpdateWindowSurface() failed. Reason: " << SDL_GetError() << std::endl;
    }
}

SDL_Window* MonitorWindow::getWindow()
{
    return this->_window;
}
