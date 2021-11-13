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
	constexpr auto WINDOW_WIDTH = 1024;
	constexpr auto WINDOW_HEIGHT = 800;
	constexpr auto WINDOW_NAME = "App_Engine";

	constexpr auto RUNNING_GIRL_FRAMES = 6;
	constexpr auto RUNNING_GIRL_IMG_WIDTH = 256;
	constexpr auto RUNNING_GIRL_IMG_HEIGHT = 220;

	constexpr auto BUTTON_FRAMES = 3;
	constexpr auto BUTTON_IMG_WIDTH = 150;
	constexpr auto BUTTON_IMG_HEIGHT = 50;

	constexpr auto BLACK_BACKGROUND_IMG_WIDTH = 1024;
	constexpr auto BLACK_BACKGROUND_IMG_HEIGHT = 800;

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

	constexpr auto buttonsCnt = 2;
	const std::string buttonPaths[buttonsCnt] = { "resources/p/buttons/button_start.png" ,
												  "resources/p/buttons/button_stop.png" };
	constexpr int32_t buttonRsrcIds[buttonsCnt] = { TextureId::START_BUTTON,
													TextureId::STOP_BUTTON };
	for (int32_t i = 0; i < buttonsCnt; ++i)
	{
		imageCfg.location = getFilePath(buttonPaths[i]);
		for (auto frameId = 0; frameId < BUTTON_FRAMES; ++frameId)
		{
			imageCfg.frames.emplace_back(
				frameId * BUTTON_IMG_WIDTH, //x
				0,							//y
				BUTTON_IMG_WIDTH,		//w
				BUTTON_IMG_HEIGHT);	//h
		}
		outCfg.imageConfigs.emplace(buttonRsrcIds[i], imageCfg);
		imageCfg.frames.clear();
	}

	imageCfg.location = getFilePath("resources/p/wheel.png");
	imageCfg.frames.emplace_back(
		0,							//x
		0,							//y
		WHEEL_IMG_WIDTH_HEIGHT,		//w
		WHEEL_IMG_WIDTH_HEIGHT);	//h
	outCfg.imageConfigs.emplace(TextureId::WHEEL, imageCfg);
	imageCfg.frames.clear();

	imageCfg.location = getFilePath("resources/p/blackBackground.png");
	imageCfg.frames.emplace_back(
		0,							 //x
		0,							 //y
		BLACK_BACKGROUND_IMG_WIDTH,	 //w
		BLACK_BACKGROUND_IMG_HEIGHT);//h
	outCfg.imageConfigs.emplace(TextureId::BLACK_BACKROUND, imageCfg);
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
	outCfg.blackBgrRsrcId = TextureId::BLACK_BACKROUND;

	outCfg.startButtonRsrcId = TextureId::START_BUTTON;
	outCfg.stopButtonRsrcId = TextureId::STOP_BUTTON;

	outCfg.textFontId = FontId::ANGELINE_VINTAGE_40;

	outCfg.wheelRotAminTimerId = TimerId::WHEEL_ROT_ANIM_ID;
	outCfg.moveGirlTimerId = TimerId::MOVE_GIRL_TIMER_ID;
	outCfg.wheelScaleAnimTimerId = TimerId::SCALE_WHEEL_TIMER_ID;
}

EngineConfig EngineConfigLoader::loadConfig()
{
	EngineConfig cfg;

	populateManagerHandlerCfg(cfg.managerHandlerCfg);
	populateGameConfig(cfg.gameCfg);

	return cfg;
}
