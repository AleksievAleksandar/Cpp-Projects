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

static const Frames EMPTY_FRAMES { Rectangle::ZERO };

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

const Frames& ImageContainer::getImageFrame(int32_t rsrcId) const
{
	auto it = this->_textureFrames.find(rsrcId);
	if (it == this->_textureFrames.end())
	{
		std::cerr << "ERROR. Invalid rsrcId: " << rsrcId << " requested. Returning ZERO rectangle." << std::endl;
		return EMPTY_FRAMES;
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

	this->_textureFrames[rsrcId] = resCfg.frames;

	return EXIT_SUCCESS;
}
