//C system includes

//C++ system includes
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>

//Thitrd-party includes
#include <SDL.h>

//Own includes
#include "sdl_utils/SDLLoader.h"

//Forward Declarations



static void draw(SDL_Window* window, SDL_Surface* screenSurface, SDL_Surface* image)
{
    SDL_BlitSurface(image, nullptr, screenSurface, nullptr);
    if(EXIT_SUCCESS != SDL_UpdateWindowSurface(window))
    {
        std::cerr << "SDL_LoadBMP() failed. Reason: " << SDL_GetError() << std::endl;
    }

    SDL_Delay(3000);
}

static int32_t loadResources(SDL_Surface*& outImage)
{
    const std::string filePath = "../resources/hello.bmp";
    outImage = SDL_LoadBMP(filePath.c_str());

    if(outImage == nullptr)
    {
        std::cerr << "SDL_LoadBMP() failed. Reason: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

static int32_t init(SDL_Window*& outWindow, SDL_Surface*& outScreenSurface, SDL_Surface*& outImage)
{
    const std::string windowName = "Hello, World!";
    const int32_t windowX = SDL_WINDOWPOS_UNDEFINED;
    const int32_t windowY = SDL_WINDOWPOS_UNDEFINED;
    const int32_t windowWidth = 640;
    const int32_t windowHeight = 480;

    outWindow = SDL_CreateWindow(windowName.c_str(), windowX, windowY, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    if(nullptr == outWindow)
    {
        std::cerr << "SDL_CreateWindow() failed. Reason: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    outScreenSurface = SDL_GetWindowSurface(outWindow);
    if(nullptr == outScreenSurface)
    {
        std::cerr << "SDL_GetWindowSurface() failed. Reason: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }


    if(EXIT_SUCCESS != loadResources(outImage))
    {
        std::cerr << "loadResources() failed." << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

static void deInit(SDL_Window*& outWindow, SDL_Surface*& outImage)
{
    SDL_FreeSurface(outImage);
    outImage = nullptr;

    if(outWindow != nullptr)
    {
        SDL_DestroyWindow(outWindow);
        outWindow = nullptr;
    }
}

static int32_t runApplication()
{
    SDL_Window* window = nullptr;
    SDL_Surface* screenSurface = nullptr;
    SDL_Surface* image = nullptr;

    if (EXIT_SUCCESS != init(window, screenSurface, image))
    {
        std::cerr << "init() failed." << std::endl;
        return EXIT_FAILURE;
    }

    draw(window, screenSurface, image);

    deInit(window, image);

    return EXIT_SUCCESS;
}

int32_t main([[maybe_unused]] int32_t argc, [[maybe_unused]] char* argv[])
{
    if (EXIT_SUCCESS != SDLLoader::init())
    {
        std::cerr << "SDLLoader::init() failed." << std::endl;
        return EXIT_FAILURE;
    }

    if (EXIT_SUCCESS != runApplication())
    {
        std::cerr << "runApplication() failed." << std::endl;
        return EXIT_FAILURE;
    }

    SDLLoader::deinit();

    return EXIT_SUCCESS;
} 
