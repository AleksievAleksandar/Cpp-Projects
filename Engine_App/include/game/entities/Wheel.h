#ifndef WHEEL_H
#define WHEEL_H

//C system includes

//C++ system includes
#include <cstdint>

//Thitrd-party includes

//Own includes
#include "manager_utils/drawing/Image.h"

//Forward Declarations
struct InputEvent;


class Wheel
{
public:
	int32_t init(const int32_t wheelRsrcId);
	void draw();
	void handleEvent(const InputEvent& event);

private:
	Image _wheelImg;
};

#endif // !WHEEL_H

