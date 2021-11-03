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

	void setFrame(int32_t frameIdx);
	void setNextFrame();
	void setPrevFrame();
	int32_t getFrame() const;

private:
	int32_t _currFrame{ 0 };
	int32_t _maxFrames{ 0 };
	//bool _isDestroyed = false;

};

#endif // !IMAGE_H
