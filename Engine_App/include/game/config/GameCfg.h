#ifndef CAME_CONFIG_H
#define CAME_CONFIG_H

//C system includes

//C++ system includes
#include <cstdint>
#include <unordered_map>
#include <string>

//Thitrd-party includes

//Own includes

//Forward Declarations


struct GameCfg
{
	int32_t runningGirlRsrcId;
	int32_t wheelRsrcId;
	int32_t blackBgrRsrcId;

	int32_t startButtonRsrcId;
	int32_t stopButtonRsrcId;

	int32_t textFontId;

	int32_t wheelRotAminTimerId;
	int32_t wheelScaleAnimTimerId;

	int32_t moveGirlTimerId;
};

#endif // !CAME_CONFIG_H
