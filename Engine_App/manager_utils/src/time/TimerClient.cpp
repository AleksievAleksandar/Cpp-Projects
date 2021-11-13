//Coresponding header
#include "manager_utils/time/TimerClient.h"

//C system includes

//C++ system includes
#include <iostream>

//Thitrd-party includes

//Own includes
#include "manager_utils/managers/TimerMgr.h"

void TimerClient::startTimer(int64_t interval, int32_t timerId, TimerType timerType)
{
	constexpr auto minTimerInterval = 20; //ms
	if (interval < minTimerInterval)
	{
		std::cerr << "Timer with ID: " << timerId << " requested interval: " << interval 
				  << " which is lower than tme minimum one: " << minTimerInterval << std::endl;
		return;
	}

	const TimerData data(interval, interval, this, timerType);
	gTimerMgr->startTimer(timerId, data);
}

void TimerClient::stopTimer(int32_t timerId)
{
	gTimerMgr->stopTimer(timerId);
}

bool TimerClient::isActiveTimerId(int32_t timerId) const
{
	return gTimerMgr->isActiveTimerId(timerId);
}