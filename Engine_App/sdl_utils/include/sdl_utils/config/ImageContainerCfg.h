#ifndef IMAGE_CONTAINER_CFG_H
#define IMAGE_CONTAINER_CFG_H

//C system includes

//C++ system includes
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

//Thitrd-party includes

//Own includes
#include "utils/drawing/Rectangle.h"

//Forward Declarations


struct ImageCfg
{
	std::string location;
	std::vector<Rectangle> frames;
};


struct ImageContainerCfg
{
	std::unordered_map<int32_t, ImageCfg> imageConfigs;
};


#endif // !IMAGE_CONTAINER_CFG_H

