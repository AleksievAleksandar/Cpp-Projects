#ifndef CLIENT_H
#define CLIENT_H

#include "IClient.h"

/*======================== ClientOne =========================================*/
class ClientOne : public IClient
{
public:
	ClientOne(CommunicationChanel& communicationChanel);
	~ClientOne() = default;
};



/*======================== ClientTwo =========================================*/
class ClientTwo : public IClient
{
public:
	ClientTwo(CommunicationChanel& communicationChanel);
	~ClientTwo() = default;
};

#endif // !CLIENT_H
