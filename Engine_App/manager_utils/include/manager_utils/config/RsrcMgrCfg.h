#ifndef RSRC_MGR_CFG_H
#define RSRC_MGR_CFG_H

//C system includes

//C++ system includes
#include <cstdint>

//Thitrd-party includes

//Own includes
#include "sdl_utils/config/ImageContainerCfg.h"
#include "sdl_utils/config/TextContainerCfg.h"

//Forward Declarations


struct RsrcMgrCfg
{
	ImageContainerCfg imageContainerCfg;
	TextContainerCfg textContainerCfg;
};

#endif // !RSRC_MGR_CFG_H

