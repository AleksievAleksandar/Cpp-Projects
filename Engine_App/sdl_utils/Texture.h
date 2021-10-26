#ifndef TEXTURE_H
#define TEXTURE_H

//C system includes

//C++ system includes
#include <cstdint>
#include <string>

//Thitrd-party includes

//Own includes
#include "utils/drawing/DrawParams.h"

//Forward Declarations
struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;
typedef struct _TTF_Font TTF_Font;
struct Color;

class Texture
{
public:
	Texture() = delete;

	static int32_t createSurfaceFromFile(const std::string& filePath, SDL_Surface*& outSurface);
	static int32_t createTextureFromFile(const std::string& filePath, SDL_Texture*& outTexture);
	static int32_t createTextureFromSurface(SDL_Surface*& inOutSurface, SDL_Texture*& outTexture);

	static int32_t createTextureFromText(const std::string& text, const Color& color, TTF_Font* font,
											SDL_Texture*& outTexture, int32_t& outTextWidth, int32_t& outTextHeight);

	static void freeSurface(SDL_Surface*& outSurface);
	static void freeTexture(SDL_Texture*& outTexture);

	static void setRenderer(SDL_Renderer* renderer);

	static int32_t setBlendModeTexture(SDL_Texture* texture, BlendMode blendMode);
	static int32_t setAlphaTexture(SDL_Texture* texture, int32_t alpha);
};

#endif // !TEXTURE_H
