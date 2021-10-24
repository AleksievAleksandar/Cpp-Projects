//Coresponding header
#include "EngineConfigLoader.h"

//C system includes

//C++ system includes
#include <array>
#include <string>

//Thitrd-party includes

//Own includes
#include "common/CommonDefines.h"

namespace
{
	constexpr auto WINDOW_WIDTH = 640;
	constexpr auto WINDOW_HEIGHT = 480;
	constexpr auto WINDOW_NAME = "App_Engine";

	constexpr auto PRESS_KEYS_WIDTH = 640;
	constexpr auto PRESS_KEYS_HEIGHT = 480;

	constexpr auto LAYER_2_IMG_WIDTH = 150;
	constexpr auto LAYER_2_IMG_HEIGHT = 150;
}

static std::string getFilePath(const std::string& relativePath)
{
#ifdef RELEASE_BUILD
	return relativePath;
#else
	return "../" + relativePath;
#endif
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
	outCfg.layer2RsrcId = TextureId::LAYER_2;
	outCfg.pressKeysRsrcId = TextureId::PRESS_KEYS;
}

static void populateImageContainerConfig(ImageContainerCfg& outCfg)
{
	ImageCfg imageCfg;
	imageCfg.location = getFilePath("resources/press_keys.png");
	imageCfg.width = PRESS_KEYS_WIDTH;
	imageCfg.height = PRESS_KEYS_HEIGHT;
	outCfg.imageConfigs.insert(std::make_pair(TextureId::PRESS_KEYS, imageCfg));

	imageCfg.location = getFilePath("resources/layer_2.png");
	imageCfg.width = LAYER_2_IMG_WIDTH;
	imageCfg.height = LAYER_2_IMG_HEIGHT;
	outCfg.imageConfigs.insert(std::make_pair(TextureId::LAYER_2, imageCfg));
}

EngineConfig EngineConfigLoader::loadConfig()
{
	EngineConfig cfg;

	populateMonitorConfig(cfg.windowCfg);
	populateImageContainerConfig(cfg.imageContainerCfg);
	populateGameConfig(cfg.gameCfg);

	return cfg;
}
