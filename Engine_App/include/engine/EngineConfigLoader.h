#ifndef ENGINE_CONFIG_LOADER_H
#define ENGINE_CONFIG_LOADER_H

//C system includes

//C++ system includes
#include <cstdint>

//Thitrd-party includes

//Own includes
#include "engine/config/EngineConfig.h"

//Forward Declarations

class EngineConfigLoader
{
public:
	EngineConfigLoader() = delete;

	static EngineConfig loadConfig();
};

#endif // !ENGINE_CONFIG_LOADER_H

