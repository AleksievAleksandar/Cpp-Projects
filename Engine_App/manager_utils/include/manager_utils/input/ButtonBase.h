#ifndef BUTTON_BASE_H
#define BUTTON_BASE_H

//C system includes

//C++ system includes
#include <cstdint>

//Thitrd-party includes

//Own includes
#include "manager_utils/drawing/Image.h"

//Forward Declarations
class InputEvent;

enum ButtonStates 
{
	UNCLICKED, 
	CLICKED, 
	DISABLED
};

class ButtonBase : public Image
{
public:
	virtual ~ButtonBase() = default;

	virtual void handleEvent(const InputEvent& e) = 0;

	virtual void draw();

	void lockInput();
	void unlockInput();

	bool isInputUnlocked() const;

	bool containsEvent(const InputEvent& e);

private:
	bool _isInputUnlocked = true;
};


#endif // !BUTTON_BASE_H

