//Coresponding header
#include "manager_utils/managers/DrawMgr.h"

//C system includes

//C++ system includes
#include <iostream>

//Thitrd-party includes

//Own includes
#include "manager_utils/config/DrawMgrCfg.h"
#include "manager_utils/managers/RsrcMgr.h"


DrawMgr* gDrawMgr = nullptr;

int32_t DrawMgr::init(const DrawMgrCfg& cfg)
{
	if (EXIT_SUCCESS != this->_window.init(cfg.windowCfg))
	{
		std::cerr << "_window.init() failed." << std::endl;
		return EXIT_FAILURE;
	}

	if (EXIT_SUCCESS != this->_renderer.init(this->_window.getWindow()))
	{
		std::cerr << "_renderer.init() failed." << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void DrawMgr::deInit()
{
	this->_renderer.deInit();
	this->_window.deInit();
}

void DrawMgr::process()
{
	//empty
}

void DrawMgr::clearScreen()
{
	this->_renderer.clearScreen();
}

void DrawMgr::finishFrame()
{
	this->_renderer.finishFrame();
}

void DrawMgr::addDrawCmd(const DrawParams& drawParams)
{
	SDL_Texture* texture = getTextureInternal(drawParams);

	this->_renderer.renderTexture(texture, drawParams);
}

void DrawMgr::setWidgetBlendMode(const DrawParams& drawParams, BlendMode blendMode)
{
	SDL_Texture* texture = getTextureInternal(drawParams);
	this->_renderer.setWidgetBlendMode(texture, blendMode);
}

void DrawMgr::setWidgetOpacity(const DrawParams& drawParams, int32_t opacity)
{
	if (drawParams.widgetType == WidgetType::IMAGE)
	{
		return;
	}

	SDL_Texture* texture = getTextureInternal(drawParams);
	this->_renderer.setWidgetOpacity(texture, opacity);
}

SDL_Texture* DrawMgr::getTextureInternal(const DrawParams& drawParams) const
{
	switch (drawParams.widgetType)
	{
	case WidgetType::IMAGE:
		return gRsrcMgr->getImageTexture(drawParams.rsrcId);
		break;

	case WidgetType::TEXT:
		return gRsrcMgr->getTextTexture(drawParams.textId);
		break;

	default:
		std::cerr << "ERROR -> received unsupported WidgetType"
			<< static_cast<int32_t>(drawParams.widgetType)
			<< " for rsrcId: " << drawParams.rsrcId
			<< std::endl;
		break;
	}

	return nullptr;
}
