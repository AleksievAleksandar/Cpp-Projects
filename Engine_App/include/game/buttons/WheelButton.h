#ifndef WHEEL_BUTTON_H
#define WHEEL_BUTTON_H

//C system includes

//C++ system includes
#include <cstdint>

//Thitrd-party includes

//Own includes
#include "manager_utils/input/ButtonBase.h"

//Forward Declarations
struct GameProxy;

class WheelButton : public ButtonBase 
{
public:
	int32_t init(GameProxy* gameProxy, int32_t buttonId);
	void handleEvent(const InputEvent& e) override;

private:
	GameProxy* _gameProxy = nullptr;
	int32_t _buttonId{ 0 };
};

#endif // !WHEEL_BUTTON_H

