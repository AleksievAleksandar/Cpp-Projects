#ifndef ENGINE_CONFIG_H
#define ENGINE_CONFIG_H

//C system includes

//C++ system includes
#include <cstdint>

//Thitrd-party includes

//Own includes
#include "manager_utils/config/DrawMgrCfg.h"
#include "sdl_utils/config/ImageContainerCfg.h"
#include "sdl_utils/config/TextContainerCfg.h"
#include "game/config/GameCfg.h"

//Forward Declarations


struct EngineConfig
{
	DrawMgrCfg drawMgrCfg;
	ImageContainerCfg imageContainerCfg;
	TextContainerCfg textContainerCfg;
	GameCfg gameCfg;
};

#endif // !ENGINE_CONFIG_H
