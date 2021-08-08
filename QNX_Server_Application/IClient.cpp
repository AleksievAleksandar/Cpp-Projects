#include "IClient.h"
#include <iostream>

IClient::IClient(CommunicationChanel& communicationChanel) :
	communicationChanel(communicationChanel),
	currentOperation(OPERATION::UNKNOWN),
	operandOne(nullptr),
	operandTwo(nullptr),
	result(0),
	idRequestToServer(-1)
{}

IClient::~IClient()
{
	delete[] this->operandOne;
	this->operandOne = nullptr;

	delete[] this->operandTwo;
	this->operandTwo = nullptr;

	std::cout << "Dtor IClient" << std::endl;
}

void IClient::sendRequest()
{
	if (communicationChanel.channelIsFreeForTransfer())
	{
		communicationChanel.changeChannelStatus();

		communicationChanel.currentOperation = this->currentOperation;
		communicationChanel.operandOne = this->operandOne;
		communicationChanel.operandTwo = this->operandTwo;

		communicationChanel.changeChannelStatus();
	}
}

void IClient::receivingRequest()
{
	if (communicationChanel.channelIsFreeForTransfer())
	{
		this->communicationChanel.changeChannelStatus();
		this->communicationChanel.changeChannelStatus();
	}
}