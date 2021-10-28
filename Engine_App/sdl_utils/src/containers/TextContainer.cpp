//Coresponding header
#include "sdl_utils/containers/TextContainer.h"

//C system includes

//C++ system includes
#include <iostream>

//Thitrd-party includes
#include <SDL_ttf.h>

//Own includes
#include "sdl_utils/Texture.h"

int32_t TextContainer::init(const TextContainerCfg& cfg)
{
	TTF_Font* currFont = nullptr;

	for (const auto& pair : cfg.fontConfigs)
	{
		const auto key = pair.first;
		const FontCfg& fontCfg = pair.second;
		currFont = TTF_OpenFont(fontCfg.location.c_str(), fontCfg.fontSize);
		if (currFont == nullptr)
		{
			std::cerr << "ERROR -> TTF_OpenFont() failed for font location: " << fontCfg.location << " .Reason: " << SDL_GetError() << std::endl;
			return EXIT_FAILURE;
		}

		this->_fonts[key] = currFont;
	}

	return EXIT_SUCCESS;
}

void TextContainer::deInit()
{
	for (auto& pair : this->_fonts)
	{
		TTF_CloseFont(pair.second);
	}
}

void TextContainer::createText(const std::string& text, const Color& color, int32_t fontId, int32_t& outTextId, int32_t& outTextWidth, int32_t& outTextHeight)
{
	auto it = this->_fonts.find(fontId);
	if (it == this->_fonts.end())
	{
		std::cerr << "ERROR -> fontId: " << fontId << " could not be found. Will not create text: " << text << std::endl;
		return;
	}

	TTF_Font* font = it->second;
	SDL_Texture* textTexture = nullptr;
	if (EXIT_SUCCESS != Texture::createTextureFromText(text, color, font, textTexture, outTextWidth, outTextHeight))
	{
		std::cerr << "ERROR -> Texture::createTextureFromText failed for text: " << text << std::endl;
		return;
	}

	this->occupyFreeSlotIndex(outTextId, textTexture);
}

void TextContainer::reloadText(const std::string& text, const Color& color, int32_t fontId, int32_t textId, int32_t& outTextWidth, int32_t& outTextHeight)
{
	auto it = this->_fonts.find(fontId);
	if (it == this->_fonts.end())
	{
		std::cerr << "ERROR -> fontId: " << fontId << "could not be found. Will not reload text: " << text << std::endl;
		return;
	}

	freeSlotIndex(textId);

	TTF_Font* font = it->second;
	SDL_Texture* textTexture = nullptr;
	if (EXIT_SUCCESS != Texture::createTextureFromText(text, color, font, textTexture, outTextWidth, outTextHeight))
	{
		std::cerr << "ERROR -> Texture::createTextureFromText() failed for text: " << text << std::endl;
		return;
	}

	this->_textures[textId] = textTexture;
}

void TextContainer::unloadText(int32_t textId)
{
	if (0 > textId || textId >= static_cast<int32_t>(this->_textures.size()))
	{
		std::cerr << "ERROR -> trying to unload non-existing textId: " << textId << std::endl;
		return;
	}

	freeSlotIndex(textId);
}

SDL_Texture* TextContainer::getTextTexture(int32_t textId) const
{
	if (0 > textId || textId >= static_cast<int32_t>(this->_textures.size()))
	{
		std::cerr << "ERROR -> trying to get non-existing textId: " << textId << std::endl;
		return nullptr;
	}
	return this->_textures[textId];
}

void TextContainer::occupyFreeSlotIndex(int32_t& outIdx, SDL_Texture* texture)
{
	const int32_t size = static_cast<int32_t>(this->_textures.size());

	for (int32_t i = 0; i < size; ++i)
	{
		if (this->_textures[i] == nullptr)
		{
			outIdx = i;
			this->_textures[i] = texture;
			return;
		}
	}
	this->_textures.push_back(texture);
	outIdx = size;
}

void TextContainer::freeSlotIndex(int32_t index)
{
	Texture::freeTexture(this->_textures[index]);
}
