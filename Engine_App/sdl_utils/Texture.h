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
struct SDL_Texture;
struct SDL_Renderer;

class Texture
{
public:
	Texture() = delete;

	static int32_t createSurfaceFromFile(const std::string& filePath, SDL_Surface*& outSurface);
	static int32_t createTextureFromFile(const std::string& filePath, SDL_Texture*& outTexture);

	static int32_t createTextureFromSurface(SDL_Surface*& inOutSurface, SDL_Texture*& outTexture);

	static void freeSurface(SDL_Surface*& outSurface);
	static void freeTexture(SDL_Texture*& outTexture);

	static void setRenderer(SDL_Renderer* renderer);
};

#endif // !TEXTURE_H
