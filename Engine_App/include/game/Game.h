#ifndef GAME_H
#define GAME_H

//C system includes

//C++ system includes
#include <cstdint>

//Thitrd-party includes

//Own includes
#include "manager_utils/drawing/Image.h"
#include "game/proxies/GameProxy.h"
#include "game/config/GameCfg.h"
#include "game/entities/Hero.h"
#include "game/entities/Wheel.h"
#include "game/buttons/WheelButton.h"

//Forward Declarations
struct InputEvent;

class Game : public GameProxy
{
public:
	int32_t init(const GameCfg& cfg);
	void deInit();
	void draw();
	void handleEvent(const InputEvent& event);
	void process();

private:
	void onButtonPressed(int32_t buttonId) override;

	enum Internals
	{
		WHEEL_START_BTN_IDX,
		WHEEL_STOP_BTN_IDX,

		WHEEL_BTNS_CNT
	};

	Hero _hero;
	Wheel _wheel;
	Image _blackBgrImg;
	WheelButton _wheelBtns[WHEEL_BTNS_CNT];
};

#endif // !GAME_H
