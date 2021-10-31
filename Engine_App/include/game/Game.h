#ifndef GAME_H
#define GAME_H

//C system includes

//C++ system includes
#include <cstdint>

//Thitrd-party includes

//Own includes
#include "game/config/GameCfg.h"
#include "utils/drawing/DrawParams.h"

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
	DrawParams pressKeysImg;
	DrawParams layer2Img;

	DrawParams helloText;
	DrawParams pressText;
	DrawParams hideText;

	bool isPressTextHidden = false;
};

#endif // !GAME_H
