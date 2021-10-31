//Coresponding header
#include "game/Game.h"

//C system includes

//C++ system includes
#include <iostream>

//Thitrd-party includes

//Own includes
#include "sdl_utils/InputEvent.h"
#include "utils/drawing/Color.h"
#include "manager_utils/managers/DrawMgr.h"
#include "manager_utils/managers/RsrcMgr.h"

static int32_t gFontId;

int32_t Game::init(const GameCfg& cfg)
{
	this->layer2Img.rsrcId = cfg.layer2RsrcId;
	Rectangle rect = gRsrcMgr->getImageFrame(layer2Img.rsrcId);
	this->layer2Img.width = rect.w;
	this->layer2Img.height = rect.h;
	this->layer2Img.pos = Point::ZERO;
	this->layer2Img.widgetType = WidgetType::IMAGE;

	this->pressKeysImg.rsrcId = cfg.pressKeysRsrcId;
	rect = gRsrcMgr->getImageFrame(pressKeysImg.rsrcId);
	this->pressKeysImg.width = rect.w;
	this->pressKeysImg.height = rect.h;
	this->pressKeysImg.pos = Point::ZERO;
	this->pressKeysImg.widgetType = WidgetType::IMAGE;

	gRsrcMgr->createText("Hello, C++ dudes", Colors::GREEN, cfg.textFontId,
								this->helloText.textId, this->helloText.width, this->helloText.height);
	this->helloText.pos = Point::ZERO;
	this->helloText.widgetType = WidgetType::TEXT;

	gRsrcMgr->createText("Press M to hide", Colors::GREEN, cfg.textFontId,
		this->pressText.textId, this->pressText.width, this->pressText.height);
	this->pressText.pos = Point::ZERO;
	this->pressText.pos.x += 100;
	this->pressText.pos.y += 100;
	this->pressText.widgetType = WidgetType::TEXT;

	gRsrcMgr->createText("Press N to show", Colors::PURPLE, cfg.textFontId,
		this->hideText.textId, this->hideText.width, this->hideText.height);
	this->hideText.pos = Point::ZERO;
	this->hideText.pos.x += 200;
	this->hideText.pos.y += 200;
	this->hideText.widgetType = WidgetType::TEXT;
	
	return EXIT_SUCCESS;
}

void Game::deInit()
{
	gRsrcMgr->unloadText(this->helloText.textId);
}

void Game::draw()
{
	gDrawMgr->addDrawCmd(this->helloText);

	if (this->isPressTextHidden)
	{
		gDrawMgr->addDrawCmd(this->hideText);
	}
	else
	{
		gDrawMgr->addDrawCmd(this->pressText);
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
		gRsrcMgr->reloadText("Kak ste, kolegi?", Colors::GREEN, gFontId,
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
