//Coresponding header
#include "utils/drawing/Point.h"

//C system includes

//C++ system includes

//Thitrd-party includes

//Own includes

//Forward Declarations


const Point Point::ZERO(0, 0);
const Point Point::UNDEFINED(1000, 1000);

Point::Point(int32_t inputX, int32_t inputY) : 
	x(inputX), y(inputY)
{}

bool Point::operator==(const Point & other) const
{
	return ((this->x == other.x) && (this->y == other.y));
}

bool Point::operator!=(const Point& other) const
{
	return !(*this == other);
}


