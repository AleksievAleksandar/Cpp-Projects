#ifndef WIDGET_H
#define WIDGET_H

//C system includes

//C++ system includes
#include <cstdint>

//Thitrd-party includes

//Own includes
#include "utils/drawing/DrawParams.h"

//Forward Declarations


class Widget 
{
public:
	void draw();
	void reset();

	void setFlipType(const WidgetFlip& flipType);

	void setWidth(const int32_t width);
	int32_t getWidth() const;

	void setRotationCenter(const Point& rotCenter);

	void setHeight(const int32_t height);
	int32_t getHeight() const;

	void setPossition(const Point& pos);
	void setPossition(const int32_t x, const int32_t y);
	Point getPosition() const;

	void setOpacity(int32_t opacity);
	int32_t getOpacity() const;

	void setRotation(const double angle);
	double getRotation() const;

	void rotateRight(double delta);
	void rotateLeft(double delta);

	void activateAlphaModulation();
	void deactivateAlphaModulation();

	void show();
	void hide();

	void moveRight(const int32_t delta);
	void moveLeft(const int32_t delta);
	void moveUp(const int32_t delta);
	void moveDown(const int32_t delta);

protected:
	DrawParams _drawParams;

	bool _isCreated = false; 
	bool _isDestroyed = true;
	bool _isVisible = true;
	bool _isAlphaModulationEnabled = false;
};


#endif // !WIDGET_H

