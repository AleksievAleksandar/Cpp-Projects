//Coresponding header
#include "manager_utils/drawing/Text.h"

//C system includes

//C++ system includes
#include <iostream>

//Thitrd-party includes

//Own includes
#include "manager_utils/managers/RsrcMgr.h"


Text::~Text()
{
	if (this->_isCreated && !this->_isDestroyed)
	{
		this->destroy();
	}
}

void Text::create(const std::string& text, int32_t fontId, const Color& color, const Point& pos)
{
	if (this->_isCreated)
	{
		std::cerr << "ERROR -> text with fontId: " << fontId << " was already created. Will not create it twice." << std::endl;
		return;
	}

	gRsrcMgr->createText(text, color, fontId, this->_drawParams.textId, this->_drawParams.width, this->_drawParams.height);
	this->_drawParams.pos = pos;
	this->_drawParams.widgetType = WidgetType::TEXT;

	this->_textContent = text;
	this->_color = color;
	this->_fontId = fontId;

	this->_isCreated = true;
	this->_isDestroyed = false;
}

void Text::destroy()
{
	if (!this->_isCreated)
	{
		std::cerr << "ERROR -> text was already destroyed." << std::endl;
		return;
	}
	this->_isCreated = false;
	this->_isDestroyed = true;

	Widget::reset();
}

void Text::setText(const std::string& text)
{
	if (this->_textContent != text)
	{
		this->_textContent = text;
		gRsrcMgr->reloadText(text, this->_color, this->_fontId,
			this->_drawParams.textId, this->_drawParams.width, this->_drawParams.height);
	}
}

void Text::setColor(const Color& color)
{
	if (this->_color != color)
	{
		this->_color = color;
		gRsrcMgr->reloadText(this->_textContent, this->_color, this->_fontId,
			this->_drawParams.textId, this->_drawParams.width, this->_drawParams.height);
	}
}

std::string Text::getTextContent() const
{
	return this->_textContent;
}