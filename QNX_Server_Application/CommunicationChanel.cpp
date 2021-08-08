#include "CommunicationChanel.h"

CommunicationChanel::CommunicationChanel() :
	communicationChannelFree(true),
	currentOperation(OPERATION::UNKNOWN),
	operandOne(nullptr),
	operandTwo(nullptr)
{}

bool CommunicationChanel::channelIsFreeForTransfer()
{
	return this->communicationChannelFree;
}

void CommunicationChanel::changeChannelStatus()
{
	this->communicationChannelFree = !this->communicationChannelFree;
}

void CommunicationChanel::transferData(OPERATION& operation, char*& operandOne, char*& operandTwo)
{
	this->currentOperation = operation;
	this->operandOne = operandOne;
	this->operandTwo = operandTwo;
}
