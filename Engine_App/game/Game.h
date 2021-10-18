#ifndef GAME_H
#define GAME_H

//C system includes

//C++ system includes
#include <cstdint>
#include <vector>

//Thitrd-party includes

//Own includes
#include "config/GameCfg.h"

//Forward Declarations
struct SDL_Texture;
struct InputEvent;


class Game
{
public:
	int32_t init(const GameCfg& cfg);
	void deInit();
	void draw(std::vector<SDL_Texture*>& outImages);
	void handleEvent(const InputEvent& event);

private:
	int32_t loadResources(const std::unordered_map<GameImages, std::string>& resources);

	SDL_Texture* _currChosenImage = nullptr;
	SDL_Texture* _imageSurfaces[COUNT]{};
};

#endif // !GAME_H
