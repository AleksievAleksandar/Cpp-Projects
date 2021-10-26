//Coresponding header
#include "Game.h"

//C system includes

//C++ system includes
#include <iostream>

//Thitrd-party includes

//Own includes
#include "sdl_utils/InputEvent.h"
#include "sdl_utils/containers/ImageContainer.h"


int32_t Game::init(const GameCfg& cfg, const ImageContainer* imgContainerInterface)
{
	if (nullptr == imgContainerInterface)
	{
		std::cerr << "ERROR, nullptr provided for imgContainerInterface." << std::endl;
		return EXIT_FAILURE;
	}

	this->_imageContainer = imgContainerInterface;

	this->layer2Img.rsrcId = cfg.layer2RsrcId;
	Rectangle rect = this->_imageContainer->getImageFrame(layer2Img.rsrcId);
	this->layer2Img.width = rect.w;
	this->layer2Img.height = rect.h;
	this->layer2Img.pos = Point::ZERO;
	this->layer2Img.widgetType = WidgetType::IMAGE;

	this->pressKeysImg.rsrcId = cfg.pressKeysRsrcId;
	rect = this->_imageContainer->getImageFrame(pressKeysImg.rsrcId);
	this->pressKeysImg.width = rect.w;
	this->pressKeysImg.height = rect.h;
	this->pressKeysImg.pos = Point::ZERO;
	this->pressKeysImg.widgetType = WidgetType::IMAGE;

	return EXIT_SUCCESS;
}

void Game::deInit()
{

}

void Game::draw(std::vector<DrawParams>& outImages)
{
	outImages.push_back(this->pressKeysImg);
	outImages.push_back(this->layer2Img);
}

void Game::handleEvent(const InputEvent& event)
{
	if (event.type != TouchEvent::KEYBOARD_RELEASE)
	{
		return;
	}

	switch (event.key)
	{
	case Keyboard::KEY_UP:
		this->pressKeysImg.pos.y -= 10;
		break;

	case Keyboard::KEY_DOWN:
		this->pressKeysImg.pos.y += 10;
		break;

	case Keyboard::KEY_LEFT:
		this->pressKeysImg.pos.x -= 10;
		break;

	case Keyboard::KEY_RIGHT:
		this->pressKeysImg.pos.x += 10;
		break;

	case Keyboard::KEY_Q:
		this->pressKeysImg.width -= 10;
		break;

	case Keyboard::KEY_W:
		this->pressKeysImg.width += 10;
		break;

	case Keyboard::KEY_E:
		this->pressKeysImg.height -= 10;
		break;

	case Keyboard::KEY_R:
		this->pressKeysImg.height += 10;
		break;

	case Keyboard::KEY_T:
		this->pressKeysImg.opacity -= 10;
		break;

	case Keyboard::KEY_Y:
		this->pressKeysImg.opacity += 10;
		break;

	default:
		break;
	}
}
