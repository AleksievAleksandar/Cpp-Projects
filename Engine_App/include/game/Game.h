#ifndef GAME_H
#define GAME_H

//C system includes

//C++ system includes
#include <cstdint>

//Thitrd-party includes

//Own includes
#include "game/config/GameCfg.h"
#include "entities/Hero.h"
#include "entities/Wheel.h"
#include "manager_utils/drawing/Image.h"
#include "manager_utils/drawing/Text.h"

//Forward Declarations
struct InputEvent;

class Game
{
public:
	int32_t init(const GameCfg& cfg);
	void deInit();
	void draw();
	void handleEvent(const InputEvent& event);

private:
	void setMousePosText(const Point& mousePos);
	Hero _hero;
	Wheel _wheel;
	Text _mousePosText;
};

#endif // !GAME_H
