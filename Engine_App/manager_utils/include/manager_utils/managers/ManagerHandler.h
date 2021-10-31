#ifndef MANAGER_HANDLER_H
#define MANAGER_HANDLER_H

//C system includes

//C++ system includes
#include <cstdint>

//Thitrd-party includes

//Own includes
#include "manager_utils/managers/MgrBase.h"

//Forward Declarations
struct ManagerHandlerCfg;

class ManagerHandler
{
public:
	int32_t init(const ManagerHandlerCfg& cfg);
	void deInit();
	void process();

private:
	static void nullifyGlobalMgr(int32_t mgrIdx);

	MgrBase* _managers[MANAGERS_COUNT];
};

#endif // !MANAGER_HANDLER_H
