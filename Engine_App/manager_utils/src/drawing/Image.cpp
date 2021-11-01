//Coresponding header
#include "manager_utils/drawing/Image.h"

//C system includes

//C++ system includes
#include <iostream>

//Thitrd-party includes

//Own includes
#include "manager_utils/managers/RsrcMgr.h"

Image::~Image()
{
	if (this->_isCreated && !this->_isDestroyed)
	{
		this->destroy();
	}
}

void Image::create(const int32_t rsrcId, const Point& pos)
{
	if (this->_isCreated)
	{
		std::cerr << "ERROR -> image with rsrcId: " << this->_drawParams.rsrcId << " was already created. Will not create it twice." << std::endl;
		return;
	}
	const Rectangle rect = gRsrcMgr->getImageFrame(rsrcId);
	this->_drawParams.rsrcId = rsrcId;
	this->_drawParams.width = rect.w;
	this->_drawParams.height = rect.h;
	this->_drawParams.pos = pos;
	this->_drawParams.widgetType = WidgetType::IMAGE;

	this->_isCreated = true;
	this->_isDestroyed = false;
}

void Image::destroy()
{
	if (!this->_isCreated)
	{
		std::cerr << "ERROR -> image was already destroyed." << std::endl;
		return;
	}
	this->_isCreated = false;
	this->_isDestroyed = true;

	Widget::reset();
}