#ifndef CAME_CONFIG_H
#define CAME_CONFIG_H

//C system includes

//C++ system includes
#include <cstdint>
#include <unordered_map>
#include <string>

//Thitrd-party includes

//Own includes

//Forward Declarations


enum GameImages
{
	UP, DOWN, LEFT, RIGHT, PRESS_KEYS, LAYER_2, COUNT
};

struct GameCfg
{
	std::unordered_map<GameImages, std::string> imgPaths;
};

#endif // !CAME_CONFIG_H
