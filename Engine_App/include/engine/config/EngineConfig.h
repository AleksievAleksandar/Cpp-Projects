#ifndef ENGINE_CONFIG_H
#define ENGINE_CONFIG_H

//C system includes

//C++ system includes
#include <cstdint>

//Thitrd-party includes

//Own includes
#include "manager_utils/config/ManagerHandlerCfg.h"
#include "game/config/GameCfg.h"

//Forward Declarations


struct EngineConfig
{
	ManagerHandlerCfg managerHandlerCfg;
	GameCfg gameCfg;
};

#endif // !ENGINE_CONFIG_H
