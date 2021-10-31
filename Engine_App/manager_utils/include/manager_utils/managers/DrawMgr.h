#ifndef DRAW_MGR_H
#define DRAW_MGR_H

//C system includes

//C++ system includes
#include <cstdint>

//Thitrd-party includes

//Own includes
#include "manager_utils/managers/MgrBase.h"
#include "sdl_utils/MonitorWindow.h"
#include "sdl_utils/Renderer.h"

//Forward Declarations
struct DrawMgrCfg;

class DrawMgr : public MgrBase
{
public:
	DrawMgr() = default;

	//forbid the copy and move constructors
	DrawMgr(const DrawMgr& other) = delete;
	DrawMgr(DrawMgr&& other) = delete;

	//forbid the copy and move assignment operators
	DrawMgr& operator=(const DrawMgr& other) = delete;
	DrawMgr& operator=(DrawMgr&& other) = delete;

	int32_t init(const DrawMgrCfg& cfg);
	void deInit() override;
	void process() override;
	void clearScreen();
	void finishFrame();
	void addDrawCmd(const DrawParams& drawParams);
	void setWidgetBlendMode(const DrawParams& drawParams, BlendMode blendMode);
	void setWidgetOpacity(const DrawParams& drawParams, int32_t opacity);


private:
	SDL_Texture* getTextureInternal(const DrawParams& drawParams) const;

	Renderer _renderer;
	MonitorWindow _window;

	//Hold maximum frame rate cap
	int64_t _maxFrames{ 0 };
};

extern DrawMgr* gDrawMgr;


#endif // !DRAW_MGR_H
