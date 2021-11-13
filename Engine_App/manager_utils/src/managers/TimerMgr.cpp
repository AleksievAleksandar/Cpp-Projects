//Coresponding header
#include "manager_utils/managers/TimerMgr.h"

//C system includes

//C++ system includes
#include <iostream>

//Thitrd-party includes

//Own includes
#include "manager_utils/time/TimerClient.h"

TimerMgr* gTimerMgr = nullptr;

void TimerMgr::process()
{
    const int64_t msElapsed = this->_elapsedTime.getElapsed().toMilliseconds();

    for (auto it = this->_timerMap.begin(); it != this->_timerMap.end(); ++it)
    {
        const int32_t timerId = it->first;
        TimerData& timerData = it->second;

        it->second.remaining -= msElapsed;
        if (0 > it->second.remaining) 
        {
            onTimerTimeout(timerId, timerData);
        }
    }
    removeTimersInternal();
}

int32_t TimerMgr::init()
{
    this->_elapsedTime.getElapsed();

    return EXIT_SUCCESS;
}

void TimerMgr::deInit()
{

}

void TimerMgr::startTimer(int32_t timerId, const TimerData& data)
{
    if (this->isActiveTimerId(timerId))
    {
        std::cerr << "ERROR -> trying to start an already existing timer with ID: " << timerId << std::endl;
        return;
    }
    this->_timerMap.emplace(timerId, data);
}

void TimerMgr::stopTimer(int32_t timerId)
{
    if (!this->isActiveTimerId(timerId))
    {
        std::cerr << "ERROR -> trying to stop an already stoped timer with ID: " << timerId << std::endl;
        return;
    }

    this->_removeTimerSet.insert(timerId);
}

bool TimerMgr::isActiveTimerId(int32_t timerId) const
{
    return (this->_removeTimerSet.end() == this->_removeTimerSet.find(timerId)) &&
           (this->_timerMap.end() != this->_timerMap.find(timerId));

}

void TimerMgr::onInitEnd()
{

}

void TimerMgr::removeTimersInternal() 
{
    for (const int32_t timerId : this->_removeTimerSet) 
    {
        auto mapIt = this->_timerMap.find(timerId);
        if (mapIt != this->_timerMap.end())
        {
            this->_timerMap.erase(mapIt);
        }
    }
    //clear the removeTimerSet
    this->_removeTimerSet.clear();
}

void TimerMgr::onTimerTimeout(int32_t timerId, TimerData& timer)
{
    if (TimerType::ONESHOT == timer.timerType)
    {
        this->_removeTimerSet.insert(timerId);
    }

    timer.tcInstance->onTimeout(timerId);
    timer.remaining += timer.interval;
}
