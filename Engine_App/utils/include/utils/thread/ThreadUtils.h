#ifndef THREAD_UTILS_H
#define THREAD_UTILS_H

//C system includes

//C++ system includes
#include <cstdint>

//Thitrd-party includes

//Own includes

//Forward Declarations


class Threading
{
public:
	Threading() = delete;

	static void sleepFor(const int64_t microseconds);
};

#endif // !THREAD_UTILS_H

