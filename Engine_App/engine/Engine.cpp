//Coresponding header
#include "engine/Engine.h"

//C system includes

//C++ system includes
#include <cstring>
#include <iostream>

//Thitrd-party includes
#include <SDL_surface.h>

//Own includes
#include "sdl_utils/Texture.h"

//Forward Declarations

int32_t Engine::init()
{
    MonitorWindowCfg cfg;
    cfg.windowName = "App_Engine";
    cfg.windowWidth = 640;
    cfg.windowHeight = 480;
    cfg.windowFlags = WINDOW_SHOWN;

    if (EXIT_SUCCESS != this->_window.init(cfg))
    {
        std::cerr << "outWindow.init() failed." << std::endl;
        return EXIT_FAILURE;
    }

    if (EXIT_SUCCESS != loadResources())
    {
        std::cerr << "loadResources() failed." << std::endl;
        return EXIT_FAILURE;
    }

    if (EXIT_SUCCESS != this->_event.init())
    {
        std::cerr << "_event.init() failed." << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void Engine::deInit()
{
    Texture::freeSurface(this->_image);
    this->_window.deInit();
    this->_event.deInit();
}

void Engine::start()
{
    this->mainLoop();
}

void Engine::mainLoop()
{
    while (true)
    {
        if (this->processFrame())
        {
            break;
        }
    }
}

void Engine::drawFrame()
{
    this->_screenSurface = this->_window.getWindowSurface();
    SDL_BlitSurface(this->_image, nullptr, this->_screenSurface, nullptr);

    this->_window.updateWindowSurface();
}

bool Engine::processFrame()
{
    while (this->_event.pollEvent())
    {
        if (this->_event.checkForExitRequest())
        {
            return true;
        }
        this->handleEvent();
    }

    this->drawFrame();

    return false;
}

void Engine::handleEvent()
{
}

int32_t Engine::loadResources()
{
    const std::string filePath = "../resources/hello.png";
    if (EXIT_SUCCESS != Texture::createSurfaceFromFile(filePath, this->_image))
    {
        std::cerr << "Texture::createSurfaceFromFile() failed for file: " << filePath << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

//while (true)
//{
//    if (event.pollEvent())
//    {
//        if (event.type == TouchEvent::KEYBOARD_PRESS)
//        {
//            std::cout << "pressed key: " << (char)event.key << std::endl;
//        }
//        else if (event.type == TouchEvent::KEYBOARD_RELEASE)
//        {
//            std::cout << "released key: " << (char)event.key << std::endl;
//        }
//        else if (event.type == TouchEvent::TOUCH_PRESS)
//        {
//            std::cout << "mouse button idx pressed: " << (char)event.mouseButton << std::endl;
//        }
//        else if (event.type == TouchEvent::TOUCH_RELEASE)
//        {
//            std::cout << "mouse button idx released: " << (char)event.mouseButton << std::endl;
//        }
//        else
//        {
//            std::cout << "event position: (" << event.pos.x << ", " << event.pos.y << ")" << std::endl;
//        }
//    }
//}