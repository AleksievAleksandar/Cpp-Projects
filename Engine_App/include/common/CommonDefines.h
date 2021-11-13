#ifndef COMMON_DEFINES_H
#define COMMON_DEFINES_H

//C system includes

//C++ system includes
#include <cstdint>

//Thitrd-party includes

//Own includes

//Forward Declarations


namespace TextureId
{
	enum ResourceId
	{ 
		RUNNING_GIRL, 
		WHEEL,
		BLACK_BACKROUND,
		START_BUTTON,
		STOP_BUTTON
	};
} //namespace TextureId

namespace FontId
{
	enum FontIdKeys
	{
		ANGELINE_VINTAGE_40
	};
} //namespace FontId

namespace TimerId
{
	enum Keys
	{
		WHEEL_ROT_ANIM_ID,
		SCALE_WHEEL_TIMER_ID,
		MOVE_GIRL_TIMER_ID
	};
} //namespace TimerId


#endif // !COMMON_DEFINES_H
