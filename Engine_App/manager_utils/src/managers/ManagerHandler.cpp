//Coresponding header
#include "manager_utils/managers/ManagerHandler.h"

//C system includes

//C++ system includes
#include <iostream>

//Thitrd-party includes

//Own includes
#include "manager_utils/config/ManagerHandlerCfg.h"
#include "manager_utils/managers/DrawMgr.h"
#include "manager_utils/managers/RsrcMgr.h"


int32_t ManagerHandler::init(const ManagerHandlerCfg& cfg)
{
	gDrawMgr = new DrawMgr();
	if (gDrawMgr == nullptr)
	{
		std::cerr << "ERROR -> gDrawMgr failed with bad alloc." << std::endl;
		return EXIT_FAILURE;
	}

	if (EXIT_SUCCESS != gDrawMgr->init(cfg.drawMgrCfg))
	{
		std::cerr << "gDrawMgr->init() failed." << std::endl;
		return EXIT_FAILURE;
	}

	gRsrcMgr = new RsrcMgr();
	if (gRsrcMgr == nullptr)
	{
		std::cerr << "ERROR -> gRsrcMgr failed with bad alloc." << std::endl;
		return EXIT_FAILURE;
	}

	if (EXIT_SUCCESS != gRsrcMgr->init(cfg.rsrcMgrCfg))
	{
		std::cerr << "gRsrcMgr->init() failed." << std::endl;
		return EXIT_FAILURE;
	}

	this->_managers[DRAW_MGR_IDX] = static_cast<MgrBase*>(gDrawMgr);
	this->_managers[RSRC_MGR_IDX] = static_cast<MgrBase*>(gRsrcMgr);

	return EXIT_SUCCESS;
}

void ManagerHandler::deInit()
{
	for (int32_t i = MANAGERS_COUNT - 1; i >= 0; --i)
	{
		this->_managers[i]->deInit();
		this->_managers[i] = nullptr;

		nullifyGlobalMgr(i);
	}
}

void ManagerHandler::process()
{
	for (int32_t i = 0; i < MANAGERS_COUNT; ++i)
	{
		this->_managers[i]->process();
	}
}

void ManagerHandler::nullifyGlobalMgr(int32_t mgrIdx)
{
	switch (mgrIdx)
	{
	case DRAW_MGR_IDX:
		delete gDrawMgr;
		gDrawMgr = nullptr;
		break;

	case RSRC_MGR_IDX:
		delete gRsrcMgr;
		gRsrcMgr = nullptr;
		break;

	default:
		std::cerr << "Received invalid mgrIdx: " << mgrIdx << std::endl;
		break;
	}
}