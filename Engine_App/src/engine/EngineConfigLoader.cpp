//Coresponding header
#include "engine/EngineConfigLoader.h"

//C system includes

//C++ system includes
#include <array>
#include <string>

//Thitrd-party includes

//Own includes
#include "common/CommonDefines.h"
#include "sdl_utils/containers/ImageContainer.h"

namespace
{
	constexpr auto WINDOW_WIDTH = 800;
	constexpr auto WINDOW_HEIGHT = 600;
	constexpr auto WINDOW_NAME = "App_Engine";

	constexpr auto RUNNING_GIRL_FRAMES = 6;
	constexpr auto RUNNING_GIRL_IMG_WIDTH = 256;
	constexpr auto RUNNING_GIRL_IMG_HEIGHT = 220;

	constexpr auto WHEEL_IMG_WIDTH_HEIGHT = 695;

	constexpr auto ANGELINE_VINTAGE_40_FONT_SIZE = 80;
	constexpr auto MAX_FRAMERATE = 30;
}

static std::string getFilePath(const std::string& relativePath)
{
#ifdef RELEASE_BUILD
	return relativePath;
#else
	return "../" + relativePath;
#endif
}

static void populateTextContainerConfig(TextContainerCfg& outCfg)
{
	FontCfg fontCfg;
	fontCfg.location = getFilePath("resources/f/AngelineVintage.ttf");
	fontCfg.fontSize = ANGELINE_VINTAGE_40_FONT_SIZE;
	outCfg.fontConfigs.insert(std::make_pair(FontId::ANGELINE_VINTAGE_40, fontCfg));
}

static void populateImageContainerConfig(ImageContainerCfg& outCfg)
{
	ImageCfg imageCfg;
	imageCfg.location = getFilePath("resources/p/sprites/running_girl_small.png");
	for (auto i = 0; i < RUNNING_GIRL_FRAMES; ++i)
	{
		imageCfg.frames.emplace_back(
									i * RUNNING_GIRL_IMG_WIDTH, //x
									0,							//y
									RUNNING_GIRL_IMG_WIDTH,		//w
									RUNNING_GIRL_IMG_HEIGHT);	//h
	}
	outCfg.imageConfigs.emplace(TextureId::RUNNING_GIRL, imageCfg);
	imageCfg.frames.clear();

	imageCfg.location = getFilePath("resources/p/wheel.png");
	imageCfg.frames.emplace_back(
		0,							//x
		0,							//y
		WHEEL_IMG_WIDTH_HEIGHT,		//w
		WHEEL_IMG_WIDTH_HEIGHT);	//h
	outCfg.imageConfigs.emplace(TextureId::WHEEL, imageCfg);
	imageCfg.frames.clear();
}

static void populateMonitorConfig(MonitorWindowCfg& outCfg)
{
	outCfg.windowName = WINDOW_NAME;
	outCfg.windowWidth = WINDOW_WIDTH;
	outCfg.windowHeight = WINDOW_HEIGHT;
	outCfg.windowFlags = WINDOW_SHOWN;
}

static void populateRsrcMgrConfig(RsrcMgrCfg& outCfg)
{
	populateImageContainerConfig(outCfg.imageContainerCfg);
	populateTextContainerConfig(outCfg.textContainerCfg);
}

static void populateDrawMgrConfig(DrawMgrCfg& outCfg)
{
	populateMonitorConfig(outCfg.windowCfg);
	outCfg.maxFrameRate = MAX_FRAMERATE;
}

static void populateManagerHandlerCfg(ManagerHandlerCfg& outCfg)
{
	populateDrawMgrConfig(outCfg.drawMgrCfg);
	populateRsrcMgrConfig(outCfg.rsrcMgrCfg);
}

static void populateGameConfig(GameCfg& outCfg)
{
	outCfg.runningGirlRsrcId = TextureId::RUNNING_GIRL;
	outCfg.wheelRsrcId = TextureId::WHEEL;

	outCfg.textFontId = FontId::ANGELINE_VINTAGE_40;
}

EngineConfig EngineConfigLoader::loadConfig()
{
	EngineConfig cfg;

	populateManagerHandlerCfg(cfg.managerHandlerCfg);
	populateGameConfig(cfg.gameCfg);

	return cfg;
}
