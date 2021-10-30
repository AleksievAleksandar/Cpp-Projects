//Coresponding header
#include "game/Game.h"

//C system includes

//C++ system includes
#include <iostream>

//Thitrd-party includes

//Own includes
#include "sdl_utils/InputEvent.h"
//TODO remove me
#include "sdl_utils/containers/ImageContainer.h"
#include "sdl_utils/containers/TextContainer.h"
#include "utils/drawing/Color.h"

static int32_t gFontId;

int32_t Game::init(const GameCfg& cfg, const ImageContainer* imgContainerInterface, TextContainer* textContainerInterface)
{
	if (nullptr == imgContainerInterface)
	{
		std::cerr << "ERROR, nullptr provided for imgContainerInterface." << std::endl;
		return EXIT_FAILURE;
	}
	this->_imageContainer = imgContainerInterface;

	gFontId = cfg.textFontId;
	if (nullptr == textContainerInterface)
	{
		std::cerr << "ERROR, nullptr provided for textContainerInterface." << std::endl;
		return EXIT_FAILURE;
	}
	this->_textContainer = textContainerInterface;

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

	this->_textContainer->createText("Hello, C++ dudes", Colors::GREEN, cfg.textFontId, 
								this->helloText.textId, this->helloText.width, this->helloText.height);
	this->helloText.pos = Point::ZERO;
	this->helloText.widgetType = WidgetType::TEXT;

	this->_textContainer->createText("Press M to hide", Colors::GREEN, cfg.textFontId,
		this->pressText.textId, this->pressText.width, this->pressText.height);
	this->pressText.pos = Point::ZERO;
	this->pressText.pos.x += 100;
	this->pressText.pos.y += 100;
	this->pressText.widgetType = WidgetType::TEXT;

	this->_textContainer->createText("Press N to show", Colors::PURPLE, cfg.textFontId,
		this->hideText.textId, this->hideText.width, this->hideText.height);
	this->hideText.pos = Point::ZERO;
	this->hideText.pos.x += 200;
	this->hideText.pos.y += 200;
	this->hideText.widgetType = WidgetType::TEXT;
	
	return EXIT_SUCCESS;
}

void Game::deInit()
{
	this->_textContainer->unloadText(this->helloText.textId);
}

void Game::draw(std::vector<DrawParams>& outImages)
{
	//outImages.push_back(this->pressKeysImg);
	//outImages.push_back(this->layer2Img);
	outImages.push_back(this->helloText);

	if (this->isPressTextHidden)
	{
		outImages.push_back(this->hideText);
	}
	else
	{
		outImages.push_back(this->pressText);
	}
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

	case Keyboard::KEY_B:
		this->_textContainer->reloadText("Kak ste, kolegi?", Colors::GREEN, gFontId,
			this->helloText.textId, this->helloText.width, this->helloText.height);
		break;

	case Keyboard::KEY_M:
		this->isPressTextHidden = true;
		break;

	case Keyboard::KEY_N:
		this->isPressTextHidden = false;
		break;

	default:
		break;
	}
}
