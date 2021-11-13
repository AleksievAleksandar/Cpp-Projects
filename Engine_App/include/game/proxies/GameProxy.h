#ifndef GAME_PROXY_H
#define GAME_PROXY_H

//C system includes

//C++ system includes
#include <cstdint>

//Thitrd-party includes

//Own includes

//Forward Declarations

class GameProxy 
{
public:
	virtual ~GameProxy() = default;
	virtual void onButtonPressed(int32_t buttonId) = 0;
};


#endif // !GAME_PROXY_H

