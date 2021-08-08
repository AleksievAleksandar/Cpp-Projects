#ifndef ICLIENT_H
#define ICLIENT_H

#include "CommunicationChanel.h"

/*======================== ClientBase =========================================*/
class IClient
{
protected:
	CommunicationChanel& communicationChanel;
public:
	OPERATION currentOperation;
	char* operandOne;
	char* operandTwo;
	char result;
	int idRequestToServer;
public:
	IClient(CommunicationChanel& communicationChanel);
	virtual ~IClient();
public:
	virtual void sendRequest();
	virtual void receivingRequest();
};

#endif // !ICLIENT_H
