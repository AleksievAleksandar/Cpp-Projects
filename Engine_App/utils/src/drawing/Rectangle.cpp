//Coresponding header
#include "utils/drawing/Rectangle.h"

//C system includes

//C++ system includes

//Thitrd-party includes

//Own includes

//Forward Declarations


const Rectangle Rectangle::ZERO(0, 0, 0, 0);
const Rectangle Rectangle::UNDEFINED(1000, 1000, 1000, 1000);

Rectangle::Rectangle(int32_t inputX, int32_t inputY, int32_t inputW, int32_t inputH):
	x(inputX), y(inputY),
	w(inputW), h(inputH)
{}

bool Rectangle::operator==(const Rectangle & other) const
{
	return (this->x == other.x &&
		this->y == other.y &&
		this->w == other.w &&
		this->h == other.h);
}

bool Rectangle::operator!=(const Rectangle& other) const
{
	return !(*this == other);
}

bool Rectangle::isPointInside(const Point& point) const
{
	const bool isInsideX = ((this->x <= point.x) && (point.x < this->x + this->w));
	const bool isInsideY = ((this->y <= point.y) && (point.y < this->y + this->h));
	
	return (isInsideX && isInsideY);
}
