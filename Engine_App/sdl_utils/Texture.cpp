//Coresponding header
#include "Texture.h"

//C system includes

//C++ system includes
#include <iostream>

//Thitrd-party includes
#include <SDL_surface.h>
#include <SDL_image.h>
#include <SDL_render.h>

//Own includes

//Forward Declarations

namespace 
{
    SDL_Renderer* globalRenderer = nullptr;
}

int32_t Texture::createSurfaceFromFile(const std::string& filePath, SDL_Surface*& outSurface)
{
    outSurface = IMG_Load(filePath.c_str());

    if (outSurface == nullptr)
    {
        std::cerr << "IMG_Load() failed. Reason: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

	return EXIT_SUCCESS;
}

void Texture::freeSurface(SDL_Surface*& outSurface)
{
    if (outSurface != nullptr)
    {
        SDL_FreeSurface(outSurface);
        outSurface = nullptr;
    }
}

int32_t Texture::createTextureFromFile(const std::string& filePath, SDL_Texture*& outTexture)
{
    SDL_Surface* tempSurface = nullptr;
    if (EXIT_SUCCESS != createSurfaceFromFile(filePath, tempSurface))
    {
        std::cerr << "createSurfaceFromFile() failed for filePath: " << filePath << std::endl;
        return EXIT_FAILURE;
    }

    if (EXIT_SUCCESS != createTextureFromSurface(tempSurface, outTexture))
    {
        std::cerr << "createTextureFromSurface() failed for filePath: " << filePath << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int32_t Texture::createTextureFromSurface(SDL_Surface*& inOutSurface, SDL_Texture*& outTexture)
{
    outTexture = SDL_CreateTextureFromSurface(globalRenderer, inOutSurface);

    if (outTexture == nullptr)
    {
        std::cerr << "SDL_CreateTextureFromSurface() failed. Reason: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    freeSurface(inOutSurface);

    return EXIT_SUCCESS;
}

void Texture::freeTexture(SDL_Texture*& outTexture)
{
    if (outTexture != nullptr)
    {
        SDL_DestroyTexture(outTexture);
        outTexture = nullptr;
    }
}

void Texture::setRenderer(SDL_Renderer* renderer)
{
    globalRenderer = renderer;
}

int32_t Texture::setBlendModeTexture(SDL_Texture* texture, BlendMode blendMode)
{
    if (EXIT_SUCCESS != SDL_SetTextureBlendMode(texture, static_cast<SDL_BlendMode>(blendMode)))
    {
        std::cerr << "SDL_SetTextureBlendMode() failed. Reason: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int32_t Texture::setAlphaTexture(SDL_Texture* texture, int32_t alpha)
{
    if (ZERO_OPACITY > alpha || alpha > FULL_OPACITY)
    {
        std::cerr << "Error, invalid alpha value: " << alpha << " provided." << std::endl;
        return EXIT_FAILURE;
    }

    if (EXIT_SUCCESS != SDL_SetTextureAlphaMod(texture, static_cast<uint8_t>(alpha)))
    {
        std::cerr << "SDL_SetTextureAlphaMod() failed. Reason: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
