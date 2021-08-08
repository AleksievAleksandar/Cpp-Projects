#ifndef COMMUNICATION_CHANEL_H
#define COMMUNICATION_CHANEL_H

#include "OperationsDefines.h"

class CommunicationChanel
{
private:
	bool communicationChannelFree;
public:
	OPERATION currentOperation;
	char* operandOne;
	char* operandTwo;

public:
	CommunicationChanel();
public:
	bool channelIsFreeForTransfer();
	void changeChannelStatus();
	void transferData(OPERATION& operation, char*& operandOne, char*& operandTwo);
};

#endif // !COMMUNICATION_CHANEL_H
