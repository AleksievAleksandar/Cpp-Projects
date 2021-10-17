#ifndef TEXTURE_H
#define TEXTURE_H

//C system includes

//C++ system includes
#include <cstdint>
#include <string>

//Thitrd-party includes

//Own includes

//Forward Declarations
struct SDL_Surface;

class Texture
{
public:
	Texture() = delete;

	static int32_t createSurfaceFromFile(const std::string& filePath, SDL_Surface*& outSurface);
	static void freeSurface(SDL_Surface*& outSurface);
};

#endif // !TEXTURE_H
