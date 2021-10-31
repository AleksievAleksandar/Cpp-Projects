#ifndef MANAGER_HANDLER_CFG_H
#define MANAGER_HANDLER_CFG_H

//C system includes

//C++ system includes
#include <cstdint>

//Thitrd-party includes

//Own includes
#include "manager_utils/config/DrawMgrCfg.h"
#include "manager_utils/config/RsrcMgrCfg.h"

//Forward Declarations


struct ManagerHandlerCfg
{
	DrawMgrCfg drawMgrCfg;
	RsrcMgrCfg rsrcMgrCfg;
};

#endif // !MANAGER_HANDLER_CFG_H
