//Coresponding header
#include "manager_utils/drawing/Widget.h"

//C system includes

//C++ system includes
#include <iostream>

//Thitrd-party includes

//Own includes
#include "manager_utils/managers/DrawMgr.h"

void Widget::draw()
{
	if (this->_isVisible)
	{
		gDrawMgr->addDrawCmd(this->_drawParams);
	}	
}

void Widget::reset()
{
	this->_isCreated = false;
	this->_isDestroyed = true;
	this->_isVisible = true;
	this->_isAlphaModulationEnabled = false;

	this->_drawParams.reset();
}

void Widget::setFlipType(const WidgetFlip& flipType)
{
	this->_drawParams.flipType = flipType;
}

void Widget::setWidth(const int32_t width)
{
	this->_drawParams.width = width;
}

void Widget::setHeight(const int32_t height)
{
	this->_drawParams.height = height;
}

int32_t Widget::getWidth() const
{
	return this->_drawParams.width;
}

int32_t Widget::getHeight() const
{
	return this->_drawParams.height;
}

void Widget::setPossition(const Point& pos)
{
	this->_drawParams.pos = pos;
}

void Widget::setRotationCenter(const Point& rotCenter)
{
	this->_drawParams.rotationCenter = rotCenter;
}

void Widget::setPossition(const int32_t x, const int32_t y)
{
	this->_drawParams.pos.x = x;
	this->_drawParams.pos.y = y;
}

void Widget::setOpacity(int32_t opacity)
{
	if (!this->_isAlphaModulationEnabled)
	{
		std::cerr << "ERROR -> alpha modulation was not enabled for rsrcId: " << this->_drawParams.rsrcId 
				  << ". Will not change opacity." << std::endl;
		return;
	}
	this->_drawParams.opacity = opacity;
	gDrawMgr->setWidgetOpacity(this->_drawParams, opacity);
}

int32_t Widget::getOpacity() const
{
	return this->_drawParams.opacity;
}

Point Widget::getPosition() const
{
	return this->_drawParams.pos;
}

void Widget::setRotation(const double angle)
{
	this->_drawParams.rotationAngle = angle;
}

double Widget::getRotation() const
{
	return this->_drawParams.rotationAngle;
}

void Widget::rotateRight(double delta)
{
	this->_drawParams.rotationAngle += delta;

	while (this->_drawParams.rotationAngle > FULL_ROTATION)
	{
		this->_drawParams.rotationAngle -= FULL_ROTATION;
	}
}

void Widget::rotateLeft(double delta)
{
	this->_drawParams.rotationAngle -= delta;

	while (this->_drawParams.rotationAngle < 0)
	{
		this->_drawParams.rotationAngle += FULL_ROTATION;
	}
}

void Widget::activateAlphaModulation()
{
	if (this->_isAlphaModulationEnabled)
	{
		std::cerr << "ERROR -> alpha modulation was already enabled for rsrcId: " << this->_drawParams.rsrcId << std::endl;
		return;
	}
	this->_isAlphaModulationEnabled = true;
	gDrawMgr->setWidgetBlendMode(this->_drawParams, BlendMode::BLEND);
}

void Widget::deactivateAlphaModulation()
{
	if (!this->_isAlphaModulationEnabled)
	{
		std::cerr << "ERROR -> alpha modulation was originally not enabled for rsrcId: " << this->_drawParams.rsrcId << std::endl;
		return;
	}
	this->_isAlphaModulationEnabled = false;
	gDrawMgr->setWidgetBlendMode(this->_drawParams, BlendMode::NONE);
}

void Widget::show()
{
	this->_isVisible = true;
}

void Widget::hide()
{
	this->_isVisible = false;
}

void Widget::moveRight(const int32_t delta)
{
	this->_drawParams.pos.x += delta;
}

void Widget::moveLeft(const int32_t delta)
{
	this->_drawParams.pos.x -= delta;
}

void Widget::moveUp(const int32_t delta)
{
	this->_drawParams.pos.y -= delta;
}

void Widget::moveDown(const int32_t delta)
{
	this->_drawParams.pos.y += delta;
}

bool Widget::containsPoint(const Point& pos) const
{
	const Rectangle bound(this->_drawParams.pos.x,
						  this->_drawParams.pos.y,
						  this->_drawParams.width,
						  this->_drawParams.height);
	return bound.isPointInside(pos);
}