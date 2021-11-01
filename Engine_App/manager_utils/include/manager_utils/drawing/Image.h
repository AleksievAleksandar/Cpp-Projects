#ifndef IMAGE_H
#define IMAGE_H

//C system includes

//C++ system includes
#include <cstdint>

//Thitrd-party includes

//Own includes
#include "manager_utils/drawing/Widget.h"

//Forward Declarations


class Image : public Widget 
{
public:
	~Image();

	void create(const int32_t rsrcId, const Point& pos = Point::ZERO);
	void destroy();
};

#endif // !IMAGE_H
