//Coresponding header
#include "EngineConfigLoader.h"

//C system includes

//C++ system includes
#include <array>

//Thitrd-party includes

//Own includes


namespace
{
	constexpr auto WINDOW_WIDTH = 640;
	constexpr auto WINDOW_HEIGHT = 480;
	constexpr auto WINDOW_NAME = "App_Engine";
}

static void populateMonitorConfig(MonitorWindowCfg& outCfg)
{
	outCfg.windowName = WINDOW_NAME;
	outCfg.windowWidth = WINDOW_WIDTH;
	outCfg.windowHeight = WINDOW_HEIGHT;
	outCfg.windowFlags = WINDOW_SHOWN;
}

static void populateGameConfig(GameCfg& outCfg)
{
	outCfg.imgPaths[UP] = "../resources/up.png";
	outCfg.imgPaths[DOWN] = "../resources/down.png";
	outCfg.imgPaths[LEFT] = "../resources/left.png";
	outCfg.imgPaths[RIGHT] = "../resources/right.png";
	outCfg.imgPaths[PRESS_KEYS] = "../resources/press_keys.png";
	outCfg.imgPaths[LAYER_2] = "../resources/layer_2.png";
}

EngineConfig EngineConfigLoader::loadConfig()
{
	EngineConfig cfg;

	populateMonitorConfig(cfg.windowCfg);
	populateGameConfig(cfg.gameCfg);

	return cfg;
}
