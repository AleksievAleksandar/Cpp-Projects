#ifndef HERO_H
#define HERO_H

//C system includes

//C++ system includes
#include <cstdint>

//Thitrd-party includes

//Own includes
#include "manager_utils/drawing/Image.h"

//Forward Declarations
struct InputEvent;


class Hero
{
public:
	int32_t init(const int32_t heroRsrcId);
	void deInit();
	void draw();
	void handleEvent(const InputEvent& event);

private:
	Image _heroImg;
};

#endif // !HERO_H
