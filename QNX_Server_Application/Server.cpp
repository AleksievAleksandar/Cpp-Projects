#include "Server.h"
#include <string.h>
#include <string.h>

const int Server::MEMORY_SIZE = 256;

Server::Server(CommunicationChanel& communicationChanel) :
	memory(new char[MEMORY_SIZE]),
	requestNumber(0),
	communicationChanel(communicationChanel)
{}

Server::~Server()
{
	delete[] this->memory;
}

void Server::performTaskFrom(IClient* clientName)
{
	clientName->idRequestToServer = this->requestNumber;
	char temp[20];
	size_t start = 0;
	size_t secondWordStartInd = 0;
	size_t end = strlen(communicationChanel.operandOne) + strlen(communicationChanel.operandTwo);

	switch (communicationChanel.currentOperation)
	{
	case OPERATION::ADD:
		this->memory[this->requestNumber] = (*communicationChanel.operandOne) + (*communicationChanel.operandTwo);
		break;

	case OPERATION::SUBSTRACT:
		this->memory[this->requestNumber] = (*communicationChanel.operandOne) + (*communicationChanel.operandTwo);
		break;

	case OPERATION::MULTIPLY:
		this->memory[this->requestNumber] = (*communicationChanel.operandOne) * (*communicationChanel.operandTwo);
		break;

	case OPERATION::DIVIDE:
		this->memory[this->requestNumber] = (*communicationChanel.operandOne) / (*communicationChanel.operandTwo);
		break;

	case OPERATION::CONCATENATE:

		while (start < strlen(communicationChanel.operandOne))
		{
			temp[start] = communicationChanel.operandOne[start];
			start++;
		}

		//start = strlen(communicationChanel.operandOne);
		while (start < end)
		{
			temp[start] = communicationChanel.operandTwo[secondWordStartInd];
			start++;
			secondWordStartInd++;
		}

		this->memory[this->requestNumber] = *temp;
		break;

	case OPERATION::SEARCH_SUBSTR:
		break;

	default:
		break;
	}
	this->requestNumber++;
}

void Server::sendAnswerTo(IClient* clientName)
{
	if (this->communicationChanel.channelIsFreeForTransfer())
	{
		this->communicationChanel.changeChannelStatus();

		clientName->result = this->memory[clientName->idRequestToServer];

		this->communicationChanel.changeChannelStatus();
	}
	
}