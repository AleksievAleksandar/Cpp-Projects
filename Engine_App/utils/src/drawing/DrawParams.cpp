//Coresponding header
#include "utils/drawing/DrawParams.h"

//C system includes

//C++ system includes
#include <iostream>

//Thitrd-party includes

//Own includes

void DrawParams::reset()
{
	this->frameRect = Rectangle::ZERO;
	this->pos = Point::UNDEFINED;
	this->width = 0;
	this->height = 0;
	this->opacity = FULL_OPACITY;
	this->rsrcId = INVALID_RSRC_ID;
	this->widgetType = WidgetType::UNKNOWN;
	this->flipType = WidgetFlip::NONE;
}