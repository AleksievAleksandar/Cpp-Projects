#ifndef GAME_H
#define GAME_H

//C system includes

//C++ system includes
#include <cstdint>
#include <vector>

//Thitrd-party includes

//Own includes
#include "game/config/GameCfg.h"
#include "utils/drawing/DrawParams.h"

//Forward Declarations
struct InputEvent;
struct ImageContainer;

class Game
{
public:
	int32_t init(const GameCfg& cfg, const ImageContainer* imgContainerInterface);
	void deInit();
	void draw(std::vector<DrawParams>& outImages);
	void handleEvent(const InputEvent& event);

private:
	DrawParams pressKeysImg;
	DrawParams layer2Img;

	//TODO remove me
	const ImageContainer* _imageContainer = nullptr;
};

#endif // !GAME_H
