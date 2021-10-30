#ifndef TEXT_CONTAINER_CFG_H
#define TEXT_CONTAINER_CFG_H

//C system includes

//C++ system includes
#include <cstdint>
#include <string>
#include <unordered_map>

//Thitrd-party includes

//Own includes

//Forward Declarations


struct FontCfg
{
	std::string location;
	int32_t fontSize = 0;
};

struct TextContainerCfg
{
	std::unordered_map<int32_t, FontCfg> fontConfigs;
};

#endif // !TEXT_CONTAINER_CFG_H

