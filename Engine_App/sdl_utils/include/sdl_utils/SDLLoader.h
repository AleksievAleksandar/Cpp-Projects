#ifndef SDL_LOADER_H
#define SDL_LOADER_H

//C system includes

//C++ system includes
#include <cstdint>

//Thitrd-party includes

//Own includes

//Forward Declarations


class SDLLoader
{
public:
	SDLLoader() = delete;
	~SDLLoader() = default;

	static int32_t init();
	static void deinit();
};

#endif