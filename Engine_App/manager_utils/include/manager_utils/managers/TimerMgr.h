#ifndef TIMER_MGR_H
#define TIMER_MGR_H

//C system includes

//C++ system includes
#include <cstdint>
#include <map>
#include <set>

//Thitrd-party includes

//Own includes
#include "manager_utils/managers/MgrBase.h"
#include "manager_utils/time/TimerData.h"
#include "utils/time/Time.h"

//Forward Declarations

class TimerMgr : public MgrBase 
{
public:
	void process() override;
	int32_t init();
	void deInit() override;
	void startTimer(int32_t timerId, const TimerData& data);
	void stopTimer(int32_t timerId);
	//void detachTimerClient(int32_t timerId);
	bool isActiveTimerId(int32_t timerId) const;
	void onInitEnd();

private:
	void removeTimersInternal();
	void onTimerTimeout(int32_t timerId, TimerData& timer);

	Time _elapsedTime;
	std::map<int32_t, TimerData> _timerMap;
	std::set<int32_t> _removeTimerSet;
};

extern TimerMgr* gTimerMgr;

#endif // !TIMER_MGR_H

