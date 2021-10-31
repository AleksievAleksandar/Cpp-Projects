#ifndef IMAGE_CONTAINER_CFG_H
#define IMAGE_CONTAINER_CFG_H

//C system includes

//C++ system includes
#include <cstdint>
#include <string>
#include <unordered_map>

//Thitrd-party includes

//Own includes

//Forward Declarations


struct ImageCfg 
{
	std::string location;
	int32_t width = 0;
	int32_t height = 0;
};

struct ImageContainerCfg
{
	std::unordered_map<int32_t, ImageCfg> imageConfigs;
};


#endif // !IMAGE_CONTAINER_CFG_H

