//C system includes

//C++ system includes
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>

//Thitrd-party includes

//Own includes
#include"engine/Engine.h"
#include "sdl_utils/SDLLoader.h"

//Forward Declarations


static int32_t runApplication()
{
    Engine engine;
    if (EXIT_SUCCESS != engine.init())
    {
        std::cerr << "engine.init() failed." << std::endl;
        return EXIT_FAILURE;
    }

    engine.start();

    engine.deInit();

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