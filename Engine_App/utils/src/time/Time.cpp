//Coresponding header
#include "utils/time/Time.h"

//C system includes

//C++ system includes

//Thitrd-party includes

//Own includes

//Forward Declarations

Time& Time::getElapsed()
{
	this->_elapsedLastCall = _now;
	this->_now = std::chrono::steady_clock::now();

	return *this;
}

int64_t Time::toSeconds() const
{
	return std::chrono::duration_cast<std::chrono::seconds>(this->_now - this->_elapsedLastCall).count();
}

int64_t Time::toMilliseconds() const
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(this->_now - this->_elapsedLastCall).count();
}

int64_t Time::toMicroseconds() const
{
	return std::chrono::duration_cast<std::chrono::microseconds>(this->_now - this->_elapsedLastCall).count();
}

int64_t Time::toNanoseconds() const
{
	return std::chrono::duration_cast<std::chrono::nanoseconds>(this->_now - this->_elapsedLastCall).count();
}
