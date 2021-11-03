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
	const Frames& frames = gRsrcMgr->getImageFrame(rsrcId);
	this->_maxFrames = static_cast<int32_t>(frames.size());

	const auto& firstFrame = frames.front();
	this->_drawParams.frameRect = firstFrame;

	this->_drawParams.rsrcId = rsrcId;
	this->_drawParams.width = this->_drawParams.frameRect.w;
	this->_drawParams.height = this->_drawParams.frameRect.h;
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

void Image::setFrame(int32_t frameIdx)
{
	if (0 > frameIdx || frameIdx >= this->_maxFrames)
	{
		std::cerr << "ERROR -> trying to set invalid frameID: " << frameIdx 
				  << " for Image with rsrcId: " << this->_drawParams.rsrcId << std::endl;
		return;
	}

	const Frames& frames = gRsrcMgr->getImageFrame(this->_drawParams.rsrcId);
	this->_drawParams.frameRect = frames[frameIdx];

	this->_currFrame = frameIdx;
}

void Image::setNextFrame()
{
	this->_currFrame++;

	if (this->_currFrame >= this->_maxFrames)
	{
		this->_currFrame = 0;
	}

	const Frames& frames = gRsrcMgr->getImageFrame(this->_drawParams.rsrcId);
	this->_drawParams.frameRect = frames[this->_currFrame];
}

void Image::setPrevFrame()
{
	this->_currFrame--;

	if (this->_currFrame < 0)
	{
		this->_currFrame = this->_maxFrames - 1;;
	}

	const Frames& frames = gRsrcMgr->getImageFrame(this->_drawParams.rsrcId);
	this->_drawParams.frameRect = frames[this->_currFrame];
}

int32_t Image::getFrame() const
{
	return this->_currFrame;
}