#ifndef HERO_H
#define HERO_H

//C system includes

//C++ system includes
#include <cstdint>

//Thitrd-party includes

//Own includes
#include "manager_utils/drawing/Image.h"
#include "manager_utils/time/TimerClient.h"

//Forward Declarations
struct InputEvent;


class Hero : public TimerClient
{
public:
	int32_t init(const int32_t heroRsrcId, int32_t moveTimerId);
	void deInit();
	void draw();
	void handleEvent(const InputEvent& event);
	void startMoveAnim();

private:
	void processMoveAnim();
	void onTimeout(int32_t timerId) override;
	Image _heroImg;
	int32_t _moveTimerId = -1;
	int32_t _moveSteps = 50;
};

#endif // !HERO_H
