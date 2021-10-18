#ifndef ENGINE_CONFIG_H
#define ENGINE_CONFIG_H

//C system includes

//C++ system includes
#include <cstdint>

//Thitrd-party includes

//Own includes
#include "sdl_utils/config/MonitorWindowCfg.h"
#include "game/config/GameCfg.h"

//Forward Declarations


struct EngineConfig
{
	MonitorWindowCfg windowCfg;
	GameCfg gameCfg;
};

#endif // !ENGINE_CONFIG_H
