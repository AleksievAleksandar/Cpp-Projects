#include <iostream>

#include "CommunicationChanel.h"
#include "Client.h"
#include "Server.h"

int main()
{
	CommunicationChanel communicationChanel;

	ClientOne clientOne(communicationChanel);
	ClientTwo clientTwo(communicationChanel);

	Server server(communicationChanel);

	clientOne.operandOne = new char[1];
	clientOne.operandOne[0] = 45;
	clientOne.operandTwo = new char[1];
	clientOne.operandTwo[0] = 45;
	clientOne.currentOperation = ADD;
	clientOne.sendRequest();

	server.performTaskFrom(&clientOne);
	server.sendAnswerTo(&clientOne);

	std::cout << (int)clientOne.result << std::endl;;

	//clientTwo.operandOne = new char[10];
	//clientTwo.operandTwo = new char[10];

	char strOne[10] = "Hello";
	char strTwo[10] = "World";
	clientTwo.operandOne = new char[10];
	clientTwo.operandOne[0] = 'H';
	clientTwo.operandOne[1] = 'i';
	clientTwo.operandOne[2] = '\0';
	clientTwo.operandTwo = new char[10];
	clientTwo.operandTwo[0] = 'A';
	clientTwo.operandTwo[1] = 'l';
	clientTwo.operandTwo[2] = '\0';
	clientTwo.currentOperation = CONCATENATE;
	clientTwo.sendRequest();

	server.performTaskFrom(&clientTwo);
	server.sendAnswerTo(&clientTwo);

	std::cout << clientTwo.result << std::endl;

	return 0;
}
