#ifndef DRAW_MGR_CFG_H
#define DRAW_MGR_CFG_H

//C system includes

//C++ system includes
#include <cstdint>

//Thitrd-party includes

//Own includes
#include "sdl_utils/config/MonitorWindowCfg.h"

//Forward Declarations


struct DrawMgrCfg
{
	MonitorWindowCfg windowCfg;
	int64_t maxFrameRate;
};

#endif // !DRAW_MGR_CFG_H
