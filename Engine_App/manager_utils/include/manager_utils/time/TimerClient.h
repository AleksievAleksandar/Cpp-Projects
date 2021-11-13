#ifndef TIMER_CLIENT_H
#define TIMER_CLIENT_H

//C system includes

//C++ system includes
#include <cstdint>

//Thitrd-party includes

//Own includes
#include "manager_utils/time/TimerData.h"

//Forward Declarations

class TimerClient
{
public:
	virtual ~TimerClient() = default;
	virtual void onTimeout(int32_t timerId) = 0;
	void startTimer(int64_t interval, int32_t timerId, TimerType timerType);
	void stopTimer(int32_t timerId);
	bool isActiveTimerId(int32_t timerId) const;

};

#endif // !TIMER_CLIENT_H

