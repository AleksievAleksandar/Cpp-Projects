//Coresponding header
#include "sdl_utils/Renderer.h"

//C system includes

//C++ system includes
#include <iostream>

//Thitrd-party includes
#include <SDL_render.h>
#include <SDL_hints.h>

//Own includes
#include "sdl_utils/Texture.h"


int32_t Renderer::init(SDL_Window* window)
{
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		std::cerr << "Warning: Linear texture filtering not enabled! "
			"SDL_SetHint() failed. SDL Error: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	constexpr auto unspecifiedDriverId = -1;
	this->_sdlRenderer = SDL_CreateRenderer(window, unspecifiedDriverId, SDL_RENDERER_ACCELERATED);

	if (this->_sdlRenderer == nullptr)
	{
		std::cerr << "SDL_CreateRenderer() failed. Reason: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	if (EXIT_SUCCESS != SDL_SetRenderDrawColor(this->_sdlRenderer, 0, 0, 255, SDL_ALPHA_OPAQUE))
	{
		std::cerr << "SDL_SetRenderDrawColor() failed. Reason: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	Texture::setRenderer(this->_sdlRenderer);

	return EXIT_SUCCESS;
}

void Renderer::deInit()
{
	if (this->_sdlRenderer != nullptr)
	{
		SDL_DestroyRenderer(this->_sdlRenderer);
		this->_sdlRenderer = nullptr;
	}	
}

void Renderer::clearScreen()
{
	if (EXIT_SUCCESS != SDL_RenderClear(this->_sdlRenderer))
	{
		std::cerr << "SDL_RenderClear() failed. Reason: " << SDL_GetError() << std::endl;
	}
}

void Renderer::finishFrame()
{
	SDL_RenderPresent(this->_sdlRenderer);
}

void Renderer::renderTexture(SDL_Texture* texture, const DrawParams& drawParams)
{
	switch (drawParams.widgetType)
	{
	case WidgetType::IMAGE:
		this->drawImage(drawParams, texture);
		break;

	case WidgetType::TEXT:
		this->drawText(drawParams, texture);
		break;

	default:
		std::cerr << "ERROR -> received unsupported WidgetType" 
				  << static_cast<int32_t>(drawParams.widgetType) 
				  << " for rsrcId: " << drawParams.rsrcId 
				  << std::endl;
		break;
	}
}

void Renderer::setWidgetBlendMode(SDL_Texture* texture, BlendMode blendMode)
{
	//temporary enable alpha blending for all existing textures
	if (EXIT_SUCCESS != Texture::setBlendModeTexture(texture, blendMode))
	{
		std::cerr << "Texture::setBlendModeTexture() failed." << std::endl;
	}
}

void Renderer::setWidgetOpacity(SDL_Texture* texture, int32_t opacity)
{
	if (EXIT_SUCCESS != Texture::setAlphaTexture(texture, opacity))
	{
		std::cerr << "Texture::setAlphaTexture() failed." << std::endl;
	}
}

void Renderer::drawImage(const DrawParams& drawParams, SDL_Texture* texture)
{
	const SDL_Rect destRect = { .x = drawParams.pos.x, .y = drawParams.pos.y, .w = drawParams.width, .h = drawParams.height };

	int32_t errorCode = EXIT_SUCCESS;
	if (FULL_OPACITY == drawParams.opacity)
	{
		errorCode = SDL_RenderCopy(this->_sdlRenderer, texture, nullptr, &destRect);
	}
	else
	{
		if (EXIT_SUCCESS != Texture::setAlphaTexture(texture, drawParams.opacity))
		{
			std::cerr << "Texture::setAlphaTexture() failed for rsrcId: " << drawParams.rsrcId << std::endl;
		}
		errorCode = SDL_RenderCopy(this->_sdlRenderer, texture, nullptr, &destRect);
		if (EXIT_SUCCESS != Texture::setAlphaTexture(texture, FULL_OPACITY))
		{
			std::cerr << "Texture::setAlphaTexture() failed for rsrcId: " << FULL_OPACITY << std::endl;
		}
	}

	if (EXIT_SUCCESS != errorCode)
	{
		std::cerr << "SDL_RenderCopy() failed for rsrcId: " << drawParams.rsrcId << ". Reason: " << SDL_GetError() << std::endl;
	}
}

void Renderer::drawText(const DrawParams& drawParams, SDL_Texture* texture)
{
	const SDL_Rect destRect = { .x = drawParams.pos.x, .y = drawParams.pos.y, .w = drawParams.width, .h = drawParams.height };

	const int32_t errorCode = SDL_RenderCopy(this->_sdlRenderer, texture, nullptr, &destRect);
	if (EXIT_SUCCESS != errorCode)
	{
		std::cerr << "SDL_RenderCopy() failed for rsrcId: " << drawParams.rsrcId << ". Reason: " << SDL_GetError() << std::endl;
	}
}
