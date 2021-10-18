//Coresponding header
#include "ThreadUtils.h"

//C system includes

//C++ system includes
#include <thread>

//Thitrd-party includes

//Own includes

//Forward Declarations


#ifdef _WIN32
#include <windows.h>
#else
#include <thread>
#endif

void Threading::sleepFor(const int64_t microseconds) 
{
	if (microseconds < 0)
	{
		return;
	}

#ifdef _WIN32
	const DWORD milliseconds = static_cast<DWORD>(microseconds / 1000);
	Sleep(milliseconds); //sleep uses milliseconds
#else
	std::this_thread::sleep_for(std::chrono::microseconds(microseconds));
#endif
}

