//Coresponding header
#include "sdl_utils/containers/ImageContainer.h"

//C system includes

//C++ system includes
#include <cstring>
#include <iostream>

//Thitrd-party includes

//Own includes
#include "sdl_utils/Texture.h"

//Forward Declarations


int32_t ImageContainer::init(const ImageContainerCfg& imageContCfg)
{
	for (const auto& pair : imageContCfg.imageConfigs)
	{
		if (EXIT_SUCCESS != this->loadSingleResource(pair.second, pair.first))
		{
			std::cerr << "Texture::loadSingleResource() failed for file: " << pair.second.location << std::endl;
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}

void ImageContainer::deInit()
{
	for (auto& pair : this->_textures)
	{
		Texture::freeTexture(pair.second);
	}
}

SDL_Texture* ImageContainer::getImageTexture(int32_t rsrcId) const
{
	auto it = this->_textures.find(rsrcId);
	if (it == this->_textures.end())
	{
		std::cerr << "ERROR. Invalid rsrcId: " << rsrcId << " requested." << std::endl;
		return nullptr;
	}
	return it->second;
}

Rectangle ImageContainer::getImageFrame(int32_t rsrcId) const
{
	auto it = this->_textureFrames.find(rsrcId);
	if (it == this->_textureFrames.end())
	{
		std::cerr << "ERROR. Invalid rsrcId: " << rsrcId << " requested. Returning ZERO rectangle." << std::endl;
		return Rectangle::ZERO;
	}
	return it->second;
}

int32_t ImageContainer::loadSingleResource(const ImageCfg& resCfg, const int32_t rsrcId)
{
	SDL_Texture* texture = nullptr;
	if (EXIT_SUCCESS != Texture::createTextureFromFile(resCfg.location, texture))
	{
		std::cerr << "Texture::createSurfaceFromFile() failed for file: " << resCfg.location << std::endl;
		return EXIT_FAILURE;
	}


	this->_textures[rsrcId] = texture;

	Rectangle& rec = this->_textureFrames[rsrcId];
	rec.x = 0;
	rec.y = 0;
	rec.w = resCfg.width;
	rec.h = resCfg.height;

	return EXIT_SUCCESS;
}
