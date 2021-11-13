#ifndef TIMER_DATA_H
#define TIMER_DATA_H

//C system includes

//C++ system includes
#include <cstdint>

//Thitrd-party includes

//Own includes
#include "manager_utils/drawing/Image.h"

//Forward Declarations
struct TimerClient;

enum class TimerType : uint8_t
{
	ONESHOT,
	PULSE
};

struct TimerData
{
	TimerData(int64_t inputInterval, int64_t inputRemaining, TimerClient* inputTcInstance, TimerType inputTimerType):
		interval(inputInterval), remaining(inputRemaining), tcInstance(inputTcInstance), timerType(inputTimerType) {}

	int64_t interval;
	int64_t remaining;
	TimerClient* tcInstance = nullptr;
	TimerType timerType;
};

#endif // !TIMER_DATA_H

