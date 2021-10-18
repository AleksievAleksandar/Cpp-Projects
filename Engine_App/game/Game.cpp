//Coresponding header
#include "Game.h"

//C system includes

//C++ system includes
#include <iostream>

//Thitrd-party includes

//Own includes
#include "sdl_utils/InputEvent.h"
#include "sdl_utils/Texture.h"


int32_t Game::loadResources(const std::unordered_map<GameImages, std::string>& resources)
{
	for (const auto& pair : resources)
	{
		if (EXIT_SUCCESS != Texture::createTextureFromFile(pair.second, this->_imageSurfaces[pair.first]))
		{
			std::cerr << "Texture::createSurfaceFromFile() failed for file: " << pair.second << std::endl;
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}

int32_t Game::init(const GameCfg& cfg)
{
	if (EXIT_SUCCESS != loadResources(cfg.imgPaths))
	{
		std::cerr << "loadResources() failed." << std::endl;
		return EXIT_FAILURE;
	}

	this->_currChosenImage = this->_imageSurfaces[PRESS_KEYS];

	return EXIT_SUCCESS;
}

void Game::deInit()
{
	for (int32_t i = 0; i < COUNT; ++i)
	{
		Texture::freeTexture(this->_imageSurfaces[i]);
	}
}

void Game::draw(std::vector<SDL_Texture*>& outImages)
{
	outImages.push_back(this->_currChosenImage);
	//outImages.push_back(this->_imageSurfaces[LAYER_2]);
}

void Game::handleEvent(const InputEvent& event)
{
	if (event.type == TouchEvent::KEYBOARD_RELEASE)
	{
		this->_currChosenImage = this->_imageSurfaces[PRESS_KEYS];
		return;
	}

	if (event.type != TouchEvent::KEYBOARD_PRESS)
	{
		return;
	}

	switch (event.key)
	{
	case Keyboard::KEY_UP:
		this->_currChosenImage = this->_imageSurfaces[UP];
		break;

	case Keyboard::KEY_DOWN:
		this->_currChosenImage = this->_imageSurfaces[DOWN];
		break;

	case Keyboard::KEY_LEFT:
		this->_currChosenImage = this->_imageSurfaces[LEFT];
		break;

	case Keyboard::KEY_RIGHT:
		this->_currChosenImage = this->_imageSurfaces[RIGHT];
		break;

	default:
		break;
	}
}
