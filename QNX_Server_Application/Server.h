#ifndef SERVER_H
#define SERVER_H

#include "CommunicationChanel.h"
#include "IClient.h"

class Server
{
public:
	static const int MEMORY_SIZE;
private:
	char* memory;
	int requestNumber;
	CommunicationChanel& communicationChanel;
public:
	Server(CommunicationChanel& communicationChanel);
	~Server();
public:
	void performTaskFrom(IClient* clientName);
	void sendAnswerTo(IClient* clientName);
};

#endif // !SERVER_H
