#ifndef RSRC_MGR_H
#define RSRC_MGR_H

//C system includes

//C++ system includes
#include <cstdint>

//Thitrd-party includes

//Own includes
#include "manager_utils/managers/MgrBase.h"
#include "sdl_utils/containers/ImageContainer.h"
#include "sdl_utils/containers/TextContainer.h"

//Forward Declarations
struct RsrcMgrCfg;

class RsrcMgr : public MgrBase,
				public ImageContainer,
				public TextContainer
{
public:
	RsrcMgr() = default;
	//forbid the copy and move constructors
	RsrcMgr(const RsrcMgr& other) = delete;
	RsrcMgr(RsrcMgr&& other) = delete;

	//forbid the copy and move assignment operators
	RsrcMgr& operator=(const RsrcMgr& other) = delete;
	RsrcMgr& operator=(RsrcMgr&& other) = delete;

	int32_t init(const RsrcMgrCfg& cfg);
	void deInit() override;
	void process() override;
};

extern RsrcMgr* gRsrcMgr;

#endif // !RSRC_MGR_H
