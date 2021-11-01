#ifndef DRAW_PARAMS_H
#define DRAW_PARAMS_H

//C system includes

//C++ system includes
#include <cstdint>

//Thitrd-party includes

//Own includes
#include "utils/drawing/Point.h"

//Forward Declarations


inline constexpr auto FULL_OPACITY = 255;
inline constexpr auto ZERO_OPACITY = 0;
inline constexpr auto INVALID_RSRC_ID = -1;

enum class BlendMode : uint8_t {
	NONE  = 0, //value for SDL_BLENDMODE_NONE
	BLEND = 1, //value for SDL_BLENDMODE_BLEND
	ADD   = 2, //value for SDL_BLENDMODE_ADD
	MOD   = 4  //value for SDL_BLENDMODE_MODE
};

enum class WidgetType : uint8_t 
{
	IMAGE,
	TEXT,
	UNKNOWN
};

struct DrawParams 
{
	void reset();
	//Top left position of texture
	Point pos = Point::UNDEFINED;

	//Draw dimensions of the texture
	int32_t width = 0;
	int32_t height = 0;

	int32_t opacity = FULL_OPACITY;

	//unique resourceId
	union 
	{
		int32_t rsrcId = INVALID_RSRC_ID;
		int32_t textId;
	};
	
	WidgetType widgetType = WidgetType::UNKNOWN;
};


#endif // !DRAW_PARAMS_H

