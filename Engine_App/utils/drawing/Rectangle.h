#ifndef RECTANGLE_H
#define RECTANGLE_H

//C system includes

//C++ system includes
#include <cstdint>

//Thitrd-party includes

//Own includes

//Forward Declarations


class Rectangle
{
public:
	Rectangle() = default;
	Rectangle(int32_t inputX, int32_t inputY, int32_t inputW, int32_t inputH);

	int32_t x = 0;
	int32_t y = 0;
	int32_t w = 0;
	int32_t h = 0;

	//static Rectangle ZERO;
	//static Rectangle UNDEFINED;
};

#endif // !RECTANGLE_H
