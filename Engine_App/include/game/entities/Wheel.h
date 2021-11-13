#ifndef WHEEL_H
#define WHEEL_H

//C system includes

//C++ system includes
#include <cstdint>

//Thitrd-party includes

//Own includes
#include "manager_utils/drawing/Image.h"
#include "manager_utils/time/TimerClient.h"

//Forward Declarations
struct InputEvent;


class Wheel : public TimerClient
{
public:
	~Wheel();
	int32_t init(const int32_t wheelRsrcId, int32_t rotAnimTimerId, int32_t scaleAnimTimerId);
	void draw();
	void handleEvent(const InputEvent& event);

	void startAnim();
	void stopAnim();

private:
	void processRotAnim();
	void processScaleAnim();
	void onTimeout(int32_t timerId) override;

	bool _isAnimActiv = false;
	Image _wheelImg;
	int32_t _rotAnimTimerId = -1;
	int32_t _scaleAnimTimerId = -1;
	int32_t _scaleSteps = 50;
	bool _isShrinking = true;
};

#endif // !WHEEL_H

